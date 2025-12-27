#include "ToolBar.h"

void ToolBar::Init(){
    this->texture = TextureManager::GetTexture("TOOLBAR");
    this->bottomMargin = 30;
    this->slotsSize = 2;

    this->x = (GetScreenWidth() / 2.0f) - ((float)texture.width / 2.0f);
    this->y = ((float)GetScreenHeight()) - (texture.height + bottomMargin);

    slots.clear();
    slots.resize(slotsSize);

    for(int i = 0; i < slotsSize; i++){
        int slotX = x + i * 40 + (i + 1) * 5;
        int slotY = y + 5;

        slots[i] = Slot(slotX, slotY, 40);
    }

    this->AddItemAt(0, ContentID::Pickaxe);
    this->AddItemAt(1, ContentID::Chest);
}

Rectangle ToolBar::GetRec()
{
    Rectangle rec = {x, y, (float)texture.width, (float)texture.height};

    return rec;
}

ContentID &ToolBar::GetSelectedItem(){
    return selectedItemID;
}


void ToolBar::AddItemAt(int slot, const ContentID& itemID){
    slots[slot].SetItem(itemID);
}


void ToolBar::Update(){
    for(auto& slot : slots){
        slot.Update();

        if(slot.IsSelected()){
            selectedItemID = slot.GetItem();
        }
    }
}

void ToolBar::Render() const{
    DrawTexture(this->texture, x, y, RAYWHITE);

    for(auto& slot : slots){
        slot.Render();
    }
}