#ifndef MANAGER_H
#define MANAGER_H

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
#include "animator.h"
#include <list>


class GameManager {
    public:
        int screenWidth, screenHeight;
        float enemy_spawn_delay;
        float score;

        Starship player; // player
        std::list<Enemy> enemies; // enemies
        Map map; // map
        Animator animator; // animator

        GameManager();
        GameManager(int screenHeight, int screenWidth);
        void render(int fps, float mouseX, float mouseY);
        void handleKeyboard(int key, int state);
        void handleMouse(int button, int state);
        void checkBullets();
        void spawnEnemy(int fps);
        void drawScore();
        void updateScore(float fps);



};

#endif // MANAGER_H