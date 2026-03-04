#pragma once

#include "VulkanPhysicalDevice.h"
#include "VulkanQueue.h"
#include "FFCore/Core/HString.h"
#include "vulkan/vulkan_core.h"

struct GLFWwindow;

namespace FFVk
{
    class VulkanCore
    {
    public:
        VulkanCore() = default;
        ~VulkanCore() = default;

        void Init(FF::HString appName, GLFWwindow* window);
        void Cleanup();
        
        i32 GetNumImages();
        void CreateCommandBuffers(u32 num, VkCommandBuffer* outCommandBuffers);
        void FreeCommandBuffers(const std::vector<VkCommandBuffer>& commandBuffers);
        const VkImage& GetImage(u32 idx) const;
        VulkanQueue* GetQueue() { return &_queue; }

        static void BeginCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferUsageFlags usageFlags);
        static void EndCommandBuffer(VkCommandBuffer commandBuffer);
        
    private:
        void CreateInstance(const char* appName);
        void CreateDebugCallback();
        void CreateSurface(GLFWwindow* window);
        void CreateDevice();
        u32 ChooseNumImages(const VkSurfaceCapabilitiesKHR& capabilities);
        VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& presentModes);
        VkSurfaceFormatKHR ChooseSurfaceFormatAndColorSpace(const std::vector<VkSurfaceFormatKHR>& surfaceFormats);
        VkImageView CreateImageView(VkDevice device, VkImage image, VkFormat format,
            VkImageAspectFlags aspectFlags, VkImageViewType imageViewType, u16 layerCount, u16 mipLevel);
        void CreateSwapChain();
        void CreateCommandBufferPool();
        
        VkInstance _instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;
        VkSurfaceKHR _surface = VK_NULL_HANDLE;
        VulkanPhysicalDevices _physicalDevices;
        u32 _queueFamily{};
        VkDevice _device = VK_NULL_HANDLE;
        VkSwapchainKHR _swapChain = VK_NULL_HANDLE;
        std::vector<VkImage> _images;
        std::vector<VkImageView> _imageViews;
        VkCommandPool _commandBufferPool;
        VulkanQueue _queue;
        bool _wasInit = false;
    };
}