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
    map.Render();
    slime->Render();
    EndMode2D();

    //render UI
    toolbar.Render();
    
    if(chestUI.IsOpen()){
        chestUI.Render();
    }
}

void GameState::HandleCameraInput(){
    float wheel = GetMouseWheelMove();
    camera.zoom += wheel * 0.05f;

    if(IsKeyDown(KEY_A)) camera.target.x -= 1.5f;
    if(IsKeyDown(KEY_D)) camera.target.x += 1.5f;
    if(IsKeyDown(KEY_W)) camera.target.y -= 1.5f;
    if(IsKeyDown(KEY_S)) camera.target.y += 1.5f;
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

    if(id == ContentID::Chest){
        std::shared_ptr<Chest> chest = std::dynamic_pointer_cast<Chest>(map.GetObject(gridX, gridY));

        if(chestUI.IsOpen()){
            chestUI.Close();
        }
        else{
            chestUI.Open(chest);
        }
    }
}

void GameState::HandleMouseClickRight(){
    map.RemoveObject(gridX, gridY);
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

void GameState::ProcessInput(){
    HandleCameraInput();

    if(chestUI.IsOpen() && IsKeyPressed(KEY_ESCAPE)){
        chestUI.Close();
    }
}
