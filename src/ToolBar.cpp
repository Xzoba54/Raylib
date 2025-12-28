#include "ToolBar.h"

void ToolBar::Init(){
    this->texture = TextureManager::GetTexture("TOOLBAR");
    this->bottomMargin = 30;
    inventorySize = 2;
    open = true;
    slotDragging = false;

    this->x = (GetScreenWidth() / 2.0f) - ((float)texture.width / 2.0f);
    this->y = ((float)GetScreenHeight()) - (texture.height + bottomMargin);

    slots.clear();
    slots.resize(inventorySize);

    for(int i = 0; i < inventorySize; i++){
        int slotX = x + i * 40 + (i + 1) * 5;
        int slotY = y + 5;

        slots[i] = Slot(slotX, slotY, 40);
    }

    this->AddItemAt(0, ContentID::Wall);
    this->AddItemAt(1, ContentID::Chest);
}

Rectangle ToolBar::GetRec() const{
    Rectangle rec = {x, y, (float)texture.width, (float)texture.height};

    return rec;
}


ContentID ToolBar::GetSelectedItem(){
    if(selectedSlot != -1){
        return slots[selectedSlot].GetItem();
    }

    return ContentID::None;
}


void ToolBar::AddItemAt(int slot, const ContentID& itemID){
    slots[slot].SetItem(itemID, 0);
}


void ToolBar::Update(){
    HandleSlots();

    for(Slot& slot : slots){
        slot.Update();
    }
}

void ToolBar::Render() const{
    DrawTexture(this->texture, x, y, RAYWHITE);
    
    RenderSlots();

    for(auto& slot : slots){
        slot.Render();
    }
}