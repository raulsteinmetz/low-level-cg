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
        std::list<SquareParticle> damage_objects;
        std::list<SquareParticle> fuel_objects;
        std::list<CircleParticle> stars;

        float explosion_time;
        float damage_time;


    public:
        // constructor
        Animator();

        // functions
        void enemy_explosion_init(float x, float y);
        void enemy_explosion_handle(float fps);
        void damage_init(float x, float y);
        void damage_handle(float fps);
        void stars_init(float screen_width, float screen_height);
        void stars_handle(float fps, float screen_height);
        void render(float fps, float screen_height);
};

#endif // ANIMATOR_H