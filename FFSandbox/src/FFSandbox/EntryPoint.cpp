#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "FFCore/Core/HString.h"
#include "FFCore/Memory/AllocTracker.h"

#include "FFEngine/Engine.h"

int main(int argc, char* argv[])
{
    FFE::Engine engine;
    engine.Init();
    
    FFE::Window::InitData initData =
    {
        .Name = "FF Sandbox",
        .Width = 1280,
        .Height = 720,
    };
    
    engine.MakeWindow(initData);
    
    engine.Update();
    engine.Cleanup();
    
    FF::Memory::DumpAllTags();
    
    return 0;
}