#include "slider_manager.h"
#include "slider.h"
SliderManager::SliderManager() {}



void SliderManager::add_slider(int x0, int y0, int bar_width, int bar_height, int circle_radius, float r, float g, float b, int app) {
    this->sliders.push_back(Slider(x0, y0, bar_width, bar_height, circle_radius, r, g, b, app));
}

void SliderManager::remove_slider(int index) {
    this->sliders.erase(sliders.begin() + index);
}

void SliderManager::draw_sliders(int state) {
    for (int i = 0; i < sliders.size(); i++) {
        if (state == sliders[i].app)
            sliders[i].draw();
    }
}

void SliderManager::highlight_sliders(int x, int y, int state) {
    for (int i = 0; i < this->sliders.size(); i++) {
       if (state == sliders[i].app && sliders[i].checkInteraction(x, y)){
            sliders[i].highlight();
       }
    }
}

void SliderManager::handle_click(int x, int y, int state) {
    for (int i = 0; i < this->sliders.size(); i++) {
       if (state == sliders[i].app && sliders[i].checkInteraction(x, y)){
            sliders[i].being_modified = true;

       } else {
            sliders[i].being_modified = false;
       }
    }
}

void SliderManager::handle_move(int x, int y, int state) {
    for (int i = 0; i < this->sliders.size(); i++) {
       if (state == sliders[i].app && sliders[i].being_modified == true) {
            sliders[i].highlight();
            sliders[i].updateCirclePosition(x);
       }
    }
}

