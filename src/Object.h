#pragma once

#include "raylib.h"
#include "Register.h"
#include <vector>

class Object{
public:
    virtual ~Object() = default;

    virtual void Update() = 0;
    virtual void Render() const = 0;

    ContentID& GetObjectID() { return this->objectID; }

    Vector2& GetPosition() { return this->position; }
    Rectangle GetRec() { return {position.x + hitboxOffsetX, position.y + hitboxOffsetY, hitboxWidth, hitboxHeight}; };

    virtual void Serialize(std::vector<uint8_t>& out) const {};

    Rectangle GetPhysicalRec() { return {position.x, position.y, textureSize.x, textureSize.y}; }

    void SetWorldPosition(Vector2 pos) {
        position = {
            (pos.x + TILESIZE / 2.0f) - ((float)textureSize.x / 2.0f),
            (pos.y + TILESIZE / 2.0f) - ((float)textureSize.y / 2.0f)
        };
    }


protected:
    Vector2 textureSize;
    Vector2 position = {0, 0};

    float hitboxWidth = 0;
    float hitboxHeight = 0;
    float hitboxOffsetX = 0;
    float hitboxOffsetY = 0;

    ContentID objectID;
};