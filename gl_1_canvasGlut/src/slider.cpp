#include "slider.h"
#include "gl_canvas2d.h"

#define SIDES 20
#define HIGHLIGHT_R 0
#define HIGHLIGHT_G 0
#define HIGHLIGHT_B 0
#define HIGHLIGHT_FACTOR 2
#define CIRCLE_OFFSET_Y -4

Slider::Slider(){}

Slider::Slider(int x0, int y0, int bar_width, int bar_height, int circle_radius, float r, float g, float b, int app){
    this->x0 = x0;
    this->y0 = y0;
    this->bar_width = bar_width;
    this->bar_height = bar_height;
    this->circle_radius = circle_radius;
    this->colorR = r;
    this->colorG = g;
    this->colorB = b;
    this->value = 0.5;
    this->being_modified = false;
    this->app = app;
}

void Slider::draw() {
    CV::color(this->colorR, this->colorG, this->colorB);
    CV::rectFill(this->x0, this->y0, this->x0 + this->bar_width, this->y0 + this->bar_height);
    CV::color(0, 0, 0);
    this->circle_x = getCircleXFromValue();
    this->circle_y = this->y0 + this->circle_radius + CIRCLE_OFFSET_Y;
    CV::circleFill(this->circle_x, this->circle_y, this->circle_radius, SIDES, 0);
    CV::color(1, 1, 1);
}

void Slider::highlight(){
    CV::color(HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
    CV::circleFill(this->circle_x, this->circle_y, this->circle_radius + HIGHLIGHT_FACTOR , SIDES, 0);
    draw();
}

float Slider::getValueFromCircleX(float circle_x) {
    float slider_range = this->bar_width - (2 * this->circle_radius);
    float value = (circle_x - this->x0 - this->circle_radius) / slider_range;
    return value;
}

float Slider::getCircleXFromValue() {
    float slider_range = this->bar_width - (2 * this->circle_radius);
    float circle_x = this->x0 + this->circle_radius + (this->value * slider_range);
    return circle_x;
}

bool Slider::checkInteraction(int x, int y) {
    // Calculate the distance from the (x, y) point to the center of the circle
    float dx = x - this->circle_x;
    float dy = y - this->y0;

    float distance = sqrt(dx * dx + dy * dy);

    // Check if the distance is less than or equal to the radius of the circle
    if (distance <= this->circle_radius) {
        return true;
    } else {
        return false;
    }
}

void Slider::updateCirclePosition(int mx) {
    // Calculate the new position of the circle based on the mouse x coordinate
    int new_circle_x = mx - this->circle_radius;

    // Make sure the circle does not go beyond the bounds of the slider bar
    if (new_circle_x < this->x0 + this->circle_radius) {
        new_circle_x = this->x0 + this->circle_radius;
    } else if (new_circle_x > this->x0 + this->bar_width - this->circle_radius) {
        new_circle_x = this->x0 + this->bar_width - this->circle_radius;
    }

    // Update the position of the circle
    this->circle_x = new_circle_x;

    // Update the value of the slider based on the new position of the circle
    float slider_range = this->bar_width - (2 * this->circle_radius);
    this->value = getValueFromCircleX(new_circle_x);
}
