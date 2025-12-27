#pragma once

#include "raylib.h"
#include "TextureManager.h"
#include "ItemRegister.h"

class Slot{
public:
    Slot(int screenX, int screenY, const ContentID& itemID);

    void Update();
    void Render() const;

    ContentID& GetSelectedItem();

    bool IsSelected() const;
private:
    Vector2 position;
    Vector2 texturePosition;

    //temp
    ContentID itemID;
    Texture2D texture;

    int slotSize;

    Rectangle hoverRec;
    Color colorIdle;
    Color colorHover;
    Color currentColor;

    bool selected;
};