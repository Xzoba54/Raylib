#include "Wall.h"

Wall::Wall(){
    this->objectID = ContentID::Wall;

    this->texture = TextureManager::GetTexture("WALL");
    this->textureSize = {(float)texture.width, (float)texture.height};
}

void Wall::Update(){

}

void Wall::Render() const{
    DrawTexture(this->texture, position.x, position.y, RAYWHITE);
}