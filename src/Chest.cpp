#include "Chest.h"

Chest::Chest(){
    this->texture = TextureManager::GetTexture("CHEST");
    this->position = {64, 64};

    this->inventorySize = 18;
    this->slotsPerInventoryRow = 6;

    this->inventoryHeight = std::ceil((float)inventorySize / float(slotsPerInventoryRow));
}

// void Chest::SetItem(const ItemDef &item, int quantity){
//     int i = 0;
//     while(inventory[i].quantity != 0 && i <= inventorySize){
//         i++;
//     }

//     //Not found
//     if(i != inventorySize){
//         inventory[i] = {item, quantity};
//     }
// }

// void Chest::SetItem(const ItemDef &item, int quantity, int x, int y){
//     inventory[y * slotsPerInventoryRow + x] = {item, quantity};
// }


void Chest::Update()
{
}

void Chest::Render() const{
    DrawTexture(texture, position.x, position.y, RAYWHITE);
}