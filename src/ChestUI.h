#pragma once

#include "raylib.h"
#include "TextureManager.h"
#include <memory>
#include "Chest.h"
#include "Window.h"
#include "Slot.h"

class ChestUI {
public:
    ChestUI() = default;

    void Update();
    void Render() const;

    void Init(Window& window);

    void Open(std::shared_ptr<Chest> chest);
    void Close();

    Rectangle GetRec();

    bool IsOpen() const;
private:
    Texture2D texture;

    float x;
    float y;

    std::shared_ptr<Chest> currentChest;

    int inventorySize;
    int slotsPerRow;

    int slotSize;
    int slotPadding;
    int headerMargin;

    std::vector<Slot> slots;

    bool open;
};