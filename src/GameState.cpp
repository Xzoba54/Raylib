#include "GameState.h"

GameState::GameState(Window& window) : 
    State(window)
{
    ObjectRegistry::Init();
    ItemRegistry::Init();
    this->InitTextures();
    this->map.Init();
    this->toolbar.Init();
    this->chestUI.Init(window);

    this->player.Init(300, 300);

    this->mode = Mode::BUILDING;
    this->selectedItemID = ContentID::Chest;

    slime = std::make_unique<Slime>(4 * TILESIZE, 4 * TILESIZE);
    
    camera = {0};
    camera.target = {300,300};
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

    player.ProcessInput();
    Vector2 playerMovement = player.GetMovement();
    Rectangle playerRec = player.GetRec();

    Rectangle recX = playerRec;
    recX.x += playerMovement.x;
    if(!CheckPlayerCollision(recX)){
        player.Move({playerMovement.x, 0});
    }

    Rectangle recY = playerRec;
    recY.y += playerMovement.y;
    if(!CheckPlayerCollision(recY)){
        player.Move({0, playerMovement.y});
    }

    selectedItemID = toolbar.GetSelectedItem();

    if(map.GetObjectID(gridX, gridY) == ContentID::Chest && IsKeyPressed(KEY_P)){
        std::shared_ptr<Chest> chest = std::dynamic_pointer_cast<Chest>(map.GetObject(gridX, gridY));

        chest->SetItem(ContentID::Pickaxe, 1, 0);
        chest->SetItem(ContentID::Chest, 4, 1);
    }

    if(chestUI.IsOpen()){
        chestUI.Update();
    }
    toolbar.Update();

    UpdateMouseRouting();
}

void GameState::Render(){
    //render world
    BeginMode2D(camera);

    //new rendering system
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

    map.RenderGround();
    map.RenderObjectsExcept(objectsAbovePlayer);

    player.Render();

    for(auto& obj : objectsAbovePlayer){
        map.RenderTile(obj.first, obj.second);
    }

    //end new rendering system
    slime->Render();
    EndMode2D();

    //render UI
    toolbar.Render();
    
    if(chestUI.IsOpen()){
        chestUI.Render();
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
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        HandleMouseClickLeft();
    }
    else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        HandleMouseClickRight();
    }
}

void GameState::HandleMouseClickLeft(){
    ContentID id = map.GetObjectID(gridX, gridY);
    
    if(selectedItemID != ContentID::None && 
       ObjectRegistry::IsPlaceable(selectedItemID)){
        map.SetObject(gridX, gridY, selectedItemID);
    }

    if(selectedItemID != ContentID::None) return;

    if(id == ContentID::Chest){
        std::shared_ptr<Chest> chest = std::dynamic_pointer_cast<Chest>(map.GetObject(gridX, gridY));

        chestUI.Open(chest);
    }
}

void GameState::HandleMouseClickRight(){
    map.RemoveObject(gridX, gridY);
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

// std::vector<Vector2> GameState::GetObjectsToRenderAfterPlayer(){
//     std::vector<Vector2> objects;

//     if(player.GetRec())
// }

void GameState::InitTextures(){
    //temp
    TextureManager::LoadTexture("PLAYER", "assets/player.png");

    //objects
    TextureManager::LoadTexture("CHEST", "assets/chest2.png");
    TextureManager::LoadTexture("WALL", "assets/wall.png");
    TextureManager::LoadTexture("BELT", "assets/conv_belt.png");

    //items
    TextureManager::LoadTexture("PICKAXE", "assets/pickaxe.png");

    //ground
    TextureManager::LoadTexture("EMPTY", "assets/empty.png");
    TextureManager::LoadTexture("DIRT", "assets/dirt.png");
    TextureManager::LoadTexture("GRASS", "assets/grass.png");
    TextureManager::LoadTexture("PLOWED", "assets/plowed.png");
    TextureManager::LoadTexture("IRON", "assets/iron.png");
    TextureManager::LoadTexture("ROCKS", "assets/rocks.png");

    //UI
    TextureManager::LoadTexture("CHEST_INVENTORY_UI", "assets/chest_inventory_ui.png");
    TextureManager::LoadTexture("TOOLBAR", "assets/toolbar.png");
}

void GameState::ProcessInput(){
    HandleCameraInput();

    if(IsKeyPressed(KEY_ESCAPE)){
        toolbar.CancelDrag();
        chestUI.CancelDrag();
        chestUI.Close();
    }
}
