#include "enemy.h"

#define Y_SPEED 0.1
#define X_SPEED 0.1

#define DEFAULT_ANGLE 90
#define PI_ 3.1415


Enemy::Enemy() {}

Enemy::Enemy(int hp, int power, float px, float py, float radius) {
    this->hp = hp;
    this->power = power;
    this->position.x = px;
    this->position.y = py;
    this->radius = radius;
    this->speed_factor.x = X_SPEED;
    this->speed_factor.y = Y_SPEED;
    gun = Gun(Vector2(0, 0), 50, (float) DEFAULT_ANGLE, 0.0001, 0.001);

    update_pos();
}

void Enemy::update_pos() {
    float rad = DEFAULT_ANGLE * PI_ / 180.0;
    float spacing = 360.0 / 3.0;

    for (int i = 0; i < 3; i++) {
        polygon_x[i] = position.x + radius * cos(rad);
        polygon_y[i] = position.y + radius * sin(rad);
        rad += (spacing * PI_ / 180.0);
    }

    gun.position.x = polygon_x[0];
    gun.position.y = polygon_y[0];

}

void Enemy::draw(){
    // drawing ship
    CV::color(1, 0.4, 0.4);
    CV::polygon(this->polygon_x, this->polygon_y, 3);
    // drawing gun
    gun.draw();
}


void Enemy::render() {
    update_pos();
    draw();
    gun.updateBullets();
}
