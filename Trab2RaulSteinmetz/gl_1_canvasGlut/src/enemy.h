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

        float polygon_x[3];
        float polygon_y[3];

        Enemy();
        Enemy(int hp, int power, float px, float py, float radius);
        void update_pos();
        void draw();
        void render(int fps, float screen_width, Vector2 player_pos);
        void takeDamage(int damage);
        void moveY(int fps);
        bool isHit(Vector2 position, float bullet_radius);
        void moveX(int fps, float screen_width);
        void shoot(int fps);
        void aim(float player_x, float player_y);
};



#endif // EMEMY_H