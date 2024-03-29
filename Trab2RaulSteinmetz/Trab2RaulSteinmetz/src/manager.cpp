/*

    Made by Raul Steinmetz

    This file is responsable for managing all elements in the game:
        Player
        Enemies
        Map
        Score
        Input
        

*/


#include "manager.h"
#include <cmath>

#define ENEMY_SPAWN_DELAY_FACTOR 5



GameManager::GameManager(){}

GameManager::GameManager(int screenHeight, int screenWidth) {
    map =  Map(50, 10, screenHeight, screenWidth);
    player = Starship(250, 5, screenWidth/2, screenHeight*0.8, 20);
    score = 1;
    ui = UserInterface(screenWidth, screenHeight);

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->enemy_spawn_delay = 0;
    this->application_state = 0;

    animator.stars_init(screenWidth, screenHeight);
}

bool pointInTriangle(float x, float y, float triangleX[3], float triangleY[3]) {
    // check if point is inside triangle
    float alpha = ((triangleY[1] - triangleY[2])*(x - triangleX[2]) + (triangleX[2] - triangleX[1])*(y - triangleY[2])) / ((triangleY[1] - triangleY[2])*(triangleX[0] - triangleX[2]) + (triangleX[2] - triangleX[1])*(triangleY[0] - triangleY[2]));
    float beta = ((triangleY[2] - triangleY[0])*(x - triangleX[2]) + (triangleX[0] - triangleX[2])*(y - triangleY[2])) / ((triangleY[1] - triangleY[2])*(triangleX[0] - triangleX[2]) + (triangleX[2] - triangleX[1])*(triangleY[0] - triangleY[2]));
    float gamma = 1.0f - alpha - beta;

    return (alpha > 0 && beta > 0 && gamma > 0);
}


bool checkColisionBetweenTriangles(float triangle1X[3], float triangle1Y[3], float triangle2X[3], float triangle2Y[3]) {
    // check if any of the points of triangle 1 is inside triangle 2
    for (int i = 0; i < 3; i++) {
        if (pointInTriangle(triangle1X[i], triangle1Y[i], triangle2X, triangle2Y)) {
            return true;
        }
    }
    // check if any of the points of triangle 2 is inside triangle 1
    for (int i = 0; i < 3; i++) {
        if (pointInTriangle(triangle2X[i], triangle2Y[i], triangle1X, triangle1Y)) {
            return true;
        }
    }
    
}




void GameManager::checkPlayerEnemyColision() {
    // iterate throught enemies
    for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        // check if enemy hit player
        if (checkColisionBetweenTriangles(it->polygon_x, it->polygon_y, player.polygon_x, player.polygon_y)) {
            // send player to the midle of the screen
            player.hp = 0;
        }
    }
}


void GameManager::render(int fps, float mouseX, float mouseY) {
    if (application_state == 0) { // menu
        ui.initial_menu(mouseX, mouseY);
    }
    else if (application_state == 1) { // game
        if (map.render(float(player.get_velocity()), float(fps), player.polygon_x, player.polygon_y)) {
            // send player to the midle of the screen
            player.position = Vector2(screenWidth/2, screenHeight*0.8);
            // reduce player hp
            player.takeDamage(1);
        }

        player.render(fps, mouseX, mouseY);

        // render enemies
        for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
            it->render(fps, screenWidth, player.position);
        }

        checkBullets();
        spawnEnemy(fps);
        drawScore();
        updateScore(fps);
        animator.render(fps, screenHeight);
        checkPlayerEnemyColision();

        if (player.hp <= 0) {
            application_state = 2;
            
        }
    }
    else if (application_state == 2) {
        // print score
        ui.death_menu(mouseX, mouseY);
        CV::color(1, 1, 1);
        char str[100];
        sprintf(str, "Score: %d", int(score));
        CV::text(screenWidth/2 - 50, 100, str);
    }

}

// to be changed when progression is implemented
void GameManager::updateScore(float fps) {
    if (score < 10000) {
        score += 100.0 / fps;
    }
    else if (score < 20000) {
        score += 200.0 / fps;
    }
    else if (score < 50000) {
        score += 300.0 / fps;
    }
    else {
        score += 500.0 / fps; 
    }
}


void GameManager::drawScore() {
    char str[100];
    sprintf(str, "Score: %d", int(score));
    CV::text(screenWidth - 150, 30, str);
}

void GameManager::handleKeyboard(int key, int state) {
    player.handleKeyboard(key, state);
}

void GameManager::handleMouse(int button, int state, float mouseX, float mouseY) {
    player.handleMouse(button, state);
    if (button == 0 && state == 0) {
        // iterate buttons on ui
        if (application_state == 0) {
            for (std::list<Button>::iterator it = ui.menu_buttons.begin(); it != ui.menu_buttons.end(); ++it) {
                Button& button = *it;
                if (button.check(mouseX, mouseY)) {
                    if (button.id == 0) { // play
                        application_state = 1;
                    }
                    else if (button.id == 1) { // quit
                        exit(0);
                    }
                }
            }
        }
        else if (application_state == 2) {
            for (std::list<Button>::iterator it = ui.death_buttons.begin(); it != ui.death_buttons.end(); ++it) {
                Button& button = *it;
                if (button.check(mouseX, mouseY)) {
                    if (button.id == 0) { // play
                        application_state = 1;
                        score = 1;
                        player.hp = 5;
                        enemies.clear();
                        player.gun.bullets.clear();
                    }
                    else if (button.id == 1) { // quit
                        exit(0);
                    }
                }
            }
        }
    }
}

void GameManager::checkBullets() {
    // iterate thorought player's gun bullets
    for (std::list<Bullet>::iterator it = player.gun.bullets.begin(); it != player.gun.bullets.end(); ++it) {
        Bullet& bullet = *it;
        // check if bullet is out of bounds
        if (bullet.position.x < 0 || bullet.position.x > screenWidth || bullet.position.y < 0 || bullet.position.y > screenHeight) {
            // remove bullet from list
            it = player.gun.bullets.erase(it);
            continue;
        }
        // check if bullet hit an enemy
        for (std::list<Enemy>::iterator it2 = enemies.begin(); it2 != enemies.end(); ++it2) {
            Enemy& enemy = *it2;
            if (enemy.isHit(bullet.position, bullet.radius) == true) {
                // remove bullet from list
                it = player.gun.bullets.erase(it);

                enemy.takeDamage(1);

                animator.damage_init(enemy.position.x, enemy.position.y);

                // remove enemy if hp == 0
                if (enemy.hp == 0) {
                    score += 3000;
                    animator.enemy_explosion_init(enemy.position.x, enemy.position.y);
                    it2 = enemies.erase(it2);

                    continue;
                }

                break;
            }
        }
    }


    // iterate thorought enemies' gun bullets
    for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        Enemy& enemy = *it;
        for (std::list<Bullet>::iterator it2 = enemy.gun.bullets.begin(); it2 != enemy.gun.bullets.end(); ++it2) {
            Bullet& bullet = *it2;
            // check if bullet is out of bounds
            if (bullet.position.x < 0 || bullet.position.x > screenWidth || bullet.position.y < 0 || bullet.position.y > screenHeight) {
                // remove bullet from list
                it2 = enemy.gun.bullets.erase(it2);
                continue;
            }
            // check if bullet hit an enemy
            if (player.isHit(bullet.position, bullet.radius) == true) {
                // remove bullet from list
                it2 = enemy.gun.bullets.erase(it2);
                player.takeDamage(enemy.power);
                animator.damage_init(player.position.x, player.position.y);
                break;
            }
        }
    }
}

void GameManager::spawnEnemy(int fps) {
    if (enemy_spawn_delay <= 0) {
        if (score < 10000) {
            // spawn enemy
            Enemy enemy(3, 1, 100 + rand() % (screenWidth - 100) , -100, 30, Vector2(200, 50));
            enemy.colorR = 1;
            enemy.colorG = 0.4;
            enemy.colorB = 0.4;
            enemies.push_back(enemy);
            // reset delay
            enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps;
        }
        else if (score < 20000) {
            // spawn enemy
            Enemy enemy(3, 1, 100 + rand() % (screenWidth - 100) , -100, 30, Vector2(300, 75));
            enemy.colorR = 1;
            enemy.colorG = 0.5;
            enemy.colorB = 0.8;
            enemy.gun.current_bullet_speed_factor = 350;
            enemies.push_back(enemy);

            // reset delay
            enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps / 2.0;
        }
        else if (score < 50000) {
            // spawn enemy
            Enemy enemy(3, 1, 100 + rand() % (screenWidth - 100) , -100, 30, Vector2(350, 100));
            enemy.colorR = 1;
            enemy.colorG = 0;
            enemy.colorB = 1;
            enemy.gun.current_bullet_speed_factor = 450;
            enemies.push_back(enemy);

            // reset delay
            enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps / 3.0;
        } else {
            // spawn enemy
            Enemy enemy(5, 1, 100 + rand() % (screenWidth - 100) , -100, 30, Vector2(400, 150));
            enemy.colorR = 1;
            enemy.colorG = 1;
            enemy.colorB = 0;
            enemy.gun.current_bullet_speed_factor = 550;
            enemies.push_back(enemy);

            // reset delay
            enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps / 3.0;
        }
    } else {
        enemy_spawn_delay--;
    }
}
