#include "FFEngine/Engine.h"

#include <GLFW/glfw3.h>


void FFE::Engine::Update()
{
    while (!_windows.empty() && !glfwWindowShouldClose(_windows[0].GetWindow()))
    {
        glfwPollEvents();
    }

    glfwTerminate();
}

void FFE::Engine::Cleanup()
{
    for (const Window& w : _windows)
    {
        glfwDestroyWindow(w.GetWindow());
    }

    glfwTerminate();
    
    ResourceManager.Stop();
    ResourceManager.UnloadAll();
    FF::Logger::GetInstance().Stop();
}

void FFE::Engine::InitGraphicsAPI()
{
    _vulkan.InitVulkan();
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

    return w;
}

FFE::Window& FFE::Engine::GetWindow(uint16_t idx)
{
    return _windows[idx];
}
