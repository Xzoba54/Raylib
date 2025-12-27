#pragma once

#include "Object.h"
#include "TextureManager.h"
#include "ObjectRegistry.h"
#include <vector>
#include <cmath>

class Chest : public Object{
public:
    Chest();

    void Update() override;
    void Render() const override;

    // void SetItem(const ItemDef& item, int quantity);
    // void SetItem(const ItemDef& item, int quantity, int x, int y);
private:
    Texture2D texture;

    int inventorySize;
    int slotsPerInventoryRow;

    int inventoryHeight;

    // std::vector<ItemStack> inventory;
};