#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "auxiliar.h"

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

// global

// screen
int screenWidth = SCREENWIDTH;
int screenHeight = SCREENHEIGHT;

// state
int app_state = 0;
// mouse coords
int mx, my;


// classes

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

// buttons

// menu
Button start_button((screenWidth - START_BUTTON_WIDTH) / 2, (screenHeight - START_BUTTON_HEIGHT) / 2, START_BUTTON_WIDTH, START_BUTTON_HEIGHT, 0, 1, 0);

// funcoes auxiliares

void menu_render(int width, int height) {
   color(MENU_RED, MENU_GREEN, MENU_BLUE);
   // paint screen
   rectFill(0, 0, width, height);

   // start button
   start_button.draw();
}

void main_app_render(int width, int height){
   color(MAIN_APP_RED, MAIN_APP_GREEN, MAIN_APP_BLUE);
   // paint screen
   rectFill(0, 0, width, height);
   
}


// verify button press
void verify_buttons(int button, int x, int y){
   // start
   if (button == 0) {
      if (app_state == 0) {
         // start
         if (x > start_button.x0 && y > start_button.y0 && x < start_button.x0 + start_button.width && y < start_button.y0 + start_button.height) {
            app_state = 1;
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

void update_res() {
   // start button
   start_button.x0 = (screenWidth - START_BUTTON_WIDTH) / 2;
   start_button.y0 = (screenHeight - START_BUTTON_HEIGHT) / 2;
   start_button.width = START_BUTTON_WIDTH;
   start_button.height = START_BUTTON_HEIGHT;
}

// render
void render()
{
   if (app_state == 0) {
      menu_render(screenWidth, screenHeight);
   }
   else if (app_state = 1) {
      main_app_render(screenWidth, screenHeight);
   }

   update_res();
}


int main(void)
{
   init(&screenWidth, &screenHeight, "Canvas 2D");
   run();
}