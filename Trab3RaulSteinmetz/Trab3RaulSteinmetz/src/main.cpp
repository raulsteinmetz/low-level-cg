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

OnePistonEngine2D engine(Vector2(screenWidth / 2.0, screenHeight / 1.5), 100, 0, true, 15);

void render()
{
    fps = frames.getFrames();
    engine.draw();
    engine.update(fps);
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
