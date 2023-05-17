#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"



int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY;


// CG_5_COR

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

void RGBtoHLS(float r, float g, float b, float *h, float *s, float *l) {
    r /= 255;
    g /= 255;
    b /= 255;

    float max_ = MAX(MAX(r, g), b);
    float min_ = MIN(MIN(r, g), b);

    *h = *s = *l = (max_ + min_) / 2;

    if (max_ == min_) *h = *s = 0; // gray
    else {
        float d = max_ - min_;
        *s = (*l > 0.5) ? d / (2 - max_ - min_) : d / (max_ + min_);

        if (max_ == r) {
          *h = (g - b) / d + (g < b ? 6 : 0);
        }
        else if (max_ == g) {
          *h = (b - r) / d + 2;
        }
        else if (max_ == b) {
          *h = (r - g) / d + 4;
        }

        *h /= 6;
    }
}



void render_cor()
{
    float h, l, s;
    int r = 50, g = 30, b = 150;
    RGBtoHLS(r, g, b, &h, &l, &s);
    printf("Converting RGB (50, 30, 150) to HLS: (%f, %f, %f)\n", h, l, s);

}

#define ORIGIN_X 100
#define ORIGIN_Y 100

#define AXIS_SIZE 300

float p1(float t) {
   return (1 - t) * (1 - t) * (1 - t);
}

float p2(float t) {
   return 3 * t * (1 - t) * (1 - t);
}

float p3(float t) {
   return 3 * t * t * (1 - t);
}
float p4(float t) {
   return t * t * t;
}

void testing_blending_funcs() {
for (float t = 0; t <= 1; t += 0.0001)
    {
        CV::color(0.5, 0.5, 0.5);
        CV::point(t * AXIS_SIZE + ORIGIN_X, p1(t) * AXIS_SIZE + ORIGIN_Y );
        CV::point(t * AXIS_SIZE + ORIGIN_X, p2(t) * AXIS_SIZE + ORIGIN_Y);
        CV::point(t * AXIS_SIZE + ORIGIN_X, p3(t)* AXIS_SIZE + ORIGIN_Y);
        CV::point(t * AXIS_SIZE + ORIGIN_X, p4(t) * AXIS_SIZE + ORIGIN_Y);
    }
}

void curvas_besier() {
    // origin
    Vector2 origin;
    origin.x = ORIGIN_X;
    origin.y = ORIGIN_Y;
    // drawing axes
    Vector2 y_;
    y_.x = ORIGIN_X;
    y_.y = ORIGIN_Y + AXIS_SIZE;
    Vector2 x_;
    x_.x = ORIGIN_X + AXIS_SIZE;
    x_.y = ORIGIN_Y;

    CV::color(0, 0, 0);

    CV::line(origin.x, origin.y, y_.x, y_.y);
    CV::line(origin.x, origin.y, x_.x, x_.y);

    // end points
    float p0_x = mouseX - 250;
    float p0_y = mouseY - 250;
    float p3_x = mouseX;
    float p3_y = mouseY;

    // control points
    float p1_x = p0_x + 250;
    float p1_y = p0_y + 10;
    float p2_x = mouseX - 100;
    float p2_y = mouseY - 100;

    // Calculate the curve points using the cubic Bézier equation
    for (float t = 0; t <= 1.0; t += 0.001)
    {
        float u = 1 - t;
        float x = u * u * u * p0_x + 3 * u * u * t * p1_x + 3 * u * t * t * p2_x + t * t * t * p3_x;
        float y = u * u * u * p0_y + 3 * u * u * t * p1_y + 3 * u * t * t * p2_y + t * t * t * p3_y;
        CV::point(x, y);
    }

    CV::point(p0_x, p0_y);
    // print("%f, %f", p0_x, p0_y);

    CV::line(p0_x, p0_y, p1_x, p1_y);
    CV::line(p1_x, p1_y, p2_x, p2_y);
    CV::line(p2_x, p2_y, p3_x, p3_y);




}


void render()
{
    curvas_besier();
}


void keyboard(int key)
{
   printf("Pressed: %d\n", key);
}


void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}


void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x;
   mouseY = y;

   //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( state == 0 )
   {

   }
}

int main(void)
{


   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}
