#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "auxiliar.h"
#include <list>


// screen
#define SCREENHEIGHT 800
#define SCREENWIDTH 800

// menu
#define MENU_RED 0.3
#define MENU_GREEN 0.5
#define MENU_BLUE 0.8
#define START_BUTTON_WIDTH 200
#define START_BUTTON_HEIGHT 100

// main application
#define MAIN_APP_RED 0.8
#define MAIN_APP_GREEN 0.8
#define MAIN_APP_BLUE 0.8
#define COLOR_BOTTON_WIDTH 50
#define COLOR_BOTTON_HEIGHT 50
#define DRAW_CIRCLES_BUTTON_WIDTH 50
#define DRAW_CIRCLES_BUTTON_HEIGHT 50
#define DRAW_CIRCLES_BUTTON_COLOR_R 1
#define DRAW_CIRCLES_BUTTON_COLOR_G 0.2
#define DRAW_CIRCLES_BUTTON_COLOR_B 1
#define CANCEL_FUNCTION_BUTTON_WIDTH 50
#define CANCEL_FUNCTION_BUTTON_HEIGHT 50
#define CANCEL_FUNCTION_BUTTON_R 1
#define CANCEL_FUNCTION_BUTTON_G 0
#define CANCEL_FUNCTION_BUTTON_B 0

// global

// screen
int screenWidth = SCREENWIDTH;
int screenHeight = SCREENHEIGHT;

// state
int app_state = 0;
// function
int function = 0;


// mouse coords
int mx, my;


// classes

// figures

class Figure {
   public:
      int colorR;
      int colorB;
      int colorG;
      Figure(){}
      Figure(int r, int g, int b) {
         this->colorR = r;
         this->colorB = b;
         this->colorG = g;
      }
      //virtual void draw() = 0;
};

class Square : public Figure {
   public:
      int x0;
      int y0;
      int height;
      int width;

      Square(int x0, int y0, int height, int width, int r, int g, int b) : Figure(r, g, b), x0(x0), y0(y0), height(height), width(width) {}
      void draw() { // implement draw() method
         color(colorR, colorG, colorB);
         rectFill(x0, y0, x0 + width, y0 + height);
      }
};

// Circle class inherits from Figure
class Circle : public Figure {
   public:
      int cX;
      int cY;
      int sides;
      int radius;

      Circle() {}
      Circle(int cX, int cY, int sides, int radius, int r, int g, int b) : Figure(r, g, b), cX(cX), cY(cY), sides(sides), radius(radius) {}

      void draw() { // implement draw() method
         color(colorR, colorG, colorB);
         circleFill(cX, cY, radius, sides);
      }
};


class FigureDrawer {
   public:
      float current_color_red;
      float current_color_green;
      float current_color_blue;
      float current_radius;
      float current_sides;
      Circle circles[10];
      int n_circles;
      FigureDrawer(float red, float green, float blue) {
         this->current_color_red = red;
         this->current_color_green = green;
         this->current_color_blue = blue;
         this->n_circles = 0;
         this->current_radius = 20;
         this->current_sides = 20;

      }

      void add_circle(int x, int y) {
         if (n_circles == 9) {
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
};


class Button {
   public:
      int x0;
      int y0;
      int width;
      int height;
      float colorR;
      float colorG;
      float colorB;

      // constructor 
      Button(int x0, int y0, int width, int height, float r, float g, float b) {
         this->x0 = x0;
         this->y0 = y0;
         this->width = width;
         this->height = height;
         this->colorR = r;
         this->colorG = g;
         this->colorB = b;
      }

      void draw() {
         color(this->colorR, this->colorG, this->colorB);
         rectFill(this->x0, this->y0, this->x0 + this->width, this->y0 + this->height);
      }
};

// entities
FigureDrawer figure_drawer(0, 1, 0);

// buttons

// menu
Button start_button((screenWidth - START_BUTTON_WIDTH) / 2, (screenHeight - START_BUTTON_HEIGHT) / 2, START_BUTTON_WIDTH, START_BUTTON_HEIGHT, 0, 1, 0);

// main app
Button collor_button(int(90.0 * screenWidth / 100.0), int(90.0 * screenHeight / 100.0), COLOR_BOTTON_WIDTH, COLOR_BOTTON_HEIGHT, figure_drawer.current_color_red, figure_drawer.current_color_green, figure_drawer.current_color_blue);

// draw circles
Button draw_circles_button(int(90.0 * screenWidth / 100.0), int(40.0 * screenHeight / 100.0), DRAW_CIRCLES_BUTTON_WIDTH, DRAW_CIRCLES_BUTTON_HEIGHT, DRAW_CIRCLES_BUTTON_COLOR_R, DRAW_CIRCLES_BUTTON_COLOR_G, DRAW_CIRCLES_BUTTON_COLOR_B);

// cancel functions
Button cancel_function_button(int(90.0 * screenWidth / 100.0), int(10.0 * screenHeight / 100.0), CANCEL_FUNCTION_BUTTON_WIDTH, CANCEL_FUNCTION_BUTTON_HEIGHT, CANCEL_FUNCTION_BUTTON_R, CANCEL_FUNCTION_BUTTON_G, CANCEL_FUNCTION_BUTTON_B);

// funcoes auxiliares

void menu_render(int width, int height) {
   // paint screen
   color(MENU_RED, MENU_GREEN, MENU_BLUE);
   rectFill(0, 0, width, height);

   // start button
   start_button.draw();
}


void main_app_render(int width, int height){
   // paint screen
   color(MAIN_APP_RED, MAIN_APP_GREEN, MAIN_APP_BLUE);
   rectFill(0, 0, width, height);

   // buttons
   collor_button.draw();
   draw_circles_button.draw();
   cancel_function_button.draw();


   // figures
   for (int i = 0; i < figure_drawer.n_circles; i++) {
      figure_drawer.circles[i].draw();
   }
   
}

int check_button_position(int x, int y, Button b) {
   if (x > b.x0 && y > b.y0 && x < b.x0 + b.width && y < b.y0 + b.height) {
      return 1;
   }
   return 0;
}


// verify button press
void verify_buttons(int button, int x, int y){
   // start
   if (button == 0) {
      if (app_state == 0) {
         // start
         if (check_button_position(x, y, start_button)) {
            app_state = 1;
         }
      }
      else if (app_state == 1) {
         
         // deactivate function
         if(check_button_position(x, y, cancel_function_button)) {
            function = 0;
         }

         if (function == 0){
            // draw circles button
            if (check_button_position(x, y, draw_circles_button)){
               function = 1;
            }
         }
         else if (function == 1){
            // draw circles activated
            figure_drawer.add_circle(x, y);
         }


      
      }
   }
}

// mouse call back
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   // mause coords
   mx = x;
   my = y;

   verify_buttons(button, x, y);
}

// key down call back
void keyboard(int key)
{
   printf("\nClicou Tecla: %d" , key);
}


// key up call back
void keyboardUp(int key)
{
   printf("\nLiberou Tecla: %d" , key);
}

int calc_position(float percent, int w_h) {
   if (w_h == 0) {
      return int(percent * screenWidth / 100.0);
   }
   return int(percent * screenHeight / 100.0);
}

// pos = position percentage compared to the screen (50% would be central, 100% would be right) * screen / 100;
void update_res() {
   // start button
   start_button.x0 = (screenWidth - START_BUTTON_WIDTH) / 2;
   start_button.y0 = (screenHeight - START_BUTTON_HEIGHT) / 2;

   // color button
   collor_button.x0 = calc_position(90, 0);
   collor_button.y0 = calc_position(90, 1);

   // draw circles button
   draw_circles_button.x0 = calc_position(90, 0);
   draw_circles_button.y0 = calc_position(40, 1);

   // cancel function button 
   cancel_function_button.x0 = calc_position(90, 0);
   cancel_function_button.y0 = calc_position(10, 1);
}

// render
void render()
{
   if (app_state == 0) { // menu
      menu_render(screenWidth, screenHeight);
   }
   else if (app_state = 1) { // main screen, no functions activated
      main_app_render(screenWidth, screenHeight);
   }

   if (function == 0) { // no function

   }
   else if (function == 1) { // drawing circles

   }

   update_res();
}


int main(void)
{
   init(&screenWidth, &screenHeight, "Canvas 2D");
   run();
}