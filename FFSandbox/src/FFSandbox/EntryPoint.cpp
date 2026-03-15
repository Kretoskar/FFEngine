#include "FFCore/Core/HString.h"
#include "FFCore/Memory/AllocTracker.h"
#include "FFCore/ResourceManagement/Resource_TextFile.h"
#include "FFEngine/Engine.h"

using namespace FF;

int main(int argc, char* argv[])
{
    FFE::Engine engine;
    engine.Init();
    
    
    std::string id = "skibidi";
    engine.ResourceManager.LoadAsync<Resource_TextFile>(id, true, [](ResourceHandle<Resource_TextFile> file)
    {
        if (file)
        {
            LOG_MESSAGE("%s", file.Get()->GetContent().data())
        }
    });
    
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