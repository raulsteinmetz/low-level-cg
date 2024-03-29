/*

    Made by Raul Steinmetz

    This file is responsable for managing the player class
        

*/



#include "starship.h"

# define BULLET_DELAY 50
# define INITIAL_BULLET_SPEED_FACTOR 300

#define PI_ 3.1415

float angle_to_radians(float angle) {
    return angle * PI_ / 180.0;
}

float radians_to_angle(float rad) {
    return rad * 180 / PI_;
}

// Constructor
Starship::Starship() {}
Starship::Starship(double speed_factor, int hp, float px, float py, float radius)
    : speed_factor(speed_factor), hp(hp), radius(radius)
{
    // movement
    go_right = false;
    go_left = false;

    fps = 0;

    // shooting
    is_shooting = false;

    position.x = px;
    position.y = py;
    angle = 270.0;

    // gun initialization
    gun = Gun(Vector2(0, 0), BULLET_DELAY, angle, INITIAL_BULLET_SPEED_FACTOR);

    color_r = 1.00;
    color_g = 1.00;
    color_b = 1.00;


    update_pos();
}


// getters
Vector2 Starship::get_position() {
    return position;
}

double Starship::get_velocity() {
    return speed_factor;
}




// render
void Starship::render(int fps, int  mouseX, int mouseY) {
    update_parameters(float(fps));
    draw();
    aim(mouseX, mouseY);
    movePos();
    update_pos();
    shoot();
    gun.render(angle, fps);
    drawHP();
    //printf("Position: %f, %f\n", position.x, position.y);
}


// methods

void Starship::update_pos() {
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

void Starship::update_parameters(float fps) {
    this->fps = fps;
}

void Starship::draw() {
    // drawing ship
    CV::color(color_r, color_g, color_b);
    CV::polygon(this->polygon_x, this->polygon_y, 3);
    // drawing gun
    gun.draw();
}

void Starship::movePos() {
    if (go_right == true) {
        position.x += cos(angle_to_radians(angle + 90)) * (speed_factor / fps);
    }
    if (go_left == true) {
        position.x += cos(angle_to_radians(angle + 270)) * (speed_factor / fps);
    }
}

void Starship::shoot() {
    if (is_shooting == true) {
        gun.shoot();
    }
}

void Starship::handleKeyboard(int command, int up) {
    if (command == MOVE_RIGHT) {
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

void Starship::takeDamage(int damage) {
    hp -= damage;
}

void Starship::drawHP() {
    for (int i = 0; i < hp; i++) {
        CV::color(255, 0, 0);
        CV::circleFill(20 + i * 20, 20, 10, 25);
    }
}

bool checkPointInsideTriangle_(Vector2 point, Vector2 triangle[]) {
    float x1 = triangle[0].x, x2 = triangle[1].x, x3 = triangle[2].x;
    float y1 = triangle[0].y, y2 = triangle[1].y, y3 = triangle[2].y;
    float x = point.x, y = point.y;

    float denominator = ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
    float a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / denominator;
    float b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / denominator;
    float c = 1 - a - b;

    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}

bool checkTriangleColision_(float traingle_x[], float traingle_y[], Vector2 bulletPosition, float bullet_radius) {

        double x = bulletPosition.x;
        double y = bulletPosition.y;


        Vector2 triangle[3];
        triangle[0] = Vector2(traingle_x[0], traingle_y[0]);
        triangle[1] = Vector2(traingle_x[1], traingle_y[1]);
        triangle[2] = Vector2(traingle_x[2], traingle_y[2]);


        for (int i = 0; i < 3; i++) {
            if (checkPointInsideTriangle_(Vector2(x, y), triangle)) {
                return true;
            }
        }

    return false;
}


bool Starship::isHit(Vector2 position, float bullet_radius) {
    return checkTriangleColision_(polygon_x, polygon_y, position, bullet_radius);
}