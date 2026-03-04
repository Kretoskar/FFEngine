#include "FFEngine/Engine.h"

void FFE::Engine::InitRenderer(uint16_t windowIdx)
{
    VulkanRenderer& renderer = CreateVulkanRenderer();
    Window& window = GetWindow(windowIdx);
    renderer.Init(window.GetName(), window.GetWindow());
}

void FFE::Engine::Update()
{
    while (!_windows.empty())
    {
        for (i32 i = _windows.size() - 1; i >= 0 ; --i)
        {
            if (glfwWindowShouldClose(_windows[i].GetWindow()))
            {
                // This breaks the whole indexing.
                // When more than 1 window will be available, need to make different container
                _windows.erase(_windows.begin() + i);
                _vulkanRenderers.erase(_vulkanRenderers.begin() + i);
            }
            else
            {
                _vulkanRenderers[i].Render();   
            }
        }

        glfwPollEvents();
    }

    glfwTerminate();
}

void FFE::Engine::Cleanup()
{
    for (VulkanRenderer& renderer : _vulkanRenderers)
    {
        renderer.Cleanup();
    }
    
    FF::Logger::GetInstance().Stop();
}

FFE::VulkanRenderer& FFE::Engine::CreateVulkanRenderer()
{
    _vulkanRenderers.push_back(VulkanRenderer());
    return _vulkanRenderers.back();
}

FFE::VulkanRenderer& FFE::Engine::GetVulkanRenderer(uint16_t idx)
{
    return _vulkanRenderers[idx];   
}

void FFE::Engine::Init()
{
    FF::Logger::GetInstance().Start();
}

FFE::Window& FFE::Engine::MakeWindow(const Window::InitData& initData)
{
    _windows.push_back(Window());
    Window& w = _windows.back();
    w.Init(initData);
    InitRenderer(_windows.size() - 1);

    return w;
}

FFE::Window& FFE::Engine::GetWindow(uint16_t idx)
{
    return _windows[idx];
}
