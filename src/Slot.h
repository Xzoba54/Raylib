#pragma once

#include "raylib.h"
#include "TextureManager.h"
#include "ItemRegister.h"

class Slot{
public:
    Slot() = default;
    Slot(int x, int y, int size);

    void Update();
    void Render() const;

    void BindData(InventorySlot* data);

    InventorySlot* GetData();

    Rectangle GetRec() const;

private:
    void UpdateTexture();
    void UpdateText();

    Vector2 position;
    Vector2 textPos;
    Vector2 texturePosition;

    Texture2D texture;

    int slotSize;

    int fontSize;
    float textPadding;

    InventorySlot* data;
};