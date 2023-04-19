#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <vector>
#include "button.h"

class ButtonManager {
public:
    std::vector<Button> buttons;
    ButtonManager();

    // adiciona botao
    void add_button(int x0, int y0, int width, int height, float r, float g, float b, int app, const std::string& name);

    // remove botao
    void remove_button(int index);

    // desenha todos os botoes
    void draw_buttons(int state);

    // indicar botao selecionado
    void highlight_buttons(int x, int y, int state);

    // responsividade, foi retirada
    void update_res();

    // adicionar botoes
    void add_all_buttons();
};


#endif // BUTTON_MANAGER_H
