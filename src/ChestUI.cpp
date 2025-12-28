#include "ChestUI.h"

void ChestUI::Init(Window& window){
    this->texture = TextureManager::GetTexture("CHEST_INVENTORY_UI");
    this->colorHover = {80, 80, 80, 255};

    this->x = (window.GetSize().x / 2.0f) - ((float)texture.width / 2.0f);
    this->y = (window.GetSize().y / 2.0f) - ((float)texture.height / 2.0f);

    this->inventorySize = 14;
    this->slotsPerRow = 6;

    this->slotSize = 40;
    this->slotPadding = 5;
    this->headerMargin = 27;

    this->hoveredSlot = -1;

    int rows = std::ceil((float)inventorySize / float(slotsPerRow));

    slots.clear();
    slots.resize(inventorySize);

    for(int i = 0; i < inventorySize; i++){
        int col = i % slotsPerRow;
        int row = i / slotsPerRow;

        float slotX = x + slotPadding + col * (slotSize + slotPadding);
        float slotY = y + headerMargin + slotPadding + row * (slotSize + slotPadding);

        slots[i] = Slot(slotX, slotY, slotSize);
    }
}

void ChestUI::Open(std::shared_ptr<Chest> chest){
    this->currentChest = chest;
    open = true;

    for(int i = 0; i < inventorySize; i++){
        ContentID id = chest->GetSlot(i).id;
        int quantity = chest->GetSlot(i).quantity;
        slots[i].SetItem(id, quantity);
    }
}

Rectangle ChestUI::GetRec() const{
    Rectangle rec = {x, y, (float)(texture.width), (float)(texture.height)};

    return rec;
}

int ChestUI::GetSlotIndexAt(const Vector2 &mouse){
    for(int i = 0; i < inventorySize; i++){
        if(CheckCollisionPointRec(mouse, slots[i].GetRec())){
            return i;
        }
    }

    return -1;
}

void ChestUI::Update(){
    hoveredSlot = GetSlotIndexAt(GetMousePosition());

    if(hoveredSlot != -1){
        hoverRec = slots[hoveredSlot].GetRec();
    }

    for(Slot& slot : slots){
        slot.Update();
    }
}

void ChestUI::Render() const{
    DrawTexture(texture, x, y, RAYWHITE);

    if(hoveredSlot != -1){
        DrawRectangleRec(hoverRec, colorHover);
    }

    for(auto& slot : slots){
        slot.Render();
    }
}