#pragma once

#include "Object.h"
#include "TextureManager.h"

class Wall : public Object {
public:
    Wall();

    void Update() override;
    void Render() const override;
private:
    Texture2D texture;
};