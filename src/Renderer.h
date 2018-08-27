#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class Renderer {
    
    public:
        Renderer();
        ~Renderer();
    
    private:
        void _initInstance();
        void _destroyInstance();
        void _initDevice();
        void _destroyDevice();
        void _setupDebug();
        void _initDebug();
        void _destroyDebug();

        VkInstance                  _instance               = nullptr;
        VkDevice                    _device                 = nullptr;
        VkPhysicalDevice            _gpu                    = nullptr;
        VkDebugReportCallbackEXT    _debugReport            = nullptr;
        
        uint32_t                    _graphicsFamilyIndex    = 0;
        
        std::vector<const char*>    _instanceLayers;
        std::vector<const char*>    _instanceExtensions;
        std::vector<const char*>    _deviceLayers;
        std::vector<const char*>    _deviceExtensions;

};