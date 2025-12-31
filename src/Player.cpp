#include "Player.h"

void Player::Update(){
    playerState = PlayerState::IDLE;

    if(IsKeyDown(KEY_A)) {
        playerState = PlayerState::WALK;
        position.x -= 1;
    }
    if(IsKeyDown(KEY_D)) {
        playerState = PlayerState::WALK;
        position.x += 1;
    }
    if(IsKeyDown(KEY_W)) {
        playerState = PlayerState::WALK;
        position.y -= 1;
    }
    if(IsKeyDown(KEY_S)) {
        playerState = PlayerState::WALK;
        position.y += 1;
    }

    if(playerState == PlayerState::WALK){
        timer += GetFrameTime();
    }

    if(timer >= frameTime){
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % 4;
    }

    if(IsKeyPressed(KEY_Q)){
        frameTime -= 0.02f;
    }
    if(IsKeyPressed(KEY_E)){
        frameTime += 0.02f;
    }

    if(IsKeyPressed(KEY_T)){
        std::cout << frameTime << "\n";
    }
}

void Player::Render() const{
    if(playerState == PlayerState::IDLE){
        DrawTexture(frames[0], position.x, position.y, RAYWHITE);
    }
    else{
        DrawTexture(frames[currentFrame], position.x, position.y, RAYWHITE);
    }
}

void Player::ProcessInput(){
    movement = {0, 0};
    float speed = 1.0f;

    if(IsKeyDown(KEY_A)) movement.x -= speed;
    if(IsKeyDown(KEY_D)) movement.x += speed;
    if(IsKeyDown(KEY_W)) movement.y -= speed;
    if(IsKeyDown(KEY_S)) movement.y += speed;
        
}

Vector2 &Player::GetPosition(){
    return position;
}

Vector2 Player::GetMovement(){
    return movement;
}

int Player::GetHeight(){
    return frames[0].height;
}

void Player::Move(Vector2 delta){
    position = {position.x + delta.x, position.y + delta.y};
}

Rectangle Player::GetRec(){
    return {position.x + hitboxOffsetX, position.y + hitboxOffsetY, hitboxWidth, hitboxHeight };
}

Rectangle Player::GetPhysicalRec(){
    return {position.x, position.y, (float)texture.width, (float)texture.height};
}

void Player::Init(int x, int y){
    this->texture = TextureManager::GetTexture("PLAYER");
    this->position = {(float)x, (float)y};

    this->playerState = PlayerState::IDLE;

    this->hitboxWidth = 9;
    this->hitboxHeight = 4; //ewentualnie 3 ale wtedy daj 28 offsetY
    this->hitboxOffsetX = 7;
    this->hitboxOffsetY = 28;

    frames.resize(4);

    frames[0] = LoadTexture("assets/player.png");
    frames[1] = LoadTexture("assets/player2.png");
    frames[2] = LoadTexture("assets/player3.png");
    frames[3] = LoadTexture("assets/player4.png");
}
