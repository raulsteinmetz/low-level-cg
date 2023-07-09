#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "frames.h"
#include "engine2d.h"
#include "engine3d.h"

#define BIDIMENTIONAL 0
#define TRIDIMENTIONAL 1


// fps control
int fps = 0;
Frames frames;
int state = TRIDIMENTIONAL;

int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

float d = 500.0;

TwoPistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);
Engine3D engine3d;

void _init() {
   engine3d = Engine3D(4);
}

double angle = 100;
float pos_x = 0;
float pos_y = 0;

void render()
{
   CV::translate(400, 400);
   fps = frames.getFrames();

   if (state == BIDIMENTIONAL) {
      engine.draw();
      engine.update(fps);
   }
   else {
      engine3d.render(fps, d);
      engine3d.x_rotation = 0;
      engine3d.y_rotation = 0;
      engine3d.z_rotation = 0;
   }

   d = mouseY;


   angle += 0.00001;
   if (angle > 2 * PI) angle = 0;
}


void keyboard(int key)
{
   if (key == 49) {
      state = BIDIMENTIONAL;
   }
   else if (key == 50){ 
      state = TRIDIMENTIONAL;
   }
}


void keyboardUp(int key)
{
   printf("key up: %d\n", key);
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
