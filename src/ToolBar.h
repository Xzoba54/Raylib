#pragma once

#include "UIWidget.h"
#include <vector>
#include "Slot.h"
#include <memory>
#include "TextureManager.h"
#include "ItemRegister.h"

class ToolBar : public UIWidget{
public:
    ToolBar() = default;

    void Update() override;
    void Render() const override;

    Rectangle GetRec() const;

    ContentID GetSelectedItem();

    void Init();
private:
    void AddItemAt(int slot, const ContentID& itemID);

    Texture2D texture;

    float x;
    float y;

    int bottomMargin;
};