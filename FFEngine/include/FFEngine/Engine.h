#pragma once

#include "Window.h"
#include "Rendering/VulkanRenderer.h"
#include "FFCore/Core/Logger.h"

class GLFWwindow;

namespace FFE
{
    class Engine
    {
    public:
        void Init();
        Window& MakeWindow(const Window::InitData& initData);
        void Update();
        void Cleanup();
        
    private:
        // TODO: when removing windows will be possible, need to change the container or keep ID
        VulkanRenderer& CreateVulkanRenderer();
        VulkanRenderer& GetVulkanRenderer(u16 idx);
        void InitRenderer(u16 windowIdx);
        std::vector<VulkanRenderer> _vulkanRenderers;
        Window& GetWindow(u16 idx);
        std::vector<Window> _windows;
    };
}
