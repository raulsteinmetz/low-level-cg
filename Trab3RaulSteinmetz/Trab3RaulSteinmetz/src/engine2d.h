#ifndef ENGINE2D_H
#define ENGINE2D_H

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "math.h"
#include "stdio.h"

#define ENGINE_ON true
#define ENGINE_OFF false


class Piston {
    public:
        Vector2 center_screw_position;
        Vector2 side_lenght;
        double connecting_rod_length;
        Vector2 connecting_rod_end_effector_position;
        double rad;

        Piston();
        Piston(Vector2 center_screw_position, Vector2 side_lenght, double connecting_rod_length, double rad);

        void draw();
        void update(Vector2 crank_center_screw_position, Vector2 end_effector_postition);
        void update_center_screw_position(Vector2 crank_center_screw_position);
};


class Crank {
    public:
        Vector2 center_screw_position;
        double radius;
        double moving_screw_radians;
        Vector2 moving_screw_position;
        bool state;
        double rpm;

        Crank();
        Crank(Vector2 center_screw_position, double radius, double moving_screw_radians, bool state);
        void draw();
        void update(double fps);
        void stop();
        void start();
        Vector2 calculate_moving_screw_position();
};

class OnePistonEngine2D {
    public:
        double rpm;
        Crank crank;
        Piston piston;
        OnePistonEngine2D();
        OnePistonEngine2D(Vector2 center_screw_position, double radius, double moving_screw_radians, bool state, double rpm);
        void draw();
        void update(double fps);
};

class TwoPistonEngine2D {
    public:
        double rpm;
        Crank crank;
        Piston right_piston;
        Piston left_piston;
        TwoPistonEngine2D();
        TwoPistonEngine2D(Vector2 center_screw_position, double radius, double moving_screw_radians, bool state, double rpm);
        void draw();
        void update(double fps);
        
};


#endif // ENGINE2D_H