#pragma once

#include "TextureManager.h"
#include <vector>

enum class PlayerState{
    IDLE,
    WALK
};

class Player{
public:
    Player() = default;

    void Update();
    void Render() const;

    void ProcessInput();

    Vector2& GetPosition();
    Vector2 GetPositionCenter();
    Vector2 GetMovement();
    int GetHeight();

    void SetPosition(float x, float y);

    //TEMP
    int GetHitboxOffsetY() { return hitboxOffsetY; };

    void Move(Vector2 delta);

    Rectangle GetRec();
    Rectangle GetPhysicalRec();

    void Init(int x, int y);
private:
    Texture2D texture;
    Vector2 position;

    int currentFrame = 0;
    float frameTime = 0.10f;
    float timer = 0.0f;

    float hitboxWidth;
    float hitboxHeight;
    float hitboxOffsetX;
    float hitboxOffsetY;

    Vector2 movement;

    std::vector<Texture2D> frames;
    PlayerState playerState;
};