#include "Slot.h"

Slot::Slot(int x, int y, int size){
    this->position = {(float)x, (float)y};
    this->slotSize = size;
    this->fontSize = 4;
    this->textPadding = 3;
    this->data = nullptr;
}

void Slot::Update(){
    if(!data) return;

    UpdateTexture();
    UpdateText();
}

void Slot::Render() const{
    if(!data) return;
    if(data->id == ContentID::None) return;

    DrawTexture(texture, texturePosition.x, texturePosition.y, RAYWHITE);

    if(data->quantity != 0){
        DrawText(std::to_string(data->quantity).c_str(), textPos.x, textPos.y, fontSize, RAYWHITE);
    }
}

void Slot::BindData(InventorySlot *data){
    this->data = data;

    Update();
}

InventorySlot *Slot::GetData(){
    return this->data;
}

Rectangle Slot::GetRec() const{
    Rectangle rec = {position.x, position.y, (float)slotSize, (float)slotSize};

    return rec;
}

void Slot::UpdateText(){
    int textWidth = MeasureText(std::to_string(data->quantity).c_str(), fontSize);

    textPos = {
        position.x + slotSize - textWidth - textPadding,
        position.y + slotSize - 2*fontSize - textPadding
    };
}

void Slot::UpdateTexture(){
    if(data->id == ContentID::None) return;

    const ItemDef& item = ItemRegistry::Get(data->id);
    texture = TextureManager::GetTexture(item.textureName);

    texturePosition.x = position.x + (slotSize / 2.0f) - ((float)texture.width / 2.0f);
    texturePosition.y = position.y + (slotSize / 2.0f) - ((float)texture.height / 2.0f);
}
