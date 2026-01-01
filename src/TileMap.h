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
#include "Player.h"
#include <algorithm>

class TileMap{
public:
    TileMap();

    void RenderGround();
    void RenderObjectsExcept(std::vector<std::pair<int, int>> except);
    void RenderObjectAt(int x, int y);

    void Update(const Vector2& mousePos);

    void SetObject(int x, int y, ContentID objectID);
    void RemoveObject(int x, int y);

    Vector2 GetSize() const;

    bool HasObject(int x, int y) const;
    bool IsValidPosition(int x, int y) const;

    void Serialize(std::vector<uint8_t>& out) const;
    void Deserialize(int width, int height, std::vector<uint8_t> data);

    std::shared_ptr<Object> GetObject(int x, int y) const;
    ContentID GetObjectID(int x, int y) const;

    void LoadMapFromFile();
private:
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;

    std::fstream stream;

    int width;
    int height;

    Rectangle hoverRec;
};