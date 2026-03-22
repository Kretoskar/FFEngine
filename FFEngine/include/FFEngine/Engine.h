#pragma once

#include "FFVulkan/Vulkan.h"

#include "Window.h"
#include "FFCore/ResourceManagement/ResourceManagement.h"

struct GLFWwindow;

namespace FFE
{
    class Engine
    {
    public:
        void Init();
        Window& MakeWindow(const Window::InitData& initData);
        void Update();
        void Cleanup();
        void InitGraphicsAPI();

        FF::ResourceManager ResourceManager;
        
    private:
        Window& GetWindow(u16 idx);
        std::vector<Window> _windows;
        FFVk::Vulkan _vulkan;
    };
}
