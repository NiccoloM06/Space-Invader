#pragma once

using namespace std;

class Enemy
{
	 char direction;
    //-1 - sinistra
    //0 - sotto
    //1 - destra

	unsigned char health;
	unsigned char hit_timer;
	unsigned char type;

	unsigned short x;
	unsigned short y;

     vector<Enemy> enemies;

public:
	Enemy(unsigned char i_type, unsigned short i_x, unsigned short i_y);

	unsigned char get_health() const;
	unsigned char get_hit_timer() const;
	unsigned char get_type() const;
	char get_direction() const;
	void set_direction();

	unsigned short get_x() const;
	unsigned short get_y() const;
	void set_y(unsigned short i_y);

	void hit();
	//void move( vector<Enemy>& all_enemies);
	void move();
	void shoot( vector<Bullet>& i_enemy_bullets);
	void update();

	sf::IntRect get_hitbox() const;

     vector<Enemy>& get_enemies();
};
