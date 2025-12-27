#pragma once

#include "raylib.h"
#include <string>

enum ButtonState{
    IDLE = 0,
    HOVER,
    PRESSED
};

class Button{
public:
    Button(float x, float y, float width, float height, const char *text);
    Button() = default;

    void Update();
    void Render();

    bool IsClicked();

private:
    Rectangle button;
    Color background_idle_color;
    Color background_hover_color;
    Color background_pressed_color;
    Color background_current_color;

    std::string text;
    float textX;
    float textY;
    int fontSize;

    bool isClicked;
};