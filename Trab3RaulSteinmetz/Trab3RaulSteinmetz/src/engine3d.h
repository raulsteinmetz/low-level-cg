#ifndef ENGINE3D_H
#define ENGINE3D_H

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "models3d.h"

#define ENGINE_ON true
#define ENGINE_OFF false


class Crank3D {
    public:
        Vector3 center_screw_position;
        Vector3 moving_screw_position;
        Cilinder body;
        double moving_screw_radians;
        bool state;
        double rpm;

        Crank3D();
        Crank3D(Vector3 center_screw_position, double radius, double moving_screw_radians, bool state, double rpm);
        void draw();
        void update(double fps);
        void stop();
        void start();
        Vector3 calculate_moving_screw_position();

};

class Engine3D {
    public:
        Engine3D();
        void draw();
        void update(double fps);
};


#endif // ENGINE3D_H