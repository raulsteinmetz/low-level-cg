#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Bola.h"
#include "Relogio.h"
#include "Botao.h"


int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY;


// CG_5_COR

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

void RGBtoHLS(float r, float g, float b, float *h, float *s, float *l) {
    r /= 255;
    g /= 255;
    b /= 255;

    float max_ = MAX(MAX(r, g), b);
    float min_ = MIN(MIN(r, g), b);

    *h = *s = *l = (max_ + min_) / 2;

    if (max_ == min_) *h = *s = 0; // gray
    else {
        float d = max_ - min_;
        *s = (*l > 0.5) ? d / (2 - max_ - min_) : d / (max_ + min_);

        if (max_ == r) {
          *h = (g - b) / d + (g < b ? 6 : 0);
        }
        else if (max_ == g) {
          *h = (b - r) / d + 2;
        }
        else if (max_ == b) {
          *h = (r - g) / d + 4;
        }

        *h /= 6;
    }
}



void render_cor()
{
    float h, l, s;
    int r = 50, g = 30, b = 150;
    RGBtoHLS(r, g, b, &h, &l, &s);
    printf("Converting RGB (50, 30, 150) to HLS: (%f, %f, %f)\n", h, l, s);

}


void render()
{
    render_cor();
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

   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( state == 0 )
   {

   }
}

int main(void)
{


   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}
