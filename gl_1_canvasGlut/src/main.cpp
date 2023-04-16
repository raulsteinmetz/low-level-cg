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
#include <string>
#include "slider.h"

int up_0_down_1 = 0;

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

Slider sl = Slider(400, 400, 100, 12, 10, 1, 0, 0);
// figure drawer
FigureDrawer figure_drawer(0, 1, 0);
// button manager
ButtonManager button_manager;

void add_all_buttons() {
    button_manager.add_button((AppManager::screen_width - BUTTON_WIDTH) / 2, (AppManager::screen_height - BUTTON_HEIGHT) / 2, BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MENU, 50, 50, "START");

    button_manager.add_button(int(90.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH, BUTTON_HEIGHT,
        figure_drawer.current_color_red, figure_drawer.current_color_green, figure_drawer.current_color_blue, MAIN_APP, 90.0, 90.0, "COLOR");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 2.0, 80.0, "DRAW");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 2.0, 85.0, "STOP");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 2.0, 90.0, "RADIUS+");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 12.0, 90.0, "RADIUS-");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(95.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 2.0, 95.0, "SIDES+");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(95.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 12.0, 95.0, "SIDES-");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 12.0, 80.0, "SAVE");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, 12.0, 85.0, "LOAD");

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

   button_manager.draw_buttons(AppManager::app_state);
   button_manager.highlight_buttons(mx, my, AppManager::app_state);

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

   sl.draw();
    if (sl.being_modified) {
        sl.highlight();
        sl.updateCirclePosition(mx);
   }
}

int find_figure(int x, int y) {
   for (int i = 0; i < figure_drawer.n_circles; i++) {
      if (distance(x, y, figure_drawer.circles[i].cX, figure_drawer.circles[i].cY) < figure_drawer.circles[i].radius) {
         return i;
      }
   }
   return -1;
}

void button_callback(int id, int x, int y) {
    if (delay_bt > 0) {
        return; // Button delay is active, do nothing.
    }
    delay_bt = BUTTON_DELAY;

    switch (id) {
        case 0: { // Start button
            AppManager::app_state = MAIN_APP;
            break;
        }
        case 1: { // Color button
            // Not implemented yet.
            break;
        }
        case 2: { // Draw function button
            if (AppManager::current_function == FUNCTION_NONE) {
                AppManager::current_function = FUNCTION_DRAW;
            }
            break;
        }
        case 3: { // Cancel function button
            if (AppManager::current_function == FUNCTION_DRAW || AppManager::current_function == FUNCTION_MODIFY) {
                AppManager::current_function = FUNCTION_NONE;
            }
            break;
        }
        case 4: { // Increase radius button
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.current_radius += RADIUS_INCREASE_DECREASE;
            }
            else if (AppManager::current_function == FUNCTION_MODIFY) {
                figure_drawer.circles[figure].radius += RADIUS_INCREASE_DECREASE;
            }
            break;
        }
        case 5: { // Decrease radius button
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.current_radius -= RADIUS_INCREASE_DECREASE;
            }
            else if (AppManager::current_function == FUNCTION_MODIFY) {
                figure_drawer.circles[figure].radius -= RADIUS_INCREASE_DECREASE;
            }
            break;
        }
        case 6: { // Increase sides button
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.current_sides += SIDES_INCREASE_DECREASE;
            }
            else if (AppManager::current_function == FUNCTION_MODIFY) {
                figure_drawer.circles[figure].sides += SIDES_INCREASE_DECREASE;
            }
            break;
        }
        case 7: { // Decrease sides button
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.current_sides -= SIDES_INCREASE_DECREASE;
            }
            else if (AppManager::current_function == FUNCTION_MODIFY) {
                figure_drawer.circles[figure].sides -= SIDES_INCREASE_DECREASE;
            }
            break;
        }
        case 8: {
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.save_circles_to_file("circles.dat");
            }
            break;
        }
        case 9: {
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.load_circles_from_file("circles.dat");
            }
            break;
        }
        default: { // Figure selection or modification
            if (AppManager::current_function == FUNCTION_NONE) {
                int f = find_figure(x, y);
                if (f != -1) {
                    AppManager::current_function = FUNCTION_MODIFY;
                    figure = f;
                }
            }
            else if (AppManager::current_function == FUNCTION_DRAW) {
                figure_drawer.add_circle(x, y);
            }
            else if (AppManager::current_function == FUNCTION_MODIFY) {
                int f = find_figure(x, y);
                if (f == figure) {
                    AppManager::current_function = FUNCTION_NONE;
                    figure = -1;
                }
            }
            break;
        }
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
        if (sl.being_modified == true){
            sl.being_modified = false;
        }
        else if (sl.checkInteraction(x, y)) {
            sl.being_modified = true;
        }

    }
    return -1;
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
   mx = x;
   my = y;

   if (button == 0) {
    if (up_0_down_1 == 0){
        up_0_down_1 = 1;
    }
    else {
        up_0_down_1 = 0;
        return;
    }
    button_callback(verify_buttons(button, x, y), x, y);

   }
}
// key down call back
void keyboard(int key){}
// key up call back
void keyboardUp(int key){}


// draw delay
void delay_manager(){
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
