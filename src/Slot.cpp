#include "Slot.h"

Slot::Slot(int screenX, int screenY, const ContentID& itemID){
    this->position = {(float)screenX, (float)screenY};
    this->itemID = itemID;

    const ItemDef& item = ItemRegistry::Get(itemID);
    this->texture = TextureManager::GetTexture(item.textureName);

    this->slotSize = 40;
    this->selected = false;

    this->hoverRec = {position.x, position.y, (float)slotSize, (float)slotSize};

    this->colorIdle = {0, 0, 0, 30};
    this->colorHover = {100, 100, 100, 150};
    this->currentColor = colorIdle;

    this->texturePosition = {
        position.x + (slotSize / 2.0f) - (texture.width / 2.0f),
        position.y + (slotSize / 2.0f) - (texture.height / 2.0f)
    };
}

void Slot::Update(){
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, hoverRec)){
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
    DrawRectangleRec(hoverRec, currentColor);

    DrawTexture(this->texture, texturePosition.x, texturePosition.y, RAYWHITE);
}

ContentID& Slot::GetSelectedItem(){
    return itemID;
}

bool Slot::IsSelected() const{
    return selected;
}
