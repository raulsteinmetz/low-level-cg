#include "models3d.h"


// UTIL
Vector2 perspective(Vector3 v, double d) {
    float x = v.x * d / (v.z);
    float y = v.y * d / (v.z);
    return Vector2(x, y);
}

// VECTOR 3
Vector3::Vector3() {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}


// CUBE

Cuboid::Cuboid() {}
Cuboid::Cuboid(double size) : size(size) {

    this->width = 1.0;
    this->hight = 1.0;
    this->depth = 1.0;

    // points in y = 0
    points[0] = Vector3(1, 1, 1);
    points[1] = Vector3(-1, 1, 1);
    points[2] = Vector3(-1, -1, 1);
    points[3] = Vector3(1, -1, 1);

    // points in y = 1
    points[4] = Vector3(1, 1, -1);
    points[5] = Vector3(-1, 1, -1);
    points[6] = Vector3(-1, -1, -1);
    points[7] = Vector3(1, -1, -1);


    // scale
    for (int i = 0; i < 8; i++) {
        points[i].x *= size;
        points[i].y *= size;
        points[i].z *= size;
    }
}

Cuboid::Cuboid(double size, double offset_x, double offset_y, double offset_z) : 
           size(size), offset_x(offset_x), offset_y(offset_y), offset_z(offset_z) {

    this->width = 1.0;
    this->hight = 1.0;
    this->depth = 1.0;

    // points in y = 0
    points[0] = Vector3(1, 1, 1);
    points[1] = Vector3(-1, 1, 1);
    points[2] = Vector3(-1, -1, 1);
    points[3] = Vector3(1, -1, 1);

    // points in y = 1
    points[4] = Vector3(1, 1, -1);
    points[5] = Vector3(-1, 1, -1);
    points[6] = Vector3(-1, -1, -1);
    points[7] = Vector3(1, -1, -1);


    // scale
    for (int i = 0; i < 8; i++) {
        points[i].x *= size;
        points[i].y *= size;
        points[i].z *= size;
    }

    // translate
    for (int i = 0; i < 8; i++) {
        points[i].x += offset_x;
        points[i].y += offset_y;
        points[i].z += offset_z;
    }
}

Cuboid::Cuboid(double width, double hight, double depth, double offset_x, double offset_y, double offset_z) : 
           width(width), hight(hight), depth(depth), offset_x(offset_x), offset_y(offset_y), offset_z(offset_z) {

    // points in y = 0
    points[0] = Vector3(width/2, hight/2, depth/2);
    points[1] = Vector3(-width/2, hight/2, depth/2);
    points[2] = Vector3(-width/2, -hight/2, depth/2);
    points[3] = Vector3(width/2, -hight/2, depth/2);

    // points in y = 1
    points[4] = Vector3(width/2, hight/2, -depth/2);
    points[5] = Vector3(-width/2, hight/2, -depth/2);
    points[6] = Vector3(-width/2, -hight/2, -depth/2);
    points[7] = Vector3(width/2, -hight/2, -depth/2);

    // translate
    for (int i = 0; i < 8; i++) {
        points[i].x += offset_x;
        points[i].y += offset_y;
        points[i].z += offset_z;
    }
}

void Cuboid::draw(double d) {
    // drawing lines
    CV::color(0, 0, 0);
    CV::line(perspective(points[0], d), perspective(points[1], d));
    CV::line(perspective(points[1], d), perspective(points[2], d));
    CV::line(perspective(points[2], d), perspective(points[3], d));
    CV::line(perspective(points[3], d), perspective(points[0], d));
    CV::line(perspective(points[4], d), perspective(points[5], d));
    CV::line(perspective(points[5], d), perspective(points[6], d));
    CV::line(perspective(points[6], d), perspective(points[7], d));
    CV::line(perspective(points[7], d), perspective(points[4], d));
    CV::line(perspective(points[0], d), perspective(points[4], d));
    CV::line(perspective(points[1], d), perspective(points[5], d));
    CV::line(perspective(points[2], d), perspective(points[6], d));
    CV::line(perspective(points[3], d), perspective(points[7], d));
}

void Cuboid::rotate(int axis, double angle) {
    double rad = angle * PI / 180;

    // translate to origin
    for (int i = 0; i < 8; i++) {
        points[i].x -= offset_x;
        points[i].y -= offset_y;
        points[i].z -= offset_z;
    }

    // rotate
    for (int i = 0; i < 8; i++) {
        if (axis == 0) {
            points[i].y = points[i].y * cos(rad) - points[i].z * sin(rad);
            points[i].z = points[i].y * sin(rad) + points[i].z * cos(rad);
        } else if (axis == 1) {
            points[i].x = points[i].x * cos(rad) + points[i].z * sin(rad);
            points[i].z = -points[i].x * sin(rad) + points[i].z * cos(rad);
        } else if (axis == 2) {
            points[i].x = points[i].x * cos(rad) - points[i].y * sin(rad);
            points[i].y = points[i].x * sin(rad) + points[i].y * cos(rad);
        }
    }

    // translate back
    for (int i = 0; i < 8; i++) {
        points[i].x += offset_x;
        points[i].y += offset_y;
        points[i].z += offset_z;
    }
}

// CILINDER

Cilinder::Cilinder() {
    this->radius = 1;
    this->height = 1;
    this->n_points = 100;
   
    for(int i = 0; i < n_points; i++) {
        float rad = 2 * PI * i / n_points;
        bottom[i] = Vector3(radius * cos(rad), radius * sin(rad), 0);
        top[i] = Vector3(radius * cos(rad), radius * sin(rad), height);
    }
}

Cilinder::Cilinder(double radius, double height, double n_points) {
    this->radius = radius;
    this->height = height;
    this->n_points = n_points;

    for(int i = 0; i < n_points; i++) {
        float rad = 2 * PI * i / n_points;
        bottom[i] = Vector3(radius * cos(rad), radius * sin(rad), 0);
        top[i] = Vector3(radius * cos(rad), radius * sin(rad), height);
    }
}

Cilinder::Cilinder(double radius, double height, double n_points, double offset_x, double offset_y, double offset_z) {
    this->radius = radius;
    this->height = height;
    this->n_points = n_points;
    this->offset_x = offset_x;
    this->offset_y = offset_y;
    this->offset_z = offset_z;

    for(int i = 0; i < n_points; i++) {
        float rad = 2 * PI * i / n_points;
        bottom[i] = Vector3(radius * cos(rad), radius * sin(rad), 0);
        top[i] = Vector3(radius * cos(rad), radius * sin(rad), height);
    }

    // translate
    for (int i = 0; i < n_points; i++) {
        bottom[i].x += offset_x;
        bottom[i].y += offset_y;
        bottom[i].z += offset_z;
        top[i].x += offset_x;
        top[i].y += offset_y;
        top[i].z += offset_z;
    }
}

void Cilinder::draw(double d) {
    // drawing lines
    CV::color(0, 0, 0);
    for (int i = 0; i < n_points; i++) {
        CV::line(perspective(bottom[i], d), perspective(bottom[(i + 1) % n_points], d));
        CV::line(perspective(top[i], d), perspective(top[(i + 1) % n_points], d));
        CV::line(perspective(bottom[i], d), perspective(top[i], d));
    }
}

void Cilinder::rotate(int axis, double angle) {
    double rad = angle * PI / 180;
    
    // translate to origin
    for (int i = 0; i < n_points; i++) {
        bottom[i].x -= offset_x;
        bottom[i].y -= offset_y;
        bottom[i].z -= offset_z;
        top[i].x -= offset_x;
        top[i].y -= offset_y;
        top[i].z -= offset_z;
    }

    // rotate
    for (int i = 0; i < n_points; i++) {
        if (axis == 0) {
            bottom[i].y = bottom[i].y * cos(rad) - bottom[i].z * sin(rad);
            bottom[i].z = bottom[i].y * sin(rad) + bottom[i].z * cos(rad);
            top[i].y = top[i].y * cos(rad) - top[i].z * sin(rad);
            top[i].z = top[i].y * sin(rad) + top[i].z * cos(rad);
        } else if (axis == 1) {
            bottom[i].x = bottom[i].x * cos(rad) + bottom[i].z * sin(rad);
            bottom[i].z = -bottom[i].x * sin(rad) + bottom[i].z * cos(rad);
            top[i].x = top[i].x * cos(rad) + top[i].z * sin(rad);
            top[i].z = -top[i].x * sin(rad) + top[i].z * cos(rad);
        } else if (axis == 2) {
            bottom[i].x = bottom[i].x * cos(rad) - bottom[i].y * sin(rad);
            bottom[i].y = bottom[i].x * sin(rad) + bottom[i].y * cos(rad);
            top[i].x = top[i].x * cos(rad) - top[i].y * sin(rad);
            top[i].y = top[i].x * sin(rad) + top[i].y * cos(rad);
        }
    }

    // translate back
    for (int i = 0; i < n_points; i++) {
        bottom[i].x += offset_x;
        bottom[i].y += offset_y;
        bottom[i].z += offset_z;
        top[i].x += offset_x;
        top[i].y += offset_y;
        top[i].z += offset_z;
    }
}