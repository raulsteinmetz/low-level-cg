#include "engine3d.h"


// rotates vector3 on z axis
Vector3 rotateVector3_z(Vector3 vector, double radians) {
    double cosTheta = cos(radians);
    double sinTheta = sin(radians);

    Vector3 rotatedVector;
    rotatedVector.x = vector.x * cosTheta - vector.y * sinTheta;
    rotatedVector.y = vector.x * sinTheta + vector.y * cosTheta;
    rotatedVector.z = vector.z;

    return rotatedVector;
}

// screw

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

// updates screw position
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

// updates screw position
void Screw3D::update_pos(double x, double y, double z) {
    this->update(Vector3(x, y, z));
}


// crank

Crank3D::Crank3D() {
    this->center_screw = Screw3D(Vector3(0, 0, 0), 0.5);
    this->moving_screw = Screw3D(Vector3(0, 0, 0), 0.05);
    this->body = Cilinder(1, 1, 1);
    this->moving_screw_radians = 0;
    this->state = ENGINE_OFF;
    this->rpm = 0;
}

Crank3D::Crank3D(Vector3 center_screw_position, double height, double radius, double moving_screw_radians, bool state, double rpm) {
    this->center_screw = Screw3D(center_screw_position, 0.5);
    this->moving_screw = Screw3D(Vector3(0, 0, center_screw_position.z), 0.25);
    this->body = Cilinder(radius, height, 100, center_screw_position.x, center_screw_position.y, center_screw_position.z);
    this->moving_screw_radians = moving_screw_radians;
    this->state = state;
    this->rpm = rpm;

}

// draws crank
void Crank3D::draw(double d) {
    this->body.draw(d);
    this->moving_screw.draw(d);
}

// stops crank rotation
void Crank3D::stop() {
    this->state = ENGINE_OFF;
}

// starts crank rotation
void Crank3D::start() {
    this->state = ENGINE_ON;
}

// calculates moving screw position
Vector3 Crank3D::calculate_moving_screw_position() {
    double x = this->center_screw.position.x + this->body.radius * cos(this->moving_screw_radians);
    double y = this->center_screw.position.y + this->body.radius * sin(this->moving_screw_radians);
    double z = this->moving_screw.position.z;
    return Vector3(x, y, z);
}

// updates moving screw angle
void Crank3D::update(double fps) {
    if (this->state == ENGINE_ON) {
        this->moving_screw_radians += (this->rpm * 2 * PI) / 60 / fps;
        this->moving_screw.update(this->calculate_moving_screw_position());
    }
}

// piston 

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

// draws piston
void Piston3D::draw(double d) {
    this->body.draw(d);
    Cilinder rod = Cilinder(0.1, 40, this->end_effector_position, this->center_screw_position);
    rod.draw(d);

}

// updates piston position
void Piston3D::update(Vector3 end_effector_pos, double fps) {
    this->update_center_screw_position(end_effector_pos);
}

// calculate distance between two tridimensional points
double distance_between_points(Vector3 p1, Vector3 p2) {
    double distance_between_points(Vector3 p1, Vector3 p2);
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;
    return sqrt(dx * dx + dy * dy + dz * dz);

}

// updates piston center screw position
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

// engine

Engine3D::Engine3D(){}

Engine3D::Engine3D(double z) {
    this->crank = Crank3D(Vector3(0, 0, z), 0.25, 0.5, 0, ENGINE_ON, 120);
    this->left_piston = Piston3D(Vector3(0, 0, z + 4), 0.5, 0.5, 0.5, 2, -PI/4.0);
    this->right_piston = Piston3D(Vector3(0, 0, z - 4), 0.5, 0.5, 0.5, 2, PI/4.0);
    this->draw_crank = RENDER_ON;
    this->draw_left_piston = RENDER_ON;
    this->draw_right_piston = RENDER_ON;
}

// draws separate parts of engine
void Engine3D::draw(double d) {

    // math tricks
    Vector3 old_left = Vector3(this->left_piston.body.offset_x, this->left_piston.body.offset_y, this->left_piston.body.offset_z);
    Vector3 new_left = rotateVector3_z(old_left, this->left_piston.rad);
    this->left_piston.body.update_pos(new_left.x, new_left.y, new_left.z);
    this->left_piston.center_screw_position = new_left;

    this->crank.moving_screw.position = rotateVector3_z(this->crank.moving_screw.position, this->left_piston.rad);
    this->crank.moving_screw.update_pos(this->crank.moving_screw.position.x, this->crank.moving_screw.position.y, this->crank.moving_screw.position.z);

    Vector3 old_right = Vector3(this->right_piston.body.offset_x, this->right_piston.body.offset_y, this->right_piston.body.offset_z);
    Vector3 new_right = rotateVector3_z(old_right, this->right_piston.rad);
    this->right_piston.body.update_pos(new_right.x, new_right.y, new_right.z);
    this->right_piston.center_screw_position = new_right;


    this->left_piston.end_effector_position = this->crank.moving_screw.position;
    this->right_piston.end_effector_position = this->crank.moving_screw.position;

    // rotations

    // crank
    for (int i = 0; i < this->crank.body.n_points; i++) {
        this->crank.body.top[i] = translate(this->crank.body.top[i], Vector3(0, 0, -this->crank.body.offset_z));
        this->crank.body.bottom[i] = translate(this->crank.body.bottom[i], Vector3(0, 0, -this->crank.body.offset_z));
        this->crank.body.top[i] = rotateVector3(AXIS_X, this->x_rotation, this->crank.body.top[i]);
        this->crank.body.bottom[i] = rotateVector3(AXIS_X, this->x_rotation, this->crank.body.bottom[i]);
        this->crank.body.bottom[i] = rotateVector3(AXIS_Y, this->y_rotation, this->crank.body.bottom[i]);
        this->crank.body.top[i] = rotateVector3(AXIS_Y, this->y_rotation, this->crank.body.top[i]);
        this->crank.body.top[i] = rotateVector3(AXIS_Z, this->z_rotation, this->crank.body.top[i]);
        this->crank.body.bottom[i] = rotateVector3(AXIS_Z, this->z_rotation, this->crank.body.bottom[i]);
        this->crank.body.top[i] = translate(this->crank.body.top[i], Vector3(0, 0, this->crank.body.offset_z));
        this->crank.body.bottom[i] = translate(this->crank.body.bottom[i], Vector3(0, 0, this->crank.body.offset_z));
    }
    // crank moving screw
    for (int i = 0; i < 8; i++) {
        this->crank.moving_screw.body.points[i] = translate(this->crank.moving_screw.body.points[i], Vector3(0, 0, -this->crank.moving_screw.body.offset_z));
        this->crank.moving_screw.body.points[i] = rotateVector3(AXIS_X, this->x_rotation, this->crank.moving_screw.body.points[i]);
        this->crank.moving_screw.body.points[i] = rotateVector3(AXIS_Y, this->y_rotation, this->crank.moving_screw.body.points[i]);
        this->crank.moving_screw.body.points[i] = rotateVector3(AXIS_Z, this->z_rotation, this->crank.moving_screw.body.points[i]);
        this->crank.moving_screw.body.points[i] = translate(this->crank.moving_screw.body.points[i], Vector3(0, 0, this->crank.moving_screw.body.offset_z));
    }

    // left piston
    for (int i = 0; i < 8; i++) {
        this->left_piston.body.points[i] = translate(this->left_piston.body.points[i], Vector3(0, 0, -this->left_piston.body.offset_z));
        this->left_piston.body.points[i] = rotateVector3(AXIS_X, this->x_rotation, this->left_piston.body.points[i]);
        this->left_piston.body.points[i] = rotateVector3(AXIS_Y, this->y_rotation, this->left_piston.body.points[i]);
        this->left_piston.body.points[i] = rotateVector3(AXIS_Z, this->z_rotation, this->left_piston.body.points[i]);
        this->left_piston.body.points[i] = translate(this->left_piston.body.points[i], Vector3(0, 0, this->left_piston.body.offset_z));
    }

    this->left_piston.end_effector_position = translate(this->left_piston.end_effector_position, Vector3(0, 0, -this->left_piston.body.offset_z));
    this->left_piston.end_effector_position = rotateVector3(AXIS_X, this->x_rotation, this->left_piston.end_effector_position);
    this->left_piston.end_effector_position = rotateVector3(AXIS_Y, this->y_rotation, this->left_piston.end_effector_position);
    this->left_piston.end_effector_position = rotateVector3(AXIS_Z, this->z_rotation, this->left_piston.end_effector_position);
    this->left_piston.end_effector_position = translate(this->left_piston.end_effector_position, Vector3(0, 0, this->left_piston.body.offset_z));

    this->left_piston.center_screw_position = translate(this->left_piston.center_screw_position, Vector3(0, 0, -this->left_piston.body.offset_z));
    this->left_piston.center_screw_position = rotateVector3(AXIS_X, this->x_rotation, this->left_piston.center_screw_position);
    this->left_piston.center_screw_position = rotateVector3(AXIS_Y, this->y_rotation, this->left_piston.center_screw_position);
    this->left_piston.center_screw_position = rotateVector3(AXIS_Z, this->z_rotation, this->left_piston.center_screw_position);
    this->left_piston.center_screw_position = translate(this->left_piston.center_screw_position, Vector3(0, 0, this->left_piston.body.offset_z));


    // right piston
    for (int i = 0; i < 8; i++) {
        this->right_piston.body.points[i] = translate(this->right_piston.body.points[i], Vector3(0, 0, -this->right_piston.body.offset_z));
        this->right_piston.body.points[i] = rotateVector3(AXIS_X, this->x_rotation, this->right_piston.body.points[i]);
        this->right_piston.body.points[i] = rotateVector3(AXIS_Y, this->y_rotation, this->right_piston.body.points[i]);
        this->right_piston.body.points[i] = rotateVector3(AXIS_Z, this->z_rotation, this->right_piston.body.points[i]);
        this->right_piston.body.points[i] = translate(this->right_piston.body.points[i], Vector3(0, 0, this->right_piston.body.offset_z));
    }

    this->right_piston.end_effector_position = translate(this->right_piston.end_effector_position, Vector3(0, 0, -this->right_piston.body.offset_z));
    this->right_piston.end_effector_position = rotateVector3(AXIS_X, this->x_rotation, this->right_piston.end_effector_position);
    this->right_piston.end_effector_position = rotateVector3(AXIS_Y, this->y_rotation, this->right_piston.end_effector_position);
    this->right_piston.end_effector_position = rotateVector3(AXIS_Z, this->z_rotation, this->right_piston.end_effector_position);
    this->right_piston.end_effector_position = translate(this->right_piston.end_effector_position, Vector3(0, 0, this->right_piston.body.offset_z));

    this->right_piston.center_screw_position = translate(this->right_piston.center_screw_position, Vector3(0, 0, -this->right_piston.body.offset_z));
    this->right_piston.center_screw_position = rotateVector3(AXIS_X, this->x_rotation, this->right_piston.center_screw_position);
    this->right_piston.center_screw_position = rotateVector3(AXIS_Y, this->y_rotation, this->right_piston.center_screw_position);
    this->right_piston.center_screw_position = rotateVector3(AXIS_Z, this->z_rotation, this->right_piston.center_screw_position);
    this->right_piston.center_screw_position = translate(this->right_piston.center_screw_position, Vector3(0, 0, this->right_piston.body.offset_z));

    if (this->draw_crank == RENDER_ON) {
        this->crank.draw(d);
    }
    if (this->draw_left_piston == RENDER_ON) {
        this->left_piston.draw(d);
    }
    if (this->draw_right_piston == RENDER_ON) {
        this->right_piston.draw(d);
    }

    // undo rotations

    // crank
    for (int i = 0; i < this->crank.body.n_points; i++) {
        this->crank.body.top[i] = translate(this->crank.body.top[i], Vector3(0, 0, -this->crank.body.offset_z));
        this->crank.body.bottom[i] = translate(this->crank.body.bottom[i], Vector3(0, 0, -this->crank.body.offset_z));
        this->crank.body.top[i] = rotateVector3(AXIS_Z, -this->z_rotation, this->crank.body.top[i]);
        this->crank.body.bottom[i] = rotateVector3(AXIS_Z, -this->z_rotation, this->crank.body.bottom[i]);
        this->crank.body.bottom[i] = rotateVector3(AXIS_Y, -this->y_rotation, this->crank.body.bottom[i]);
        this->crank.body.top[i] = rotateVector3(AXIS_Y, -this->y_rotation, this->crank.body.top[i]);
        this->crank.body.top[i] = rotateVector3(AXIS_X, -this->x_rotation, this->crank.body.top[i]);
        this->crank.body.bottom[i] = rotateVector3(AXIS_X, -this->x_rotation, this->crank.body.bottom[i]);
        this->crank.body.top[i] = translate(this->crank.body.top[i], Vector3(0, 0, this->crank.body.offset_z));
        this->crank.body.bottom[i] = translate(this->crank.body.bottom[i], Vector3(0, 0, this->crank.body.offset_z));
    }
    // crank moving screw
    for (int i = 0; i < 8; i++) {
        this->crank.moving_screw.body.points[i] = translate(this->crank.moving_screw.body.points[i], Vector3(0, 0, -this->crank.moving_screw.body.offset_z));
        this->crank.moving_screw.body.points[i] = rotateVector3(AXIS_Z, -this->z_rotation, this->crank.moving_screw.body.points[i]);
        this->crank.moving_screw.body.points[i] = rotateVector3(AXIS_Y, -this->y_rotation, this->crank.moving_screw.body.points[i]);
        this->crank.moving_screw.body.points[i] = rotateVector3(AXIS_X, -this->x_rotation, this->crank.moving_screw.body.points[i]);
        this->crank.moving_screw.body.points[i] = translate(this->crank.moving_screw.body.points[i], Vector3(0, 0, this->crank.moving_screw.body.offset_z));
    }

    //left piston
    
    for (int i = 0; i < 8; i++) {
        this->left_piston.body.points[i] = translate(this->left_piston.body.points[i], Vector3(0, 0, -this->left_piston.body.offset_z));
        this->left_piston.body.points[i] = rotateVector3(AXIS_Z, -this->z_rotation, this->left_piston.body.points[i]);
        this->left_piston.body.points[i] = rotateVector3(AXIS_Y, -this->y_rotation, this->left_piston.body.points[i]);
        this->left_piston.body.points[i] = rotateVector3(AXIS_X, -this->x_rotation, this->left_piston.body.points[i]);
        this->left_piston.body.points[i] = translate(this->left_piston.body.points[i], Vector3(0, 0, this->left_piston.body.offset_z));
    }

    this->left_piston.end_effector_position = translate(this->left_piston.end_effector_position, Vector3(0, 0, -this->left_piston.body.offset_z));
    this->left_piston.end_effector_position = rotateVector3(AXIS_Z, -this->z_rotation, this->left_piston.end_effector_position);
    this->left_piston.end_effector_position = rotateVector3(AXIS_Y, -this->y_rotation, this->left_piston.end_effector_position);
    this->left_piston.end_effector_position = rotateVector3(AXIS_X, -this->x_rotation, this->left_piston.end_effector_position);
    this->left_piston.end_effector_position = translate(this->left_piston.end_effector_position, Vector3(0, 0, this->left_piston.body.offset_z));

    this->left_piston.center_screw_position = translate(this->left_piston.center_screw_position, Vector3(0, 0, -this->left_piston.body.offset_z));
    this->left_piston.center_screw_position = rotateVector3(AXIS_Z, -this->z_rotation, this->left_piston.center_screw_position);
    this->left_piston.center_screw_position = rotateVector3(AXIS_Y, -this->y_rotation, this->left_piston.center_screw_position);
    this->left_piston.center_screw_position = rotateVector3(AXIS_X, -this->x_rotation, this->left_piston.center_screw_position);
    this->left_piston.center_screw_position = translate(this->left_piston.center_screw_position, Vector3(0, 0, this->left_piston.body.offset_z));

    //right piston
    for (int i = 0; i < 8; i++) {
        this->right_piston.body.points[i] = translate(this->right_piston.body.points[i], Vector3(0, 0, -this->right_piston.body.offset_z));
        this->right_piston.body.points[i] = rotateVector3(AXIS_Z, -this->z_rotation, this->right_piston.body.points[i]);
        this->right_piston.body.points[i] = rotateVector3(AXIS_Y, -this->y_rotation, this->right_piston.body.points[i]);
        this->right_piston.body.points[i] = rotateVector3(AXIS_X, -this->x_rotation, this->right_piston.body.points[i]);
        this->right_piston.body.points[i] = translate(this->right_piston.body.points[i], Vector3(0, 0, this->right_piston.body.offset_z));
    }

    this->right_piston.end_effector_position = translate(this->right_piston.end_effector_position, Vector3(0, 0, -this->right_piston.body.offset_z));
    this->right_piston.end_effector_position = rotateVector3(AXIS_Z, -this->z_rotation, this->right_piston.end_effector_position);
    this->right_piston.end_effector_position = rotateVector3(AXIS_Y, -this->y_rotation, this->right_piston.end_effector_position);
    this->right_piston.end_effector_position = rotateVector3(AXIS_X, -this->x_rotation, this->right_piston.end_effector_position);
    this->right_piston.end_effector_position = translate(this->right_piston.end_effector_position, Vector3(0, 0, this->right_piston.body.offset_z));

    this->right_piston.center_screw_position = translate(this->right_piston.center_screw_position, Vector3(0, 0, -this->right_piston.body.offset_z));
    this->right_piston.center_screw_position = rotateVector3(AXIS_Z, -this->z_rotation, this->right_piston.center_screw_position);
    this->right_piston.center_screw_position = rotateVector3(AXIS_Y, -this->y_rotation, this->right_piston.center_screw_position);
    this->right_piston.center_screw_position = rotateVector3(AXIS_X, -this->x_rotation, this->right_piston.center_screw_position);
    this->right_piston.center_screw_position = translate(this->right_piston.center_screw_position, Vector3(0, 0, this->right_piston.body.offset_z));

    

    // undo math tricks

    this->left_piston.body.update_pos(old_left.x, old_left.y, old_left.z);
    this->left_piston.center_screw_position = old_left;

    this->crank.moving_screw.position = rotateVector3_z(this->crank.moving_screw.position, -this->left_piston.rad * 2);
    this->crank.moving_screw.update_pos(this->crank.moving_screw.position.x, this->crank.moving_screw.position.y, this->crank.moving_screw.position.z);

    this->right_piston.body.update_pos(old_right.x, old_right.y, old_right.z);
    this->right_piston.center_screw_position = old_right;

    this->left_piston.end_effector_position = this->crank.moving_screw.position;
    this->right_piston.end_effector_position = this->crank.moving_screw.position;

}

// updates parts of the engine
void Engine3D::update(double fps) {
    this->crank.update(fps);
    this->left_piston.update(this->crank.calculate_moving_screw_position(), fps);
    this->right_piston.update(rotateVector3_z(this->crank.calculate_moving_screw_position(), this->left_piston.rad * 2), fps);
}

// engine's render function
void Engine3D::render(double fps, double d){
    this->draw(d);
    this->update(fps);
}

