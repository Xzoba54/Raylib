#pragma once

#include "MainMenuState.h"
#include "GameState.h"
#include "Register.h"

class Game {
public:
    Game();
    ~Game();

    void Run();
    void Update();
    void Render();

    void SetupWindow(int width, int height, const char* title);
    void InitState();
private:
    Window window;

    std::stack<std::unique_ptr<State>> states;
};