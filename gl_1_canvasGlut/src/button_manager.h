#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <vector>
#include "button.h"

class ButtonManager {
public:
    std::vector<Button> buttons;
    ButtonManager();

    // Add a new button to the list
    void add_button(int x0, int y0, int width, int height, float r, float g, float b, int app, float percentageW, float percentageH);

    // Remove a button from the list
    void remove_button(int index);

    // Draw all buttons
    void draw_buttons(int state);

    void highlight_buttons(int x, int y, int state);

    void update_res();
};


#endif // BUTTON_MANAGER_H
