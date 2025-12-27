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

    Vector2 position;

    int bottomMargin;

    int slotsSize;

    std::vector<std::unique_ptr<Slot>> slots;

    ContentID selectedItemID;
};