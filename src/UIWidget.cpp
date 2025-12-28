#include "UIWidget.h"

UIWidget::UIWidget(){
    this->colorSlotHover = {80, 80, 80, 255};
    this->hoveredSlot = -1;
    this->selectedSlot = -1;
    this->open = false;
    this->slotDragging = true;
}

void UIWidget::HandleSlots(){
    hoveredSlot = GetSlotIndexAt(GetMousePosition());

    if(hoveredSlot != -1){
        hoverRec = slots[hoveredSlot].GetRec();
    }

    if(hoveredSlot != -1 && selectedSlot != -1 && slotDragging && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && slots[hoveredSlot].GetItem() == ContentID::None){
        slots[hoveredSlot].SetItem(dragging.id, dragging.quantity);

        selectedSlot = -1;
        return;
    }

    if(selectedSlot == -1 && hoveredSlot != -1 && slots[hoveredSlot].GetItem() != ContentID::None && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        selectedSlot = hoveredSlot;
        std::cout << (int)slots[selectedSlot].GetItem();

        if(!slotDragging) return;

        dragging = {slots[selectedSlot].GetItem(), slots[selectedSlot].GetQuantity()};
        slots[selectedSlot].SetItem(ContentID::None, 0);
    }
}

void UIWidget::RenderSlots() const{
    if(hoveredSlot != -1){
        DrawRectangleRec(hoverRec, colorSlotHover);
    }

    if(selectedSlot != -1 && slotDragging){
        Texture2D tex = TextureManager::GetTexture(ItemRegistry::Get(dragging.id).textureName);
        Vector2 mouse = GetMousePosition(); 

        DrawTexture(tex, mouse.x, mouse.y, RAYWHITE);
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
