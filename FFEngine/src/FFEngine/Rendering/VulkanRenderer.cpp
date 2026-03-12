#include "FFEngine/Rendering/VulkanRenderer.h"

#include "FFCore/Memory/AllocTracker.h"
#include "FFVulkan/VulkanShader.h"

using namespace FFE;

void VulkanRenderer::Init(FF::HString appName, GLFWwindow* window)
{
    FF_MEMORY_SCOPE(Rendering)
    
    _vulkanCore.Init(appName, window);
    _numImages = _vulkanCore.GetNumImages();

    _vulkanQueue = _vulkanCore.GetQueue();
            
    _renderPass = _vulkanCore.CreateSimpleRenderPass();
    _framebuffers = _vulkanCore.CreateFramebuffers(_renderPass);
    
    _cmdBuffers.resize(_numImages);
    _vulkanCore.CreateCommandBuffers(_numImages, _cmdBuffers.data());
    RecordCommandBuffers();
    
    vertexShader = FFVk::CreateShaderModuleFromText(_vulkanCore.GetDevice(), "test.vert");
    fragmentShader = FFVk::CreateShaderModuleFromText(_vulkanCore.GetDevice(), "test.frag");
    
    _wasInit = true;
}

void VulkanRenderer::Cleanup()
{
    if (_wasInit)
    {
        _vulkanCore.FreeCommandBuffers(_cmdBuffers);
        _vulkanCore.Cleanup();
        
        vkDestroyShaderModule(_vulkanCore.GetDevice(), vertexShader, nullptr);
        vkDestroyShaderModule(_vulkanCore.GetDevice(), fragmentShader, nullptr);
        
        vkDestroyRenderPass(_vulkanCore.GetDevice(), _renderPass, nullptr);
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
    
    VkClearValue clearValue;
    clearValue.color = clearColor;
    
    VkRenderPassBeginInfo renderPassBeginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .pNext = nullptr,
        .renderPass = _renderPass,
        .renderArea =
        { 
            .offset =  
            {   
                .x = 0,
                .y = 0
            },
            .extent = 
                {
                    .width =  WindowWidth,
                    .height = WindowHeight
                }
        },
        .clearValueCount = 1,
        .pClearValues = &clearValue
    };
    

    for (u32 i = 0; i < _cmdBuffers.size(); ++i)
    {
        // Command buffer
        FFVk::VulkanCore::BeginCommandBuffer(
            _cmdBuffers[i],
            VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);
        {
            renderPassBeginInfo.framebuffer = _framebuffers[i];
            
            // Render pass
            vkCmdBeginRenderPass(_cmdBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
            {
                
            } vkCmdEndRenderPass(_cmdBuffers[i]);
            
        } FFVk::VulkanCore::EndCommandBuffer(_cmdBuffers[i]);
    }
}
