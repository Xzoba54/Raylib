#include "Slime.h"

Slime::Slime(int x, int y)
{
    this->pos = {(float)x, (float)y};
    frames.resize(4);

    this->frames[0] = LoadTexture("slime1.png");
    this->frames[1] = LoadTexture("slime2.png");
    this->frames[2] = LoadTexture("slime3.png");
    this->frames[3] = LoadTexture("slime4.png");

    PickRandomNeighbor();
}

void Slime::Update(){
    timer += GetFrameTime();

    if(timer >= frameTime){
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % 4;
    }

    if(!moving){
        PickRandomNeighbor();
    }
    else{
        Vector2 dir = Vector2Subtract(targetTileWorldPos, pos);
        float dist = Vector2Length(dir);

        if(dist > 1.0f){
            dir = Vector2Normalize(dir);
            pos = Vector2Add(pos, Vector2Scale(dir, 0.05f));
        }else{
            moving = false;
        }
    }
}

void Slime::Render() const{
    DrawTexture(frames[currentFrame], pos.x, pos.y, RAYWHITE);
}

void Slime::PickRandomNeighbor(){
    int index = std::rand() % 8;

    Vector2 currentTile = { floor(pos.x / 32), floor(pos.y / 32) };
    Vector2 nextTile = { currentTile.x + dirs[index].x,
                         currentTile.y + dirs[index].y };

    targetTileWorldPos = {
        nextTile.x * 32 + 32/2,
        nextTile.y * 32 + 32/2
    };

    moving = true;
}