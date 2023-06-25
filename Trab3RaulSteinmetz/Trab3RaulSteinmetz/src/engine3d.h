#ifndef ENGINE3D_H
#define ENGINE3D_H

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "models3d.h"

#define ENGINE_ON true
#define ENGINE_OFF false


class Screw {
    public:
        Vector3 position;
        Cuboid body;
        Screw();
        Screw(Vector3 position, double size);
        void draw(double d);
        void update(Vector3 position);
        void rotate(int axis, double angle);
};

class Crank3D {
    public:
        Screw center_screw;
        Screw moving_screw;
        Cilinder body;
        double moving_screw_radians;
        bool state;
        double rpm;

        Crank3D();
        Crank3D(Vector3 center_screw_position, double height, double radius, double moving_screw_radians, bool state, double rpm);
        void draw(double d);
        void update(double fps);
        void stop();
        void start();
        Vector3 calculate_moving_screw_position();
        void rotate(int axis, double angle);

};

class Rod {
    public:
        Vector3 start_effector;
        Vector3 end_effector;
        Cuboid body_front;
        Cuboid body_back;
        double width;
        double height;
        double lenght;
        Rod();
        Rod(Vector3 start_effector, Vector3 end_effector, double width, double height, double lenght);
};

class Piston3D {
    public:
        Vector3 center_screw_position;
        double width;
        double height;
        double depth;
        double rad;

        Piston3D();
        Piston3D(Vector3 center_screw_position, double width, double height, double depth, double rod_length, double rad);
        void draw(double d);
        void update(Vector3 crank_center_screw_pos, Vector3 end_effector_pos, double fps);
        void update_center_screw_position(Vector3 end_effector_pos);
};

class Engine3D {
    public:
        Crank3D crank;
        Engine3D();
        void draw(double d);
        void update(double fps);
        void rotate(int axis, double angle);
};


#endif // ENGINE3D_H