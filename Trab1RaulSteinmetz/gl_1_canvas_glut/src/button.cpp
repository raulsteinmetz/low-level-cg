#include "button.h"
#include "gl_canvas2d.h"
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#define TEXT_OFFSET_X 3
#define TEXT_OFFSET_Y 12

// Botao
Button::Button() {}
Button::Button(int x0, int y0, int width, int height, float r, float g, float b, int app, const std::string& name) {
    this->x0 = x0;
    this->y0 = y0;
    this->width = width;
    this->height = height;
    this->colorR = r;
    this->colorG = g;
    this->colorB = b;
    this->app = app;
    this->name = name;
}
// Desenhar Botao
void Button::draw() {
    CV::color(this->colorR, this->colorG, this->colorB);
    CV::rectFill(this->x0, this->y0, this->x0 + this->width, this->y0 + this->height);
    CV::color(1, 1, 1);
    CV::text(this->x0 + TEXT_OFFSET_X, this->y0 + TEXT_OFFSET_Y, this->name.c_str());
}
// Indicar botao sendo pressionado
void Button::highlight(){
    CV::color(HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
    CV::rectFill(this->x0 - HIGHLIGHT_FACTOR, this->y0 - HIGHLIGHT_FACTOR, this->x0 + this->width + HIGHLIGHT_FACTOR, this->y0 + this->height + HIGHLIGHT_FACTOR);
    draw();
}
