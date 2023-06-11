#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include "Vector2.h"
#include "gun.h"
#include "gl_canvas2d.h"
#include <list>

// implements a bezier curve
class CubicBezierCurve {
    private:
        double calculatePoint(double t, double p0, double p1, double p2, double p3);


    public:
        Vector2 points[4];
        CubicBezierCurve();
        CubicBezierCurve(int n_points, Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3);
        void draw();
        bool checkTriangleColision(float triangle_x[], float triangle_y[]);
        int n_points;      
};


class Map {
    public:
        int point_resolution;
        int n_curves;
        int screen_height;
        int screen_width;
        std::list<CubicBezierCurve> right_boundary;
        std::list<CubicBezierCurve> left_boundary;

        Map();
        Map(int point_resolution, int n_screens, int screen_height, int screen_width);
        bool render(float player_velocity, float fps, float player_points_x[], float player_points_y[]);
        void infiniteGeneration(); 
        bool verifyPlayerColision(float player_x[], float player_y[]);
};


#endif // ENVIRONMENT_H