#ifndef BUTTON_H
#define BUTTON_H

// highlighting
#define HIGHLIGHT_R 0.4
#define HIGHLIGHT_G 0.7
#define HIGHLIGHT_B 0.9
#define HIGHLIGHT_FACTOR 5
#define HIGHLIGHT_NONE -1
#define HIGHLIGHTED 1


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
    float percentageW;
    float percentageH;
    void (*callback)(void); // function pointer member variable

    Button();
    Button(int x0, int y0, int width, int height, float r, float g, float b, int app, float percentageW, float percentageH);
    void draw();
    void highlight();
    void set_callback(void (*callback)(void)); // method to set the function pointer
    void onClick();
};


int check_button_position(int x, int y, Button b);


#endif // BUTTON_H
