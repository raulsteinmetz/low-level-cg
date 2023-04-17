#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>

#define DRAW_FUNCTION_DELAY 500
// figures
#define CIRCLE 0
#define MAX_CIRCLES 100

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
      float angle;

      Circle();
      Circle(int cX, int cY, int sides, int radius, float r, float g, float b, float angle);

      void draw();
};




class FigureDrawer {
    public:
        float current_color_red;
        float current_color_green;
        float current_color_blue;
        float current_radius;
        float current_sides;
        float angle;
        Circle circles[MAX_CIRCLES];
        int n_circles;
        int draw_delay;
        FigureDrawer(float red, float green, float blue);
        void add_circle(int x, int y);

        void save_to_file(const std::string& file_name) {
            std::ofstream file(file_name, std::ios::binary);
            if (file.is_open()) {
                file.write(reinterpret_cast<char*>(this), sizeof(FigureDrawer));
                file.close();
            }
        }

        void load_from_file(const std::string& file_name) {
            std::ifstream file(file_name, std::ios::binary);
            if (file.is_open()) {
                file.read(reinterpret_cast<char*>(this), sizeof(FigureDrawer));
                file.close();
            }
        }
};



#endif // FIGURE_H
