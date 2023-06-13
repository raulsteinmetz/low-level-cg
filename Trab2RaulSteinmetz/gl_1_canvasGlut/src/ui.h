#ifndef UI_H
#define UI_H

#include <list>



class Button {

    public:
        float w;
        float h;
        int id;
        char *text;

        Button();
        Button(int id, float w, float h, char *text);
        
        bool checkClick(float mx, float my);
};


class UserInterface {
    public:
        std::list<Button> buttons;
        void initial_menu();
        void ranking();
        void death_menu();
};


#endif UI_H
