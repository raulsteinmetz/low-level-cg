#ifndef MODELS3D_H
#define MODELS3D_H


#include "Vector2.h"
#include "gl_canvas2d.h"

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

class Cube {
    public:
        Vector3 points[8];
        double size;
        double offset_x, offset_y, offset_z;
        Cube();
        Cube(float size);
        Cube(float size, float offset_x, float offset_y, float offset_z);
        void rotate(int axis, double angle);
        void draw(double d);
};

class Cilinder {
    public:
        Vector3 bottom[100];
        Vector3 top[100];
        int n_points;
        double radius, height;
        double offset_x, offset_y, offset_z;
        Cilinder();
        Cilinder(float radius, float height, float n_points);
        Cilinder(float radius, float height, float n_points, float offset_x, float offset_y, float offset_z);
        void rotate(int axis, double angle);
        void draw(double d);

};



#endif // MODELS3D_H