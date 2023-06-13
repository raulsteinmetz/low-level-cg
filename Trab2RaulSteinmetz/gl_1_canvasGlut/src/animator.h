#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "gl_canvas2d.h"
#include <list>

/*

    Made by Raul Steinmetz

    This file is responsable for the animations in the game

*/

class CircleParticle {
    public:
        float radius;
        float x, y;
        float r;
        float g;
        float b;
        CircleParticle();
        void draw(); // draws particle
};

class SquareParticle {
    public:
        float side;
        float x, y;
        float r;
        float g;
        float b;
        SquareParticle();
        void draw(); // draws particle
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
        Animator();

        // functions
        void enemy_explosion_init(float x, float y); // explosion setup
        void enemy_explosion_handle(float fps); // animation render
        void damage_init(float x, float y); // damage setup
        void damage_handle(float fps); // damage render
        void stars_init(float screen_width, float screen_height); // stars setup
        void stars_handle(float fps, float screen_height); // stars handle
        void render(float fps, float screen_height); // animator render (calls all renders)
};

#endif // ANIMATOR_H