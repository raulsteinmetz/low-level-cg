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
#include "slider_manager.h"
#include "Frames.h"



/* REQUISITOS PREENCHIDOS NO TRABALHO

Basicos:
  inserir/excluir figura
  cor da figura
  preenchimento da figura
  tamanho da figura
  orientacao da figura (90 graus)
  enviar para frente/traz
  salvar e carregar em arquivo

Extras
  sinalizar qual figura esta selecionada
  rotacionar a figura em qualquer angulo
  permitir poligonos quais quer, desde que regulares e equilateros
  criptografia no arquivo
  sliders
  mover figura
*/


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

int fps;

// figure drawer
FigureDrawer figure_drawer(0, 1, 0);
// button manager
ButtonManager button_manager;
// slider manager
SliderManager slider_manager;

Frames frames;

void add_all_buttons() {
    button_manager.add_button((AppManager::screen_width - BUTTON_WIDTH) / 2, (AppManager::screen_height - BUTTON_HEIGHT) / 2, BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MENU, "START");

    button_manager.add_button(int(22.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH, BUTTON_HEIGHT,
        figure_drawer.current_color_red, figure_drawer.current_color_green, figure_drawer.current_color_blue, MAIN_APP, "COLOR");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "DRAW");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "STOP");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "RADIUS+");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "RADIUS-");

    button_manager.add_button(int(2.0 * AppManager::screen_width / 100.0), int(95.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "SIDES+");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(95.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "SIDES-");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(80.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "SAVE");

    button_manager.add_button(int(12.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP,  "LOAD");

    button_manager.add_button(int(42.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "ANGLE");

    button_manager.add_button(int(60.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "MOVE");

    button_manager.add_button(int(70.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "CLEAN");

    button_manager.add_button(int(80.0 * AppManager::screen_width / 100.0), int(85.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH * 1.7,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "FILL/UNFILL");

    button_manager.add_button(int(70.0 * AppManager::screen_width / 100.0), int(90.0 * AppManager::screen_height / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, MAIN_APP, "UP");


}

void add_all_sliders() {
    slider_manager.add_slider(350, 650, 100, 12, 10, 1, 0, 0, MAIN_APP);
    slider_manager.add_slider(350, 700, 100, 12, 10, 1, 0, 0, MAIN_APP);
    slider_manager.add_slider(350, 750, 100, 12, 10, 1, 0, 0, MAIN_APP);
    slider_manager.add_slider(600, 700, 100, 12, 10, 1, 0, 0, MAIN_APP);
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
            CV::circleFill(figure_drawer.circles[i].cX, figure_drawer.circles[i].cY, figure_drawer.circles[i].radius + 10, figure_drawer.circles[i].sides, figure_drawer.circles[i].angle);
         }
      }
      figure_drawer.circles[i].draw();
   }

   button_manager.draw_buttons(AppManager::app_state);
   button_manager.highlight_buttons(mx, my, AppManager::app_state);

   // preview
   Circle preview;
   preview.sides = figure_drawer.current_sides;
   preview.radius = figure_drawer.current_radius;
   preview.colorR = figure_drawer.current_color_red;
   preview.colorG = figure_drawer.current_color_green;
   preview.colorB = figure_drawer.current_color_blue;
   preview.angle = figure_drawer.angle;
   preview.cX = calc_position(PREVIEW_X_PERCENT, 0, AppManager::screen_width, AppManager::screen_height);
   preview.cY = calc_position(PREVIEW_Y_PERCENT, 1, AppManager::screen_width, AppManager::screen_height);
   preview.filled = figure_drawer.fill;
   preview.draw();

   slider_manager.draw_sliders(AppManager::app_state);
   slider_manager.handle_move(mx, my, AppManager::app_state);
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
    delay_bt = int(fps / 6);

    if (AppManager::current_function == FUNCTION_MOVE) {
        printf("should have moved\n");
        figure_drawer.circles[figure].cX = x;
        figure_drawer.circles[figure].cY = y;
        AppManager::current_function = FUNCTION_MODIFY;
        return;
    }

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
                figure_drawer.save_to_file("./figuras.gr", "key1");
            }
            break;
        }
        case 9: {
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.load_from_file("./figuras.gr", "key1");
            }
            break;
        }
        case 11: {
            if (AppManager::current_function == FUNCTION_MODIFY) {
                AppManager::current_function = FUNCTION_MOVE;
            }
            break;
        }
        case 12: {
            if (AppManager::current_function == FUNCTION_NONE) {
                figure_drawer.n_circles = 0;
            } else if (AppManager::current_function == FUNCTION_MODIFY) {
                for (int i = figure; i < figure_drawer.n_circles; i++) {
                    figure_drawer.circles[i].colorB = figure_drawer.circles[i + 1].colorB;
                    figure_drawer.circles[i].colorR = figure_drawer.circles[i + 1].colorR;
                    figure_drawer.circles[i].colorG = figure_drawer.circles[i + 1].colorG;
                    figure_drawer.circles[i].angle = figure_drawer.circles[i + 1].angle;
                    figure_drawer.circles[i].radius = figure_drawer.circles[i + 1].radius;
                    figure_drawer.circles[i].cX = figure_drawer.circles[i + 1].cX;
                    figure_drawer.circles[i].cY = figure_drawer.circles[i + 1].cY;
                    figure_drawer.circles[i].sides = figure_drawer.circles[i + 1].sides;
                    figure_drawer.circles[i].filled = figure_drawer.circles[i + 1].filled;
                }
                figure_drawer.n_circles -= 1;
                figure = -1;
                AppManager::current_function = FUNCTION_NONE;
            }
        }
        case 13: {
            if (AppManager::current_function == FUNCTION_NONE) {
                if (figure_drawer.fill == 1) {
                    figure_drawer.fill = 0;
                } else {
                    figure_drawer.fill = 1;
                }
            } else if (AppManager::current_function == FUNCTION_MODIFY) {
                if(figure_drawer.circles[figure].filled == 1){
                    figure_drawer.circles[figure].filled = 0;
                } else {
                    figure_drawer.circles[figure].filled = 1;
                }
            }
        }
        case 14: {
            if (AppManager::current_function == FUNCTION_MODIFY) {
                printf("HERE");
                Circle aux(0, 0, 0, 0, 0, 0, 0, 0);
                aux.colorR = figure_drawer.circles[figure].colorR;
                aux.colorB = figure_drawer.circles[figure].colorB;
                aux.colorG = figure_drawer.circles[figure].colorG;
                aux.angle = figure_drawer.circles[figure].angle;
                aux.radius = figure_drawer.circles[figure].radius;
                aux.cX = figure_drawer.circles[figure].cX;
                aux.cY = figure_drawer.circles[figure].cY;
                aux.sides = figure_drawer.circles[figure].sides;
                aux.filled = figure_drawer.circles[figure].filled;

                for (int i = figure; i < figure_drawer.n_circles; i++) {
                    figure_drawer.circles[i].colorB = figure_drawer.circles[i + 1].colorB;
                    figure_drawer.circles[i].colorR = figure_drawer.circles[i + 1].colorR;
                    figure_drawer.circles[i].colorG = figure_drawer.circles[i + 1].colorG;
                    figure_drawer.circles[i].angle = figure_drawer.circles[i + 1].angle;
                    figure_drawer.circles[i].radius = figure_drawer.circles[i + 1].radius;
                    figure_drawer.circles[i].cX = figure_drawer.circles[i + 1].cX;
                    figure_drawer.circles[i].cY = figure_drawer.circles[i + 1].cY;
                    figure_drawer.circles[i].sides = figure_drawer.circles[i + 1].sides;
                    figure_drawer.circles[i].filled = figure_drawer.circles[i + 1].filled;
                }
                figure_drawer.circles[figure_drawer.n_circles].colorB = aux.colorB;
                figure_drawer.circles[figure_drawer.n_circles - 1].colorR = aux.colorR;
                figure_drawer.circles[figure_drawer.n_circles - 1].colorG = aux.colorG;
                figure_drawer.circles[figure_drawer.n_circles - 1].angle = aux.angle;
                figure_drawer.circles[figure_drawer.n_circles - 1].radius = aux.radius;
                figure_drawer.circles[figure_drawer.n_circles - 1].cX = aux.cX;
                figure_drawer.circles[figure_drawer.n_circles - 1].cY = aux.cY;
                figure_drawer.circles[figure_drawer.n_circles - 1].sides = aux.sides;
                figure_drawer.circles[figure_drawer.n_circles - 1].filled = aux.filled;
                figure = figure_drawer.n_circles - 1;
            }
        }
        default: { // Figure selection or modification
            if (AppManager::current_function == FUNCTION_NONE) {
                int f = find_figure(x, y);
                if (f != -1) {
                    AppManager::current_function = FUNCTION_MODIFY;
                    figure = f;
                    slider_manager.sliders[0].value = figure_drawer.circles[figure].colorR;
                    slider_manager.sliders[1].value = figure_drawer.circles[figure].colorG;
                    slider_manager.sliders[2].value = figure_drawer.circles[figure].colorB;
                    slider_manager.sliders[3].value = figure_drawer.circles[figure].angle / 3;
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

    if(AppManager::current_function == FUNCTION_NONE) {
        button_manager.buttons[1].colorR = slider_manager.sliders[0].value;
        figure_drawer.current_color_red = slider_manager.sliders[0].value;
        button_manager.buttons[1].colorG = slider_manager.sliders[1].value;
        figure_drawer.current_color_green = slider_manager.sliders[1].value;
        button_manager.buttons[1].colorB = slider_manager.sliders[2].value;
        figure_drawer.current_color_blue = slider_manager.sliders[2].value;
        figure_drawer.angle = slider_manager.sliders[3].value * 3;
    }

    if (AppManager::current_function == FUNCTION_MODIFY) {
        figure_drawer.circles[figure].colorR = slider_manager.sliders[0].value;
        figure_drawer.circles[figure].colorG = slider_manager.sliders[1].value;
        figure_drawer.circles[figure].colorB = slider_manager.sliders[2].value;
        figure_drawer.circles[figure].angle = slider_manager.sliders[3].value * 3;

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

        slider_manager.handle_click(x, y, AppManager::app_state);

    }
    return -1;
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
    fps = frames.getFrames();

   delay_manager();
}

// main
int main(void)
{
    add_all_buttons();
    add_all_sliders();
    CV::init(&AppManager::screen_width, &AppManager::screen_height, "Canvas 2D");
    CV::run();
}
