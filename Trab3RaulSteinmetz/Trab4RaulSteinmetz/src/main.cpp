/*

Trabalho 4 - Raul Steinmetz

Requisitos cumpridos:

- Básicos (todos)
	- Modelagem matemática do motor e projeção em 3d
	- Permite exibir ou esconder peças em específico
	- Visualização ortográfica (2D) e sobre perspectiva (3D)
	- Visualização por vários ângulos (rotação livre no eixo x, y e z)
- Avançados
	- Ajuste do ângulo entre os dois pistões, quantos graus quiser


Como usar:

- A interação com o programa é bem simples, possuí interface com botões
- Clique nos botões para mudar perspectiva, rotacionar o objeto, mudar o ângulo entre os pistões, etc.
- Tudo que é possível fazer é na interface, não tem nenhuma feature dependente de comandos.

*/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "frames.h"
#include "engine2d.h"
#include "engine3d.h"
#include "interface.h"

#define BIDIMENTIONAL 0
#define TRIDIMENTIONAL 1


// fps control
int fps = 0;
Frames frames;
// state of the application
int state = TRIDIMENTIONAL;
int screenWidth = 800, screenHeight = 700;
int mouseX, mouseY;
// perspective
float d = 600.0;

int render_mode = DRAW_PERSPECTIVE;

// 2d engine
TwoPistonEngine2D engine(Vector2(0, 0), 50, 0, true, 15);
// 3d engine
Engine3D engine3d;

// buttons of the interface
Button perspective_plus = Button(5, 5, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "PERSPECTIVE +");
Button perpective_minus = Button(5, 45, 150, 35, 0.5, 0.5, 0.5, BIDIMENTIONAL, "PERSPECTIVE -");
Button state_3d = Button(5, 85, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "3D");
Button state_2d = Button(5, 125, 150, 35, 0.5, 0.5, 0.5, BIDIMENTIONAL, "2D");
Button angle_x_plus = Button(5, 165, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "ANGLE X+");
Button angle_x_minus = Button(5, 205, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "ANGLE X-");
Button angle_y_plus = Button(5, 245, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "ANGLE Y+");
Button angle_y_minus = Button(5, 285, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "ANGLE Y-");
Button angle_z_plus = Button(5, 325, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "ANGLE Z+");
Button angle_z_minus = Button(5, 365, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "ANGLE Z-");
Button rpm_plus = Button(5, 405, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "RPM +");
Button rpm_minus = Button(5, 445, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "RPM -");
Button piston_angle_plus = Button(5, 485, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "P ANGLE +");
Button piston_angle_minus = Button(5, 525, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "P ANGLE -");
Button draw_crank = Button(5, 565, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "DRAW CRANK");
Button draw_right_piston = Button(5, 605, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "DRAW PISTON");
Button draw_left_piston = Button(5, 645, 150, 35, 0.5, 0.5, 0.5, TRIDIMENTIONAL, "DRAW PISTON");


void _init() {
   engine3d = Engine3D(4);
   engine3d.x_rotation = 0;
   engine3d.y_rotation = 0;
   engine3d.z_rotation = 0;
}

double angle = 0;
float pos_x = 0;
float pos_y = 0;

void render()
{
   CV::translate(500, 400);
   fps = frames.getFrames();

   if (state == BIDIMENTIONAL) {
      engine.draw();
      engine.update(fps);
   }
   else {
      engine3d.render(fps, d, render_mode);
   }


   // interface
   CV::translate(0, 0);
   perspective_plus.render(mouseX, mouseY);
   perpective_minus.render(mouseX, mouseY);
   state_3d.render(mouseX, mouseY);
   state_2d.render(mouseX, mouseY);
   angle_x_plus.render(mouseX, mouseY);
   angle_x_minus.render(mouseX, mouseY);
   angle_y_plus.render(mouseX, mouseY);
   angle_y_minus.render(mouseX, mouseY);
   angle_z_plus.render(mouseX, mouseY);
   angle_z_minus.render(mouseX, mouseY);
   rpm_plus.render(mouseX, mouseY);
   rpm_minus.render(mouseX, mouseY);
   piston_angle_plus.render(mouseX, mouseY);
   piston_angle_minus.render(mouseX, mouseY);
   draw_crank.render(mouseX, mouseY);
   draw_right_piston.render(mouseX, mouseY);
   draw_left_piston.render(mouseX, mouseY);
}

void handleClick(float mouseX, float mouseY) {
   if (perspective_plus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      d += 20;
   }
   else if (perpective_minus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      d -= 20;
   }
   else if (state_3d.check_click(mouseX, mouseY) == CLICK_TRUE) {
      state = TRIDIMENTIONAL;
   }
   else if (state_2d.check_click(mouseX, mouseY) == CLICK_TRUE) {
      state = BIDIMENTIONAL;
   }
   else if (angle_x_plus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.x_rotation += 0.1;
   }
   else if (angle_x_minus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.x_rotation -= 0.1;
   }
   else if (angle_y_plus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.y_rotation += 0.1;
   }
   else if (angle_y_minus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.y_rotation -= 0.1;
   }
   else if (angle_z_plus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.z_rotation += 0.1;
   }
   else if (angle_z_minus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.z_rotation -= 0.1;
   }
   else if (rpm_plus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.crank.rpm += 10;
      engine.rpm += 10;
   }
   else if (rpm_minus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.crank.rpm -= 10;
      engine.rpm -= 10;
   }
   else if (piston_angle_plus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.left_piston.rad -= 0.1;
      engine3d.right_piston.rad += 0.1;
   }
   else if (piston_angle_minus.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.left_piston.rad += 0.1;
      engine3d.right_piston.rad -= 0.1;
   }
   else if (draw_crank.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.draw_crank = !engine3d.draw_crank;
   }
   else if (draw_right_piston.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.draw_right_piston = !engine3d.draw_right_piston;
   }
   else if (draw_left_piston.check_click(mouseX, mouseY) == CLICK_TRUE) {
      engine3d.draw_left_piston = !engine3d.draw_left_piston;
   }

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
   if (button == 0 && state == 0) {
      handleClick(x, y);
   }

}

int main(void)
{
   _init();
   CV::init(&screenWidth, &screenHeight, "V TWIN");
   CV::run();
}
