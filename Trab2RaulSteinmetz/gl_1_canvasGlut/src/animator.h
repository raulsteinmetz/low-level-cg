#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "gl_canvas2d.h"
#include <list>

class CircleParticle {
    public:
        float radius;
        float x, y;
        float r;
        float g;
        float b;
        CircleParticle();
        void draw();
};

class SquareParticle {
    public:
        float side;
        float x, y;
        float r;
        float g;
        float b;
        SquareParticle();
        void draw();
};

class Animator {
    private:
        // list of animation objects
        std::list<CircleParticle> explosion_objects;
        std::list<SquareParticle> player_damage_objects;
        std::list<SquareParticle> enemy_damage_objects;
        std::list<SquareParticle> fuel_objects;

        float explosion_time;


    public:
        // constructor
        Animator();

        // functions
        void enemy_explosion_init(float x, float y);
        void enemy_explosion_handle(float fps);
        void enemy_damage(float x, float y, float fps);
        void player_damage(float x, float y, float fps);
        void player_fuel(float x, float y, float fps);
        void render(float fps);
};

#endif // ANIMATOR_H