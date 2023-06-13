#include "manager.h"

#define ENEMY_SPAWN_DELAY_FACTOR 5



GameManager::GameManager(){}

GameManager::GameManager(int screenHeight, int screenWidth) {
    map =  Map(50, 10, screenHeight, screenWidth);
    player = Starship(250, 5, screenWidth/2, screenHeight*0.8, 20);
    score = 0;
    // test enemy
    Enemy enemy(3, 100, 100, -100, 30);
    enemies.push_back(enemy);
    
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->enemy_spawn_delay = 0;

    animator.stars_init(screenWidth, screenHeight);
}


void GameManager::render(int fps, float mouseX, float mouseY) {
    if (map.render(float(player.get_velocity()), float(fps), player.polygon_x, player.polygon_y)) {
        // send player to the midle of the screen
        player.position = Vector2(screenWidth/2, screenHeight*0.8);
        // reduce player hp
        player.takeDamage(1);
    }

    animator.render(fps, screenHeight);

    player.render(fps, mouseX, mouseY);
    
    // render enemies
    for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        it->render(fps, screenWidth, player.position);
    }

    checkBullets();
    spawnEnemy(fps);
    drawScore();
    updateScore(fps);
}

// to be changed when progression is implemented
void GameManager::updateScore(float fps) {
    score += 1;
}

void GameManager::drawScore() {
    char str[100];
    sprintf(str, "Score: %d", int(score));
    CV::text(screenWidth - 150, 30, str);
}

void GameManager::handleKeyboard(int key, int state) {
    player.handleKeyboard(key, state);
}

void GameManager::handleMouse(int button, int state) {
    player.handleMouse(button, state);
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
                score += 100;
                continue;
            }
            // check if bullet hit an enemy
            if (player.isHit(bullet.position, bullet.radius) == true) {
                // remove bullet from list
                it2 = enemy.gun.bullets.erase(it2);
                player.takeDamage(1);
                break;
            }
        }
    }
}

void GameManager::spawnEnemy(int fps) {
    if (enemy_spawn_delay <= 0) {
        if (score < 10000) {
            // spawn enemy
            Enemy enemy(3, 100, 100 + rand() % (screenWidth - 100) , -100, 30);
            enemy.colorR = 1;
            enemy.colorG = 0.4;
            enemy.colorB = 0.4;
            enemies.push_back(enemy);
            // reset delay
            enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps * 2;
        }
        else if (score < 20000) {
            // spawn enemy
            Enemy enemy(3, 100, 100 + rand() % (screenWidth - 100) , -100, 30);
            enemy.colorR = 1;
            enemy.colorG = 0.5;
            enemy.colorB = 0.8;
            enemy.gun.current_bullet_speed_factor = 350;
            enemies.push_back(enemy);

            // reset delay
            enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps;
        }
        else if (score < 50000) {
            // spawn enemy
            Enemy enemy(3, 100, 100 + rand() % (screenWidth - 100) , -100, 30);
            enemy.colorR = 1;
            enemy.colorG = 0;
            enemy.colorB = 1;
            enemy.gun.current_bullet_speed_factor = 450;
            enemies.push_back(enemy);

            // reset delay
            enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps / 2.0;
        } else {
            // spawn enemy
            Enemy enemy(3, 100, 100 + rand() % (screenWidth - 100) , -100, 30);
            enemy.colorR = 1;
            enemy.colorG = 0;
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