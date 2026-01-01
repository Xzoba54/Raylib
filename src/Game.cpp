#include "Game.h"

Game::Game(){
    this->SetupWindow(1300, 800, "raylib");
    this->InitState();
}

void Game::SetupWindow(int width, int height, const char* title){
    this->window.Init(width, height, title);
    this->window.SetFps(120);
}

void Game::InitState(){
    this->states.push(std::make_unique<MainMenuState>(window));
}

void Game::Run(){
    while(!window.ShouldClose()){
        this->Update();
        this->Render();
    }
}

void Game::Update(){
    if(states.empty()){
        window.CloseWindow();
        return;
    }

    std::unique_ptr<State>& state = states.top();
    state->Update();

    StateAction action = state->GetAction();
    if(action == StateAction::Pop)                              states.pop();
    if(action == StateAction::PushGameStateSingleplayer)        states.push(std::make_unique<GameState>(this->window, GameMode::Singleplayer));
    if(action == StateAction::PushGameStateMultiplayerServer)   states.push(std::make_unique<GameState>(this->window, GameMode::Multiplayer, true));
    if(action == StateAction::PushGameStateMultiplayerClient)   states.push(std::make_unique<GameState>(this->window, GameMode::Multiplayer, false));
    if(action == StateAction::PushMainMenuState)                states.push(std::make_unique<MainMenuState>(this->window));

    state->ClearAction();
}

void Game::Render(){
    BeginDrawing();
    ClearBackground(BLACK);

    if(!this->states.empty()){
        this->states.top()->Render();
    }

    EndDrawing();
}

Game::~Game(){
    
}
