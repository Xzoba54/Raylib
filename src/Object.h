#pragma once

#include "raylib.h"

class Object{
public:
    virtual ~Object() = default;

    virtual void Update() = 0;
    virtual void Render() const = 0;

    void SetWorldPosition(Vector2 pos) { this->position = pos; }


protected:
    Vector2 position = {0, 0};
};