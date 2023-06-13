/*

    Made by Raul Steinmetz

    This file is responsable for managing all elements in the game:
        Player
        Enemies
        Map
        Score
        Input
        

*/

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
#include "ui.h"
#include <list>


class GameManager {
    public:
        int screenWidth, screenHeight;
        float enemy_spawn_delay;
        double score;
        int application_state; // 0 = menu, 1 = game, 2 = game over

        Starship player; // player
        std::list<Enemy> enemies; // enemies
        Map map; // map
        Animator animator; // animator
        UserInterface ui; // user interface

        GameManager();
        GameManager(int screenHeight, int screenWidth);
        void render(int fps, float mouseX, float mouseY); // controlls all game renders (player, enemy...)
        void handleKeyboard(int key, int state); // keyboard press handle
        void handleMouse(int button, int state, float mouseX, float mouseY); // mouse button press handle
        void checkBullets(); // check if any bullet hit any target
        void spawnEnemy(int fps); // spawns enemies in the game, controlled by a cetain delay
        void drawScore(); // draw player score
        void updateScore(float fps); // increment score based on time passed



};

#endif // MANAGER_H