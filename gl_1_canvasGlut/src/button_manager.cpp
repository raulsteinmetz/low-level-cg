#include "button_manager.h"

ButtonManager::ButtonManager() {}

void ButtonManager::add_button(int x0, int y0, int width, int height, float r, float g, float b, int app, float percentageW, float percentageH) {
    buttons.push_back(Button(x0, y0, width, height, r, g, b, app, percentageW, percentageH));
}

void ButtonManager::remove_button(int index) {
    buttons.erase(buttons.begin() + index);
}

void ButtonManager::draw_buttons(int state) {
    for (int i = 0; i < buttons.size(); i++) {
        if (state == buttons[i].app)
            buttons[i].draw();
    }
}

int check_button_position(int x, int y, Button b) {
   if (x > b.x0 && y > b.y0 && x < b.x0 + b.width && y < b.y0 + b.height) {
      return HIGHLIGHTED;
   }
   return HIGHLIGHT_NONE;
}

void ButtonManager::highlight_buttons(int x, int y, int state) {
    for (int i = 0; i < buttons.size(); i++) {
        if (check_button_position(x, y, buttons[i]) != HIGHLIGHT_NONE) {
            if (state == buttons[i].app)
                buttons[i].highlight();
        }
    }
}







