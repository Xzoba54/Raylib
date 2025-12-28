#pragma once

#include "UIWidget.h"
#include "TextureManager.h"
#include "Chest.h"
#include "Window.h"
#include <memory>

class ChestUI : public UIWidget{
public:
    ChestUI() = default;

    void Update() override;
    void Render() const override;

    void Init(Window& window);

    Rectangle GetRec() const override;

    void Open(std::shared_ptr<Chest> chest);
private:
    Texture2D texture;

    float x;
    float y;

    int slotsPerRow;

    int slotSize;
    int slotPadding;
    int headerMargin;

    std::shared_ptr<Chest> currentChest;
};