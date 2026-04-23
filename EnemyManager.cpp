#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>


#include "Animation.h"
#include "Constants.h"
#include "Enemy.h"
#include "EnemyManager.h"

#include <algorithm>

using namespace std;

EnemyManager::EnemyManager() : shoot_distribution(0, ENEMY_SHOOT_CHANCE) {
    reset(0);

    enemy_bullet_texture.loadFromFile(IMAGES_PATH+"EnemyBullet.png");

    enemy_bullet_sprite.emplace(enemy_bullet_texture);
    for (unsigned char a = 0; a < ENEMY_TYPES; a++)
        enemy_animations.push_back(Animation(1 + move_pause, BASE_SIZE,
                                             IMAGES_PATH+"Enemy" + to_string(static_cast<unsigned short>(a)) + ".png"));
}

bool EnemyManager::reached_player(unsigned short i_player_y) const {
    for (const Enemy &enemy: enemies) {
        if (enemy.get_y() > i_player_y - 0.5f * BASE_SIZE) {
            return 1;
        }
    }

    return 0;
}

void EnemyManager::draw(sf::RenderWindow &i_window) {
    for (const Bullet &bullet: enemy_bullets) {
        enemy_bullet_sprite->setPosition({ static_cast<float>(bullet.x), static_cast<float>(bullet.y)});
        i_window.draw(*enemy_bullet_sprite);
    }

    for (Enemy &enemy: enemies) {
        sf::Color enemy_color = sf::Color(255, 255, 255);

        if (0 == enemy.get_hit_timer()) {
            switch (enemy.get_type()) {
                case 0: {
                    enemy_color = sf::Color(0, 200, 100);

                    break;
                }
                case 1: {
                    enemy_color = sf::Color(255, 0, 255);

                    break;
                }
                case 2: {
                    enemy_color = sf::Color(0, 255, 0);
                }
            }
        }

        enemy_animations[enemy.get_type()].draw(enemy.get_x(), enemy.get_y(), i_window, enemy_color);
    }
}

void EnemyManager::reset(unsigned short i_level) {
    unsigned char enemy_x = 0;
    unsigned char enemy_y = 0;

    string level_sketch = "";

    move_pause = max<short>(ENEMY_MOVE_PAUSE_START_MIN, ENEMY_MOVE_PAUSE_START - ENEMY_MOVE_PAUSE_DECREASE * i_level);
    move_timer = move_pause;


    shoot_distribution = uniform_int_distribution<unsigned short>(
        0, max<short>(ENEMY_SHOOT_CHANCE_MIN, ENEMY_SHOOT_CHANCE - ENEMY_SHOOT_CHANCE_INCREASE * i_level));

    for (Animation &enemy_animation: enemy_animations) {
        enemy_animation.reset();
    }

    enemy_bullets.clear();

    enemies.clear();


    switch (i_level) {
        case 0: {
            level_sketch = "0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0";

            break;
        }
        case 1: {
            level_sketch = "0000000000000000\n0000000000000000\n0000000000000000\n0000000000000000";

            break;
        }
        case 2: {
            level_sketch = "1010101010101010\n0101010101010101\n1010101010101010\n0101010101010101";

            break;
        }
        case 3: {
            level_sketch = "1111111111111111\n1111111111111111\n1111111111111111\n1111111111111111";

            break;
        }
        case 4: {
            level_sketch = "2222222222222222\n1111111111111111\n1010101010101010\n0101010101010101";

            break;
        }
        case 5: {
            level_sketch = "0000000000000000\n2222222222222222\n1111111111111111\n1111111111111111";


            break;
        }
        case 6: {
            level_sketch = "2121212121212121\n1212121212121212\n2121212121212121\n1212121212121212";

            break;
        }
        case 7: {
            level_sketch = "2222222222222222\n2222222222222222\n2222222222222222\n2222222222222222";
        }
    }

    for (char sketch_character: level_sketch) {
        enemy_x++;

        switch (sketch_character) {
            case '\n': {
                enemy_x = 0;
                enemy_y++;

                break;
            }
            case '0': {
                enemies.push_back(Enemy(0, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y)));
                break;
            }
            case '1': {
                enemies.push_back(Enemy(1, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y)));
                break;
            }
            case '2': {
                enemies.push_back(Enemy(2, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y)));
                break;
            }
        }
    }
}

bool dead(const Enemy &i_enemy) {
    return 0 == i_enemy.get_health();
}

bool deadBullet(const Bullet &i_bullet) {
    return 1 == i_bullet.dead;
}

void dead2(const Enemy &i_enemy, unsigned short &i_score) {
    if (i_enemy.get_health() == 0 && i_enemy.get_type() == 0) {
        i_score += 10;
    } else if (i_enemy.get_health() == 0 && i_enemy.get_type() == 1) {
        i_score += 20;
    } else if (i_enemy.get_health() == 0 && i_enemy.get_type() == 2) {
        i_score += 30;
    }
}

void EnemyManager::update(mt19937_64 &i_random_engine, unsigned short &i_score) {
    vector<Enemy>::iterator dead_enemies_start;
    bool hit_border = false;

    if (0 == move_timer) {
        move_timer = move_pause;

        for (Enemy &enemy: enemies) {
            if ((1 == enemy.get_direction() && enemy.get_x() == SCREEN_WIDTH - 2 * BASE_SIZE) || (
                    -1 == enemy.get_direction() && enemy.get_x() == BASE_SIZE)) {
                hit_border = true;
            }
        }
        if (hit_border) {
            for (Enemy &enemy: enemies) {
                enemy.set_y(ENEMY_MOVE_SPEED);
                enemy.set_direction();
            }
        } else {
            for (Enemy &enemy: enemies) {
                enemy.move();
            }
        }

        for (Animation &enemy_animation: enemy_animations) {
            enemy_animation.change_current_frame();
        }
    } else {
        move_timer--;
    }

    for (Enemy &enemy: enemies) {
        enemy.update();

        if (0 == shoot_distribution(i_random_engine)) {
            enemy.shoot(enemy_bullets);
        }
    }
    for (Enemy &i_enemy: enemies) {
        dead2(i_enemy, i_score);
    }
    dead_enemies_start = remove_if(enemies.begin(), enemies.end(), dead);

    enemies.erase(dead_enemies_start, enemies.end());

    for (Bullet &enemy_bullet: enemy_bullets) {
        enemy_bullet.update();
    }


    enemy_bullets.erase(remove_if(enemy_bullets.begin(), enemy_bullets.end(), deadBullet), enemy_bullets.end());
}

vector<Bullet> &EnemyManager::get_enemy_bullets() {
    return enemy_bullets;
}

vector<Enemy> &EnemyManager::get_enemies() {
    return enemies;
}
