/*

    Made by Raul Steinmetz

    This file is responsable for gun (player's and enemy's), shooting, bullets physics

*/

#include "gun.h"
#include "enemy.h"
#include "list"

#define DELAY_FACTOR 0.25

#define PI_ 3.1415

float angle_to_radians_(float angle) {
    return angle * PI_ / 180.0;
}

float radians_to_angle_(float rad) {
    return rad * 180 / PI_;
}


// bullet constructor
Bullet::Bullet(Vector2 position, float speed_factor, float angle, float radius)
       : position(position), speed_factor(speed_factor), angle(angle), radius(radius) {}

void Bullet::draw() {
    CV::color(1.0, 1.0, 1.0);
    CV::circleFill(position.x, position.y, radius, 20);
}


// constructor
Gun::Gun(){}
Gun::Gun(Vector2 position, int delay_factor, float angle, float current_bullet_speed_factor)
    : position(position), delay(delay), angle(angle), current_bullet_speed_factor(current_bullet_speed_factor)
{
    app_fps = 0;
    delay = 0;
}

// gun methods
void Gun::shoot()
{
    if (delay >= 0) {
        return;
    }
    Bullet bullet(position, current_bullet_speed_factor, angle, float(BULLET_RADIUS));
    bullets.push_back(bullet);
    delay = int(float(DELAY_FACTOR) * float(app_fps));
}
void Gun::updateDelay() {
    delay -= 1;
}


void Gun::updateBullets() {
    for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
        Bullet& bullet = *it;
        float rad = angle_to_radians_(bullet.angle);
        bullet.position.x += (bullet.speed_factor / float(app_fps)) * cos(rad);
        bullet.position.y += (bullet.speed_factor / float(app_fps)) * sin(rad);
    } 
}


void Gun::draw() {
    CV::color(1.0, 1.0, 1.0);
    CV::circle(position.x, position.y, 20, 20);
    // Draw bullets
    for (std::list<Bullet>::const_iterator it = bullets.begin(); it != bullets.end(); ++it) {
        Bullet bullet = *it;
        bullet.draw();
    }

}

void Gun::updateAngle(float new_angle) {
    angle = new_angle;
}

void Gun::updateParameters(int fps) {
    app_fps = fps;
}


void Gun::render(float new_angle, float fps) {
    draw();
    updateBullets();
    updateDelay();
    updateAngle(new_angle);
    updateParameters(fps);
}
