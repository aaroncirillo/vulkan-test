#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class Renderer {
    
    public:
        Renderer();
        ~Renderer();
        VkInstance getInstance();
        VkDevice getDevice();
        VkPhysicalDevice getPhysicalDevice();
        VkQueue getQueue();
        uint32_t getGraphicsFamilyIndex();
    
    private:
        void _initInstance();
        void _destroyInstance();
        void _initDevice();
        void _destroyDevice();
        void _setupDebug();
        void _initDebug();
        void _destroyDebug();

        VkInstance                  _instance               = VK_NULL_HANDLE;
        VkDevice                    _device                 = VK_NULL_HANDLE;
        VkPhysicalDevice            _gpu                    = VK_NULL_HANDLE;
        VkDebugReportCallbackEXT    _debugReport            = VK_NULL_HANDLE;
        VkQueue                     _queue                  = VK_NULL_HANDLE;
        
        uint32_t                    _graphicsFamilyIndex    = 0;
        
        std::vector<const char*>    _instanceLayers;
        std::vector<const char*>    _instanceExtensions;
        std::vector<const char*>    _deviceLayers;
        std::vector<const char*>    _deviceExtensions;

};