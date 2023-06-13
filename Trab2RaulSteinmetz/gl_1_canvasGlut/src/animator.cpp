#include "animator.h"

#define EXPLOSION_END 0.5
#define DAMAGE_END 0.25

// circle
CircleParticle::CircleParticle() {
    radius = 0;
    x = 0;
    y = 0;
    r = 0;
    g = 0;
    b = 0;
}

void CircleParticle::draw() {
    CV::color(r, g, b);
    CV::circleFill(x, y, radius, 20);
}


// square
SquareParticle::SquareParticle() {
    side = 0;
    x = 0;
    y = 0;
    r = 0;
    g = 0;
    b = 0;
}

void SquareParticle::draw() {
    CV::color(r, g, b);
    CV::rectFill(x, y, x + side, y + side);
}



// constructor
Animator::Animator() {
    explosion_time = EXPLOSION_END ;
}

// functions
void Animator::enemy_explosion_init(float x, float y) {
    for (int i = 0; i < 20; i++) {
        CircleParticle particle;
        particle.radius = 5;

        // randomize initial positions in a radius of 20
        particle.x = x + (rand() % 40) - 20;
        particle.y = y + (rand() % 40) - 20;

        // randomize colors between yellow, red and black
        particle.r = 1;
        particle.g = (rand() % 100) / 100.0;
        particle.b = 0;

        explosion_objects.push_back(particle);
    }
}

void Animator::enemy_explosion_handle(float fps) {
    for (std::list<CircleParticle>::iterator it = explosion_objects.begin(); it != explosion_objects.end(); ++it) {
        // randomize angle in radians
        float angle = (rand() % 360) * 3.1415 / 180.0;
        // randomize speed
        float speed = (rand() % 100);
        // update position
        it->x += cos(angle) * speed / fps;
    }

    // check if list is not empty
    if (!explosion_objects.empty()) {
        // draw all particles
        for (std::list<CircleParticle>::iterator it = explosion_objects.begin(); it != explosion_objects.end(); ++it) {
            it->draw();
        }
        explosion_time -= 1.0 / fps;
    }



    if (explosion_time <= 0) {
        explosion_objects.clear();
        explosion_time = EXPLOSION_END;
    }
    
}

void Animator::damage_init(float x, float y) {
    for (int i = 0; i < 5; i++) {
        SquareParticle particle;
        particle.side = 5;

        // randomize initial positions in a radius of 20
        particle.x = x + (rand() % 40) - 20;
        particle.y = y + (rand() % 40) - 20;

        // randomize colors between yellow, red and black
        particle.r = 1;
        particle.g = (rand() % 100) / 100.0;
        particle.b = 0;

        damage_objects.push_back(particle);
    }
}

void Animator::damage_handle(float fps) {
    for (std::list<SquareParticle>::iterator it = damage_objects.begin(); it != damage_objects.end(); ++it) {
        // randomizing particle movement angle
        float angle = (rand() % 360) * 3.1415 / 180.0;
        // randomize speed
        float speed = (rand() % 100);
        // update position
        it->x += cos(angle) * speed / fps;
    }

    // check if list is not empty
    if (!damage_objects.empty()) {
        // draw all particles
        for (std::list<SquareParticle>::iterator it = damage_objects.begin(); it != damage_objects.end(); ++it) {
            it->draw();
        }
        damage_time -= 1.0 / fps;
    }



    if (damage_time <= 0) {
        damage_objects.clear();
        damage_time = EXPLOSION_END;
    }
    
}

void Animator::stars_init(float screen_width, float screen_height) {
    // randomize 50 stars in screen width, (-screen_height, screen_height)
    for (int i = 0; i < 50; i++) {
        CircleParticle particle;
        particle.radius = 2;

        // randomize initial positions in a radius of 20
        particle.x = (rand() % (int)screen_width);
        particle.y = (rand() % (int)screen_height);

        // randomize colors between yellow, red and black
        particle.r = 1;
        particle.g = 1;
        particle.b = 1;

        stars.push_back(particle);
    }
}

void Animator::stars_handle(float fps, float screen_height) {
    // decrease y position of all stars
    for (std::list<CircleParticle>::iterator it = stars.begin(); it != stars.end(); ++it) {
        if (it->y > screen_height)
            it->y -= screen_height;
        else
            it->y += 5 / fps;
        it->draw();
    }
}


void Animator::render(float fps, float screen_height) {
    enemy_explosion_handle(fps);
    damage_handle(fps);
    stars_handle(fps, screen_height);
}

