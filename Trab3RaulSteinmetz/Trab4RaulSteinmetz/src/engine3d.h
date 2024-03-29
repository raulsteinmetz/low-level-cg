#ifndef ENGINE3D_H
#define ENGINE3D_H

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "models3d.h"

#define ENGINE_ON true
#define ENGINE_OFF false
#define RENDER_ON true
#define RENDER_OFF false


// this code contains codes for the 3d engine class


// screw class (used for crank and piston)
class Screw3D {
    public:
        Vector3 position;
        Cuboid body;
        Screw3D();
        Screw3D(Vector3 position, double size);
        void draw(double d, int view_mode);
        void update(Vector3 position);
        void update_pos(double off_set_x, double off_set_y, double off_set_z);

};

// crank class
class Crank3D {
    public:
        Screw3D center_screw;
        Screw3D moving_screw;
        Cilinder body;
        double moving_screw_radians;
        bool state;
        double rpm;

        Crank3D();
        Crank3D(Vector3 center_screw_position, double height, double radius, double moving_screw_radians, bool state, double rpm);
        void draw(double d, int view_mode);
        void update(double fps);
        void stop();
        void start();
        Vector3 calculate_moving_screw_position();

};

// piston class
class Piston3D {
    public:
        Vector3 center_screw_position;
        double width;
        double height;
        double depth;
        double rad;
        Cuboid body;
        double connecting_rod_lenght;
        Vector3 end_effector_position;

        Piston3D();
        Piston3D(Vector3 center_screw_position, double width, double height, double depth, double rod_length, double rad);
        void draw(double d, int view_mode);
        void update(Vector3 end_effector_pos, double fps);
        void update_center_screw_position(Vector3 end_effector_pos);
};

// entire engine in 3d
class Engine3D {
    public:
        double x_rotation;
        double y_rotation;
        double z_rotation;

        int draw_crank;
        int draw_left_piston;
        int draw_right_piston;

        Crank3D crank;
        Piston3D left_piston;
        Piston3D right_piston;
        Engine3D(double z);
        Engine3D();
        void draw(double d, int view_mode);
        void update(double fps);
        void render(double fps, double d, int view_mode);
        
};


#endif // ENGINE3D_H