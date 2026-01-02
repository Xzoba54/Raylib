#pragma once

#include "NetworkManager.h"
#include "State.h"
#include "TileMap.h"
#include "Slime.h"
#include "Chest.h"
#include "ToolBar.h"
#include "ObjectRegistry.h"
#include "ItemRegister.h"
#include "ChestUI.h"
#include "Player.h"

#include <iostream>

enum class GameMode{
    Singleplayer,
    Multiplayer
};

class GameState : public State {
public:
    GameState(Window& window, GameMode mode, bool isServer = false);

    void Update() override;
    void Render() override;
private:
    std::vector<std::pair<int, int>> GetObjectsAbovePlayer();

    Vector2 GetScreenToGridPosition(Vector2 pos);

    void InitTextures();
    void InitCamera();

    void ProcessInput();
    void HandleCameraInput();
    void UpdateMouseRouting();
    void HandleWorldClick();
    void HandleMouseClickLeft();
    void HandleMouseClickRight();

    void ProcessPlayerMovement();
    bool CheckPlayerCollision(Rectangle playerRec);
    bool ShouldRenderAbovePlayer(int tileX, int tileY);

    void UpdateNetwork();

    TileMap map;
    Camera2D camera;

    GameMode mode;

    Player player;
    std::unique_ptr<Slime> slime;

    Vector2 mousePosInWorld;
    float gridX;
    float gridY;
    
    ContentID selectedItemID;

    ToolBar toolbar;
    ChestUI chestUI;

    float maxDistanceToInteract = TILESIZE * 5;

    //multiplayer
    std::unordered_map<uint8_t, Player> remotePlayers;
    uint8_t localPlayerID = 0;

    NetworkManager network;
};