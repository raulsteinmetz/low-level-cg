#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "starship.h"


int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY;

Starship starship(10.0, 5.0, 2, 1, 50, 100, 100, 300, 300, 20);

void setup() {

}


void render()
{
    starship.draw();
}


void keyboard(int key)
{
   // printf("Pressed: %d\n", key);
}


void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}


void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x;
   mouseY = y;

   // printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( state == 0 )
   {

   }
}

int main(void)
{
   setup();
   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}
