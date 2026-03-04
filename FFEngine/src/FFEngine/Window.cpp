#include "FFEngine/Window.h"

#include "FFCore/Memory/AllocTracker.h"

using namespace FFE;

bool Window::Init(const InitData& initData)
{
    FF_MEMORY_SCOPE(Core)
    
    ASSERT(glfwInit(), "Failed to initialize GLFW")
    ASSERT(glfwVulkanSupported(), "GLFW does not support Vulkan")

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(
        static_cast<int32_t>(initData.Width),
        static_cast<int32_t>(initData.Height),
        initData.Name.Get(),
        nullptr,
        nullptr);

    if (!_window)
    {
        glfwTerminate();
        LOG_ERROR("Failed to create GLFW window")
        return false;
    }

    _name = initData.Name;
    _currentWidth = initData.Width;
    _currentHeight = initData.Height;
    
    return true;
   // glfwSetKeyCallback(window, GLFW_KeyCallback);
}
