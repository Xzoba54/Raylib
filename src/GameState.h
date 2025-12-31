#pragma once

#include "State.h"
#include "TileMap.h"
#include <iostream>
#include "Slime.h"
#include "Chest.h"
#include "ToolBar.h"
#include "ObjectRegistry.h"
#include "ItemRegister.h"
#include "ChestUI.h"
#include "Player.h"

enum class Mode{
    NORMAL,
    BUILDING
};

class GameState : public State {
public:
    GameState(Window& window);

    void Update() override;
    void Render() override;

    void InitTextures();
private:
    void ProcessInput();
    void HandleCameraInput();

    void UpdateMouseRouting();
    void HandleWorldClick();

    void HandleMouseClickLeft();
    void HandleMouseClickRight();

    bool CheckPlayerCollision(Rectangle playerRec);
    bool ShouldRenderAbovePlayer(int tileX, int tileY);

    Vector2 GetScreenToGridPosition(Vector2 pos);
    // std::vector<Vector2> GetObjectsToRenderAfterPlayer();

    TileMap map;
    Camera2D camera;

    std::unique_ptr<Slime> slime;

    ToolBar toolbar;

    Vector2 mousePosInWorld;
    float gridX;
    float gridY;
    
    Mode mode;
    
    ContentID selectedItemID;

    Player player;

    ChestUI chestUI;
};