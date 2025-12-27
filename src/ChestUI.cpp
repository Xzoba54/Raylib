#include "ChestUI.h"

void ChestUI::Update(){
    for(auto& slot : slots){
        slot.Update();
    }
}

void ChestUI::Render() const{
    DrawTexture(texture, x, y, RAYWHITE);

    for(auto& slot : slots){
        slot.Render();
    }
}

void ChestUI::Init(Window& window){
    this->texture = TextureManager::GetTexture("CHEST_INVENTORY_UI");

    this->open = false;

    this->x = (window.GetSize().x / 2.0f) - ((float)texture.width / 2.0f);
    this->y = (window.GetSize().y / 2.0f) - ((float)texture.height / 2.0f);

    this->inventorySize = 14;
    this->slotsPerRow = 6;
    this->slotSize = 40;
    this->slotPadding = 5;

    this->headerMargin = 27;

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
    this->open = true;

    for(int i = 0; i < inventorySize; i++){
        ContentID id = chest->GetSlot(i).id;
        slots[i].SetItem(id);
    }
}

void ChestUI::Close(){
    this->currentChest = nullptr;
    this->open = false;
}

Rectangle ChestUI::GetRec(){
    Rectangle rec = {x, y, (float)(texture.width), (float)(texture.height)};

    return rec;
}

bool ChestUI::IsOpen() const{
    return this->open;
}
