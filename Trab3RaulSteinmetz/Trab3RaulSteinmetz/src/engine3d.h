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

class Engine3D {
    public:
        Crank3D crank;
        Engine3D();
        void draw(double d);
        void update(double fps);
        void rotate(int axis, double angle);
};


#endif // ENGINE3D_H