#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "starship.h"
#include "frames.h"
#include "environment.h"

// fps control
int fps = 0;
Frames frames;





int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

Map map(50, 1, screenHeight, screenWidth);
Starship starship(400, 400, 3, 100, 100, 30);
CubicBezierCurve a(100, Vector2(200.0, 200.0), Vector2(250.0, 250.0), Vector2(300.0, 150.0), Vector2(350.0, 350.0));

void setup() {

}


void render()
{
    fps = frames.getFrames();
    starship.render(fps, mouseX, mouseY);
    map.render();
    //a.draw();
}


void keyboard(int key)
{
    // printf("Pressed: %d\n", key);
    starship.handleKeyboard(key, 0);
}


void keyboardUp(int key)
{
    starship.handleKeyboard(key, 1);
}


void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x;
   mouseY = y;

   // 0 0 click
   // 0 1 solta

   //printf("button - %d, state - %d\n", button, state);
   starship.handleMouse(button, state);
}

int main(void)
{
   setup();
   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}
