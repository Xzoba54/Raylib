#pragma once

#include "Object.h"
#include "TextureManager.h"
#include "ItemRegister.h"
#include <vector>
#include <cmath>

class Chest : public Object{
public:
    Chest();

    void Update() override;
    void Render() const override;

    void SetItem(const ContentID& itemID, int quantity, int index);
    void SetItem(const ContentID& itemID, int quantity, int x, int y);

    InventorySlot& GetSlot(int x, int y);
    InventorySlot& GetSlot(int index);
private:
    Texture2D texture;

    int inventorySize;
    int slotsPerInventoryRow;

    int inventoryHeight;

    std::vector<InventorySlot> inventory;
};