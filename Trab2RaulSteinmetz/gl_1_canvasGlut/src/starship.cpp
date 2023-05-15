#include "starship.h"
#include "gl_canvas2d.h"

#include "util.h"
#include "stdio.h"

// Constructor
Starship::Starship(double max_speed, double current_speed, int missile_delay,
                   int bullet_delay, int bullet_power, int missile_power, int hp, float px, float py, float radius)
                   : max_speed(max_speed), current_speed(current_speed), missile_delay(missile_delay),
                     bullet_delay(bullet_delay), bullet_power(bullet_power), missile_power(missile_power),
                     hp(hp), radius(radius), px(px), py(py)
{
    angle = 270.0;
    updatePos();
}

void Starship::updatePos() {
    float rad = angle_to_radians(angle);
    float spacing = 360.0 / 3.0;

    for (int i = 0; i < 3; i++) {
        polygon_x[i] = px + radius * cos(rad);
        polygon_y[i] = py + radius * sin(rad);
        rad += angle_to_radians(spacing);
    }

    gun_x = polygon_x[0];
    gun_y = polygon_y[0];
}

void Starship::aim(float x, float y) {
    Vector2 direction(x - px, y - py);
    float rad = atan2(direction.y, direction.x);
    angle = radians_to_angle(rad);

}


// Getter implementations
double Starship::getMaxSpeed() {
    return max_speed;
}

double Starship::getCurrentSpeed() {
    return current_speed;
}

int Starship::getMissileDelay() {
    return missile_delay;
}

int Starship::getBulletDelay() {
    return bullet_delay;
}

int Starship::getHP() {
    return hp;
}

int Starship::getBulletPower() {
    return bullet_power;
}

int Starship::getMissilePower() {
    return missile_power;
}

int Starship::getColor_r() {
    return color_r;
}

int Starship::getColor_g() {
    return color_g;
}

int Starship::getColor_b() {
    return color_b;
}



// Setter implementations
void Starship::setMaxSpeed(double max_speed) {
    this->max_speed = max_speed;
}

void Starship::setCurrentSpeed(double current_speed) {
    this->current_speed = current_speed;
}

void Starship::setMissileDelay(int missile_delay) {
    this->missile_delay = missile_delay;
}

void Starship::setBulletDelay(int bullet_delay) {
    this->bullet_delay = bullet_delay;
}

void Starship::setHP(int hp) {
    this->hp = hp;
}

void Starship::setBulletPower(int bullet_power) {
    this->bullet_power = bullet_power;
}

void Starship::setMissilePower(int missile_power) {
    this->missile_power = missile_power;
}

void Starship::setColor_r(int color_r) {
    this->color_r = color_r;
}

void Starship::setColor_g(int color_g) {
    this->color_g = color_g;
}

void Starship::setColor_b(int color_b) {
    this->color_b = color_b;
}



void Starship::draw() {
    CV::color(0, 0, 0);
    CV::polygon(this->polygon_x, this->polygon_y, 3);
    CV::color(0.5, 0.5, 0.5);
    CV::circle(gun_x, gun_y, 5, 20);
}
