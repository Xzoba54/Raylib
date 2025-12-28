#include "ToolBar.h"

void ToolBar::Init(){
    this->texture = TextureManager::GetTexture("TOOLBAR");
    this->bottomMargin = 30;
    this->slotsSize = 2;
    open = true;
    
    this->hoveredSlot = -1;
    this->selectedSlot = -1;
    this->colorHover = {80, 80, 80, 255};

    this->x = (GetScreenWidth() / 2.0f) - ((float)texture.width / 2.0f);
    this->y = ((float)GetScreenHeight()) - (texture.height + bottomMargin);

    slots.clear();
    slots.resize(slotsSize);

    for(int i = 0; i < slotsSize; i++){
        int slotX = x + i * 40 + (i + 1) * 5;
        int slotY = y + 5;

        slots[i] = Slot(slotX, slotY, 40);
    }

    this->AddItemAt(0, ContentID::Wall);
    this->AddItemAt(1, ContentID::Chest);
}

int ToolBar::GetSlotIndexAt(const Vector2 &mouse){
    for(int i = 0; i < slotsSize; i++){
        if(CheckCollisionPointRec(mouse, slots[i].GetRec())){
            return i;
        }
    }

    return -1;
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
    hoveredSlot = GetSlotIndexAt(GetMousePosition());

    if(hoveredSlot != -1){
        hoverRec = slots[hoveredSlot].GetRec();
    }

    if(hoveredSlot != -1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        selectedSlot = hoveredSlot;
    }

    for(Slot& slot : slots){
        slot.Update();
    }
}

void ToolBar::Render() const{
    DrawTexture(this->texture, x, y, RAYWHITE);

    if(hoveredSlot != -1){
        DrawRectangleRec(hoverRec, colorHover);
    }

    for(auto& slot : slots){
        slot.Render();
    }
}