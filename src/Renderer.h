#pragma once
#include <vulkan/vulkan.h>

class Renderer {
    
    public:
        Renderer();
        ~Renderer();
    
    private:
        void _initInstance();
        void _destroyInstance();
        void _initDevice();
        void _destroyDevice();

        VkInstance          _instance = nullptr;
        VkDevice            _device = nullptr;
        VkPhysicalDevice    _gpu = nullptr;
        uint32_t            _graphicsFamilyIndex = 0;

};