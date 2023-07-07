#include "engine2d.h"

Vector2 rotateVector(Vector2 vector, double radians) {
    // Compute sine and cosine of the rotation angle
    double cosTheta = cos(radians);
    double sinTheta = sin(radians);

    // Apply rotation transformation
    Vector2 rotatedVector;
    rotatedVector.x = vector.x * cosTheta - vector.y * sinTheta;
    rotatedVector.y = vector.x * sinTheta + vector.y * cosTheta;

    return rotatedVector;
}

double calculate_ditance(Vector2 a, Vector2 b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// piston
Piston::Piston() {
    this->center_screw_position = Vector2(0, 0);
    this->side_lenght = Vector2(0, 0);
    this->connecting_rod_length = 0;
}

Piston::Piston(Vector2 center_screw_position, Vector2 side_lenght, double connecting_rod_length, double rad) {
    this->center_screw_position = center_screw_position;
    this->side_lenght = side_lenght;
    this->connecting_rod_length = connecting_rod_length;
    this->rad = rad;
}

void Piston::update_center_screw_position(Vector2 crank_center_screw_position) {
    // aqui pae
    double x = crank_center_screw_position.x;
    double ca = calculate_ditance(connecting_rod_end_effector_position, Vector2(crank_center_screw_position.x, connecting_rod_end_effector_position.y));
    double hip = connecting_rod_length;
    double co = sqrt(pow(hip, 2) - pow(ca, 2));
    double y = connecting_rod_end_effector_position.y - co;
   


    this->center_screw_position = Vector2(x, y);
}

void Piston::draw() {
    CV::color(0, 0, 0);
    // piston
    CV::rect(center_screw_position.x - side_lenght.x,
            center_screw_position.y - side_lenght.y, 
            center_screw_position.x + side_lenght.x, 
            center_screw_position.y + side_lenght.y);

    
    // center screw
    CV::color(1, 0, 0);
    CV::circle(center_screw_position.x, center_screw_position.y, 10, 100);
    

    // connecting rod
    CV::color(0, 0, 1);
    CV::line(center_screw_position.x, center_screw_position.y, 
            connecting_rod_end_effector_position.x, connecting_rod_end_effector_position.y);

    printf("Distance: %f\n", calculate_ditance(center_screw_position, connecting_rod_end_effector_position));

}

void Piston::update(Vector2 crank_center_screw_position, Vector2 end_effector_postition) {
    this->connecting_rod_end_effector_position = end_effector_postition;
    update_center_screw_position(crank_center_screw_position);
}




// crank

Crank::Crank() {
    this->center_screw_position = Vector2(0, 0);
    this->radius = 0;
    this->moving_screw_radians = 0;
    this->state = false;
}

Crank::Crank(Vector2 center_screw_position, double radius, double moving_screw_radians, bool state) {
    this->center_screw_position = center_screw_position;
    this->radius = radius;
    this->moving_screw_radians = moving_screw_radians;
    this->state = state;
    this->moving_screw_position = calculate_moving_screw_position();
}

Vector2 Crank::calculate_moving_screw_position() {
    double x = this->center_screw_position.x + this->radius * cos(this->moving_screw_radians);
    double y = this->center_screw_position.y + this->radius * sin(this->moving_screw_radians);
    return Vector2(x, y);
}


void Crank::draw() {
    CV::color(0, 0, 0);
    CV::circle(center_screw_position.x, center_screw_position.y, radius, 100);
    CV::color(1, 0, 0);
    CV::circle(moving_screw_position.x, moving_screw_position.y, 10, 100);
}

void Crank::update(double fps) {
    if (this->state == ENGINE_ON) {
        double move = this->rpm / 60.0; // rotations per second
        this->moving_screw_radians += move * 2 * PI / fps;
        this->moving_screw_position = calculate_moving_screw_position();
    }
}


// v twin
TwoPistonEngine2D::TwoPistonEngine2D() {
    this->crank = Crank();
    this->left_piston = Piston();
    this->right_piston = Piston();
}

TwoPistonEngine2D::TwoPistonEngine2D(Vector2 center_screw_position, double radius, double moving_screw_radians, bool state, double rpm) {
    this->crank = Crank(center_screw_position, radius, moving_screw_radians, state);
    this->left_piston = Piston(Vector2(center_screw_position.x, center_screw_position.y - 200), Vector2(50, 50), 150, - PI/6.0);
    this->right_piston = Piston(Vector2(center_screw_position.x, center_screw_position.y - 200), Vector2(50, 50), 150, + PI/6.0);
    this->rpm = rpm;
    crank.rpm = rpm;
}

void TwoPistonEngine2D::draw() {

    this->left_piston.center_screw_position = rotateVector(this->left_piston.center_screw_position, this->left_piston.rad);
    this->left_piston.connecting_rod_end_effector_position = rotateVector(this->left_piston.connecting_rod_end_effector_position, this->left_piston.rad);
    this->crank.moving_screw_position = rotateVector(this->crank.moving_screw_position, this->left_piston.rad);

    this->right_piston.center_screw_position = rotateVector(this->right_piston.center_screw_position, this->right_piston.rad);
    this->right_piston.connecting_rod_end_effector_position = rotateVector(this->right_piston.connecting_rod_end_effector_position, this->right_piston.rad);


    this->left_piston.draw();
    this->crank.draw();
    this->right_piston.draw();
}

void TwoPistonEngine2D::update(double fps) {
    this->crank.update(fps);
    this->left_piston.update(this->crank.center_screw_position, this->crank.moving_screw_position);
    this->right_piston.update(this->crank.center_screw_position, rotateVector(this->crank.moving_screw_position, this->left_piston.rad * 2));
}

