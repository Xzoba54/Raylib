#pragma once

#include "UIWidget.h"
#include "TextureManager.h"
#include <memory>
#include "Chest.h"
#include "Window.h"

class ChestUI : public UIWidget{
public:
    ChestUI() = default;

    void Update() override;
    void Render() const override;

    void Init(Window& window);

    void Open(std::shared_ptr<Chest> chest);

    Rectangle GetRec() const override;
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