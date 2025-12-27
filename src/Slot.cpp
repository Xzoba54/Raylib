#include "Slot.h"

Slot::Slot(int x, int y, int size){
    this->position = {(float)x, (float)y};
    this->slotSize = size;
    this->itemID = ContentID::None;
    this->selected = false;

    this->rect = {position.x, position.y, (float)slotSize, (float)slotSize};

    colorIdle = {62, 62, 62, 255};
    colorHover = {80, 80, 80, 255};
    currentColor = colorIdle;
}

void Slot::Update()
{
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, rect)){
        this->currentColor = colorHover;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            this->selected = true;
        }
    }else{
        this->currentColor = colorIdle;
        this->selected = false;
    }
}

void Slot::Render() const{
    DrawRectangleRec(rect, currentColor);

    if(itemID != ContentID::None){
        DrawTexture(texture, texturePosition.x, texturePosition.y, RAYWHITE);
    }
}

void Slot::SetItem(ContentID itemID){
    this->itemID = itemID;
    
    UpdateTexture();
}

ContentID Slot::GetItem() const{
    return itemID;
}

bool Slot::IsSelected() const{
    return selected;
}

void Slot::UpdateTexture(){
    if(itemID != ContentID::None){
        const ItemDef& item = ItemRegistry::Get(itemID);
        this->texture = TextureManager::GetTexture(item.textureName);

        this->texturePosition.x = position.x + (slotSize / 2.0f) - ((float)texture.width / 2.0f);
        this->texturePosition.y = position.y + (slotSize / 2.0f) - ((float)texture.height / 2.0f);
    }
}
