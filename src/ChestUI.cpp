#include "ChestUI.h"

void ChestUI::Init(Window& window){
    this->texture = TextureManager::GetTexture("CHEST_INVENTORY_UI");

    this->x = (window.GetSize().x / 2.0f) - ((float)texture.width / 2.0f);
    this->y = (window.GetSize().y / 2.0f) - ((float)texture.height / 2.0f);

    inventorySize = 14;
    open = false;
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

void ChestUI::Update(){
    HandleSlots();

    for(int i = 0; i < inventorySize; i++){
        slots[i].Update();

        currentChest->SetItem(slots[i].GetItem(), slots[i].GetQuantity(), i);
    }
}

void ChestUI::Render() const{
    DrawTexture(this->texture, x, y, RAYWHITE);

    RenderSlots();

    for(auto& slot : slots){
        slot.Render();
    }
}