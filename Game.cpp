#include "Game.h"

#include <iostream>
#include <thread>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Constants.h"
#include "DrawText.h"

#include <tracy/Tracy.hpp>

Game::Game() : state(GameState::Menu),
               level(0),
               score(0),
               next_level_timer(NEXT_LEVEL_TRANSITION),
               lag(0),
               random_engine(std::chrono::system_clock::now().time_since_epoch().count()),
               window(sf::VideoMode({SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT}),
                      "Space Invaders"),
               ufo(random_engine),
               main_menu(60, 80, 20) {
    window.setView(sf::View(sf::FloatRect({0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT})));
    //vSync ma ho gia il controllo con sleep_unitl
    //window.setVerticalSyncEnabled(true);


    if (!background_texture.loadFromFile(IMAGES_PATH+"Background.png")) {
        std::cerr << "Errore caricamento Background.png\n";
    }

    if (!font_texture.loadFromFile(FONTS_PATH+"Font.png")) {
        std::cerr << "Errore caricamento Font.png\n";
    }
    background_sprite.emplace(background_texture);
    previous_time = std::chrono::steady_clock::now();

    main_menu.addItem("Start Game",[this]() {
        state = GameState::Playing;
    });
    main_menu.addItem("Exit",[this]() {
        window.close();
    });
}

void Game::processEvents() {
    ZoneScoped;
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (state == GameState::Menu) {
            main_menu.handleEvent(*event, window);
        }
        if (event->is<sf::Event::KeyPressed>()) {
            auto key = event->getIf<sf::Event::KeyPressed>()->code;
            if (key == sf::Keyboard::Key::Escape) {
                if (state == GameState::Menu) {
                    state = GameState::Playing;
                }
                else if (state == GameState::Playing) {
                    state = GameState::Menu;
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        window.close();
    }
}

void Game::update() {
    ZoneScoped;
    if (player.get_dead_animation_over()) {
        state = GameState::GameOver;
    }
    if (enemy_manager.reached_player(player.get_y())) {
        state = GameState::GameOver;
        player.die();
    }
    if (state != GameState::GameOver && level != TOTAL_LEVELS) {
        if (0 == enemy_manager.get_enemies().size()) {
            state = GameState::NextLevel;
        }
    }
    switch (state) {
        case GameState::Playing:
            player.update(random_engine, enemy_manager.get_enemy_bullets(), enemy_manager.get_enemies(), ufo, score);
            enemy_manager.update(random_engine, score);
            ufo.update(random_engine);

            if (enemy_manager.get_enemies().empty()) {
                state = GameState::NextLevel;
            }

            break;
        case GameState::GameOver:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                reset();
            }
            break;
        case GameState::NextLevel:
            if (next_level_timer == 0) {
                level++;

                if (level == TOTAL_LEVELS) {
                    state = GameState::Win;
                } else {
                    next_level_timer = NEXT_LEVEL_TRANSITION;

                    player.reset();
                    enemy_manager.reset(level);
                    ufo.reset(1, random_engine);

                    state = GameState::Playing;
                }
            } else {
                next_level_timer--;
            }

            break;
        case GameState::Win:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                reset();
            }
            break;
        case GameState::Menu:
            main_menu.update(window);
            break;
    }
}

void Game::render() {
    ZoneScoped;
    window.clear();

    // sfondo
    window.draw(*background_sprite);

    // entità (solo se vivo)
    if (player.get_dead() == 0) {
        enemy_manager.draw(window);
        ufo.draw(window);
    }

    // player sempre disegnato (anche animazione morte)
    player.draw(window);

    // UI base
    draw_text(10, 8,
              "Level: " + std::to_string(level + 1),
              window, font_texture);

    draw_text(10, 20,
              "Score: " + std::to_string(score),
              window, font_texture);

    // stati
    switch (state) {
        case GameState::GameOver: {
            draw_text(100, 100, "Game Over!", window, font_texture);
            draw_text(100, 140, "Press E to restart", window, font_texture);
            break;
        }
        case GameState::NextLevel: {
            draw_text(100, 100, "Next Level!", window, font_texture);
            break;
        }
        case GameState::Win: {
            window.clear(); // opzionale: schermo pulito
            draw_text(100, 100, "YOU WIN!", window, font_texture);
            draw_text(100, 140, "Press E to restart", window, font_texture);
            break;
        }
        case GameState::Menu: {
            main_menu.draw(window,font_texture);
            break;
        }
        default: {
            break;
        }
    }

    window.display();
}

void Game::reset() {
    ZoneScoped;
    state = GameState::Menu;
    level = 0;
    score = 0;

    player.reset();
    enemy_manager.reset(level);
    ufo.reset(1, random_engine);
}

void Game::run() {
    while (window.isOpen()) {
        auto current_time = std::chrono::steady_clock::now();

        std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(
            current_time - previous_time);
        previous_time = current_time;

        lag += delta_time;


        processEvents();

        while (FRAME_DURATION <= lag) {
            update();
            lag -= FRAME_DURATION;
        }
        render();
        std::this_thread::sleep_until(previous_time + FRAME_DURATION);

        FrameMark;
    }
}
