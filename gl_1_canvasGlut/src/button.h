#ifndef SAMPLE_H
#define SAMPLE_H


// highlighting
#define HIGHLIGHT_R 0.4
#define HIGHLIGHT_G 0.7
#define HIGHLIGHT_B 0.9
#define HIGHLIGHT_FACTOR 5
#define HIGHLIGHT_NONE -1


class Button {
public:
    int x0;
    int y0;
    int width;
    int height;
    float colorR;
    float colorG;
    float colorB;

    Button();
    Button(int x0, int y0, int width, int height, float r, float g, float b);
    void draw();
    void highlight();
};

int check_button_position(int x, int y, Button b);



class ButtonManager {
public:
    int n_buttons;
    Button buttons[15];
    ButtonManager();
};

#endif // SAMPLE_H
