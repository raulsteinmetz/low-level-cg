/*

    Made by Raul Steinmetz

    This file is responsable for managing the player class
        

*/

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
        void draw(float mouseX, float mouseY); // button draw
        bool render(); // button render
        bool check(float mx, float my); // checks if mouse is placed upon button
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
        void initial_menu(float mouseX, float mouseY); // initial menu render
        void death_menu(float mouseX, float mouseY); // death menu render
};


#endif // UI_H
