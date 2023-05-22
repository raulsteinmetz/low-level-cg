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
    double max_speed_factor;
    double current_speed_factor;
    double true_speed;
    int missile_delay;
    int bullet_delay;
    int hp;
    int bullet_power;
    int missile_power;
    float angle;
    float radius;
    Vector2 position;


    // render
    int color_r;
    int color_g;
    int color_b;
    float polygon_x[3];
    float polygon_y[3];

    // movement
    bool go_forward;
    bool go_left;
    bool go_right;
    bool go_backwards;

    // shooting
    bool is_shooting;

    void movePos (float angle_);



public:
    Gun gun;
    // Constructor
    Starship(double max_speed_factor, double current_speed_factor, int hp, float px, float py, float radius);

    void render(int fps, int mouseX, int mouseY);
    void update_parameters(int fps);
    void draw();
    void updatePos();
    void aim(float x, float y);
    void handleKeyboard(int command, int up);
    void handleMouse(int button, int state);
    void movePos();
    void shoot();

};

#endif // STARSHIP_H
