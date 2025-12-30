#pragma once

#include "raylib.h"
#include "Object.h"
#include <memory>
#include <iostream>

class Tile{
public:
    Tile(int x, int y, const Texture2D& texture);

    void Render() const;

    //TEMP
    void RenderObject();

    void SetObject(const std::shared_ptr<Object>& obj);
    std::shared_ptr<Object>& GetObject() { return this->object; }

    ContentID GetObjectID() const;

    Vector2 GetWorldPosition() const { return this->position; }
    Rectangle GetRec() { return {position.x, position.y, TILESIZE, TILESIZE}; }
private:
    Texture2D texture;
    Vector2 position;

    std::shared_ptr<Object> object;
};