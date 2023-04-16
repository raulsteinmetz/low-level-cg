#ifndef SLIDER_MANAGER_H
#define SLIDER_MANAGER_H

#include "Slider.h"
#include <vector>

class SliderManager {
public:
    std::vector<Slider> sliders;

    SliderManager();

    // Add a new slider to the list
    void add_slider(int x0, int y0, int bar_width, int bar_height, int circle_radius, float r, float g, float b, int app);

    // Remove a slider from the list
    void remove_slider(int index);

    // Draw all sliders
    void draw_sliders(int state);

    // Highlight sliders based on mouse position
    void highlight_sliders(int x, int y, int state);

    // Add all sliders
    void add_all_sliders();

    // Update the circle position of the currently being modified slider
    void update_slider_circle_position(int mx);

    void handle_click(int x, int y, int state);

    void handle_move(int x, int y, int state);
};

#endif // SLIDER_MANAGER_H
