#include "Tile.h"

Tile::Tile(int x, int y, const Texture2D& texture) :
    position{(float)x, (float)y}, texture(texture)
{
}

void Tile::Render() const
{
    DrawTexture(texture, position.x, position.y, WHITE);
    if(this->object){
        this->object->Render();
    }
}

void Tile::SetObject(const std::shared_ptr<Object>& obj){
    this->object = obj;
    if(this->object){
        this->object->SetWorldPosition(position);
    }
}
