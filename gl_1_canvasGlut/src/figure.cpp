#include "figure.h"
#include "gl_canvas2d.h"
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

// FIGURE

Figure::Figure(){}

Figure::Figure(int r, int g, int b){
    this->colorR = r;
    this->colorB = b;
    this->colorG = g;
}


// CIRCLE

Circle::Circle(){}

Circle::Circle(int cX, int cY, int sides, int radius, int r, int g, int b) : Figure(r, g, b), cX(cX), cY(cY), sides(sides), radius(radius) {}

void Circle::draw(){
    CV::color(colorR, colorG, colorB);
    CV::circleFill(cX, cY, radius, sides);
}


// FIGURE DRAWER

FigureDrawer::FigureDrawer(float red, float green, float blue){
         this->current_color_red = red;
         this->current_color_green = green;
         this->current_color_blue = blue;
         this->n_circles = 0;
         this->current_radius = 20;
         this->current_sides = 20;
         this->draw_delay = DRAW_FUNCTION_DELAY;
}


void FigureDrawer::add_circle(int x, int y){
    if (n_circles == 20) {
            n_circles = 0;
         }
         circles[n_circles].cX = x;
         circles[n_circles].cY = y;
         circles[n_circles].colorR = current_color_red;
         circles[n_circles].colorG = current_color_green;
         circles[n_circles].colorB = current_color_blue;
         circles[n_circles].radius = current_radius;
         circles[n_circles].sides = current_sides;
         n_circles++;
         draw_delay = DRAW_FUNCTION_DELAY;
}
