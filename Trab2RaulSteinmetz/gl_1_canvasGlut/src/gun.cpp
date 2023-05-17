#include "gun.h"
#include "gl_canvas2d.h"
#include "stdio.h"

#define DELAY_FACTOR 0.25


// bullet constructor
Bullet::Bullet(Vector2 position, float speed_factor, float angle, float radius)
       : position(position), speed_factor(speed_factor), angle(angle), radius(radius) {}


// constructor
Gun::Gun(){}
Gun::Gun(Vector2 position, int delay_factor, float angle, float current_bullet_speed_factor, float max_bullet_speed_factor)
    : position(position), delay(delay), angle(angle), current_bullet_speed_factor(current_bullet_speed_factor),
      max_bullet_speed_factor(max_bullet_speed_factor){}

// gun methods
void Gun::shoot()
{
    if (delay >= 0) {
        return;
    }
    Bullet bullet(position, current_bullet_speed_factor, angle, float(BULLET_RADIUS));
    bullets.push_back(bullet);
    printf("POW!\n");
    delay = int(float(DELAY_FACTOR) * float(app_fps));
    printf("%d\n", delay);
}
void Gun::updateDelay() {
    delay -= 1;
}

