#include "Chest.h"

Chest::Chest(){
    this->objectID = ContentID::Chest;

    this->texture = TextureManager::GetTexture("CHEST");
    this->position = {64, 64};

    this->inventorySize = 14;
    this->slotsPerInventoryRow = 6;

    inventory.resize(inventorySize);

    this->inventoryHeight = std::ceil((float)inventorySize / float(slotsPerInventoryRow));
}

void Chest::SetItem(const ContentID &itemID, int quantity, int index){
    inventory[index] = {itemID, quantity};
}

void Chest::SetItem(const ContentID &itemID, int quantity, int x, int y){
    inventory[y * slotsPerInventoryRow + x] = {itemID, quantity};
}

InventorySlot &Chest::GetSlot(int x, int y){
    return inventory[y * slotsPerInventoryRow + x];
}

InventorySlot &Chest::GetSlot(int index){
    return inventory[index];
}

void Chest::Update()
{
}

void Chest::Render() const{
    DrawTexture(texture, position.x, position.y, RAYWHITE);
}