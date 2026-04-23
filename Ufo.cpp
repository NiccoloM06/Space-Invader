#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Constants.h"
#include "Ufo.h"
using namespace std;

Ufo::Ufo( mt19937_64& i_random_engine) : 
	y(BASE_SIZE),
	timer_distribution(UFO_TIMER_MIN, UFO_TIMER_MAX),
	animation(UFO_ANIMATION_SPEED, 2 * BASE_SIZE, IMAGES_PATH+"Ufo.png"),
	explosion(EXPLOSION_ANIMATION_SPEED, 2 * BASE_SIZE, IMAGES_PATH+"ExplosionBig.png")
{
	reset(1, i_random_engine);
}

bool Ufo::check_bullet_collision( mt19937_64& i_random_engine, const sf::IntRect& i_bullet_hitbox, unsigned short& i_score){
	if (0 == dead)
	{
		if (get_hitbox().findIntersection(i_bullet_hitbox))
		{
			dead = 1;

			explosion_x = x;

            i_score += 50;

			return 1;
		}
	}

	return 0;
}

void Ufo::draw(sf::RenderWindow& i_window){
	if (0 == dead)
	{
		animation.draw(x, y, i_window);
	}

	if (0 == dead_animation_over)
	{
		explosion.draw(explosion_x, y - 0.5f * BASE_SIZE, i_window, sf::Color(255, 36, 0));
	}
}

void Ufo::reset(bool i_dead,  mt19937_64& i_random_engine)
{
	dead = i_dead;
	dead_animation_over = 0;

	explosion_x = SCREEN_WIDTH;
	x = SCREEN_WIDTH;

	timer = timer_distribution(i_random_engine);

	animation.reset();
	explosion.reset();
}

void Ufo::update( mt19937_64& i_random_engine){
	if (0 == dead)
	{
		x -= UFO_MOVE_SPEED;

		if (x <= -2 * BASE_SIZE)
		{
			dead = 1;
		}

		animation.update();
	}
	else{
		if (0 == dead_animation_over)
		{
			dead_animation_over = explosion.update();
		}

		if (0 == timer)
		{
			reset(0, i_random_engine);
		}
		else
		{
			timer--;
		}
	}
}

sf::IntRect Ufo::get_hitbox() const
{
	return sf::IntRect({x, y}, {2 * BASE_SIZE, BASE_SIZE});
}
