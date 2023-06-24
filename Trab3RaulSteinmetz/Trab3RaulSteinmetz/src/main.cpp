#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "frames.h"
#include "engine2d.h"

// fps control
int fps = 0;
Frames frames;


int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

float d = 500.0;

//OnePistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);
TwoPistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);


class Vector3 {
    public:
        float x, y, z;
        Vector3(){}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

Vector3 cube[8];

Vector3 cilinder_bottom[100];
Vector3 cilinder_top[100];



void setupCube() {
    // points in y = 0
    cube[0] = Vector3(1, 1, 1);
    cube[1] = Vector3(-1, 1, 1);
    cube[2] = Vector3(-1, -1, 1);
    cube[3] = Vector3(1, -1, 1);

    // points in y = 1
    cube[4] = Vector3(1, 1, -1);
    cube[5] = Vector3(-1, 1, -1);
    cube[6] = Vector3(-1, -1, -1);
    cube[7] = Vector3(1, -1, -1);


    // tranlade in z (5 units)
    for(int i = 0; i < 8; i++) {
        cube[i].z += 5;
    }

}

void setupCilinder() {
      float radius = 1;
      float height = 2;
   
      for(int i = 0; i < 100; i++) {
         float rad = 2 * PI * i / 100;
         cilinder_bottom[i] = Vector3(radius * cos(rad), radius * sin(rad), 0);
         cilinder_top[i] = Vector3(radius * cos(rad), radius * sin(rad), height);
      }

      // tranlade in z (5 units)
      for(int i = 0; i < 100; i++) {
         cilinder_bottom[i].z += 10;
         cilinder_top[i].z += 10;
      }
}

void rotateCilinderYaxis(double angle) {
      double rad = angle * PI / 180.0;
      for(int i = 0; i < 100; i++) {
         // center cilinder in 0, 0, 0
         cilinder_bottom[i].z -= 10;
         cilinder_top[i].z -= 10;


         float x = cilinder_bottom[i].x * cos(rad) - cilinder_bottom[i].z * sin(rad);
         float z = cilinder_bottom[i].x * sin(rad) + cilinder_bottom[i].z * cos(rad);
         cilinder_bottom[i].x = x;
         cilinder_bottom[i].z = z;

         x = cilinder_top[i].x * cos(rad) - cilinder_top[i].z * sin(rad);
         z = cilinder_top[i].x * sin(rad) + cilinder_top[i].z * cos(rad);
         cilinder_top[i].x = x;
         cilinder_top[i].z = z;


         cilinder_bottom[i].z += 10;
         cilinder_top[i].z += 10;
      }
}


Vector2 perspective(Vector3 v) {
    float x = v.x * d / (v.z);
    float y = v.y * d / (v.z);
    return Vector2(x, y);
}

void cilinder3d () {
      //CV::translate(float(screenWidth)/2.0, float(screenHeight)/2.0);

      d = mouseY;
   
      // drawing lines
      CV::color(0, 0, 0);
      for(int i = 0; i < 100; i++) {
         CV::line(perspective(cilinder_bottom[i]), perspective(cilinder_bottom[(i+1)%100]));
         CV::line(perspective(cilinder_top[i]), perspective(cilinder_top[(i+1)%100]));
         CV::line(perspective(cilinder_bottom[i]), perspective(cilinder_top[i]));
      }
}


void cube3d() {
    CV::translate(float(screenWidth)/2.0, float(screenHeight)/2.0);

    // drawing lines
    CV::color(0, 0, 0);
    CV::line(perspective(cube[0]), perspective(cube[1]));
    CV::line(perspective(cube[1]), perspective(cube[2]));
    CV::line(perspective(cube[2]), perspective(cube[3]));
    CV::line(perspective(cube[3]), perspective(cube[0]));
    CV::line(perspective(cube[4]), perspective(cube[5]));
    CV::line(perspective(cube[5]), perspective(cube[6]));
    CV::line(perspective(cube[6]), perspective(cube[7]));
    CV::line(perspective(cube[7]), perspective(cube[4]));
    CV::line(perspective(cube[0]), perspective(cube[4]));
    CV::line(perspective(cube[1]), perspective(cube[5]));
    CV::line(perspective(cube[2]), perspective(cube[6]));
    CV::line(perspective(cube[3]), perspective(cube[7]));


}


double angle = 0;

void render()
{
   CV::translate(400, 300);
   fps = frames.getFrames();
   engine.draw();
   engine.update(fps);
   cube3d();

   angle += 0.00001;
   if (angle > 360) angle = 0;
   rotateCilinderYaxis(angle);
   cilinder3d();
}


void keyboard(int key)
{

}


void keyboardUp(int key)
{

}


void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x;
   mouseY = y;

   // 0 0 click
   // 0 1 solta;
}

int main(void)
{
   setupCube();
   setupCilinder();
   CV::init(&screenWidth, &screenHeight, "V TWIN");
   CV::run();
}
