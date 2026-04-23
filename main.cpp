#include <array>
#include <chrono>
#include <random>
#include <bits/this_thread_sleep.h>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "DrawText.h"
#include "Constants.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Game.h"
#include "Ufo.h"
#include "Player.h"

int main() {
/*    bool game_over = 0;
    bool next_level = 0;
    unsigned short level = 0;
    unsigned short score = 0;
    unsigned short next_level_timer = NEXT_LEVEL_TRANSITION;

    std::chrono::microseconds lag(0); //Questo tipo rappresenta un intervallo di tempo misurato in microsecondi.

    std::chrono::steady_clock::time_point previous_time; //rappresentare un istante temporale stabile e monotono

    std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    //sf::Event event;

    sf::RenderWindow window(sf::VideoMode({SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT}),
                            "Space Invaders");
    window.setView(sf::View(sf::FloatRect({0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT})));

    //sf::Sprite background_sprite;

    sf::Texture background_texture;
    background_texture.loadFromFile("Background.png");

    sf::Texture font_texture;
    font_texture.loadFromFile("Font.png");

  //  sf::Texture powerup_bar_texture;
   // powerup_bar_texture.loadFromFile("PowerupBar.png");

    EnemyManager enemy_manager;

    Player player;

    Ufo ufo(random_engine);

    sf::Sprite background_sprite(background_texture);
    //background_sprite.setTexture(background_texture);

    previous_time = std::chrono::steady_clock::now();

    while (window.isOpen()) {
        std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now() - previous_time);

        lag += delta_time;

        previous_time += delta_time;


        while (FRAME_DURATION <= lag) {
            lag -= FRAME_DURATION;

            while (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
            }

            if (player.get_dead_animation_over()) {
                game_over = 1;
            }

            if (enemy_manager.reached_player(player.get_y())) {
                game_over = 1;
                player.die();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
                window.close();
            }

            if (!game_over && level != TOTAL_LEVELS) {
                if (0 == enemy_manager.get_enemies().size()) {
                    if (0 == next_level_timer) {
                        next_level = 0;

                        level++;
                        next_level_timer = NEXT_LEVEL_TRANSITION;

                        player.reset();

                        enemy_manager.reset(level);

                        ufo.reset(1, random_engine);
                    } else {
                        next_level = 1;

                        next_level_timer--;
                    }
                } else {
                    player.update(random_engine, enemy_manager.get_enemy_bullets(), enemy_manager.get_enemies(), ufo,
                                  score);


                    enemy_manager.update(random_engine, score);


                    ufo.update(random_engine);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                game_over = 0;

                level = 0;

                score = 0;

                player.reset();

                enemy_manager.reset(level);

                ufo.reset(1, random_engine);
            }


            if (FRAME_DURATION > lag) {
                window.clear();

                window.draw(background_sprite);

                if (0 == player.get_dead()) {
                    enemy_manager.draw(window);

                    ufo.draw(window);
                }

                player.draw(window);

                draw_text(0.25f * BASE_SIZE, 0.25f * BASE_SIZE, "Level: " + std::to_string(level + 1), window,
                          font_texture);
                draw_text(0.25f * BASE_SIZE, BASE_SIZE, "Score: " + std::to_string(score), window, font_texture);
                if (1 == game_over) {
                    draw_text(0.5f * (SCREEN_WIDTH - 5 * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE), "Game over!",
                              window, font_texture);
                } else if (level == TOTAL_LEVELS) {
                    window.clear();
                    draw_text(0.5f * (SCREEN_WIDTH - 5.5f * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE), "YOU WINX!",
                              window, font_texture);
                    draw_text(0.5f * (SCREEN_WIDTH - 15 * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE + 90),
                              " INVIO{ricomincia},C{chiude}", window, font_texture);
                } else if (1 == next_level && level != TOTAL_LEVELS - 1) {
                    draw_text(0.5f * (SCREEN_WIDTH - 5.5f * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE),
                              "Next level!", window, font_texture);
                }

                window.display();
            }
        }
    }

    // ottimizzazione del frame
    std::this_thread::sleep_until(previous_time + FRAME_DURATION);*/
    Game game;
    game.run();
    return 0;



}
