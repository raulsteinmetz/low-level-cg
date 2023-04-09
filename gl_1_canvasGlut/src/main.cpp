#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include <list>
#include "button.h"
#include "figure.h"
#include "app_manager.h"

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

// background rgb
#define MAIN_APP_RED 0.8
#define MAIN_APP_GREEN 0.8
#define MAIN_APP_BLUE 0.8

// color button
#define COLOR_BOTTON_WIDTH 50
#define COLOR_BOTTON_HEIGHT 50

// draw circles button
#define DRAW_CIRCLES_BUTTON_WIDTH 50
#define DRAW_CIRCLES_BUTTON_HEIGHT 50
#define DRAW_CIRCLES_BUTTON_COLOR_R 1
#define DRAW_CIRCLES_BUTTON_COLOR_G 0.2
#define DRAW_CIRCLES_BUTTON_COLOR_B 1

// cancel function button
#define CANCEL_FUNCTION_BUTTON_WIDTH 50
#define CANCEL_FUNCTION_BUTTON_HEIGHT 50
#define CANCEL_FUNCTION_BUTTON_R 1
#define CANCEL_FUNCTION_BUTTON_G 0
#define CANCEL_FUNCTION_BUTTON_B 0

// radius plus button
#define RADIUS_PLUS_BUTTON_WIDTH 40
#define RADIUS_PLUS_BUTTON_HEIGHT 40
#define RADIUS_PLUS_BUTTON_R 0
#define RADIUS_PLUS_BUTTON_G 1
#define RADIUS_PLUS_BUTTON_B 0

// radius minus button
#define RADIUS_MINUS_BUTTON_WIDTH 40
#define RADIUS_MINUS_BUTTON_HEIGHT 40
#define RADIUS_MINUS_BUTTON_R 1
#define RADIUS_MINUS_BUTTON_G 0
#define RADIUS_MINUS_BUTTON_B 0
#define RADIUS_INCREASE_DECREASE 10

// sides plus button
#define SIDES_PLUS_BUTTON_WIDTH 40
#define SIDES_PLUS_BUTTON_HEIGHT 40
#define SIDES_PLUS_BUTTON_R 0
#define SIDES_PLUS_BUTTON_G 1
#define SIDES_PLUS_BUTTON_B 0
#define SIDES_INCREASE_DECREASE 1

// sides minus button
#define SIDES_MINUS_BUTTON_WIDTH 40
#define SIDES_MINUS_BUTTON_HEIGHT 40
#define SIDES_MINUS_BUTTON_R 1
#define SIDES_MINUS_BUTTON_G 0
#define SIDES_MINUS_BUTTON_B 0

// preview
#define PREVIEW_X_PERCENT 10
#define PREVIEW_Y_PERCENT 10
#define PREVIEW_RADIUS_DIV 5

// figure selected colors
#define FIGURE_SELECTED_R 0
#define FIGURE_SELECTED_G 0.8
#define FIGURE_SELECTED_B 0.8



// figures
#define CIRCLE 0




// global


int delay_bt = BUTTON_DELAY;
// current figure to be drawed
int current_figure = CIRCLE;
// current highlighted button
int current_hightlight = HIGHLIGHT_NONE;
// modifying figures
int figure = -1;


// mouse coords
int mx, my;

// button manager
ButtonManager button_manager();


int calc_position(float percent, int w_h) {
   if (w_h == 0) {
      return int(percent * AppManager::screen_width / 100.0);
   }
   return int(percent * AppManager::screen_height / 100.0);
}


// entities
FigureDrawer figure_drawer(0, 1, 0);

// buttons

// menu
Button start_button((AppManager::screen_width - START_BUTTON_WIDTH) / 2, (AppManager::screen_height - START_BUTTON_HEIGHT) / 2, START_BUTTON_WIDTH, START_BUTTON_HEIGHT, 0, 1, 0);

// main app
Button collor_button(int(90.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), COLOR_BOTTON_WIDTH, COLOR_BOTTON_HEIGHT, figure_drawer.current_color_red, figure_drawer.current_color_green, figure_drawer.current_color_blue);

// draw circles
Button draw_circles_button(int(90.0 * AppManager::screen_width / 100.0), int(40.0 * AppManager::screen_height / 100.0), DRAW_CIRCLES_BUTTON_WIDTH, DRAW_CIRCLES_BUTTON_HEIGHT, DRAW_CIRCLES_BUTTON_COLOR_R, DRAW_CIRCLES_BUTTON_COLOR_G, DRAW_CIRCLES_BUTTON_COLOR_B);

// cancel functions
Button cancel_function_button(int(90.0 * AppManager::screen_width / 100.0), int(10.0 * AppManager::screen_height / 100.0), CANCEL_FUNCTION_BUTTON_WIDTH, CANCEL_FUNCTION_BUTTON_HEIGHT, CANCEL_FUNCTION_BUTTON_R, CANCEL_FUNCTION_BUTTON_G, CANCEL_FUNCTION_BUTTON_B);

// radius size
Button radius_size_plus(int(10.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), RADIUS_PLUS_BUTTON_WIDTH, RADIUS_PLUS_BUTTON_HEIGHT, RADIUS_PLUS_BUTTON_R, RADIUS_PLUS_BUTTON_G, RADIUS_PLUS_BUTTON_B);
Button radius_size_minus(int(30.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), RADIUS_MINUS_BUTTON_WIDTH, RADIUS_MINUS_BUTTON_HEIGHT, RADIUS_MINUS_BUTTON_R, RADIUS_MINUS_BUTTON_G, RADIUS_MINUS_BUTTON_B);

// sides size
Button sides_plus(int(10.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), SIDES_PLUS_BUTTON_WIDTH, SIDES_PLUS_BUTTON_HEIGHT, SIDES_PLUS_BUTTON_R, SIDES_PLUS_BUTTON_G, SIDES_PLUS_BUTTON_B);
Button sides_minus(int(30.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), SIDES_MINUS_BUTTON_WIDTH, SIDES_MINUS_BUTTON_HEIGHT, SIDES_MINUS_BUTTON_R, SIDES_MINUS_BUTTON_G, SIDES_MINUS_BUTTON_B);

// funcoes auxiliares

void menu_render(int width, int height) {
   // paint screen
   CV::color(MENU_RED, MENU_GREEN, MENU_BLUE);
   CV::rectFill(0, 0, width, height);

   // start button
   start_button.draw();
}


void main_app_render(int width, int height){
   // paint screen
   CV::color(MAIN_APP_RED, MAIN_APP_GREEN, MAIN_APP_BLUE);
   CV::rectFill(0, 0, width, height);

   // buttons
   collor_button.draw();
   draw_circles_button.draw();
   cancel_function_button.draw();
   radius_size_plus.draw();
   radius_size_minus.draw();
   sides_plus.draw();
   sides_minus.draw();


   // figures
   for (int i = 0; i < figure_drawer.n_circles; i++) {
      if (figure != -1) {
         if (figure == i) {
            CV::color(FIGURE_SELECTED_R, FIGURE_SELECTED_G, FIGURE_SELECTED_B);
            CV::circleFill(figure_drawer.circles[i].cX, figure_drawer.circles[i].cY, figure_drawer.circles[i].radius + 10, figure_drawer.circles[i].sides);
         }
      }
      figure_drawer.circles[i].draw();
   }

   // preview
   Circle preview;
   preview.sides = figure_drawer.current_sides;
   preview.radius = int (figure_drawer.current_radius / PREVIEW_RADIUS_DIV);
   preview.colorR = figure_drawer.current_color_red;
   preview.colorG = figure_drawer.current_color_green;
   preview.colorB = figure_drawer.current_color_blue;
   preview.cX = calc_position(PREVIEW_X_PERCENT, 0);
   preview.cY = calc_position(PREVIEW_Y_PERCENT, 1);
   preview.draw();

}

int distance(int x0, int y0, int x1, int y1) {
   return int(sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

int find_figure(int x, int y) {
   for (int i = 0; i < figure_drawer.n_circles; i++) {
      if (distance(x, y, figure_drawer.circles[i].cX, figure_drawer.circles[i].cY) < figure_drawer.circles[i].radius) {
         return i;
      }
   }
   return -1;
}

// verify button press
void verify_buttons(int button, int x, int y){
   // button delay
   if (delay_bt > 0) return;
   delay_bt = BUTTON_DELAY;
   if (button == 0) {
      if (AppManager::app_state == MENU) {
         // start
         if (check_button_position(x, y, start_button)) {
            AppManager::app_state = MAIN_APP;
         }
      }
      else if (AppManager::app_state == MAIN_APP) {
         // deactivate function
         if(check_button_position(x, y, cancel_function_button)) {
           AppManager::current_function = FUNCTION_NONE;
         }

         if (AppManager::current_function == FUNCTION_NONE){
            // draw circles button
            if (check_button_position(x, y, draw_circles_button)){
              AppManager::current_function = FUNCTION_DRAW;
               figure_drawer.draw_delay = DRAW_FUNCTION_DELAY;
            }
            // radius configuration
            else if (check_button_position(x, y, radius_size_plus)) {
               figure_drawer.current_radius += RADIUS_INCREASE_DECREASE;
            }
            else if (check_button_position(x, y, radius_size_minus)) {
               figure_drawer.current_radius -= RADIUS_INCREASE_DECREASE;
            }
            else if (check_button_position(x, y, sides_plus)) {
               figure_drawer.current_sides += SIDES_INCREASE_DECREASE;
            }
            else if (check_button_position(x, y, sides_minus)) {
               figure_drawer.current_sides -= SIDES_INCREASE_DECREASE;
            }
            else { // clicking on a figure or not
               int f = find_figure(x, y);
               if (f != -1) {
                 AppManager::current_function = FUNCTION_MODIFY;
                  figure = f;
               }
            }
         }
         else if (AppManager::current_function == FUNCTION_DRAW){
            // draw circles activated
            if (figure_drawer.draw_delay <= 0) {
               figure_drawer.add_circle(x, y);
            }
         }
         else if (AppManager::current_function == FUNCTION_MODIFY) {
            int f = find_figure(x, y);
            if (f == -1) {
              AppManager::current_function = FUNCTION_NONE;
               figure = -1;
            }
         }
      }
   }
   else if (button == -2) {
      // AQUI, HIGHLIGHT BUTTON
      // for no manager, achou botao, atribui o sublinhado (idx) a variavel global, caso nao, -1
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

void delay_manager(){
   // draw delay
   if (figure_drawer.draw_delay > 0) {
      figure_drawer.draw_delay --;
   }
   if (delay_bt > 0) {
      delay_bt --;
   }
}

// pos = position percentage compared to the screen (50% would be central, 100% would be right) * screen / 100;
void update_res() {
   // start button
   start_button.x0 = (AppManager::screen_width - START_BUTTON_WIDTH) / 2;
   start_button.y0 = (AppManager::screen_height - START_BUTTON_HEIGHT) / 2;

   // color button
   collor_button.x0 = calc_position(90, 0);
   collor_button.y0 = calc_position(90, 1);

   // draw circles button
   draw_circles_button.x0 = calc_position(90, 0);
   draw_circles_button.y0 = calc_position(40, 1);

   // cancel function button
   cancel_function_button.x0 = calc_position(90, 0);
   cancel_function_button.y0 = calc_position(10, 1);

   // radius configuration buttons
   radius_size_plus.x0 = calc_position(10, 0);
   radius_size_plus.y0 = calc_position(90, 1);
   radius_size_minus.x0 = calc_position(30, 0);
   radius_size_minus.y0 = calc_position(90, 1);

   // sides configuration button
   sides_plus.x0 = calc_position(10, 0);
   sides_plus.y0 = calc_position(80, 1);
   sides_minus.x0 = calc_position(30, 0);
   sides_minus.y0 = calc_position(80, 1);
}

// render
void render()
{
   if (AppManager::app_state == MENU) { // menu
      menu_render(AppManager::screen_width, AppManager::screen_height);
   }
   else if (AppManager::app_state = MAIN_APP) { // main screen, no functions activated
      main_app_render(AppManager::screen_width, AppManager::screen_height);
   }


   update_res();
   delay_manager();
}


int main(void)
{
   CV::init(&AppManager::screen_width, &AppManager::screen_height, "Canvas 2D");
   CV::run();
}
