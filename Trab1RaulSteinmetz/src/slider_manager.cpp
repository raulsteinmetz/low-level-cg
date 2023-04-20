#include "slider_manager.h"
#include "slider.h"

// Manager para Sliders (de RGB e Angulo)
SliderManager::SliderManager() {}

// Adiciona novo slider ao manager
void SliderManager::add_slider(int x0, int y0, int bar_width, int bar_height, int circle_radius, float r, float g, float b, int app) {
    this->sliders.push_back(Slider(x0, y0, bar_width, bar_height, circle_radius, r, g, b, app));
}

// Remove slider do manager
void SliderManager::remove_slider(int index) {
    this->sliders.erase(sliders.begin() + index);
}

// Desenhar todos os sliders do manager
void SliderManager::draw_sliders(int state) {
    for (int i = 0; i < sliders.size(); i++) {
        if (state == sliders[i].app)
            sliders[i].draw();
    }
}

// Sinalizacao do slider (quando o mouse passa encima)
void SliderManager::highlight_sliders(int x, int y, int state) {
    for (int i = 0; i < this->sliders.size(); i++) {
       if (state == sliders[i].app && sliders[i].checkInteraction(x, y)){
            sliders[i].highlight();
       }
    }
}

// Click no Slider (Para arrastar)
void SliderManager::handle_click(int x, int y, int state) {
    for (int i = 0; i < this->sliders.size(); i++) {
       if (state == sliders[i].app && sliders[i].checkInteraction(x, y)){
            sliders[i].being_modified = true;

       } else {
            sliders[i].being_modified = false;
       }
    }
}

// Slider Modificado
void SliderManager::handle_move(int x, int y, int state) {
    for (int i = 0; i < this->sliders.size(); i++) {
       if (state == sliders[i].app && sliders[i].being_modified == true) {
            sliders[i].highlight();
            sliders[i].updateCirclePosition(x);
       }
    }
}

void SliderManager::add_all_sliders(int main_app) {
    add_slider(350, 650, 100, 12, 10, 1, 0, 0, main_app);
    add_slider(350, 700, 100, 12, 10, 1, 0, 0, main_app);
    add_slider(350, 750, 100, 12, 10, 1, 0, 0, main_app);
    add_slider(600, 700, 100, 12, 10, 1, 0, 0, main_app);
}

