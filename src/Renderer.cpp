#include "Renderer.h"
#include <cstdlib>
#include <iostream>
#include <vector>

Renderer::Renderer() {
    _setupDebug();
    _initInstance();
    _initDebug();
    _initDevice();
}

Renderer::~Renderer() {
    _destroyDevice();
    #ifdef ENABLE_DEBUG
    _destroyDebug();
    #endif
    _destroyInstance();
}

void Renderer::_initInstance() {
    VkApplicationInfo applicationInfo {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 3);
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.pApplicationName = "Vulkan Test Program";

    VkInstanceCreateInfo instanceCreateInfo {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.enabledLayerCount = _instanceLayers.size();
    instanceCreateInfo.ppEnabledLayerNames = _instanceLayers.data();
    instanceCreateInfo.enabledExtensionCount = _instanceExtensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = _instanceExtensions.data();

    auto err = vkCreateInstance(&instanceCreateInfo, nullptr, &_instance);
    if(err != VK_SUCCESS) {
        std::cout << "Vulkan ERROR: Create instance failed\n";
        std::exit(-1);
    } else {
        std::cout << "Vulkan SUCCESS: Created instance\n";
    }
}

void Renderer::_initDevice() {
    
    {
        uint32_t gpuCount = 0;
        vkEnumeratePhysicalDevices(_instance, &gpuCount, nullptr);
        std::vector<VkPhysicalDevice> gpuList(gpuCount);
        vkEnumeratePhysicalDevices(_instance, &gpuCount, gpuList.data());
        _gpu = gpuList[0];
    }
    {
        uint32_t familyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &familyCount, nullptr);
        std::vector<VkQueueFamilyProperties> familyProperties(familyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &familyCount, familyProperties.data());
        bool found = false;
        for(uint32_t i = 0; i < familyCount; i++) {
            if(familyProperties[i].queueCount > 0 && familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                _graphicsFamilyIndex = i;
                found = true;
            }
        }
        if(!found) {
            std::cout << "Vulkan ERROR: Queue family supporting graphics not found\n";
            std::exit(-1);
        }
    }
    {
        uint32_t layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> layerProperties(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());
        for(auto &i : layerProperties) {
            std::cout << "Vulkan INFO: Found instance layer " << i.layerName << "\t\t" << i.description << "\n";
        }
    }
    {
        uint32_t layerCount = 0;
        vkEnumerateDeviceLayerProperties(_gpu, &layerCount, nullptr);
        std::vector<VkLayerProperties> layerProperties(layerCount);
        vkEnumerateDeviceLayerProperties(_gpu, &layerCount, layerProperties.data());
        for(auto &i : layerProperties) {
            std::cout << "Vulkan INFO: Found device layer " << i.layerName << "\t\t" << i.description << "\n";
        }
    }

    float queuePriorities[] {1.0f};
    VkDeviceQueueCreateInfo deviceQueueCreateInfo {};
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.pQueuePriorities = queuePriorities;
    deviceQueueCreateInfo.queueFamilyIndex = _graphicsFamilyIndex;

    VkDeviceCreateInfo deviceCreateInfo {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount = _deviceLayers.size();
    deviceCreateInfo.ppEnabledLayerNames = _deviceLayers.data();

    auto err = vkCreateDevice(_gpu, &deviceCreateInfo, nullptr, &_device);
    if(err != VK_SUCCESS) {
        std::cout << "Vulkan ERROR: Unable to initialize device\n";
    } else {
        std::cout << "Vulkan SUCCESS: Created Device\n";
    }
}

void Renderer::_setupDebug() {
    #ifdef ENABLE_DEBUG
    _instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
    _deviceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
    _instanceExtensions.push_back("VK_EXT_debug_report");
    std::cout << "Vulkan INFO: debug build, enabling layers\n";
    #endif
}

PFN_vkCreateDebugReportCallbackEXT fvkCreateDebugReportCallbackEXT = nullptr;
PFN_vkDestroyDebugReportCallbackEXT fvkDestroyDebugReportCallbackEXT = nullptr;

VKAPI_ATTR VkBool32 VKAPI_CALL vulkanDebugCallback(
    VkDebugReportFlagsEXT msgFlags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t srcObject,
    size_t location,
    int32_t msgCode,
    const char *layerPrefix,
    const char *msg,
    void *userDate) {
        
    }

void Renderer::_initDebug() {
    #ifdef ENABLE_DEBUG
    fvkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(_instance, "vkCreateDebugReportCallbackEXT");
    fvkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(_instance, "vkDestroyDebugReportCallbackEXT");
    if(fvkCreateDebugReportCallbackEXT == nullptr || fvkDestroyDebugReportCallbackEXT == nullptr) {
        std::cout << "Vulkan ERROR: failed to initialize debug layers\n";
        std::exit(-1);
    }
    VkDebugReportCallbackCreateInfoEXT debugCallbackCreateInfo {};
    debugCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
    debugCallbackCreateInfo.pfnCallback = vulkanDebugCallback;
    debugCallbackCreateInfo.flags = 
        VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
        VK_DEBUG_REPORT_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_ERROR_BIT_EXT | 
        VK_DEBUG_REPORT_DEBUG_BIT_EXT;
    fvkCreateDebugReportCallbackEXT(_instance, &debugCallbackCreateInfo, nullptr, &_debugReport);
    #endif
}

void Renderer::_destroyDebug() {
    fvkDestroyDebugReportCallbackEXT(_instance, _debugReport, nullptr);
    _debugReport = nullptr;
}

void Renderer::_destroyDevice() {
    vkDestroyDevice(_device, nullptr);
    _device = nullptr;
    std::cout << "Vulkan SUCCESS: Destroyed device\n";
}

void Renderer::_destroyInstance() {
    vkDestroyInstance(_instance, nullptr);
    _instance = nullptr;
    std::cout << "Vulkan SUCCESS: Destroyed instance\n";
}

