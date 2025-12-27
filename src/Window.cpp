#include "Window.h"

void Window::Init(int width, int height, const char *title){
    this->size = {(float)width, (float)height};

    InitWindow(width, height, title);
    SetFps(60);
}

void Window::SetFps(int fps)
{
    SetTargetFPS(fps);
}

void Window::SetSize(int width, int height){
    this->size = {(float)width, (float)height};
    
    SetWindowSize(width, height);
}

void Window::CloseWindow(){
    CloseWindow();
}

Vector2 &Window::GetSize() {
    return this->size;
}

bool Window::ShouldClose(){
    return WindowShouldClose();
}