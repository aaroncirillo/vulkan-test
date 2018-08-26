#include "Renderer.h"
#include <cstdlib>
#include <iostream>
#include <vector>

Renderer::Renderer() {
    _initInstance();
    _initDevice();
}

Renderer::~Renderer() {
    _destroyDevice();
    _destroyInstance();
}

void Renderer::_initInstance() {
    VkApplicationInfo applicationInfo {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 2);
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.pApplicationName = "Vulkan Test Program";

    VkInstanceCreateInfo instanceCreateInfo {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

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

    auto err = vkCreateDevice(_gpu, &deviceCreateInfo, nullptr, &_device);
    if(err != VK_SUCCESS) {
        std::cout << "Vulkan ERROR: Unable to initialize device\n";
    } else {
        std::cout << "Vulkan SUCCESS: Created Device\n";
    }
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

