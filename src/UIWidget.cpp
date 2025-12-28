#include "UIWidget.h"

UIWidget::UIWidget(){
    this->colorSlotHover = {80, 80, 80, 255};
    this->hoveredSlot = -1;
    this->selectedSlot = -1;
    this->open = false;
    this->canDrag = true;
}

void UIWidget::CancelDrag(){
    if(drag.src){
        *drag.src = drag.item;
    }

    drag.src = nullptr;
}

void UIWidget::HandleSlots()
{
    hoveredSlot = GetSlotIndexAt(GetMousePosition());

    if(hoveredSlot != -1){
        hoverRec = slots[hoveredSlot].GetRec();
    }

    if(!canDrag && hoveredSlot != -1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        InventorySlot* src = slots[hoveredSlot].GetData();

        if(drag.src == src){
            drag.src = nullptr;
        }
        else{
            drag.src = src;
            drag.item = *src;
        }

        return;
    }

    if(hoveredSlot != -1 && !drag.src && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) TakeItem();
    else if(hoveredSlot != -1 && drag.src && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) PlaceItem();
}

void UIWidget::RenderSlots() const{
    if(hoveredSlot != -1){
        DrawRectangleRec(hoverRec, colorSlotHover);
    }

    if(drag.src){
        Texture2D tex = TextureManager::GetTexture(ItemRegistry::Get(drag.item.id).textureName);
        Vector2 mouse = GetMousePosition(); 

        DrawTexture(tex, mouse.x, mouse.y, RAYWHITE);

        if(canDrag){
            float textX = mouse.x + tex.width;
            float textY = mouse.y + tex.height;
            DrawText(std::to_string(drag.item.quantity).c_str(), textX, textY, 4, RAYWHITE);
        }
    }
}

int UIWidget::GetSlotIndexAt(const Vector2 &mouse){
    for(int i = 0; i < inventorySize; i++){
        if(CheckCollisionPointRec(mouse, slots[i].GetRec())){
            return i;
        }
    }

    return -1;
}

void UIWidget::TakeItem(){
    if(slots[hoveredSlot].GetData()->id == ContentID::None) return;

    InventorySlot* src = slots[hoveredSlot].GetData();

    drag.src = src;
    drag.item = *src;

    if(canDrag){
        drag.src->id = ContentID::None;
        drag.src->quantity = 0;
    }
}

void UIWidget::PlaceItem(){
    if(slots[hoveredSlot].GetData()->id != ContentID::None) return;

    InventorySlot* target = slots[hoveredSlot].GetData();

    target->id = drag.item.id;
    target->quantity = drag.item.quantity;

    drag.src = nullptr;
    slots[hoveredSlot].Update();
}
