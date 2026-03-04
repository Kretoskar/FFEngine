#pragma once
#include "FFCore/Core/HString.h"
#include "FFVulkan/VulkanCore.h"

struct GLFWwindow;

namespace FFE
{
    class VulkanRenderer
    {
    public:
        VulkanRenderer(){}

        ~VulkanRenderer()
        {
            if (_wasInit)
            {
                _vulkanCore.FreeCommandBuffers(_cmdBuffers);
            }
        }

        void Init(FF::HString appName, GLFWwindow* window);
        void Render();
        
    private:
        void RecordCommandBuffers();

        bool _wasInit = false;
        FFVk::VulkanCore _vulkanCore;
        i32 _numImages = 0;
        std::vector<VkCommandBuffer> _cmdBuffers;

        FFVk::VulkanQueue* _vulkanQueue = nullptr;
    };
}
