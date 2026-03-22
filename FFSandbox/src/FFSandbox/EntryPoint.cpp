#include "FFEngine/Engine.h"

#include <stdexcept>
#include <cstdlib>

#include "FFCore/Core/HString.h"
#include "FFCore/Memory/AllocTracker.h"
#include "FFCore/ResourceManagement/Resource_TextFile.h"

using namespace FF;

FFE::Window::InitData initData =
{
    .Name = "FF Sandbox",
    .Width = 1280,
    .Height = 720,
};

int main(int argc, char* argv[])
{
    FFE::Engine engine;
    engine.Init();
    
    engine.MakeWindow(initData);

    engine.InitGraphicsAPI();
    
    engine.Update();
    engine.Cleanup();
    
    FF::Memory::DumpAllTags();
    
    return 0;
}