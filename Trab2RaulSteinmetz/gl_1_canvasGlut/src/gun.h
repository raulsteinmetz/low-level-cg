#ifndef GUN_H
#define GUN_H

#include "Vector2.h"
#include <list>
#include "stdio.h"

#define BULLET_RADIUS 5

class Bullet {
public:
    float speed_factor;
    float app_fps;
    float angle;
    float radius;
    Vector2 position;


    Bullet(Vector2 position, float speed_factor, float angle, float radius);

};


class Gun {
public:
    std::list<Bullet> bullets;
    Vector2 position;
    int delay;
    float angle;
    float current_bullet_speed_factor;
    float max_bullet_speed_factor;
    float app_fps;


    Gun();
    Gun(Vector2 position, int delay, float angle, float current_bullet_speed_factor, float max_bullet_speed_factor);
    void shoot();
    void updateDelay();

};




#endif // GUN_H
