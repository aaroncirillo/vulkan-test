#include "ErrorUtils.h"

void errorCheck(VkResult result) {
    if(result < 0) {
        char *error;
        switch(result) {
            case VK_SUCCESS:
                error = (char *) "VK_SUCCESS";
                break;
            case VK_NOT_READY:
                error = (char *) "VK_NOT_READY";
                break;
            case VK_TIMEOUT:
                error = (char *) "VK_TIMEOUT";
                break;
            case VK_EVENT_SET:
                error = (char *) "VK_EVENT_SET";
                break;
            case VK_EVENT_RESET:
                error = (char *) "VK_EVENT_RESET";
                break;
            case VK_INCOMPLETE:
                error = (char *) "VK_INCOMPLETE";
                break;
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                error = (char *) "VK_ERROR_OUT_OF_HOST_MEMORY";
                break;
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                error = (char *) "VK_ERROR_OUT_OF_DEVICE_MEMORY";
                break;
            case VK_ERROR_INITIALIZATION_FAILED:
                error = (char *) "VK_ERROR_INITIALIZATION_FAILED";
                break;
            case VK_ERROR_DEVICE_LOST:
                error = (char *) "VK_ERROR_DEVICE_LOST";
                break;
            case VK_ERROR_MEMORY_MAP_FAILED:
                error = (char *) "VK_ERROR_MEMORY_MAP_FAILED";
                break;
            case VK_ERROR_LAYER_NOT_PRESENT:
                error = (char *) "VK_ERROR_LAYER_NOT_PRESENT";
                break;
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                error = (char *) "VK_ERROR_EXTENSION_NOT_PRESENT";
                break;
            case VK_ERROR_FEATURE_NOT_PRESENT:
                error = (char *) "VK_ERROR_FEATURE_NOT_PRESENT";
                break;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                error = (char *) "VK_ERROR_INCOMPATIBLE_DRIVER";
                break;
            case VK_ERROR_TOO_MANY_OBJECTS:
                error = (char *) "VK_ERROR_TOO_MANY_OBJECTS";
                break;
            case VK_ERROR_FORMAT_NOT_SUPPORTED:
                error = (char *) "VK_ERROR_FORMAT_NOT_SUPPORTED";
                break;
            case VK_ERROR_FRAGMENTED_POOL:
                error = (char *) "VK_ERROR_FRAGMENTED_POOL";
                break;
            case VK_ERROR_OUT_OF_POOL_MEMORY:
                error = (char *) "VK_ERROR_OUT_OF_POOL_MEMORY";
                break;
            case VK_ERROR_INVALID_EXTERNAL_HANDLE:
                error = (char *) "VK_ERROR_INVALID_EXTERNAL_HANDLE";
                break;
            case VK_ERROR_SURFACE_LOST_KHR:
                error = (char *) "VK_ERROR_SURFACE_LOST_KHR";
                break;
            case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                error = (char *) "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
                break;
            case VK_SUBOPTIMAL_KHR:
                error = (char *) "VK_SUBOPTIMAL_KHR";
                break;
            case VK_ERROR_OUT_OF_DATE_KHR:
                error = (char *) "VK_ERROR_OUT_OF_DATE_KHR";
                break;
            case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                error = (char *) "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
                break;
            case VK_ERROR_VALIDATION_FAILED_EXT:
                error = (char *) "VK_ERROR_VALIDATION_FAILED_EXT";
                break;
            case VK_ERROR_INVALID_SHADER_NV:
                error = (char *) "VK_ERROR_INVALID_SHADER_NV";
                break;
            case VK_ERROR_NOT_PERMITTED_EXT:
                error = (char *) "VK_ERROR_NOT_PERMITTED_EXT";
                break;
            case VK_RESULT_RANGE_SIZE:
                error = (char *) "VK_RESULT_RANGE_SIZE";
                break;
            case VK_RESULT_MAX_ENUM:
                error = (char *) "VK_RESULT_MAX_ENUM";
                break;
        }
        std::cerr << "Vulkan ERROR: " << error << std::endl;
        std::exit(-1);
    }
}