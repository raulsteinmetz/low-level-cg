#include "button_manager.h"
#include "interface.h"

// Manager de Botoes
ButtonManager::ButtonManager() {}
// Adicionar Botao
void ButtonManager::add_button(int x0, int y0, int width, int height, float r, float g, float b, int app, const std::string& name) {
    buttons.push_back(Button(x0, y0, width, height, r, g, b, app, name));
}
// Remover Botao
void ButtonManager::remove_button(int index) {
    buttons.erase(buttons.begin() + index);
}
// Desenhar todos os Botoes
void ButtonManager::draw_buttons(int state) {
    for (int i = 0; i < buttons.size(); i++) {
        if (state == buttons[i].app)
            buttons[i].draw();
    }
}
// Checar se o mouse esta sobre o botao
int check_button_position(int x, int y, Button b) {
   if (x > b.x0 && y > b.y0 && x < b.x0 + b.width && y < b.y0 + b.height) {
      return HIGHLIGHTED;
   }
   return HIGHLIGHT_NONE;
}
// Indicar qual botao esta o mouse esta em cima
void ButtonManager::highlight_buttons(int x, int y, int state) {
    for (int i = 0; i < buttons.size(); i++) {
        if (check_button_position(x, y, buttons[i]) != HIGHLIGHT_NONE) {
            if (state == buttons[i].app)
                buttons[i].highlight();
        }
    }
}

void ButtonManager::add_all_buttons(int screenWidth, int screenHeight, int state_menu, int state_app) {
    add_button((screenWidth - BUTTON_WIDTH) / 2, (screenHeight - BUTTON_HEIGHT) / 2, BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_menu, "START");

    add_button(int(22.0 * screenWidth / 100.0), int(85.0 * screenHeight / 100.0), BUTTON_WIDTH, BUTTON_HEIGHT,
        0.5, 0.5, 0.5, state_app, "COLOR");

    add_button(int(2.0 * screenWidth / 100.0), int(80.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "DRAW");

    add_button(int(2.0 * screenWidth / 100.0), int(85.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "STOP");

    add_button(int(2.0 * screenWidth / 100.0), int(90.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "RADIUS+");

    add_button(int(12.0 * screenWidth / 100.0), int(90.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "RADIUS-");

    add_button(int(2.0 * screenWidth / 100.0), int(95.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "SIDES+");

    add_button(int(12.0 * screenWidth / 100.0), int(95.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "SIDES-");

    add_button(int(12.0 * screenWidth / 100.0), int(80.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "SAVE");

    add_button(int(12.0 * screenWidth / 100.0), int(85.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app,  "LOAD");

    add_button(int(42.0 * screenWidth / 100.0), int(85.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "ANGLE");

    add_button(int(60.0 * screenWidth / 100.0), int(85.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "MOVE");

    add_button(int(70.0 * screenWidth / 100.0), int(85.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "CLEAN");

    add_button(int(80.0 * screenWidth / 100.0), int(85.0 * screenHeight / 100.0), BUTTON_WIDTH * 1.7,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "FILL/UNFILL");

    add_button(int(70.0 * screenWidth / 100.0), int(90.0 * screenHeight / 100.0), BUTTON_WIDTH,
        BUTTON_HEIGHT, BUTTON_COLOR_R, BUTTON_COLOR_G, BUTTON_COLOR_B, state_app, "UP");
}
