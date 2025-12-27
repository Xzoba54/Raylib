#pragma once

#include "Tile.h"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "TextureManager.h"
#include "Chest.h"
#include "ObjectRegistry.h"

constexpr int TILESIZE = 32;

constexpr const char* IDToNames[] = {
    "EMPTY",
    "GRASS",
    "DIRT",
    "PLOWED",
    "IRON",
    "ROCKS"
};

class TileMap{
public:
    TileMap() = default;

    void Render();
    void Update(const Vector2& mousePos);

    void Init();

    void SetObject(int x, int y, const std::shared_ptr<Object>& object);
    bool HasObject(int x, int y) const;
    bool IsValidPosition(int x, int y) const;

    void LoadMapFromFile();
private:
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;

    std::fstream stream;

    int width;
    int height;

    Rectangle hoverRec;
};