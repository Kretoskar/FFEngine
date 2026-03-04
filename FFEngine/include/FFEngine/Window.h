#pragma once
#include <GLFW/glfw3.h>

#include "FFCore/Core/HString.h"



namespace FFE
{
    class Window
    {
    public:
        struct InitData
        {
            FF::HString Name;
            u32 Width{};
            u32 Height{};
        };
        
        bool Init(const InitData& initData);

        
        
    private:
        FF::HString _name;
        u32 _currentWidth{};
        u32 _currentHeight{};
        GLFWwindow* _window = nullptr;

    public:
        FF::HString GetName() const { return _name; }
        GLFWwindow* GetWindow() const { return _window; }
    };
}
