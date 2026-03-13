#include "FFEngine/Engine.h"

#include <GLFW/glfw3.h>


void FFE::Engine::Update()
{
    while (!_windows.empty())
    {
        glfwPollEvents();
    }

    glfwTerminate();
}

void FFE::Engine::Cleanup()
{

    FF::Logger::GetInstance().Stop();
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
