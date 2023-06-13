/*

    Made by Raul Steinmetz

    This file is responsable for managing the player class
        

*/

#ifndef STARSHIP_H
#define STARSHIP_H


#include <string>
#include "Vector2.h"
#include "gun.h"
#include "gl_canvas2d.h"

#define MOVE_FORWARD 119
#define MOVE_BACKWARDS 115
#define MOVE_RIGHT 100
#define MOVE_LEFT 97

#define SHOOT_BUTTON 0



#define MAX_SPEED 400


class Starship {
    private:
        // attributes
        double speed_factor;
        int bullet_delay;
        int bullet_power;
        float angle;
        float radius;
        float fps;




        // render
        int color_r;
        int color_g;
        int color_b;

        // movement
        bool go_forward;
        bool go_left;
        bool go_right;
        bool go_backwards;

        // shooting
        bool is_shooting;

        void movePos (float angle_);




    public:
        int hp;
        Gun gun;
        Vector2 position;
        // Constructor
        Starship();
        Starship(double speed_factor, int hp, float px, float py, float radius);

        // getters
        Vector2 get_position();
        double get_velocity();


        void render(int fps, int mouseX, int mouseY); // player render
        void update_parameters(float fps); // fps control
        void draw(); // draw player
        void update_pos(); // update player position and physics
        void aim(float x, float y); // aiming  
        void handleKeyboard(int command, int up); // keyboard input handle
        void handleMouse(int button, int state); // mouse input handle
        void movePos(); // move player
        void shoot(); // shoot control
        bool isHit(Vector2 position, float bullet_radius); // check if player was hit by given bullet

        void takeDamage(int damage); // decreases player hp

        void drawHP(); // hp drawing

        // attributes
        // physics 2d
        float polygon_x[3];
        float polygon_y[3];

};

#endif // STARSHIP_H
