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

    void SetItem(ContentID itemID);

    ContentID GetItem() const;

    bool IsSelected() const;

private:
    void UpdateTexture();

    Vector2 position;
    Vector2 texturePosition;

    int slotSize;

    ContentID itemID;
    Texture2D texture;

    Rectangle rect;

    Color colorIdle;
    Color colorHover;
    Color currentColor;

    bool selected;
};