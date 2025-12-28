#include "Slot.h"

Slot::Slot(int x, int y, int size){
    this->position = {(float)x, (float)y};
    this->slotSize = size;
    this->itemID = ContentID::None;
    this->fontSize = 4;
    this->textPadding = 3;
}

void Slot::Update(){

}

void Slot::Render() const{
    if(itemID != ContentID::None){
        DrawTexture(texture, texturePosition.x, texturePosition.y, RAYWHITE);

        if(quantity != 0){
            DrawText(std::to_string(quantity).c_str(), textPos.x, textPos.y, fontSize, RAYWHITE);
        }
    }
}

void Slot::SetItem(ContentID itemID, int quantity){
    this->itemID = itemID;
    this->quantity = quantity;
    
    UpdateTexture();
    UpdateText();
}

ContentID Slot::GetItem() const{
    return itemID;
}

Rectangle Slot::GetRec() const{
    Rectangle rec = {position.x, position.y, (float)slotSize, (float)slotSize};

    return rec;
}

void Slot::UpdateText(){
    int textWidth = MeasureText(std::to_string(quantity).c_str(), fontSize);

    textPos = {
        position.x + slotSize - textWidth - textPadding,
        position.y + slotSize - 2*fontSize - textPadding
    };
}

void Slot::UpdateTexture(){
    if(itemID != ContentID::None){
        const ItemDef& item = ItemRegistry::Get(itemID);
        this->texture = TextureManager::GetTexture(item.textureName);

        this->texturePosition.x = position.x + (slotSize / 2.0f) - ((float)texture.width / 2.0f);
        this->texturePosition.y = position.y + (slotSize / 2.0f) - ((float)texture.height / 2.0f);
    }
}
