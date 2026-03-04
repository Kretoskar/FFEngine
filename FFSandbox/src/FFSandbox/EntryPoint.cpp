#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "FFCore/Core/Assert.h"
#include "FFCore/Core/Logger.h"
#include "FFCore/Core/Types.h"
#include "FFCore/Core/HString.h"
#include "FFCore/Math/Vec3.h"
#include "FFCore/Memory/AllocTracker.h"

#include "FFEngine/Engine.h"


void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

struct A
{
    i32 a,b,c;
};

int main(int argc, char* argv[])
{
    FFE::Engine engine;
    FFE::Window::InitData initData =
    {
        .Name = "FF Sandbox",
        .Width = 1280,
        .Height = 720,
    };
    engine.CreateWindowFF(initData);

    engine.Update();
    
    FF::Memory::DumpAllTags();
    
    return 0;
}