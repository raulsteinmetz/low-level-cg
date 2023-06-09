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
        int hp;
        int bullet_power;
        float angle;
        float radius;
        float fps;
        Vector2 position;


        // physics 2d
        float polygon_x[3];
        float polygon_y[3];



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

        void take_damage(int damage);



    public:
        Gun gun;
        // Constructor
        Starship(double speed_factor, int hp, float px, float py, float radius);

        // getters
        Vector2 get_position();
        double get_velocity();


        void render(int fps, int mouseX, int mouseY);
        void update_parameters(float fps);
        void draw();
        void update_pos();
        void aim(float x, float y);
        void handleKeyboard(int command, int up);
        void handleMouse(int button, int state);
        void movePos();
        void shoot();

};

#endif // STARSHIP_H
