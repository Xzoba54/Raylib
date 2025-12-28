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

    void SetItem(ContentID itemID, int quantity);

    ContentID GetItem() const;
    Rectangle GetRec() const;

private:
    void UpdateTexture();
    void UpdateText();

    Vector2 position;
    Vector2 texturePosition;

    int slotSize;

    ContentID itemID;
    Texture2D texture;
    int quantity;

    Vector2 textPos;
    int fontSize;
    float textPadding;
};