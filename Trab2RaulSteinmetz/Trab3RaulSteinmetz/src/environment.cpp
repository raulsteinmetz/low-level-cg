/*

    Made by Raul Steinmetz

    This file is responsable for map render and its physics

*/


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

    CV::color(0.5, 0, 1);

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


bool checkPointInsideTriangle(Vector2 point, Vector2 triangle[]) {
    float x1 = triangle[0].x, x2 = triangle[1].x, x3 = triangle[2].x;
    float y1 = triangle[0].y, y2 = triangle[1].y, y3 = triangle[2].y;
    float x = point.x, y = point.y;

    float denominator = ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
    float a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / denominator;
    float b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / denominator;
    float c = 1 - a - b;

    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}


bool CubicBezierCurve::checkTriangleColision(float traingle_x[], float traingle_y[]) {

    for (float t = 0; t <= 1; t+=float(1.0/n_points)) {
        double x = calculatePoint(t, points[0].x, points[1].x, points[2].x, points[3].x);
        double y = calculatePoint(t, points[0].y, points[1].y, points[2].y, points[3].y);


        Vector2 triangle[3];
        triangle[0] = Vector2(traingle_x[0], traingle_y[0]);
        triangle[1] = Vector2(traingle_x[1], traingle_y[1]);
        triangle[2] = Vector2(traingle_x[2], traingle_y[2]);


        for (int i = 0; i < 3; i++) {
            if (checkPointInsideTriangle(Vector2(x, y), triangle)) {
                return true;
            }
        }
        
    }
    return false;
}


// environment

float generateRandomFloat(float minValue, float maxValue) {
    return minValue + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxValue - minValue)));
}


Map::Map() {}

Map::Map(int point_resolution, int n_curves, int screen_height, int screen_width) {
    this->n_curves = n_curves;
    this->screen_height = screen_height;
    this->screen_width = screen_width;
    this->point_resolution = point_resolution;

    // right boundary
    Vector2 last_finish_pointR(float(screen_width * 0.7), float(screen_height));
    Vector2 last_finish_pointL(float(screen_width * 0.3), float(screen_height));
    for (int i = 0; i < n_curves; i++) {
        left_boundary.push_back(
            CubicBezierCurve(
                this->point_resolution,
                last_finish_pointL,
                Vector2(
                    generateRandomFloat(float(screen_width * 0.2), float(screen_width * 0.4)),
                    last_finish_pointL.y - (float) (screen_height * 0.3)
                ),
                Vector2(
                    generateRandomFloat(float(screen_width * 0.2), float(screen_width * 0.4)),
                    last_finish_pointL.y - (float) (screen_height * 0.7)
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
                    last_finish_pointR.y - (float) (screen_height * 0.3)
                ),
                Vector2(
                    generateRandomFloat(float(screen_width * 0.6), float(screen_width * 0.8)),
                    last_finish_pointR.y - (float) (screen_height * 0.7)
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


void Map::infiniteGeneration() {
    // check if the curve in curves [n-1]'s last point is greater then 0
    // if it is, generate a new curve and push it to the end of the vector
    if (left_boundary.back().points[3].y > 0 - screen_height) {
        left_boundary.push_back(
            CubicBezierCurve(
                this->point_resolution,
                left_boundary.back().points[3],
                Vector2(
                    generateRandomFloat(float(screen_width * 0.2), float(screen_width * 0.4)),
                    left_boundary.back().points[3].y - (float) (screen_height * 0.3)
                ),
                Vector2(
                    generateRandomFloat(float(screen_width * 0.2), float(screen_width * 0.4)),
                    left_boundary.back().points[3].y - (float) (screen_height * 0.7)
                ),
                Vector2(
                    float(screen_width * 0.3),
                    float(left_boundary.back().points[3].y - screen_height)
                )
            )
        );
        right_boundary.push_back(
            CubicBezierCurve(
                this->point_resolution,
                right_boundary.back().points[3],
                Vector2(
                    generateRandomFloat(float(screen_width * 0.6), float(screen_width * 0.8)),
                    right_boundary.back().points[3].y - (float) (screen_height * 0.3)
                ),
                Vector2(
                    generateRandomFloat(float(screen_width * 0.6), float(screen_width * 0.8)),
                    right_boundary.back().points[3].y - (float) (screen_height * 0.7)
                ),
                Vector2(
                    float(screen_width * 0.7),
                    float(right_boundary.back().points[3].y - screen_height)
                )
            )
        );

        // pop the first curve
        left_boundary.erase(left_boundary.begin());
        right_boundary.erase(right_boundary.begin());
        
    }
}

// check if player triangle colides with any of the curves
bool Map::verifyPlayerColision(float player_x[], float player_y[]) {
    // calculating the curves
    for (auto it = left_boundary.begin(); it != left_boundary.end(); it++) {
        if (it->checkTriangleColision(player_x, player_y)) {
            return true;
        }
    }

    for (auto it = right_boundary.begin(); it != right_boundary.end(); it++) {
        if (it->checkTriangleColision(player_x, player_y)) {
            return true;
        }
    }
    
}


// returns flag if the player is out of the map
bool Map::render(float player_velocity, float fps, float player_points_x[], float player_points_y[]) {

    // black screen
    CV::color(0, 0, 0);
    CV::rectFill(0, 0, screen_width, screen_height);
    

    // reducing y on all curves
    for (auto it = left_boundary.begin(); it != left_boundary.end(); it++) {
        for (int i = 0; i < 4; i++) {
            it->points[i].y += player_velocity / fps;
        }
    }

    for (auto it = right_boundary.begin(); it != right_boundary.end(); it++) {
        for (int i = 0; i < 4; i++) {
            it->points[i].y += player_velocity / fps;
        }
    }

    int how_many_cuves = 0;
    // drawing curves
    for (auto it = left_boundary.begin(); it != left_boundary.end(); it++) {
        how_many_cuves++;
        it->draw();
    }

    for (auto it = right_boundary.begin(); it != right_boundary.end(); it++) {
        it->draw();
    }

    infiniteGeneration();

    // checking colision
    if (verifyPlayerColision(player_points_x, player_points_y)) {
        return true;
    }
    return false;
}
