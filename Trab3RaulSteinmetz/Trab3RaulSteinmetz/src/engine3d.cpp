#include "engine3d.h"

Screw::Screw() {
    this->position = Vector3(0, 0, 0);
    this->body = Cuboid(1);
}

Screw::Screw(Vector3 position, double size) {
    this->position = position;
    this->body = Cuboid(size, position.x, position.y, position.z);
}

void Screw::draw(double d) {
    this->body.draw(d);
}

void Screw::update(Vector3 position) {
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

void Screw::rotate(int axis, double radians) {
    this->body.rotate(axis, radians);
}

Crank3D::Crank3D() {
    this->center_screw = Screw(Vector3(0, 0, 0), 0.5);
    this->moving_screw = Screw(Vector3(0, 0, 0), 0.25);
    this->body = Cilinder(1, 1, 1);
    this->moving_screw_radians = 0;
    this->state = ENGINE_OFF;
    this->rpm = 0;
}

Crank3D::Crank3D(Vector3 center_screw_position, double height, double radius, double moving_screw_radians, bool state, double rpm) {
    this->center_screw = Screw(center_screw_position, 0.5);
    this->moving_screw = Screw(Vector3(0, 0, 0), 0.5);
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
    double z = this->center_screw.position.z;
    return Vector3(x, y, z);
}


void Crank3D::update(double fps) {
    if (this->state == ENGINE_ON) {
        this->moving_screw_radians += (this->rpm * 2 * PI) / 60 / fps;
        this->moving_screw.update(this->calculate_moving_screw_position());
    }
}

void Crank3D::rotate(int axis, double angle) {
    this->center_screw.rotate(axis, angle);
    this->moving_screw.rotate(axis, angle);
    this->body.rotate(axis, angle);
}

Engine3D::Engine3D() {
    this->crank = Crank3D(Vector3(0, 0, 6), 1, 2, 0, ENGINE_ON, 5);
}

void Engine3D::draw(double d) {
    this->crank.draw(d);
}

void Engine3D::update(double fps) {
    this->crank.update(fps);
}

void Engine3D::rotate(int axis, double angle) {
    this->crank.rotate(axis, angle);
}