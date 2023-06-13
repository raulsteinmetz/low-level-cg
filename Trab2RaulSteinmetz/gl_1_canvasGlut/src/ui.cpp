#include "ui.h"


Button::Button(){}

Button::Button(int id, float w, float h, char* text) {
    this->id = id;
    this->text = text;
    this->w = w;
    this->h = h;
}