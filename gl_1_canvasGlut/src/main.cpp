#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "button.h"
#include "button_manager.h"
#include "figure.h"
#include "app_manager.h"
#include "interface.h"
#include "auxiliar_functions.h"
#include <list>



// global
int delay_bt = BUTTON_DELAY;
// current figure to be drawed
int current_figure = CIRCLE;
// current highlighted button
int current_hightlight = HIGHLIGHT_NONE;
// modifying figures
int figure = -1;

// mouse coordinates
int mx, my;



// figure drawer
FigureDrawer figure_drawer(0, 1, 0);
// button manager
ButtonManager button_manager;


void add_all_buttons() {
    button_manager.add_button(
        (AppManager::screen_width - START_BUTTON_WIDTH) / 2,
        (AppManager::screen_height - START_BUTTON_HEIGHT) / 2,
        START_BUTTON_WIDTH,
        START_BUTTON_HEIGHT,
        0,
        1,
        0,
        MENU,
        50,
        50

    );

    button_manager.add_button(
        int(90.0 * AppManager::screen_width / 100.0),
        int(90.0 * AppManager::screen_height / 100.0),
        COLOR_BOTTON_WIDTH,
        COLOR_BOTTON_HEIGHT,
        figure_drawer.current_color_red,
        figure_drawer.current_color_green,
        figure_drawer.current_color_blue,
        MAIN_APP,
        90.0,
        90.0
    );

    button_manager.add_button(
        int(90.0 * AppManager::screen_width / 100.0),
        int(40.0 * AppManager::screen_height / 100.0),
        DRAW_CIRCLES_BUTTON_WIDTH,
        DRAW_CIRCLES_BUTTON_HEIGHT,
        DRAW_CIRCLES_BUTTON_COLOR_R,
        DRAW_CIRCLES_BUTTON_COLOR_G,
        DRAW_CIRCLES_BUTTON_COLOR_B,
        MAIN_APP,
        90.0,
        40.0
    );

    button_manager.add_button(
        int(90.0 * AppManager::screen_width / 100.0),
        int(10.0 * AppManager::screen_height / 100.0),
        CANCEL_FUNCTION_BUTTON_WIDTH,
        CANCEL_FUNCTION_BUTTON_HEIGHT,
        CANCEL_FUNCTION_BUTTON_R,
        CANCEL_FUNCTION_BUTTON_G,
        CANCEL_FUNCTION_BUTTON_B,
        MAIN_APP,
        90.0,
        10.0
    );

    button_manager.add_button(
        int(10.0 * AppManager::screen_width / 100.0),
        int(90.0 * AppManager::screen_height / 100.0),
        RADIUS_PLUS_BUTTON_WIDTH,
        RADIUS_PLUS_BUTTON_HEIGHT,
        RADIUS_PLUS_BUTTON_R,
        RADIUS_PLUS_BUTTON_G,
        RADIUS_PLUS_BUTTON_B,
        MAIN_APP,
        10.0,
        90.0
    );

    button_manager.add_button(
        int(30.0 * AppManager::screen_width / 100.0),
        int(90.0 * AppManager::screen_height / 100.0),
        RADIUS_MINUS_BUTTON_WIDTH,
        RADIUS_MINUS_BUTTON_HEIGHT,
        RADIUS_MINUS_BUTTON_R,
        RADIUS_MINUS_BUTTON_G,
        RADIUS_MINUS_BUTTON_B,
        MAIN_APP,
        30.0,
        90.0
    );

    button_manager.add_button(
        int(10.0 * AppManager::screen_width / 100.0),
        int(80.0 * AppManager::screen_height / 100.0),
        SIDES_PLUS_BUTTON_WIDTH,
        SIDES_PLUS_BUTTON_HEIGHT,
        SIDES_PLUS_BUTTON_R,
        SIDES_PLUS_BUTTON_G,
        SIDES_PLUS_BUTTON_B,
        MAIN_APP,
        10.0,
        80.0
    );

    button_manager.add_button(
        int(30.0 * AppManager::screen_width / 100.0),
        int(80.0 * AppManager::screen_height / 100.0),
        SIDES_MINUS_BUTTON_WIDTH,
        SIDES_MINUS_BUTTON_HEIGHT,
        SIDES_MINUS_BUTTON_R,
        SIDES_MINUS_BUTTON_G,
        SIDES_MINUS_BUTTON_B,
        MAIN_APP,
        30.0,
        80.0
    );
}



void menu_render(int width, int height) {
    // paint screen
    CV::color(MENU_RED, MENU_GREEN, MENU_BLUE);
    CV::rectFill(0, 0, width, height);

    // draw start button
    button_manager.draw_buttons(AppManager::app_state);
    button_manager.highlight_buttons(mx, my, AppManager::app_state);

}

void main_app_render(int width, int height){
   // paint screen
   CV::color(MAIN_APP_RED, MAIN_APP_GREEN, MAIN_APP_BLUE);
   CV::rectFill(0, 0, width, height);

   button_manager.draw_buttons(AppManager::app_state);
   button_manager.highlight_buttons(mx, my, AppManager::app_state);


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
   preview.cX = calc_position(PREVIEW_X_PERCENT, 0, AppManager::screen_width, AppManager::screen_height);
   preview.cY = calc_position(PREVIEW_Y_PERCENT, 1, AppManager::screen_width, AppManager::screen_height);
   preview.draw();

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
   /*if (delay_bt > 0) return;
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
   }*/
}

// position = position percentage compared to the screen (50% would be central, 100% would be right) * screen / 100;
void update_res() {
    // start button
    button_manager.buttons[0].x0 = (AppManager::screen_width - START_BUTTON_WIDTH) / 2;
    button_manager.buttons[0].y0 = (AppManager::screen_height - START_BUTTON_HEIGHT) / 2;


    for (int i = 1; i < button_manager.buttons.size(); i++) {
        button_manager.buttons[i].x0 = calc_position(button_manager.buttons[i].percentageW, 0, AppManager::screen_width, AppManager::screen_height);
        button_manager.buttons[i].y0 = calc_position(button_manager.buttons[i].percentageH, 1, AppManager::screen_width, AppManager::screen_height);
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


// draw delay
void delay_manager(){
   if (figure_drawer.draw_delay > 0) {
      figure_drawer.draw_delay --;
   }
   if (delay_bt > 0) {
      delay_bt --;
   }
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

// main
int main(void)
{
    add_all_buttons();
    CV::init(&AppManager::screen_width, &AppManager::screen_height, "Canvas 2D");
    CV::run();
}
