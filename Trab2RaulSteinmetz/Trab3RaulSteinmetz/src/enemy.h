/*

    Made by Raul Steinmetz

    This file is responsable for enemy control

*/

#ifndef EMEMY_H
#define EMEMY_H


#include "vector2.h"
#include "gun.h"


class Enemy {
    public:
        int hp;
        int power;
        Vector2 position;
        float radius;
        Vector2 speed_factor;
        Gun gun;
        float delay;
        float colorR;
        float colorG;
        float colorB;
        

        float polygon_x[3];
        float polygon_y[3];

        Enemy();
        Enemy(int hp, int power, float px, float py, float radius, Vector2 speed_factor);
        void update_pos(); // position update and points calculations
        void draw(); // draws enemy
        void render(int fps, float screen_width, Vector2 player_pos); // enemy render
        void takeDamage(int damage); // enemy loses hp
        void moveY(int fps); // move position.y constantly
        bool isHit(Vector2 position, float bullet_radius); // check if enemy is hit by a bullet
        void moveX(int fps, float screen_width); // moves X randomly
        void shoot(int fps); // shoots when the delay is reached
        void aim(float player_x, float player_y); // aims towards player
};



#endif // EMEMY_H