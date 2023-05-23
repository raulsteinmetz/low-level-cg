#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"



int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY;

// Curvas de Bezier

#define ORIGIN_X 100
#define ORIGIN_Y 100

#define AXIS_SIZE 300

void curvas_besier() {
    // origin
    Vector2 origin;
    origin.x = ORIGIN_X;
    origin.y = ORIGIN_Y;
    // drawing axes
    Vector2 y_;
    y_.x = ORIGIN_X;
    y_.y = ORIGIN_Y + AXIS_SIZE;
    Vector2 x_;
    x_.x = ORIGIN_X + AXIS_SIZE;
    x_.y = ORIGIN_Y;

    CV::color(0, 0, 0);

    CV::line(origin.x, origin.y, y_.x, y_.y);
    CV::line(origin.x, origin.y, x_.x, x_.y);

    // end points
    float p0_x = mouseX - 250;
    float p0_y = mouseY - 250;
    float p3_x = mouseX;
    float p3_y = mouseY;

    // control points
    float p1_x = p0_x + 250;
    float p1_y = p0_y + 10;
    float p2_x = mouseX - 100;
    float p2_y = mouseY - 100;

    // Calculate the curve points using the cubic B�zier equation
    for (float t = 0; t <= 1.0; t += 0.001)
    {
        float u = 1 - t;
        float x = u * u * u * p0_x + 3 * u * u * t * p1_x + 3 * u * t * t * p2_x + t * t * t * p3_x;
        float y = u * u * u * p0_y + 3 * u * u * t * p1_y + 3 * u * t * t * p2_y + t * t * t * p3_y;
        CV::point(x, y);
    }

    CV::point(p0_x, p0_y);
    // print("%f, %f", p0_x, p0_y);

    CV::line(p0_x, p0_y, p1_x, p1_y);
    CV::line(p1_x, p1_y, p2_x, p2_y);
    CV::line(p2_x, p2_y, p3_x, p3_y);

}


// PROVA 1 2022

#define DRAW_ORIGIN 200

void multiplyMatrices(float mat1[2][2], float mat2[2][2], float result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

class P1_2022 {
    public:
        double rotate_var;

        P1_2022() {
            rotate_var = 4 * PI;
        }

        void questao_3 () {

            /*  Implemente em C/pseudocodigo a função render()
                da canvas2D de modo que seja gerado uma figura
                em forma de caracol. Este caracol deve estar 
                girando em sentido horário (animado). Pode-se 
                definir variáveis globais. Utilize a função 
                point() da canvas2D para desenho  */

            CV::color(0);
            float radius = 200;

            for (float rad = rotate_var; rad < 4 * PI + rotate_var; rad += 0.001, radius -= 200 / ((4 * PI) / 0.001)) {
                float x = radius * cos(rad) + DRAW_ORIGIN;
                float y = radius * sin(rad) + DRAW_ORIGIN;
                CV::point(x, y);
            }

            rotate_var -= 0.001;
            if (rotate_var == 0) {
                rotate_var = 4 * PI;
            }
            
        }

        static void questao_4() {
            // desenhando eixos
            Vector2 x_axe(ORIGIN_X + AXIS_SIZE, ORIGIN_Y);
            Vector2 y_axe(ORIGIN_X, ORIGIN_Y + AXIS_SIZE);
            CV::color(0);
            CV::line(ORIGIN_X, ORIGIN_Y, x_axe.x, x_axe.y);
            CV::line(ORIGIN_X, ORIGIN_Y, y_axe.x, y_axe.y);

            // ramp
            float ramp[4];
            ramp[0] = ORIGIN_X;
            ramp[1] = y_axe.y;
            ramp[2] = x_axe.x * 0.8;
            ramp[3] = ORIGIN_Y;
            CV::line(ramp[0], ramp[1], ramp[2], ramp[3]);

            // initial rect 
            float rect[4];
            rect[0] = ORIGIN_X;
            rect[1] = ORIGIN_Y;
            rect[2] = ORIGIN_X - 50;
            rect[3] = ORIGIN_Y - 50;
            // initial line
            float line[4];
            line[0] = ORIGIN_X - 50;
            line[1] = ORIGIN_Y - 10;
            line[2] = ORIGIN_X;
            line[3] = ORIGIN_Y - 10;

            CV::rect(rect[0], rect[1], rect[2], rect[3]);
            CV::line(line[0], line[1], line[2], line[3]);


            // rotation and scaling matrix

            // first we find out the angle of the ramp
            // we formulate the vector that represents the ramp
            // then we apply arc tangent to find the angle
            float rad = atan2(ramp[3] - ramp[1], ramp[2] - ramp[0]);
            // then we set scaling factor (1/4)
            float scaling_factor = 0.25;
            // now we set up the matrix

            // scaling matrix
            float scaling_matrix[2][2] = {
                {scaling_factor, 0},
                {0, scaling_factor}
            };

            // rotation matrix
            float rotation_matrix[2][2] = {
                {cos(rad), -sin(rad)},
                {sin(rad), cos(rad)}
            };


        }
};

P1_2022 p1_2022 = P1_2022();

void render() {
    //curvas_besier();
    // P1 2022
    //p1_2022.questao_3();
    p1_2022.questao_4();
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


   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}
