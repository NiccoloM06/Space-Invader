#pragma once

using namespace std;

class EnemyManager
{
	unsigned short move_pause;
	unsigned short move_timer;

	 uniform_int_distribution<unsigned short> shoot_distribution;

	 vector<Animation> enemy_animations;

	 vector<Bullet> enemy_bullets;

	 vector<Enemy> enemies;
	//sf::Sprite enemy_bullet_sprite;
	sf::Texture enemy_bullet_texture;
	std::optional<sf::Sprite> enemy_bullet_sprite;


public:
	EnemyManager();


	bool reached_player(unsigned short i_player_y) const;

	void draw(sf::RenderWindow& i_window);
	void reset(unsigned short i_level);
	void update( mt19937_64& i_random_engine, unsigned short& i_score);

	 vector<Bullet>& get_enemy_bullets();

	 vector<Enemy>& get_enemies();
};
