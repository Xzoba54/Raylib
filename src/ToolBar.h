#pragma once

#include "UIWidget.h"
#include "Slot.h"
#include "TextureManager.h"
#include "ItemRegister.h"
#include <vector>
#include <memory>

class ToolBar : public UIWidget{
public:
    ToolBar() = default;

    void Update() override;
    void Render() const override;

    Rectangle GetRec() const;

    ContentID GetSelectedItem();

    void Init();
private:
    void AddItem(const ContentID& itemID, int slot);

    Texture2D texture;

    float x;
    float y;

    int bottomMargin;

    std::vector<InventorySlot> toolbarSlots;
};