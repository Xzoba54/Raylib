#pragma once

#include "State.h"
#include "Button.h"
#include <unordered_map>
#include <iostream>

class MainMenuState : public State{
public:
    MainMenuState(Window& window);

    void Update() override;
    void Render() override;
private:

    void InitButtons();

    std::unordered_map<std::string, Button> buttons;
};