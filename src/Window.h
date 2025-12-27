#pragma once

#include "raylib.h"
#include <memory>

class Window{
public:
    Window() {};

    void Init(int width, int height, const char* title);

    void SetFps(int fps);
    void SetSize(int width, int height);
    void CloseWindow();

    Vector2& GetSize();

    bool ShouldClose();
private:
    Vector2 size;
};