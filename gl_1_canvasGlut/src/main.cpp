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
    button_manager.add_button((AppManager::screen_width - START_BUTTON_WIDTH) / 2, (AppManager::screen_height - START_BUTTON_HEIGHT) / 2, START_BUTTON_WIDTH,
        START_BUTTON_HEIGHT, 0, 1, 0, MENU, 50, 50);

    button_manager.add_button(int(90.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), COLOR_BOTTON_WIDTH, COLOR_BOTTON_HEIGHT,
        figure_drawer.current_color_red, figure_drawer.current_color_green, figure_drawer.current_color_blue, MAIN_APP, 90.0, 90.0);

    button_manager.add_button(int(90.0 * AppManager::screen_width / 100.0), int(40.0 * AppManager::screen_height / 100.0), DRAW_CIRCLES_BUTTON_WIDTH,
        DRAW_CIRCLES_BUTTON_HEIGHT, DRAW_CIRCLES_BUTTON_COLOR_R, DRAW_CIRCLES_BUTTON_COLOR_G, DRAW_CIRCLES_BUTTON_COLOR_B, MAIN_APP, 90.0, 40.0);

    button_manager.add_button(int(90.0 * AppManager::screen_width / 100.0), int(10.0 * AppManager::screen_height / 100.0), CANCEL_FUNCTION_BUTTON_WIDTH,
        CANCEL_FUNCTION_BUTTON_HEIGHT, CANCEL_FUNCTION_BUTTON_R, CANCEL_FUNCTION_BUTTON_G, CANCEL_FUNCTION_BUTTON_B, MAIN_APP, 90.0, 10.0);

    button_manager.add_button(int(10.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), RADIUS_PLUS_BUTTON_WIDTH,
        RADIUS_PLUS_BUTTON_HEIGHT, RADIUS_PLUS_BUTTON_R, RADIUS_PLUS_BUTTON_G, RADIUS_PLUS_BUTTON_B, MAIN_APP, 10.0, 90.0);

    button_manager.add_button(int(30.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), RADIUS_MINUS_BUTTON_WIDTH,
        RADIUS_MINUS_BUTTON_HEIGHT, RADIUS_MINUS_BUTTON_R, RADIUS_MINUS_BUTTON_G, RADIUS_MINUS_BUTTON_B, MAIN_APP, 30.0, 90.0);

    button_manager.add_button(int(10.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), SIDES_PLUS_BUTTON_WIDTH,
        SIDES_PLUS_BUTTON_HEIGHT, SIDES_PLUS_BUTTON_R, SIDES_PLUS_BUTTON_G, SIDES_PLUS_BUTTON_B, MAIN_APP, 10.0, 80.0);

    button_manager.add_button(int(30.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), SIDES_MINUS_BUTTON_WIDTH,
        SIDES_MINUS_BUTTON_HEIGHT, SIDES_MINUS_BUTTON_R, SIDES_MINUS_BUTTON_G, SIDES_MINUS_BUTTON_B, MAIN_APP, 30.0, 80.0);

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

void button_callback(int id) {
    if (id < 0) return;

    // button delay
    if (delay_bt > 0) return;
    delay_bt = BUTTON_DELAY;

    // functions
    if (id == 0) {
        // start button
        AppManager::app_state = MAIN_APP;
    }
    else if (id == 1) {
        // color
        // not implemented yet
    }
    else if (id == 2 && AppManager::current_function == FUNCTION_NONE) {
        // draw function
        AppManager::current_function = FUNCTION_DRAW;
        figure_drawer.draw_delay = DRAW_FUNCTION_DELAY;
    }
    else if (id == 3) {
        // cancel function
        AppManager::current_function = FUNCTION_NONE;
    }
    else if (id == 4 && AppManager::current_function == FUNCTION_NONE) {
        // radius +
        figure_drawer.current_radius += RADIUS_INCREASE_DECREASE;
    }
    else if (id == 5 && AppManager::current_function == FUNCTION_NONE) {
        // radius +
        figure_drawer.current_radius -= RADIUS_INCREASE_DECREASE;
    }
    else if (id == 6 && AppManager::current_function == FUNCTION_NONE) {
        figure_drawer.current_sides += SIDES_INCREASE_DECREASE;
    }
    else if (id == 7 && AppManager::current_function == FUNCTION_NONE) {
        figure_drawer.current_sides -= SIDES_INCREASE_DECREASE;
    }


}

// verify button press
int verify_buttons(int button, int x, int y){
    if (button == 0) {
        for (int i = 0; i < button_manager.buttons.size(); i++) {
            if (check_button_position(x, y, button_manager.buttons[i]) && button_manager.buttons[i].app == AppManager::app_state) {
                printf("CLICOU BOTAO! %d \n", i);
                return i;
            }
        }
    }
    return -1;
}

   /*

        ESTOU AQUI

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
   }*/


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
   mx = x;
   my = y;
   if (button == 0) button_callback(verify_buttons(button, x, y));
}
// key down call back
void keyboard(int key){}
// key up call back
void keyboardUp(int key){}


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
