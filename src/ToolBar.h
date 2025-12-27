#pragma once

#include "raylib.h"
#include <vector>
#include "Slot.h"
#include <memory>
#include "TextureManager.h"
#include "ItemRegister.h"

class ToolBar{
public:
    ToolBar() = default;

    void Update();
    void Render() const;

    Rectangle GetRec();

    ContentID& GetSelectedItem();

    void Init();
private:
    void AddItemAt(int slot, const ContentID& itemID);

    Texture2D texture;

    float x;
    float y;

    int bottomMargin;

    int slotsSize;

    std::vector<Slot> slots;

    ContentID selectedItemID;
};