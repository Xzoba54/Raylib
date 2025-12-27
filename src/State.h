#pragma once

#include "Window.h"
#include <stack>

enum class StateAction{
    None,
    Pop,
    PushMainMenuState,
    PushGameState
};

class State{
public:
    State(Window& window) : window(window), action(StateAction::None) {};
    virtual ~State() = default;

    StateAction GetAction() const { return action; };
    void ClearAction() { action = StateAction::None; };
    void SetAction(StateAction action) { this->action = action; };

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    Window& window;
    StateAction action;
};