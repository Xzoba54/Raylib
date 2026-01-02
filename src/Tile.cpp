#include "Tile.h"

Tile::Tile(int x, int y, GroundID id){
    this->position = {static_cast<float>(x), static_cast<float>(y)};
    this->groundID = id;

    this->texture = TextureManager::GetTexture(groundID);
}

void Tile::Render() const
{
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Tile::RenderObject(){
    if(!object) return;
    
    object->Render();
}

void Tile::SetObject(const std::shared_ptr<Object> &obj)
{
    this->object = obj;
    if(this->object){
        this->object->SetWorldPosition(position);
    }
}

ContentID Tile::GetType() const{
    return object->GetType();
}

GroundID Tile::GetGroundID() const{
    return groundID;
}
