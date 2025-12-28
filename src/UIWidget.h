#pragma once

#include "raylib.h"

class UIWidget{
public:
    virtual ~UIWidget() = default;

    virtual void Update() = 0;
    virtual void Render() const = 0;

    virtual Rectangle GetRec() const = 0;

    virtual void Open() { this->open = true; }
    virtual void Close() { this->open = false; }

    bool IsOpen() const { return this->open; }
protected:
    bool open = false;
};