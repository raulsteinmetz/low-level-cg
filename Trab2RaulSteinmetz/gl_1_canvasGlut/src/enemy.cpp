/*

    Made by Raul Steinmetz

    This file is responsable for enemy control

*/


#include "enemy.h"

#define Y_SPEED 50
#define X_SPEED 200
#define DELAYFACTOR 2

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
    this->delay = 0;
    this->colorR = 1;
    this->colorG = 0.4;
    this->colorB = 0.4;

    gun = Gun(Vector2(0, 0), 50, (float) DEFAULT_ANGLE, 250);

    update_pos();
}

void Enemy::draw(){
    // drawing ship
    CV::color(colorR, colorG, colorB);
    CV::polygon(this->polygon_x, this->polygon_y, 3);
    // drawing gun
    gun.draw();
}

void Enemy::takeDamage(int damage) {
    hp -= damage;
}


void Enemy::render(int fps, float screen_width, Vector2 player_pos) {
    update_pos();
    draw();
    moveY(fps);
    moveX(fps, screen_width);
    shoot(fps);
    gun.render(gun.angle, fps);
    aim(player_pos.x, player_pos.y);
    update_pos();
}

void Enemy::moveY(int fps) {
    position.y += speed_factor.y / fps;
}

bool _checkPointInsideTriangle(Vector2 point, Vector2 triangle[]) {
    float x1 = triangle[0].x, x2 = triangle[1].x, x3 = triangle[2].x;
    float y1 = triangle[0].y, y2 = triangle[1].y, y3 = triangle[2].y;
    float x = point.x, y = point.y;

    float denominator = ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
    float a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / denominator;
    float b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / denominator;
    float c = 1 - a - b;

    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}

bool _checkTriangleColision(float traingle_x[], float traingle_y[], Vector2 bulletPosition, float bullet_radius) {

        double x = bulletPosition.x;
        double y = bulletPosition.y;


        Vector2 triangle[3];
        triangle[0] = Vector2(traingle_x[0], traingle_y[0]);
        triangle[1] = Vector2(traingle_x[1], traingle_y[1]);
        triangle[2] = Vector2(traingle_x[2], traingle_y[2]);


        for (int i = 0; i < 3; i++) {
            if (_checkPointInsideTriangle(Vector2(x, y), triangle)) {
                return true;
            }
        }

    return false;
}

bool Enemy::isHit(Vector2 position, float bullet_radius) {
    return _checkTriangleColision(polygon_x, polygon_y, position, bullet_radius);
}

void Enemy::moveX(int fps, float screen_width) {
    // Randomly choose a direction
    int direction = rand() % 2; // 0 for subtracting, 1 for adding

    // Calculate the change in position based on speed_factor and fps
    float delta = speed_factor.x / fps;

    // Update position based on the chosen direction
    if (direction == 0) {
        position.x -= delta;
    } else {
        position.x += delta;
    }

    // Ensure position stays within the screen bounds
    if (position.x < 0.4f * screen_width) {
        position.x = 0.4f * screen_width;
    } else if (position.x > 0.6 * screen_width) {
        position.x = 0.6 * screen_width;
    }
}

void Enemy::shoot(int fps) {
    if (delay <= 0){
        gun.shoot();
        delay = float(fps) * float(DELAYFACTOR);
    } else {
        delay -= 1.0;
    }
}

void Enemy::update_pos() {
    float rad = gun.angle * PI_ / 180.0;
    float spacing = 360.0 / 3.0;

    for (int i = 0; i < 3; i++) {
        polygon_x[i] = position.x + radius * cos(rad);
        polygon_y[i] = position.y + radius * sin(rad);
        rad += (spacing * PI_ / 180.0);
    }

    gun.position.x = polygon_x[0];
    gun.position.y = polygon_y[0];
}


void Enemy::aim(float player_x, float player_y) {
    // check angle between player and enemy
    float angle = atan2(player_y - position.y, player_x - position.x) * 180 / PI_;

    if (gun.angle > angle) {
        gun.angle -= 1;
    } else if (gun.angle < angle) {
        gun.angle += 1;
    }
}
