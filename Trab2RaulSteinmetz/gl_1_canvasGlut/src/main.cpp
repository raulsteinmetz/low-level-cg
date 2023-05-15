#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "starship.h"


int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY;

Starship starship(10.0, 5.0, 2, 1, 50, 100, 100, 200, 200, 20);

void setup() {

}


void render()
{
    starship.draw();
    starship.aim(mouseX, mouseY);
    starship.updatePos();
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
