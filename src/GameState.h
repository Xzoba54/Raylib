#pragma once

#include "State.h"
#include "TileMap.h"
#include <iostream>
#include "Slime.h"
#include "Chest.h"
#include "ToolBar.h"
#include "ObjectRegistry.h"
#include "ItemRegister.h"

enum class Mode{
    NORMAL,
    BUILDING
};

class GameState : public State {
public:
    GameState(Window& window);

    void Update() override;
    void Render() override;

    void ProcessInput();
    void HandleMouseClick(int gridX, int gridY);

    void PlaceObject(int gridX, int gridY, const ContentID& objectID);
    void RemoveObject(int gridX, int gridY);

    void InitTextures();
private:
    TileMap map;
    Camera2D camera;

    std::unique_ptr<Slime> slime;

    ToolBar toolbar;

    Vector2 mousePosInWorld;
    
    Mode mode;
    
    ContentID selectedItemID;
    Texture2D chestUI;
};