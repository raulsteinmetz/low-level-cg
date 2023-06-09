#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


#include "gl_canvas2d.h"



int screenWidth = 800, screenHeight = 800;
int mouseX, mouseY;


#define ORIGIN_X 200
#define ORIGIN_Y 200

#define AXIS_SIZE 300

// bezier
double calculatePointBezier(double t, double p0, double p1, double p2, double p3) {
    double a = pow((1 - t), 3) * p0;
    double b = 3 * pow((1 - t), 2) * t * p1;
    double c = 3 * (1 - t) * pow(t, 2) * p2;
    double d = pow(t, 3) * p3;
    return a + b + c + d;
}

//b-spline

double calculatePointBSpline(double t, double p0, double p1, double p2, double p3) {
    double a = 1.0/6.0 * (1 - t * t * t) * p0;
    double b = 1.0/6.0 * (3 * t * t * t - 6 * t * t + 4) * p1;
    double c = 1.0/6.0 * (-3 * t * t * t + 3 * t * t + 3 * t + 1) * p2;
    double d = 1.0/6.0 * t * t * t * p3;
    return a + b + c + d;

}

// PROVA 1 2022

#define DRAW_ORIGIN 200
#define MATRIX_SIZE 3

// Function to multiply two matrices
void multiplyMatrices(float matrix1[][MATRIX_SIZE], float matrix2[][MATRIX_SIZE], float result[][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            result[i][j] = 0; // Initialize result cell to 0

            // Perform matrix multiplication
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
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

        void questao_2() {
            // array with 8 points
            float points_x[8] = {0 + ORIGIN_X, 50 + ORIGIN_X, 100 + ORIGIN_X, 150 + ORIGIN_X,
                                 200 + ORIGIN_X, 300 + ORIGIN_X, 320 + ORIGIN_X, 400 + ORIGIN_X};

            float points_y[8] = {0 + ORIGIN_Y, 100 + ORIGIN_Y, -100 + ORIGIN_Y, -50 + ORIGIN_Y,
                                 200 + ORIGIN_Y, 300 + ORIGIN_Y, 40 + ORIGIN_Y, 50 + ORIGIN_Y};

            // drawing points
            for (int i = 0; i < 8; i++) {
                CV::color(0);
                CV::circle(points_x[i], points_y[i], 5, 10);
            }
            // drawing lines 
            for (int i = 0; i < 7; i++) {
                CV::color(0);
                CV::line(points_x[i], points_y[i], points_x[i + 1], points_y[i + 1]);
            }


            float min_x;
            float min_y;

            float max_x;
            float max_y;

            CV::color(0);
            for (int p = 0; p < 6; p ++) {
                for (float t = 0; t <= 1; t+= 0.001) {
                    float x = calculatePointBSpline(t, points_x[p], points_x[p + 1], points_x[p + 2], points_x[p + 3]);
                    float y = calculatePointBSpline(t, points_y[p], points_y[p + 1], points_y[p + 2], points_y[p + 3]);
                    CV::point(x, y);
                    if (t == 0 && p == 0) {
                        min_x = x;
                        min_y = y;
                        max_x = x;
                        max_y = y;
                    } else {
                        if (x < min_x) {
                            min_x = x;
                        }
                        if (y < min_y) {
                            min_y = y;
                        }
                        if (x > max_x) {
                            max_x = x;
                        }
                        if (y > max_y) {
                            max_y = y;
                        }
                    }
                }
            }
            CV::color(0);
            CV::rect(min_x, min_y, max_x, max_y);
            printf("min_x: %f, min_y: %f, max_x: %f, max_y: %f\n", min_x, min_y, max_x, max_y);

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

        double init_rad = 10 * PI;
        void questao_3_2() {
            CV::translate(200, 200);
            float rad = init_rad;
            float radius = 100;
            while (radius > 0 && rad >= (init_rad - 10 * PI)) {
                float x = radius * cos(rad);
                float y = radius * sin(rad);
                CV::color(0);
                CV::point(x, y);
                radius -= 0.1;
                rad -= 0.01;
            }
            init_rad -= 0.01;
            if (init_rad <= 0) {
                init_rad = 10 * PI;
            }

        }
      
        void questao_4() {
            float scaling_factor = 0.5;
            float rad = PI / 4;

            float lado = 10;

            // translation matrix - deixa na posicao 0 0
            float translation_matrix[3][3] = {
                {1, 0, lado},
                {0, 1, lado},
                {0, 0, 1}
            };

            // scaling matrix - diminiui lado
            float scaling_matrix[3][3] = {
                {scaling_factor, 0, 0},
                {0, scaling_factor, 0},
                {0, 0, scaling_factor}
            };

            // rotation matrix - rotaciona pelo angulo
            float rotation_matrix[3][3] = {
                {cos(rad), -sin(rad), 0},
                {sin(rad), cos(rad), 0},
                {0, 0, 0}
            };

            float tx = 100;

            // translada para o x do vetor
            float translation_matrix2[3][3] = {
                {1, 0, tx},
                {0, 1, 0},
                {0, 0, 1}
            };

            // final matrix  = translation2 * rotation * scaling * translation

        }
};

class P1_2020 {
    public:
        float init_angle;

        P1_2020(){
            init_angle = 0;
        }
        
        void questao_2() {
            CV::color(0);
            float radius = 80;
            float angle = init_angle;
            Vector2 last_point(-1, - 1);
            while (angle <= init_angle + 360) {
                float rad = angle * PI / 180;
                Vector2 p(radius * cos(rad) + DRAW_ORIGIN, radius * sin(rad) + DRAW_ORIGIN);
                if (last_point.x != -1 && last_point.y != -1) {
                    CV::line(last_point.x, last_point.y, p.x, p.y);
                }
                radius += 20;
                angle += 5;
                rad = angle * PI / 180;
                Vector2 p2(radius * cos(rad) + DRAW_ORIGIN, radius * sin(rad) + DRAW_ORIGIN);
                CV::line(p.x, p.y, p2.x, p2.y);
                angle += 10;
                rad = angle * PI / 180;
                Vector2 p3(radius * cos(rad) + DRAW_ORIGIN, radius * sin(rad) + DRAW_ORIGIN);
                CV::line(p2.x, p2.y, p3.x, p3.y);
                radius -= 20;
                angle += 5;
                rad = angle * PI / 180;
                Vector2 p4(radius * cos(rad) + DRAW_ORIGIN, radius * sin(rad) + DRAW_ORIGIN);
                CV::line(p3.x, p3.y, p4.x, p4.y);
                angle += 10;
                last_point = p4;
            }
            init_angle += 0.01;
            if (init_angle == 360) {
                init_angle = 0;
            }
        }

        void questao_3() {

            CV::translate(ORIGIN_X, ORIGIN_Y);

            // drawing y and x axes
            CV::color(0);
            CV::line(0, 0, AXIS_SIZE, 0);
            CV::line(0, 0, 0, AXIS_SIZE);

            // desenhando blending functions bezzier
            CV::color(3);
            for (float t = 0; t <= 1; t += 0.001) {
                CV::point(t * AXIS_SIZE, AXIS_SIZE * pow((1 - t), 3));
                CV::point(t * AXIS_SIZE, AXIS_SIZE * 3 * pow((1 - t), 2) * t);
                CV::point(t * AXIS_SIZE, AXIS_SIZE * 3 * (1 - t) * pow(t, 2));
                CV::point(t * AXIS_SIZE, AXIS_SIZE * pow(t, 3));
            }

            // desenhando blending functions b-spline
            CV::color(2);
            for (float t = 0; t <= 1; t += 0.001) {
                CV::point(t * AXIS_SIZE, AXIS_SIZE * pow((1 - t), 3) / 6.0);
                CV::point(t * AXIS_SIZE, AXIS_SIZE * (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6.0);
                CV::point(t * AXIS_SIZE, AXIS_SIZE * (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6.0);
                CV::point(t * AXIS_SIZE, AXIS_SIZE * pow(t, 3) / 6.0);
            }
        }

};

P1_2022 p1_2022 = P1_2022();
P1_2020 p1_2020 = P1_2020();


void render() {

    // P1 2022
    //p1_2022.questao_2();
    //p1_2022.questao_3();
    //p1_2022.questao_4();
    //p1_2022.questao_3_2();

    // P1 2020
    //p1_2020.questao_2();
    //p1_2020.questao_3();



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
