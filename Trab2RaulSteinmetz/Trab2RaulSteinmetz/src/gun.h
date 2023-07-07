/*

    Made by Raul Steinmetz

    This file is responsable for gun (player's and enemy's), shooting, bullets physics

*/


#ifndef GUN_H
#define GUN_H

#include "Vector2.h"
#include <list>
#include "stdio.h"
#include "gl_canvas2d.h"


#define BULLET_RADIUS 5

class Bullet {
public:
    float speed_factor;
    float app_fps;
    float angle;
    float radius;
    Vector2 position;

    Bullet(Vector2 position, float speed_factor, float angle, float radius);
    void draw(); // draws bullet

};


class Gun {
public:
    std::list<Bullet> bullets;
    Vector2 position;
    int delay;
    float angle;
    float current_bullet_speed_factor;
    float app_fps;


    Gun();
    Gun(Vector2 position, int delay, float angle, float current_bullet_speed_factor);
    void shoot(); // shoots bullet on the current angle direction
    void updateDelay(); // reduces bullet delay
    void draw(); // draw all the bullets and the gun
    void updateBullets(); // update bullet positions
    void updateAngle(float new_angle); // update gun angles
    void render(float new_angle, float fps); // gun render
    void updateParameters(int fps); // used for fps control
};




#endif // GUN_H
