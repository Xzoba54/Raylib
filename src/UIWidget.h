#pragma once

#include "raylib.h"
#include "Slot.h"
#include <vector>

class UIWidget{ 
public:
    UIWidget();
    virtual ~UIWidget() = default;

    virtual void Update() = 0;
    virtual void Render() const = 0;

    virtual Rectangle GetRec() const = 0;

    virtual void Open() { this->open = true; }
    virtual void Close() { this->open = false; }

    bool IsOpen() const { return this->open; }
protected:
    void HandleSlots();
    void RenderSlots() const;

    Color colorSlotHover;
    Rectangle hoverRec;

    int hoveredSlot;
    int selectedSlot;
    int slotDragging;

    bool open;

    int inventorySize;

    std::vector<Slot> slots;
    InventorySlot dragging;
private:
    int GetSlotIndexAt(const Vector2& mouse);
};