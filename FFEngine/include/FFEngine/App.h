#pragma once

#include <GLFW/glfw3.h>

class App
{
public:
    void Start();
    virtual void Start_Internal(){}
    void Update();
    virtual void Update_Internal(){}
    void ShutDown();
    virtual void ShutDown_Internal(){}

private:
    GLFWwindow* _window;
};
