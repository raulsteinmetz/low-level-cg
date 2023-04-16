#ifndef FIGURE_H
#define FIGURE_H

#include <string> // Add this line

#define DRAW_FUNCTION_DELAY 500
// figures
#define CIRCLE 0

class Figure {
   public:
      float colorR;
      float colorB;
      float colorG;
      Figure();
      Figure(float r, float g, float b);
      //virtual void draw() = 0;
};

// Circle class inherits from Figure
class Circle : public Figure {
   public:
      int cX;
      int cY;
      int sides;
      int radius;

      Circle();
      Circle(int cX, int cY, int sides, int radius, float r, float g, float b);

      void draw();
};




class FigureDrawer {
   public:
      float current_color_red;
      float current_color_green;
      float current_color_blue;
      float current_radius;
      float current_sides;
      Circle circles[20];
      int n_circles;
      int draw_delay;
      FigureDrawer(float red, float green, float blue);
      void add_circle(int x, int y);
      void save_circles_to_file(const std::string& file_name);
      void load_circles_from_file(const std::string& file_name);
};



#endif // FIGURE_H
