#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "manager.h"

// fps control
int fps = 0;
Frames frames;


int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

GameManager gameManager(screenHeight, screenWidth);


void setup() {

}


void render()
{
    fps = frames.getFrames();
    gameManager.render(fps, mouseX, mouseY);
}


void keyboard(int key)
{
    gameManager.handleKeyboard(key, 0);
}


void keyboardUp(int key)
{
    gameManager.handleKeyboard(key, 1);
}


void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x;
   mouseY = y;

   // 0 0 click
   // 0 1 solta

   gameManager.handleMouse(button, state, mouseX, mouseY);
}

int main(void)
{
   setup();
   CV::init(&screenWidth, &screenHeight, "Singularity");
   CV::run();
}
