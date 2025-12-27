#include "Button.h"

Button::Button(float x, float y, float width, float height, const char *text) :
    button{x, y, width, height}
{
    this->text = text;
    this->fontSize = 20;

    this->isClicked = false;

    this->background_idle_color = {122, 122, 122, 255};
    this->background_hover_color = {100, 100, 100, 255};
    this->background_pressed_color = {80, 80, 80, 255};
    this->background_current_color = this->background_idle_color;

    int textWidth = MeasureText(text, fontSize);

    this->textX = x + (width / 2.0f) - (textWidth / 2.0f);
    this->textY = y + (height / 2.0f) - (this->fontSize / 2.0f);
}

void Button::Update(){
    Vector2 mousePos = GetMousePosition();

    if(CheckCollisionPointRec(mousePos, button)){
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            this->background_current_color = this->background_pressed_color;
        }else{
            this->background_current_color = this->background_hover_color;
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            this->isClicked = true;
        }else{
            this->isClicked = false;
        }
    }else{
        this->background_current_color = this->background_idle_color;
    }
}

void Button::Render(){
    DrawRectangleRec(this->button, this->background_current_color);
    DrawText(text.c_str(), this->textX, this->textY, 23, RED);
}

bool Button::IsClicked(){
    return this->isClicked;
}
