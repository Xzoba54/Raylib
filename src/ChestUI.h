#pragma once

#include "UIWidget.h"
#include "TextureManager.h"
#include <memory>
#include "Chest.h"
#include "Window.h"
#include "Slot.h"

class ChestUI : public UIWidget{
public:
    ChestUI() = default;

    void Update() override;
    void Render() const override;

    void Init(Window& window);

    void Open(std::shared_ptr<Chest> chest);

    Rectangle GetRec() const override;
private:
    int GetSlotIndexAt(const Vector2& mouse);

    Texture2D texture;
    Color colorHover;

    Rectangle hoverRec;
    int hoveredSlot;

    float x;
    float y;

    int inventorySize;
    int slotsPerRow;

    int slotSize;
    int slotPadding;
    int headerMargin;

    std::vector<Slot> slots;
    std::shared_ptr<Chest> currentChest;
};