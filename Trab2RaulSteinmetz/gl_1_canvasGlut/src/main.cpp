#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "starship.h"
#include "frames.h"
#include "environment.h"
#include "enemy.h"

// fps control
int fps = 0;
Frames frames;


int screenWidth = 800, screenHeight = 600;
int mouseX, mouseY;

Map map(50, 10, screenHeight, screenWidth);
Starship player(250, 5, screenWidth/2, screenHeight*0.8, 20);
CubicBezierCurve a(100, Vector2(200.0, 200.0), Vector2(250.0, 250.0), Vector2(300.0, 150.0), Vector2(350.0, 350.0));

// test enemy
Enemy enemy(100, 100, 100, 100, 30);


void setup() {

}


void render()
{
    fps = frames.getFrames();
    if (map.render(float(player.get_velocity()), float(fps), player.polygon_x, player.polygon_y)) {
        // send player to the midle of the screen
        player.position = Vector2(screenWidth/2, screenHeight*0.8);
        // reduce player hp
        player.takeDamage(1);
    }
    player.render(fps, mouseX, mouseY);
    enemy.render(fps);
}


void keyboard(int key)
{
    // printf("Pressed: %d\n", key);
    player.handleKeyboard(key, 0);
}


void keyboardUp(int key)
{
    player.handleKeyboard(key, 1);
}


void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x;
   mouseY = y;

   // 0 0 click
   // 0 1 solta

   //printf("button - %d, state - %d\n", button, state);
   player.handleMouse(button, state);
}

int main(void)
{
   setup();
   CV::init(&screenWidth, &screenHeight, "Singularity");
   CV::run();
}
