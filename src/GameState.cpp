#include "GameState.h"

GameState::GameState(Window& window, GameMode mode, bool isServer) : 
    State(window)
{
    ObjectRegistry::Init();
    ItemRegistry::Init();
    this->InitTextures();
    this->toolbar.Init();
    this->chestUI.Init(window);

    this->player.Init(300, 300);
    slime = std::make_unique<Slime>(4 * TILESIZE, 4 * TILESIZE);

    this->InitCamera();

    this->selectedItemID = ContentID::None;

    this->mode = mode;
    if(mode == GameMode::Multiplayer){
        if(isServer){
            network.InitServer();
            map.LoadMapFromFile();
            window.SetTitle("Server");
            mode = GameMode::Multiplayer;
        }else{
            network.InitClient();
            window.SetTitle("Client");
            mode = GameMode::Multiplayer;
        }
    }
    else{
        window.SetTitle("Singleplayer");
        map.LoadMapFromFile();
        mode = GameMode::Singleplayer;
    }
}

void GameState::InitCamera(){
    camera = {0};
    camera.target = {player.GetPosition().x, player.GetPosition().y};
    camera.offset = {window.GetSize().x / 2.0f, window.GetSize().y / 2.0f};
    camera.zoom = 1.8;
}


void GameState::Update(){
    ProcessInput();

    mousePosInWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    gridX = mousePosInWorld.x / TILESIZE;
    gridY = mousePosInWorld.y / TILESIZE;

    map.Update(mousePosInWorld);
    slime->Update();

    ProcessPlayerMovement();

    selectedItemID = toolbar.GetSelectedItem();

    //TEMP
    if(map.GetObjectType(gridX, gridY) == ContentID::Chest && IsKeyPressed(KEY_P)){
        std::shared_ptr<Chest> chest = std::dynamic_pointer_cast<Chest>(map.GetObject(gridX, gridY));

        std::vector<uint8_t> out;

        chest->SetItem(ContentID::Pickaxe, 1, 0);
        chest->SetItem(ContentID::Chest, 4, 1);

        chest->Serialize(out);
    }

    if(chestUI.IsOpen()) chestUI.Update();
    toolbar.Update();

    if(mode == GameMode::Multiplayer) UpdateNetwork();
    
    UpdateMouseRouting();
}

void GameState::Render(){
    /*  ========================
        ===RENDER PERSPECTIVE===
        ========================
    */
    BeginMode2D(camera);
    std::vector<std::pair<int, int>> objectsAbovePlayer = GetObjectsAbovePlayer();

    map.RenderGround();
    map.RenderObjectsExcept(objectsAbovePlayer);
 
    slime->Render();
    player.Render();

    if(mode == GameMode::Multiplayer){
        for(auto& [_, remotePlayer] : remotePlayers){
            remotePlayer.Render();
        }
    }
    for(auto& [x, y] : objectsAbovePlayer){
        map.RenderObjectAt(x, y);
    }
    EndMode2D();

    /*  ===============
        ===RENDER UI===
        ===============
    */ 
    toolbar.Render();    
    if(chestUI.IsOpen()){
        chestUI.Render();
    }
}

void GameState::ProcessInput(){
    HandleCameraInput();

    if(IsKeyPressed(KEY_ESCAPE)){
        toolbar.CancelDrag();
        chestUI.CancelDrag();
        chestUI.Close();
    }
}


bool GameState::ShouldRenderAbovePlayer(int tileX, int tileY){
    if(!map.HasObject(tileX, tileY)) return false;

    Rectangle objectPhysicalRec = map.GetObject(tileX, tileY)->GetPhysicalRec();
    Rectangle playerPhysicalRec = player.GetPhysicalRec();

    return playerPhysicalRec.y < objectPhysicalRec.y &&
           objectPhysicalRec.y + objectPhysicalRec.height > playerPhysicalRec.y + playerPhysicalRec.height &&
           player.GetPosition().y + player.GetPhysicalRec().height <= map.GetObject(tileX, tileY)->GetRec().y;
}

void GameState::UpdateNetwork(){
    localPlayerID = network.GetLocalPlayerID();

    network.Update();
    network.SendPlayerPosition(player.GetPosition().x, player.GetPosition().y);

    for(auto& [id, pos] : network.GetRemotePlayerPositions()){
        if(id == localPlayerID) continue;

        if(remotePlayers.find(id) == remotePlayers.end()){
            Player p;
            p.Init(pos.x, pos.y);
            remotePlayers[id] = p;
        }else{
            remotePlayers[id].SetPosition(pos.x, pos.y);
        }
    }

    network.onClientConnected = [this](uint8_t newClientID){
        if(network.GetMode() == NetworkMode::Server){
            int width = map.GetSize().x;
            int height = map.GetSize().y;

            std::vector<uint8_t> data;
            map.Serialize(data);

            network.SendTileMapGround(newClientID, width, height, data);
        }
    };

    network.onTileMapGroundReceived = [this](uint8_t clientID, int width, int height, std::vector<uint8_t> data){
        if(network.GetMode() == NetworkMode::Client && clientID == localPlayerID){
            map.Deserialize(width, height, data);
        }
    };
}

std::vector<std::pair<int, int>> GameState::GetObjectsAbovePlayer(){
    std::vector<std::pair<int, int>> objectsAbovePlayer;

    int leftTileX = GetScreenToGridPosition(player.GetPosition()).x;
    int tileY = GetScreenToGridPosition({player.GetPosition().x, player.GetPosition().y + player.GetHeight()}).y;

    if(ShouldRenderAbovePlayer(leftTileX, tileY)){
        objectsAbovePlayer.push_back(std::make_pair(leftTileX, tileY));
    }

    int rightTileX = GetScreenToGridPosition({
        player.GetPosition().x + player.GetPhysicalRec().width,
        player.GetPhysicalRec().y}
    ).x;

    if(leftTileX != rightTileX && ShouldRenderAbovePlayer(rightTileX, tileY)){
        objectsAbovePlayer.push_back(std::make_pair(rightTileX, tileY));
    }

    return objectsAbovePlayer;
}

Vector2 GameState::GetScreenToGridPosition(Vector2 pos){
    return {pos.x / TILESIZE, pos.y / TILESIZE};
}

void GameState::HandleCameraInput(){
    float wheel = GetMouseWheelMove();

    camera.zoom += wheel * 0.05f;
    camera.target = player.GetPosition();
}

void GameState::UpdateMouseRouting(){
    Vector2 mouse = GetMousePosition();

    if(CheckCollisionPointRec(mouse, toolbar.GetRec())) return;
    if(chestUI.IsOpen() && CheckCollisionPointRec(mouse, chestUI.GetRec())) return;

    HandleWorldClick();
}

void GameState::HandleWorldClick(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) HandleMouseClickLeft();
    else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) HandleMouseClickRight();
}

void GameState::HandleMouseClickLeft(){
    ContentID objectType = map.GetObjectType(gridX, gridY);
    
    //building
    if(selectedItemID != ContentID::None && ObjectRegistry::IsPlaceable(selectedItemID)){
        map.SetObject(gridX, gridY, selectedItemID);
    }
    if(selectedItemID != ContentID::None) return;

    //interaction with objects
    if(objectType == ContentID::Chest){
        std::shared_ptr<Chest> chest = std::dynamic_pointer_cast<Chest>(map.GetObject(gridX, gridY));
        chestUI.Open(chest);
    }
}

void GameState::HandleMouseClickRight(){
    map.RemoveObject(gridX, gridY);
}

void GameState::ProcessPlayerMovement(){
    player.ProcessInput();

    Vector2 playerMovement = player.GetMovement();
    Rectangle playerRec = player.GetRec();

    Rectangle recX = playerRec;
    recX.x += playerMovement.x;
    if(!CheckPlayerCollision(recX)) player.Move({playerMovement.x, 0});

    Rectangle recY = playerRec;
    recY.y += playerMovement.y;
    if(!CheckPlayerCollision(recY)) player.Move({0, playerMovement.y});
}

bool GameState::CheckPlayerCollision(Rectangle playerRec){
    int minX = playerRec.x / TILESIZE;
    int minY = playerRec.y / TILESIZE;
    int maxX = (playerRec.x + playerRec.width) / TILESIZE;
    int maxY = (playerRec.y + playerRec.height) / TILESIZE;

    for(int y = minY; y <= maxY; y++){
        for(int x = minX; x <= maxX; x++){
            if(!map.IsValidPosition(x, y)) continue;
            if(!map.HasObject(x, y)) continue;;

            auto obj = map.GetObject(x, y);
            if(!obj) continue;

            if(CheckCollisionRecs(playerRec, obj->GetRec())){
                return true;
            }
        }
    }
    return false;
}

void GameState::InitTextures(){
    //Objects
    TextureManager::LoadTexture("CHEST", "assets/chest2.png");
    TextureManager::LoadTexture("WALL", "assets/wall.png");
    TextureManager::LoadTexture("BELT", "assets/conv_belt.png");

    //Entities
    TextureManager::LoadTexture("PLAYER", "assets/player.png");

    //items
    TextureManager::LoadTexture("PICKAXE", "assets/pickaxe.png");

    //ground
    TextureManager::LoadTexture(GroundID::None, "assets/empty.png");
    TextureManager::LoadTexture(GroundID::Dirt, "assets/dirt.png");
    TextureManager::LoadTexture(GroundID::Grass, "assets/grass.png");
    TextureManager::LoadTexture(GroundID::Plowed, "assets/plowed.png");
    TextureManager::LoadTexture(GroundID::Iron, "assets/iron.png");
    TextureManager::LoadTexture(GroundID::Rocks, "assets/rocks.png");

    //UI
    TextureManager::LoadTexture("CHEST_INVENTORY_UI", "assets/chest_inventory_ui.png");
    TextureManager::LoadTexture("TOOLBAR", "assets/toolbar.png");
}