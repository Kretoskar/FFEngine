#include "FFEngine/Rendering/VulkanRenderer.h"

#include "FFCore/Memory/AllocTracker.h"

using namespace FFE;

void VulkanRenderer::Init(FF::HString appName, GLFWwindow* window)
{
    FF_MEMORY_SCOPE(Rendering)
    
    _vulkanCore.Init(appName, window);
    _numImages = _vulkanCore.GetNumImages();

    _vulkanQueue = _vulkanCore.GetQueue();
            
    _cmdBuffers.resize(_numImages);
    _vulkanCore.CreateCommandBuffers(_numImages, _cmdBuffers.data());
    RecordCommandBuffers();
    
    _wasInit = true;
}

void VulkanRenderer::Cleanup()
{
    if (_wasInit)
    {
        _vulkanCore.FreeCommandBuffers(_cmdBuffers);
        _vulkanCore.Cleanup();
    }
}

void VulkanRenderer::Render()
{
    u32 imageIndex = _vulkanQueue->AcquireNextImage();
    _vulkanQueue->SubmitAsync(_cmdBuffers[imageIndex]);
    _vulkanQueue->Present(imageIndex);
}

void VulkanRenderer::RecordCommandBuffers()
{
    VkClearColorValue clearColor = { 1.0f, 0.0f, 0.0f, 0.0f };

    VkImageSubresourceRange imageRange =
    {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,    // just clear the color buffers
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1,
    };

    for (u32 i = 0; i < _cmdBuffers.size(); ++i)
    {
        VkImageMemoryBarrier presentToClearBarrier =
        {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            .pNext = nullptr,
            .srcAccessMask = VK_ACCESS_MEMORY_READ_BIT,
            .dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = _vulkanCore.GetImage(i),
            .subresourceRange = imageRange,
        };

        VkImageMemoryBarrier clearToPresentBarrier =
        {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            .pNext = nullptr,
            .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
            .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT,
            .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = _vulkanCore.GetImage(i),
            .subresourceRange = imageRange,
        };
        
        FFVk::VulkanCore::BeginCommandBuffer(
            _cmdBuffers[i],
            VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);

        vkCmdPipelineBarrier(
            _cmdBuffers[i],
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            0,
            0, nullptr,
            0, nullptr,
            1, &presentToClearBarrier);
        
        vkCmdClearColorImage(
            _cmdBuffers[i],
            _vulkanCore.GetImage(i),
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            &clearColor, 1, &imageRange);

        vkCmdPipelineBarrier(
            _cmdBuffers[i],
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            0,
            0, nullptr,
            0, nullptr,
            1, &clearToPresentBarrier);
        
        FFVk::VulkanCore::EndCommandBuffer(_cmdBuffers[i]);
    }
}
