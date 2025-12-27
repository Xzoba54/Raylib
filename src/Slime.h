#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

class Slime{
public:
    Slime(int x, int y);

    void Update();
    void Render() const;

    void PickRandomNeighbor();
private:
    Vector2 pos;

    int currentFrame = 0;
    float frameTime = 0.15f;
    float timer = 0.0f;

    std::vector<Texture2D> frames;

    Vector2 targetTileWorldPos;
    bool moving;

    Vector2 dirs[8] = {
        {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}
    };
};