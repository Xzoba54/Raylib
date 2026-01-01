#pragma once

#include <cstdint>

constexpr int TILESIZE = 32;

enum class GroundID : uint16_t {
    None = 0,

    Grass,
    Dirt,
    Plowed,
    Iron,
    Rocks,

    COUNT
};

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