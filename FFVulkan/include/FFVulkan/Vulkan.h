#pragma once

#include <vulkan/vulkan_raii.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace FFVk
{
    class Vulkan
    {
    public:
        void InitVulkan();
        
    private:
        vk::raii::Context _context;
        vk::raii::Instance _instance = nullptr;
    };
}