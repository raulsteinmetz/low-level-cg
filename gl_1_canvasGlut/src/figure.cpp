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

Circle::Circle(int cX, int cY, int sides, int radius, float r, float g, float b) : Figure(r, g, b), cX(cX), cY(cY), sides(sides), radius(radius) {}

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
}

void FigureDrawer::save_circles_to_file(const std::string& file_name) {
  std::ofstream file(file_name, std::ios::trunc);

  if (!file) {
    std::cerr << "Error: could not open file " << file_name << " for writing" << std::endl;
    return;
  }

  file << n_circles << std::endl;

  for (int i = 0; i < n_circles; i++) {
    Circle circle = circles[i];

    file << circle.cX << " " << circle.cY << " "
         << circle.sides << " " << circle.radius << " "
         << circle.colorR << " " << circle.colorG << " " << circle.colorB << std::endl;
  }

  file.close();
  printf("Circles Saved");
}

void FigureDrawer::load_circles_from_file(const std::string& file_name) {
  std::ifstream file(file_name);

  if (!file) {
    std::cerr << "Error: could not open file " << file_name << " for reading" << std::endl;
    return;
  }

  file >> n_circles;

  for (int i = 0; i < n_circles; i++) {
    int cX, cY, sides, radius, r, g, b;

    file >> cX >> cY >> sides >> radius >> r >> g >> b;

    circles[i] = Circle(cX, cY, sides, radius, r, g, b);
  }

  file.close();
  printf("Circles Loaded");
}
