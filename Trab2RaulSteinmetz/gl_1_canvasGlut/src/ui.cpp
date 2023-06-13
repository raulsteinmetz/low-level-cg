#include "ui.h"


Button::Button(){}

Button::Button(int id, float x, float y, float w, float h, char* text) {
    this->x = x;
    this->y = y;
    this->id = id;
    this->text = text;
    this->w = w;
    this->h = h;

}

bool Button::check(float mouseX, float mouseY) {
    if (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
        return true;
    }
    return false;
}

void Button::draw(float mouseX, float mouseY) {
    // purple
    CV::color(0.5, 0, 1);
    // if mouse in button
    if (check(mouseX, mouseY)) {
        // light purple
        CV::rectFill(x, y, x + w, y + h);
    } else {
        CV::rect(x, y, x + w, y + h);
    }
    CV::color(1, 1, 1);
    CV::text(x + w/2 - 20, y + h/2 + 5, text);
}

UserInterface::UserInterface() {}

UserInterface::UserInterface(float screen_width, float screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    // start in the middle of the screen
    menu_buttons.push_back(Button(0, screen_width/2 - 50, screen_height/2 - 25, 100, 50, (char*)"Start"));
    menu_buttons.push_back(Button(1, screen_width/2 - 50, screen_height/2 + 25, 100, 50, (char*)"Exit"));

    // play again button
    death_buttons.push_back(Button(0, screen_width/2 - 50, screen_height/2 - 25, 125, 50, (char*)"Again"));
    death_buttons.push_back(Button(1, screen_width/2 - 50, screen_height/2 + 25, 125, 50, (char*)"Exit"));

}

void UserInterface::initial_menu(float mouseX, float mouseY) {

    // black background
    CV::color(0, 0, 0);
    CV::rectFill(0, 0, screen_width, screen_height);

    // buttons
    for (std::list<Button>::iterator it = menu_buttons.begin(); it != menu_buttons.end(); ++it) {
        it->draw(mouseX, mouseY);
    }

}

void UserInterface::death_menu(float mouseX, float mouseY) {
    // dark red background
    CV::color(0.5, 0, 0);
    CV::rectFill(0, 0, screen_width, screen_height);

    // buttons
    for (std::list<Button>::iterator it = death_buttons.begin(); it != death_buttons.end(); ++it) {
        it->draw(mouseX, mouseY);
    }
}

