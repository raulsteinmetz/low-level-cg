#ifndef MODELS3D_H
#define MODELS3D_H


#include "Vector2.h"
#include "gl_canvas2d.h"
#include "models3d.h"

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2


// util
class Vector3 {
    public:
        float x, y, z;
        Vector3();
        Vector3(float x, float y, float z);
};

Vector2 perspective(Vector3 v);

Vector3 rotateVector3(int axis, double rad, Vector3 v);

Vector3 translate(Vector3 v, Vector3 t);

class Cuboid {
    public:
        Vector3 points[8];
        double size;
        double offset_x, offset_y, offset_z;
        double hight, width, depth;
        Cuboid();
        Cuboid(double size);
        Cuboid(double size, double offset_x, double offset_y, double offset_z);
        Cuboid(double hight, double width, double depth, double offset_x, double offset_y, double offset_z);
        void draw(double d);
        void update_pos(double offset_x, double offset_y, double offset_z);
};

class Cilinder {
    public:
        Vector3 bottom[100];
        Vector3 top[100];
        Vector3 top_center;
        Vector3 bottom_center;
        int n_points;
        double radius, height;
        double offset_x, offset_y, offset_z;
        Cilinder();
        Cilinder(double radius, double height, double n_points);
        Cilinder(double radius, double height, double n_points, double offset_x, double offset_y, double offset_z);
        Cilinder(double radius, double n_points, Vector3 bottom_center, Vector3 top_center);
        void compute_cilinder_points();
        void draw(double d);
};



#endif // MODELS3D_H
