#ifndef UI_H
#define UI_H

#include <list>
#include "gl_canvas2d.h"



class Button {

    public:
        float x;
        float y;
        float w;
        float h;
        int id;
        char *text;
        Button();
        Button(int id, float x, float y, float w, float h, char *text);
        void draw(float mouseX, float mouseY);
        bool render();
        bool check(float mx, float my);
};


class UserInterface {
    public:
        float screen_width;
        float screen_height;
        std::list<Button> menu_buttons;
        std::list<Button> death_buttons;
        std::list<Button> ranking_buttons;
        
        UserInterface();
        UserInterface(float screen_width, float screen_height);
        void initial_menu(float mouseX, float mouseY);
        void ranking();
        void death_menu(float mouseX, float mouseY);
};


#endif // UI_H
