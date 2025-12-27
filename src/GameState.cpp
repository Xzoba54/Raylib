#include "GameState.h"

GameState::GameState(Window& window) : 
    State(window)
{
    ObjectRegistry::Init();
    ItemRegistry::Init();
    this->InitTextures();
    this->map.Init();
    this->toolbar.Init();

    this->mode = Mode::BUILDING;
    this->selectedItemID = ContentID::Chest;

    //TEMP
    this->chestUI = TextureManager::GetTexture("CHEST_INVENTORY_UI");

    slime = std::make_unique<Slime>(4 * TILESIZE, 4 * TILESIZE);
    
    camera = {0};
    camera.target = {300,300};
    camera.offset = {window.GetSize().x / 2.0f, window.GetSize().y / 2.0f};
    camera.zoom = 1.8;
}

void GameState::Update(){
    this->ProcessInput();

    mousePosInWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    int gridX = mousePosInWorld.x / TILESIZE;
    int gridY = mousePosInWorld.y / TILESIZE;

    map.Update(mousePosInWorld);
    slime->Update();

    selectedItemID = toolbar.GetSelectedItem();

    if(CheckCollisionPointRec(GetMousePosition(), toolbar.GetRec())){
        toolbar.Update();
    }
    else{
        this->HandleMouseClick(gridX, gridY);
    }
}

void GameState::Render(){
    //render world
    BeginMode2D(camera);
    map.Render();
    slime->Render();
    EndMode2D();

    //render UI
    toolbar.Render();
    DrawTexture(this->chestUI, 300, 300, RAYWHITE);
}

void GameState::ProcessInput(){
    float mouseWheelPos = GetMouseWheelMove();

    if(mouseWheelPos < 0){
        camera.zoom -= 0.05f;
    }
    else if(mouseWheelPos > 0){
        camera.zoom += 0.05f;
    }

    if(IsKeyDown(KEY_A)){
        camera.target.x -= 1.5f;
    }
    if(IsKeyDown(KEY_D)){
        camera.target.x += 1.5f;
    }
    if(IsKeyDown(KEY_W)){
        camera.target.y -= 1.5f;
    }
    if(IsKeyDown(KEY_S)){
        camera.target.y += 1.5f;
    }
}

void GameState::HandleMouseClick(int gridX, int gridY){
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        PlaceObject(gridX, gridY, selectedItemID);
    }
    else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        RemoveObject(gridX, gridY);
    }
}

void GameState::PlaceObject(int gridX, int gridY, const ContentID& objectID){
    if(objectID == ContentID::None) return;
    if(!ObjectRegistry::IsPlaceable(objectID)) return;
    if(map.HasObject(gridX, gridY)) return;

    std::shared_ptr<Object> object = ObjectRegistry::Create(objectID);
    map.SetObject(gridX, gridY, object);
}

void GameState::RemoveObject(int gridX, int gridY){
    if(!map.HasObject(gridX, gridY)) return;

    map.SetObject(gridX, gridY, nullptr);
}

void GameState::InitTextures(){
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
