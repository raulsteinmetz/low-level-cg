#include "engine3d.h"

Vector3 rotateVector3(Vector3 vector, double radians) {
    // Compute sine and cosine of the rotation angle
    double cosTheta = cos(radians);
    double sinTheta = sin(radians);

    // Apply rotation transformation
    Vector3 rotatedVector;
    rotatedVector.x = vector.x * cosTheta - vector.y * sinTheta;
    rotatedVector.y = vector.x * sinTheta + vector.y * cosTheta;
    rotatedVector.z = vector.z;

    return rotatedVector;
}


Screw3D::Screw3D() {
    this->position = Vector3(0, 0, 0);
    this->body = Cuboid(1);
}

Screw3D::Screw3D(Vector3 position, double size) {
    this->position = position;
    this->body = Cuboid(size, position.x, position.y, position.z);
}

void Screw3D::draw(double d) {
    this->body.draw(d);
}

void Screw3D::update(Vector3 position) {
    this->position = position;

    for (int i = 0; i < 8; i++) {
        this->body.points[i].x -= this->body.offset_x;
        this->body.points[i].y -= this->body.offset_y;
        this->body.points[i].z -= this->body.offset_z;
    }

    this->body.offset_x = position.x;
    this->body.offset_y = position.y;
    this->body.offset_z = position.z;

    for (int i = 0; i < 8; i++) {
        this->body.points[i].x += this->body.offset_x;
        this->body.points[i].y += this->body.offset_y;
        this->body.points[i].z += this->body.offset_z;
    }

}

void Screw3D::update_pos(double x, double y, double z) {
    this->update(Vector3(x, y, z));
}

void Screw3D::rotate(int axis, double radians) {
    this->body.rotate_on_origin(axis, radians);
}

Crank3D::Crank3D() {
    this->center_screw = Screw3D(Vector3(0, 0, 0), 0.5);
    this->moving_screw = Screw3D(Vector3(0, 0, 0), 0.1);
    this->body = Cilinder(1, 1, 1);
    this->moving_screw_radians = 0;
    this->state = ENGINE_OFF;
    this->rpm = 0;
}

Crank3D::Crank3D(Vector3 center_screw_position, double height, double radius, double moving_screw_radians, bool state, double rpm) {
    this->center_screw = Screw3D(center_screw_position, 0.5);
    this->moving_screw = Screw3D(Vector3(0, 0, center_screw_position.z), 0.5);
    this->body = Cilinder(radius, height, 100, center_screw_position.x, center_screw_position.y, center_screw_position.z);
    this->moving_screw_radians = moving_screw_radians;
    this->state = state;
    this->rpm = rpm;

}

void Crank3D::draw(double d) {
    this->body.draw(d);
    this->center_screw.draw(d);
    this->moving_screw.draw(d);
}

void Crank3D::stop() {
    this->state = ENGINE_OFF;
}

void Crank3D::start() {
    this->state = ENGINE_ON;
}


Vector3 Crank3D::calculate_moving_screw_position() {
    double x = this->center_screw.position.x + this->body.radius * cos(this->moving_screw_radians);
    double y = this->center_screw.position.y + this->body.radius * sin(this->moving_screw_radians);
    double z = this->moving_screw.position.z;
    return Vector3(x, y, z);
}


void Crank3D::update(double fps) {
    if (this->state == ENGINE_ON) {
        this->moving_screw_radians += (this->rpm * 2 * PI) / 60 / fps;
        this->moving_screw.update(this->calculate_moving_screw_position());
    }
}

void Crank3D::rotate(int axis, double angle) {

}


Rod3D::Rod3D() {
    this->start_effector = Vector3(0, 0, 0);
    this->end_effector = Vector3(0, 0, 0);
    this->width = 1.0;
    this->height = 1.0;
    this->depth = 1.0;
    this->body_back = Cuboid(1.0, 0.2, 0.1, 0, 0, 0);
}

Rod3D::Rod3D(Vector3 start_effector, Vector3 end_effector, double width, double height, double lenght) {

}



Piston3D::Piston3D(){
    this->depth = 1.0;
    this->width = 1.0;
    this->height = 1.0;
    this->center_screw_position = Vector3(0, 0, 0);
    this->body = Cuboid(1.0, 1.0, 1.0, 0, 0, 0);
}

Piston3D::Piston3D(Vector3 center_screw_position, double width, double height, double depth, double rod_length, double rad) {
    this->depth = depth;
    this->width = width;
    this->height = height;
    this->center_screw_position = center_screw_position;
    this->body = Cuboid(depth, width, height, center_screw_position.x, center_screw_position.y, center_screw_position.z);
    this->rad = rad;
    this->connecting_rod_lenght = rod_length;
}

void Piston3D::draw(double d) {
    this->body.draw(d);
}

void Piston3D::update(Vector3 end_effector_pos, double fps) {
    this->update_center_screw_position(end_effector_pos);
}

double distance_between_points(Vector3 p1, Vector3 p2) {
    double distance_between_points(Vector3 p1, Vector3 p2);
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;
    return sqrt(dx * dx + dy * dy + dz * dz);

}

void Piston3D::update_center_screw_position(Vector3 end_effector_pos) {
    double x = this->center_screw_position.x;
    double ca = distance_between_points(end_effector_pos, Vector3(this->center_screw_position.x, end_effector_pos.y, end_effector_pos.z));
    double hip = this->connecting_rod_lenght;
    double co = sqrt(pow(hip, 2) - pow(ca, 2));
    double y = end_effector_pos.y - co;
    double z = end_effector_pos.z;


    Vector3 new_pos(x, y, z);
    this->center_screw_position = new_pos;


    this->body.update_pos(x, y, z);
}




Engine3D::Engine3D() {
    this->crank = Crank3D(Vector3(0, 0, 6), 1, 2, 0, ENGINE_ON, 30);
    this->left_piston = Piston3D(Vector3(0, 0, 6), 1, 1, 1, 5, 30.0);
    this->right_piston = Piston3D(Vector3(0, 0, 6), 1, 1, 1, 5, -30.0);
}

void Engine3D::draw(double d) {

    this->left_piston.draw(d);
    this->crank.draw(d);
    this->right_piston.draw(d);

}

void Engine3D::update(double fps) {
    this->crank.update(fps);
    this->left_piston.update(this->crank.calculate_moving_screw_position(), fps);
    this->right_piston.update(this->crank.calculate_moving_screw_position(), fps);
}

void Engine3D::rotate(int axis, double angle) {
    //this->crank.rotate(axis, angle);
    //this->piston.rotate(axis, angle);
}
