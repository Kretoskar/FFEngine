#pragma once
#include "FFCore/Core/HString.h"
#include "FFVulkan/VulkanCore.h"

struct GLFWwindow;

namespace FFE
{
    class VulkanRenderer
    {
    public:
        void Init(FF::HString appName, GLFWwindow* window);
        void Cleanup();
        void Render();
        
    private:
        void RecordCommandBuffers();

        bool _wasInit = false;
        FFVk::VulkanCore _vulkanCore;
        i32 _numImages = 0;
        std::vector<VkCommandBuffer> _cmdBuffers;

        FFVk::VulkanQueue* _vulkanQueue = nullptr;
        
        VkRenderPass _renderPass = VK_NULL_HANDLE;
        std::vector<VkFramebuffer> _framebuffers;
        u32 WindowHeight = 720;
        u32 WindowWidth = 1280;
    };
}
