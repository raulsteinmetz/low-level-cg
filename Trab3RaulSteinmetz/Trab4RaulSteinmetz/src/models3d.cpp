#include "models3d.h"

#define SCALE_ORTHO 200.0000

// UTIL
Vector2 perspective(Vector3 v, double d) {
    float x = v.x * d / (v.z);
    float y = v.y * d / (v.z);
    return Vector2(x, y);
}

Vector2 ortho(Vector3 v) {
    return Vector2(v.x, v.y);
}

// VECTOR 3
Vector3::Vector3() {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 rotateVector3(int axis, double rad, Vector3 v) {
    double cosTheta = cos(rad);
    double sinTheta = sin(rad);

    if (axis == AXIS_X) {
        double y = v.y * cosTheta - v.z * sinTheta;
        double z = v.y * sinTheta + v.z * cosTheta;
        return {v.x, y, z};
    } else if (axis == AXIS_Y) {
        double x = v.x * cosTheta + v.z * sinTheta;
        double z = -v.x * sinTheta + v.z * cosTheta;
        return {x, v.y, z};
    } else if (axis == AXIS_Z) {
        double x = v.x * cosTheta - v.y * sinTheta;
        double y = v.x * sinTheta + v.y * cosTheta;
        return {x, y, v.z};
    }

    // Handle invalid axis input
    return v;
}

Vector3 translate(Vector3 v, Vector3 t) {
    return {v.x + t.x, v.y + t.y, v.z + t.z};
}


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

void Cuboid::scale(double scale_x, double scale_y, double scale_z) {
    for (int i = 0; i < 8; i++) {
        this->points[i].x -= this->offset_x;
        this->points[i].y -= this->offset_y;
        this->points[i].z -= this->offset_z;
    }

    for (int i = 0; i < 8; i++) {
        this->points[i].x *= scale_x;
        this->points[i].y *= scale_y;
        this->points[i].z *= scale_z;
    }

    for (int i = 0; i < 8; i++) {
        this->points[i].x += this->offset_x;
        this->points[i].y += this->offset_y;
        this->points[i].z += this->offset_z;
    }
}

void Cuboid::draw(double d, int view_mode) {
    // drawing lines
    if (view_mode == DRAW_PERSPECTIVE) {
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
    } else if (view_mode == DRAW_ORTHO) {
        this->scale(SCALE_ORTHO, SCALE_ORTHO, SCALE_ORTHO);
        CV::color(0, 0, 0);
        CV::line(ortho(points[0]), ortho(points[1]));
        CV::line(ortho(points[1]), ortho(points[2]));
        CV::line(ortho(points[2]), ortho(points[3]));
        CV::line(ortho(points[3]), ortho(points[0]));
        CV::line(ortho(points[4]), ortho(points[5]));
        CV::line(ortho(points[5]), ortho(points[6]));
        CV::line(ortho(points[6]), ortho(points[7]));
        CV::line(ortho(points[7]), ortho(points[4]));
        CV::line(ortho(points[0]), ortho(points[4]));
        CV::line(ortho(points[1]), ortho(points[5]));
        CV::line(ortho(points[2]), ortho(points[6]));
        CV::line(ortho(points[3]), ortho(points[7]));
        this->scale(1/SCALE_ORTHO, 1/SCALE_ORTHO, 1/SCALE_ORTHO);
    }
}


void Cuboid::update_pos(double offset_x, double offset_y, double offset_z) {
    for (int i = 0; i < 8; i++) {
        this->points[i].x -= this->offset_x;
        this->points[i].y -= this->offset_y;
        this->points[i].z -= this->offset_z;
    }

    this->offset_x = offset_x;
    this->offset_y = offset_y;
    this->offset_z = offset_z;

    for (int i = 0; i < 8; i++) {
        this->points[i].x += this->offset_x;
        this->points[i].y += this->offset_y;
        this->points[i].z += this->offset_z;
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
        bottom[i] = Vector3(radius * cos(rad), radius * sin(rad), -height / 2.0);
        top[i] = Vector3(radius * cos(rad), radius * sin(rad), height / 2.0);
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

void Cilinder::compute_cilinder_points() {
    Vector3 direction = Vector3(top_center.x - bottom_center.x, top_center.y - bottom_center.y, top_center.z - bottom_center.z);
    double length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    direction.x /= length;
    direction.y /= length;
    direction.z /= length;

    Vector3 perpendicular;
    if (fabs(direction.x) < 0.1 && fabs(direction.y) < 0.1)
        perpendicular = Vector3(1.0, 0.0, 0.0);
    else
        perpendicular = Vector3(-direction.y, direction.x, 0.0);

    double angleIncrement = 2 * PI / n_points;
    for (int i = 0; i < n_points; i++) {
        double angle = i * angleIncrement;
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);

        bottom[i] = Vector3(bottom_center.x + (perpendicular.x * radius * cosAngle), bottom_center.y + (perpendicular.y * radius * cosAngle), bottom_center.z + (perpendicular.z * radius * cosAngle));
        top[i] = Vector3(top_center.x + (perpendicular.x * radius * cosAngle), top_center.y + (perpendicular.y * radius * cosAngle), top_center.z + (perpendicular.z * radius * cosAngle));
    }
}

Cilinder::Cilinder(double radius, double n_points, Vector3 bottom_center, Vector3 top_center) {
    this->radius = radius;
    this->n_points = n_points;
    this->bottom_center = bottom_center;
    this->top_center = top_center;
    compute_cilinder_points();
}

void Cilinder::scale(double scale_x, double scale_y, double scale_z) {
    for (int i = 0; i < n_points; i++) {
        bottom[i].x -= bottom_center.x;
        bottom[i].y -= bottom_center.y;
        bottom[i].z -= bottom_center.z;
        bottom[i].x *= scale_x;
        bottom[i].y *= scale_y;
        bottom[i].z *= scale_z;
        bottom[i].x += bottom_center.x;
        bottom[i].y += bottom_center.y;
        bottom[i].z += bottom_center.z;

        top[i].x -= top_center.x;
        top[i].y -= top_center.y;
        top[i].z -= top_center.z;
        top[i].x *= scale_x;
        top[i].y *= scale_y;
        top[i].z *= scale_z;
        top[i].x += top_center.x;
        top[i].y += top_center.y;
        top[i].z += top_center.z;
    }
}



void Cilinder::draw(double d, int view_mode) {
    // drawing lines
    CV::color(0, 0, 0);
    for (int i = 0; i < n_points; i++) {
        if (view_mode == DRAW_PERSPECTIVE) {
            CV::line(perspective(bottom[i], d), perspective(bottom[(i + 1) % n_points], d));
            CV::line(perspective(top[i], d), perspective(top[(i + 1) % n_points], d));
            CV::line(perspective(bottom[i], d), perspective(top[i], d));
        }
        else {
            this->scale(SCALE_ORTHO, SCALE_ORTHO, SCALE_ORTHO);
            CV::line(ortho(bottom[i]), ortho(bottom[(i + 1) % n_points]));
            CV::line(ortho(top[i]), ortho(top[(i + 1) % n_points]));
            CV::line(ortho(bottom[i]), ortho(top[i]));
            this->scale(1.0 / SCALE_ORTHO, 1.0 / SCALE_ORTHO, 1.0 / SCALE_ORTHO);
        }
    }
}

