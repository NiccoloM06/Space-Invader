#pragma once

using namespace std;

#include <cmath>

// Paths
inline const std::string ASSETS_PATH   = "assets/";
inline const std::string IMAGES_PATH   = ASSETS_PATH + "images/";
inline const std::string FONTS_PATH    = ASSETS_PATH + "fonts/";
inline const std::string SOUNDS_PATH   = ASSETS_PATH + "sounds/";

constexpr unsigned short BASE_SIZE = 16;
constexpr unsigned short ENEMY_BULLET_SPEED = 2; //a 2 per far diventare il nemico bianco prima della morte
constexpr unsigned short ENEMY_HIT_TIMER_DURATION = 2;
constexpr unsigned short ENEMY_MOVE_PAUSE_DECREASE = 1;
constexpr unsigned short ENEMY_MOVE_PAUSE_MIN = 3;
constexpr unsigned short ENEMY_MOVE_PAUSE_START = 63;
constexpr unsigned short ENEMY_MOVE_PAUSE_START_MIN = 47;
constexpr unsigned short ENEMY_MOVE_SPEED = 8;
constexpr unsigned short ENEMY_TYPES = 3;
constexpr unsigned short EXPLOSION_ANIMATION_SPEED = 2;
constexpr unsigned short FAST_RELOAD_DURATION = 7;
constexpr unsigned short NEXT_LEVEL_TRANSITION = 64;
constexpr unsigned short PLAYER_BULLET_SPEED = 4;
constexpr unsigned short PLAYER_MOVE_SPEED = 3;
constexpr unsigned short RELOAD_DURATION = 23;
constexpr unsigned short SCREEN_RESIZE = 4;
constexpr unsigned short TOTAL_LEVELS = 8;
constexpr unsigned short UFO_ANIMATION_SPEED = 8;
constexpr unsigned short UFO_MOVE_SPEED = 2;
constexpr unsigned short ENEMY_SHOOT_CHANCE = 4096;
constexpr unsigned short ENEMY_SHOOT_CHANCE_INCREASE = 64;
constexpr unsigned short ENEMY_SHOOT_CHANCE_MIN = 1024;
constexpr unsigned short SCREEN_HEIGHT = 200;
constexpr unsigned short SCREEN_WIDTH = 340;
constexpr unsigned short UFO_TIMER_MAX = 1024;
constexpr unsigned short UFO_TIMER_MIN = 768;



constexpr  chrono::microseconds FRAME_DURATION(16667);

struct Bullet
{
	bool dead;

	float real_x;
	float real_y;
	float step_x;
	float step_y;

	short x;
	short y;
	

	Bullet(float i_step_x, float i_step_y, short i_x, short i_y) :
		dead(0),
		real_x(i_x),
		real_y(i_y),
		step_x(i_step_x),
		step_y(i_step_y),
		x(i_x),
		y(i_y)
	{
	}

	void update()
	{
        if (0 == dead)
        {
            real_x += step_x;
            real_y += step_y;

            x = real_x;
            y = real_y;

            if (real_x <= -BASE_SIZE || real_y <= -BASE_SIZE || SCREEN_HEIGHT <= real_y || SCREEN_WIDTH <= real_x)
            {
                dead = 1;
            }
        }
    }

    sf::IntRect get_hitbox() const
    {
        return sf::IntRect({static_cast<int>(x + 0.25f * BASE_SIZE), static_cast<int>(y + 0.25f * BASE_SIZE)},{ static_cast<int>(0.5f * BASE_SIZE), static_cast<int>(0.5f * BASE_SIZE)});
    }
};
