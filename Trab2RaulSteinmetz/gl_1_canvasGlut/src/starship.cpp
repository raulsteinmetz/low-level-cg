#include "starship.h"

# define BULLET_DELAY 50
# define INITIAL_BULLET_SPEED_FACTOR 0.00001
# define MAX_BULLET_SPEED_FACTOR 0.0001

#define PI_ 3.1415

float angle_to_radians(float angle) {
    return angle * PI_ / 180.0;
}

float radians_to_angle(float rad) {
    return rad * 180 / PI_;
}

// Constructor
Starship::Starship(double max_speed_factor, double current_speed_factor, int hp, float px, float py, float radius)
    : max_speed_factor(max_speed_factor), current_speed_factor(current_speed_factor), hp(hp), radius(radius)
{
    // movement
    go_forward = false;
    go_backwards = false;
    go_right = false;
    go_left = false;

    // shooting
    is_shooting = false;

    position.x = px;
    position.y = py;
    angle = 270.0;

    // gun initialization
    gun = Gun(Vector2(0, 0), BULLET_DELAY, angle, INITIAL_BULLET_SPEED_FACTOR, MAX_BULLET_SPEED_FACTOR);

    updatePos();
}



// render
void Starship::render(int fps, int  mouseX, int mouseY) {
    draw();
    aim(mouseX, mouseY);
    movePos();
    updatePos();
    shoot();
    gun.updateBullets();
    update_parameters(fps);
}


// methods

void Starship::updatePos() {
    float rad = angle_to_radians(angle);
    float spacing = 360.0 / 3.0;

    for (int i = 0; i < 3; i++) {
        polygon_x[i] = position.x + radius * cos(rad);
        polygon_y[i] = position.y + radius * sin(rad);
        rad += angle_to_radians(spacing);
    }

    gun.position.x = polygon_x[0];
    gun.position.y = polygon_y[0];
}

void Starship::aim(float x, float y) {
    Vector2 direction(x - position.x, y - position.y);
    float rad = atan2(direction.y, direction.x);
    angle = radians_to_angle(rad);

}

void Starship::update_parameters(int fps) {
    max_speed_factor = MAX_SPEED / fps;
    true_speed = current_speed_factor / fps;
    gun.updateDelay();
    gun.updateAngle(angle);
    gun.app_fps = fps;

}

void Starship::draw() {
    // drawing ship
    CV::color(0, 0, 0);
    CV::polygon(this->polygon_x, this->polygon_y, 3);
    // drawing gun
    gun.draw();
}

void Starship::movePos() {
    if (go_forward == true) {
        position.x += cos(angle_to_radians(angle)) * true_speed;
        position.y += sin(angle_to_radians(angle)) * true_speed;
    }
    if (go_backwards == true) {
        position.x += cos(angle_to_radians(angle + 180)) * true_speed;
        position.y += sin(angle_to_radians(angle + 180)) * true_speed;
    }
    if (go_right == true) {
        position.x += cos(angle_to_radians(angle + 90)) * true_speed;
        position.y += sin(angle_to_radians(angle + 90)) * true_speed;
    }
    if (go_left == true) {
        position.x += cos(angle_to_radians(angle + 270)) * true_speed;
        position.y += sin(angle_to_radians(angle + 270)) * true_speed;
    }
}

void Starship::shoot() {
    if (is_shooting == true) {;
        gun.shoot();
    }
}

void Starship::handleKeyboard(int command, int up) {
    if (command == MOVE_FORWARD) {
        if (up == 0) {
            go_forward = true;
        } else {
            go_forward = false;
        }
    } else if (command == MOVE_BACKWARDS) {
        if (up == 0) {
            go_backwards = true;
        } else {
            go_backwards = false;
        }
    } else if (command == MOVE_RIGHT) {
        if (up == 0) {
            go_right = true;
        } else {
            go_right = false;
        }
    } else if (command == MOVE_LEFT) {
        if (up == 0) {
            go_left = true;
        } else {
            go_left = false;
        }
    }
}

void Starship::handleMouse(int button, int state) {
    if (button == 0) {
        if (state == 0) {
            is_shooting = true;
        }
        else {
            is_shooting = false;
        }
    }
}

