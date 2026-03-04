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
        Engine()
        {
            FF::Logger::GetInstance().Start();
        }
        ~Engine()
        {
            FF::Logger::GetInstance().Stop();   
        }

        Window& CreateWindowFF(const Window::InitData& initData);
        void Update();
        
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
