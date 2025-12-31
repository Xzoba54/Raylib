#include "Tile.h"

Tile::Tile(int x, int y, const Texture2D& texture) :
    position{(float)x, (float)y}, texture(texture)
{
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

ContentID Tile::GetObjectID() const{
    return object->GetObjectID();
}
