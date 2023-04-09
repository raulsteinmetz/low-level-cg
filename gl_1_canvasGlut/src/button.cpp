#include "button.h"
#include "gl_canvas2d.h"
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

Button::Button() {}

Button::Button(int x0, int y0, int width, int height, float r, float g, float b, int app, float percentageW, float percentageH) {
    this->x0 = x0;
    this->y0 = y0;
    this->width = width;
    this->height = height;
    this->colorR = r;
    this->colorG = g;
    this->colorB = b;
    this->app = app;
    this->percentageW = percentageW;
    this->percentageH = percentageH;
}

void Button::draw() {
    CV::color(this->colorR, this->colorG, this->colorB);
    CV::rectFill(this->x0, this->y0, this->x0 + this->width, this->y0 + this->height);
}

void Button::highlight(){
    CV::color(HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
    CV::rectFill(this->x0 - HIGHLIGHT_FACTOR, this->y0 - HIGHLIGHT_FACTOR, this->x0 + this->width + HIGHLIGHT_FACTOR, this->y0 + this->height + HIGHLIGHT_FACTOR);
}


