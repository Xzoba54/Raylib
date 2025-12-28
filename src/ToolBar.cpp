#include "ToolBar.h"

void ToolBar::Init(){
    this->texture = TextureManager::GetTexture("TOOLBAR");
    this->bottomMargin = 30;

    inventorySize = 2;
    open = true;
    canDrag = false;

    this->x = (GetScreenWidth() / 2.0f) - ((float)texture.width / 2.0f);
    this->y = ((float)GetScreenHeight()) - (texture.height + bottomMargin);

    slots.clear();
    slots.resize(inventorySize);

    toolbarSlots.clear();
    toolbarSlots.resize(inventorySize);

    for(int i = 0; i < inventorySize; i++){
        int slotX = x + i * 40 + (i + 1) * 5;
        int slotY = y + 5;

        slots[i] = Slot(slotX, slotY, 40);
        slots[i].BindData(&toolbarSlots[i]);
    }

    AddItem(ContentID::Wall, 0);
    AddItem(ContentID::Chest, 1);
}

void ToolBar::AddItem(const ContentID &itemID, int slot){
    toolbarSlots[slot] = {itemID, 0};
    slots[slot].Update();
}

Rectangle ToolBar::GetRec() const{
    Rectangle rec = {x, y, (float)texture.width, (float)texture.height};

    return rec;
}

ContentID ToolBar::GetSelectedItem(){
    if(drag.src){
        return drag.item.id;
    }

    return ContentID::None;
}

void ToolBar::Update(){
    HandleSlots();

    for(Slot& slot : slots){
        slot.Update();
    }
}

void ToolBar::Render() const{
    DrawTexture(texture, x, y, RAYWHITE);
    
    RenderSlots();

    for(auto& slot : slots){
        slot.Render();
    }
}