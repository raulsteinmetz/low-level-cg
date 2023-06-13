#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


#include "gl_canvas2d.h"



int screenWidth = 800, screenHeight = 800;
int mouseX, mouseY;

float d = 500.0;


class Vector3 {
    public:
        float x, y, z;
        Vector3(){}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

Vector3 cube[8];


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


Vector2 perspective(Vector3 v) {
    float x = v.x * d / (v.z);
    float y = v.y * d / (v.z);
    return Vector2(x, y);
}


void cube3d() {
    CV::translate(float(screenWidth)/2.0, float(screenHeight)/2.0);

    d = mouseY;

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


void render() {
    cube3d();
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

    setupCube();
    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
    CV::run();
}
