#ifndef UTIL_H
#define UTIL_H

#define PI_ 3.1415

float angle_to_radians(float angle) {
    return angle * PI_ / 180.0;
}

float radians_to_angle(float rad) {
    return rad * 180 / PI_;
}


#endif // UTIL_H
