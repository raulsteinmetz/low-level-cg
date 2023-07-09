#ifndef INTERFACE_H
#define INTERFACE_H


#include "string"
// highlighting
#define HIGHLIGHT_R 0.4
#define HIGHLIGHT_G 0.7
#define HIGHLIGHT_B 0.9
#define HIGHLIGHT_FACTOR 5
#define HIGHLIGHT_NONE 0
#define HIGHLIGHTED 1

#define CLICK_TRUE 1
#define CLICK_FALSE 0



class Button {
public:
    int x0;
    int y0;
    int width;
    int height;
    int app;
    float colorR;
    float colorG;
    float colorB;
    std::string name;

    Button();
    Button(int x0, int y0, int width, int height, float r, float g, float b, int app, const std::string& name); // updated constructor
    void draw(); // desenhar botao
    void highlight(); // indicar botao selecionado
    void render(double mouse_x, double mouse_y);
    int check_click(double mouse_x, double mouse_y);

};



int check_button_position(int x, int y, Button b);


#endif // INTERFACE_H