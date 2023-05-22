#include "environment.h"
#include <stdio.h>

// bezier curve

CubicBezierCurve::CubicBezierCurve() {}

CubicBezierCurve::CubicBezierCurve(int n_points, Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3) {
    this->n_points = n_points;
    // nao sei em
    points[0] = p0;
    points[1] = p1;
    points[2] = p2;
    points[3] = p3;

}

double CubicBezierCurve::calculatePoint(double t, double p0, double p1, double p2, double p3) {
    double a = pow((1 - t), 3) * p0;
    double b = 3 * pow((1 - t), 2) * t * p1;
    double c = 3 * (1 - t) * pow(t, 2) * p2;
    double d = pow(t, 3) * p3;
    return a + b + c + d;
}


void CubicBezierCurve::draw() {
    CV::color(0, 0, 0);
    float last_x = 0, last_y = 0;
    bool first_it = true;

    //draw control points
    CV::color(0, 0, 255);
    for (int i = 0; i < 4; i++) {
        CV::circle(points[i].x, points[i].y, 5, 20);
    }

    //draw curve
    for (float t = 0; t <= 1; t+=float(1.0/n_points)) {
        double x = calculatePoint(t, points[0].x, points[1].x, points[2].x, points[3].x);
        double y = calculatePoint(t, points[0].y, points[1].y, points[2].y, points[3].y);

        if (first_it == true) {
            CV::point(x, y);
            first_it = false;
        }
        else {
            CV::line(last_x, last_y, x, y);
        }
        last_x = x;
        last_y = y;
    }
}


// environment

float generateRandomFloat(float minValue, float maxValue) {
    return minValue + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxValue - minValue)));
}


Map::Map() {}

Map::Map(int point_resolution, int n_screens, int screen_height, int screen_width) {
    this->n_screens = n_screens;
    this->screen_height = screen_height;
    this->screen_width = screen_width;
    this->point_resolution = point_resolution;

    // right boundary
    Vector2 last_finish_pointR(float(screen_width * 0.7), float(screen_height));
    Vector2 last_finish_pointL(float(screen_width * 0.3), float(screen_height));
    for (int i = 0; i < n_screens; i++) {
        left_boundary.push_back(
            CubicBezierCurve(
                this->point_resolution,
                last_finish_pointL,
                Vector2(
                    generateRandomFloat(float(screen_width * 0.2), float(screen_width * 0.4)),
                    (float) (screen_height * 0.3)
                ),
                Vector2(
                    generateRandomFloat(float(screen_width * 0.2), float(screen_width * 0.4)),
                    (float) (screen_height * 0.7)
                ),
                Vector2(
                    float(screen_width * 0.3),
                    float(last_finish_pointL.y - screen_height)
                )
            )
        );
        right_boundary.push_back(
            CubicBezierCurve(
                this->point_resolution,
                last_finish_pointR,
                Vector2(
                    generateRandomFloat(float(screen_width * 0.6), float(screen_width * 0.8)),
                    (float) (screen_height * 0.3)
                ),
                Vector2(
                    generateRandomFloat(float(screen_width * 0.6), float(screen_width * 0.8)),
                    (float) (screen_height * 0.7)
                ),
                Vector2(
                    float(screen_width * 0.7),
                    float(last_finish_pointR.y - screen_height)
                )
            )
        );

        // setting up last finish point
        last_finish_pointL = left_boundary.back().points[3];
        last_finish_pointR = right_boundary.back().points[3];
    }
}

void Map::render(){
    for (auto it = left_boundary.begin(); it != left_boundary.end(); it++) {
        it->draw();
    }
    for (auto it = right_boundary.begin(); it != right_boundary.end(); it++) {
        it->draw();
    }
}