#include "ToolBar.h"

void ToolBar::Init(){
    this->texture = TextureManager::GetTexture("TOOLBAR");
    this->bottomMargin = 30;
    this->slotsSize = 2;

    this->position = {
        (float)GetScreenWidth() / 2.0f - ((float)texture.width / 2.0f), 
        (float)GetScreenHeight() - texture.height - bottomMargin
    };

    this->slots.resize(slotsSize);
    this->AddItemAt(0, ContentID::Pickaxe);
    this->AddItemAt(1, ContentID::Chest);
}

Rectangle ToolBar::GetRec()
{
    Rectangle rec = {position.x, position.y, (float)texture.width, (float)texture.height};

    return rec;
}

ContentID &ToolBar::GetSelectedItem(){
    return selectedItemID;
}


void ToolBar::AddItemAt(int slot, const ContentID& itemID){
    slots[slot] = std::make_unique<Slot>(slot * 40 + slot * 5 + position.x + 5, position.y + 5, itemID);
}


void ToolBar::Update(){
    for(auto& slot : slots){
        if(slot == nullptr){
            break;
        }

        slot->Update();
        if(slot->IsSelected()){
            selectedItemID = slot->GetSelectedItem();
        }
    }
}

void ToolBar::Render() const{
    DrawTexture(this->texture, position.x, position.y, RAYWHITE);

    for(auto& slot : slots){
        if(slot){
            slot->Render();
        }
    }
}