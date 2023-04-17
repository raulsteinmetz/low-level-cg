#include "figure.h"
#include "gl_canvas2d.h"
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <string> // Add this line
#include <fstream>
#include <iostream>

// FIGURE

Figure::Figure(){}

Figure::Figure(float r, float g, float b){
    this->colorR = r;
    this->colorB = b;
    this->colorG = g;
}


// CIRCLE

Circle::Circle(){}

Circle::Circle(int cX, int cY, int sides, int radius, float r, float g, float b, float angle) : Figure(r, g, b), cX(cX), cY(cY), sides(sides), radius(radius), angle(angle) {}

void Circle::draw(){
    CV::color(colorR, colorG, colorB);
    CV::circleFill(cX, cY, radius, sides, angle);
}


// FIGURE DRAWER

FigureDrawer::FigureDrawer(float red, float green, float blue){
         this->current_color_red = red;
         this->current_color_green = green;
         this->current_color_blue = blue;
         this->n_circles = 0;
         this->current_radius = 20;
         this->current_sides = 20;
         this->angle = 0;
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
     circles[n_circles].angle = angle;
     n_circles++;
}


