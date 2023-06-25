#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "frames.h"
#include "engine2d.h"
#include "engine3d.h"

// fps control
int fps = 0;
Frames frames;


int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

float d = 500.0;

//OnePistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);
TwoPistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);

Cuboid testCube(1.0, 2, 2, 2);
Cilinder testCilinder(1.0, 2.0, 100, 0, 0, 2);
Cuboid testCuboid(1.0, 2.0, 3.0, 0, 0, 5.0);

Engine3D engine3d;

void _init() {
   engine3d = Engine3D();
}

double angle = 0;

void render()
{
   CV::translate(400, 300);
   fps = frames.getFrames();
   engine.draw();

   angle += 0.00001;
   if (angle > 360) angle = 0;
   engine.update(fps);

   d = mouseY;

   engine3d.draw(d);
   engine3d.update(fps);

   // testing
   /* testCube.draw(d);
   testCilinder.draw(d);
   testCuboid.draw(d);

   testCube.rotate(AXIS_Z, angle);
   testCube.rotate(AXIS_X, angle);
   testCube.rotate(AXIS_Y, angle);

   testCilinder.rotate(AXIS_Z, angle);
   testCilinder.rotate(AXIS_X, angle);
   testCilinder.rotate(AXIS_Y, angle);

   testCuboid.rotate(AXIS_Z, angle);
   testCuboid.rotate(AXIS_X, angle);
   testCuboid.rotate(AXIS_Y, angle);*/

   //engine3d.rotate(AXIS_Z, angle/fps);
   //engine3d.rotate(AXIS_X, angle/fps);
   //engine3d.rotate(AXIS_Y, angle/fps);


   angle += 10;
   if (angle > 360) angle = 0; 
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
   _init();
   CV::init(&screenWidth, &screenHeight, "V TWIN");
   CV::run();
}
