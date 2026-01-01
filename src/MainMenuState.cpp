#include "MainMenuState.h"

MainMenuState::MainMenuState(Window& window) : 
    State(window)    
{
    this->InitButtons();
}

void MainMenuState::Update(){
    if(buttons["QUIT"].IsClicked())         this->SetAction(StateAction::Pop);
    if(buttons["NEW GAME"].IsClicked())     this->SetAction(StateAction::PushGameStateSingleplayer);
    if(buttons["HOST GAME"].IsClicked())    this->SetAction(StateAction::PushGameStateMultiplayerServer);
    if(buttons["JOIN GAME"].IsClicked())    this->SetAction(StateAction::PushGameStateMultiplayerClient);

    for(auto& [name, button] : buttons){
        button.Update();
    }
}

void MainMenuState::Render(){
    for(auto& [name, button] : buttons){
        button.Render();
    }
}

void MainMenuState::InitButtons(){
    buttons.emplace("NEW GAME", Button(40, 250, 140, 50, "New Game"));
    buttons.emplace("HOST GAME", Button(500, 250, 140, 50, "Host Game"));
    buttons.emplace("JOIN GAME", Button(660, 250, 140, 50, "Join Game"));
    buttons.emplace("QUIT", Button(40, 320, 140, 50, "Quit"));
}