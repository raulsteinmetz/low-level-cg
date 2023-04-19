#ifndef SLIDER_MANAGER_H
#define SLIDER_MANAGER_H

#include "Slider.h"
#include <vector>

// manager de sliders

class SliderManager {
public:
    std::vector<Slider> sliders;

    SliderManager();

    // adiciona slider
    void add_slider(int x0, int y0, int bar_width, int bar_height, int circle_radius, float r, float g, float b, int app);

    // remove slider
    void remove_slider(int index);

    // desenha sliders
    void draw_sliders(int state);

    // indica mouse em cima de um slider
    void highlight_sliders(int x, int y, int state);

    // adiciona sliders no manager
    void add_all_sliders();

    // interacao do usuario com slider
    void update_slider_circle_position(int mx);
    void handle_click(int x, int y, int state);
    void handle_move(int x, int y, int state);
};

#endif // SLIDER_MANAGER_H
