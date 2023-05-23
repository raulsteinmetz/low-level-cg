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

        float polygon_x[3];
        float polygon_y[3];

        Enemy();
        Enemy(int hp, int power, float px, float py, float radius);
        void update_pos();
        void draw();
        void render();
        void take_damage(int damage);
};



#endif // EMEMY_H