#ifndef SLIDER_H
#define SLIDER_H

class Slider {
public:
    int x0;
    int y0;
    int bar_width;
    int bar_height;
    int circle_radius;
    int circle_x;
    int circle_y;
    float value;
    float colorR;
    float colorG;
    float colorB;
    bool being_modified;

    Slider();
    Slider(int x0, int y0, int bar_width, int bar_height, int circle_radius, float r, float g, float b); // updated constructor
    void draw();
    void highlight();
    float getValueFromCircleX(float circle_x);
    float getCircleXFromValue();
    bool checkInteraction(int x, int y);
    void updateCirclePosition(int mx);
};


#endif // SLIDER_H
