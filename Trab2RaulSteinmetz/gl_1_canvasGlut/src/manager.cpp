#include "manager.h"

#define ENEMY_SPAWN_DELAY_FACTOR 5



GameManager::GameManager(){}

GameManager::GameManager(int screenHeight, int screenWidth) {
    map =  Map(50, 10, screenHeight, screenWidth);
    player = Starship(250, 5, screenWidth/2, screenHeight*0.8, 20);
    // test enemy
    Enemy enemy(3, 100, 100, -100, 30);
    enemies.push_back(enemy);
    
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    this->enemy_spawn_delay = 0;

}


void GameManager::render(int fps, float mouseX, float mouseY) {
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
    
                // remove enemy if hp == 0
                if (enemy.hp == 0) {
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
                player.takeDamage(1);
                break;
            }
        }
    }
}

void GameManager::spawnEnemy(int fps) {
    if (enemy_spawn_delay <= 0) {
        printf("spawning enemy\n");
        // spawn enemy
        Enemy enemy(3, 100, 100 + rand() % (screenWidth - 100) , -100, 30);
        enemies.push_back(enemy);
        // reset delay
        enemy_spawn_delay = ENEMY_SPAWN_DELAY_FACTOR * fps;
    } else {
        enemy_spawn_delay--;
    }
}