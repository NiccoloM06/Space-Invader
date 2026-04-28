#pragma once

#include <chrono>
#include <random>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


#include "Animation.h"
#include "DrawText.h"
#include "Constants.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Ufo.h"
#include "Player.h"
#include "GameState.h"
#include "Menu.h"
#include "cmake-build-debug/GameMode.h"

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update();
    void render();
    void reset();

    Menu main_menu;
    GameState state;
    GameMode mode;
    EnemyManager enemy_manager;
    //Player player;
    std::vector<Player> players;
    Ufo ufo;

    unsigned short level;
    unsigned short score;
    unsigned short next_level_timer;

    unsigned short fps;
    unsigned short fps_counter;
    std::chrono::steady_clock::time_point fps_last_time;

    std::chrono::microseconds lag;
    std::chrono::steady_clock::time_point previous_time;

    std::mt19937_64 random_engine;

    sf::RenderWindow window;

    sf::Texture background_texture;
    sf::Texture font_texture;
    std::optional<sf::Sprite> background_sprite ;

};




