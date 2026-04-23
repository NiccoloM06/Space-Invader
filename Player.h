#pragma once

using namespace std;

class Player
{
	bool dead;
	bool dead_animation_over;
	bool shield_animation_over;

	unsigned char current_power;
	unsigned char reload_timer;

	unsigned short power_timer;
	unsigned short x;
	unsigned short y;

	 vector<Bullet> bullets;

	//sf::Sprite bullet_sprite;
	//sf::Sprite sprite;

	sf::Texture bullet_texture;
	sf::Texture texture;
	std::optional<sf::Sprite> bullet_sprite;
	std::optional<sf::Sprite> sprite;

	Animation explosion;
public:
	Player();

	bool get_dead() const;
	bool get_dead_animation_over() const;

	unsigned short get_y() const;

	void die();
	void draw(sf::RenderWindow& i_window);
	void reset();
	void update( mt19937_64& i_random_engine,  vector<Bullet>& i_enemy_bullets,  vector<Enemy>& i_enemies, Ufo& i_ufo, unsigned short& i_score);

	sf::IntRect get_hitbox() const;
};
