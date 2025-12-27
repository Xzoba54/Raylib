#pragma once
#include <cstdint>

enum class ContentID : uint16_t {
    None = 0,
    //objects
    Chest,
    Wall,

    //items (that aren't overlaping with objects)
    Pickaxe,

    COUNT
};

struct InventorySlot{
    ContentID id = ContentID::None;
    int quantity = 0;
};