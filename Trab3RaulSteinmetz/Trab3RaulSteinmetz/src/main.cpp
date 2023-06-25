#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "frames.h"
#include "engine2d.h"
#include "models3d.h"

// fps control
int fps = 0;
Frames frames;


int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

float d = 500.0;

//OnePistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);
TwoPistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);

Cube testCube(1.0, 2, 2, 2);
Cilinder testCilinder(1.0, 2.0, 100, 0, 0, 2);


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

   // testing 
   testCube.draw(d);
   testCilinder.draw(d);

   testCube.rotate(AXIS_Z, angle);
   testCube.rotate(AXIS_X, angle);
   testCube.rotate(AXIS_Y, angle);

   testCilinder.rotate(AXIS_Z, angle);
   testCilinder.rotate(AXIS_X, angle);
   testCilinder.rotate(AXIS_Y, angle);

   angle += 0.00001;
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
   CV::init(&screenWidth, &screenHeight, "V TWIN");
   CV::run();
}
