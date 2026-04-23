#pragma once

using namespace std;

class Animation
{
	unsigned short animation_iterator;
	unsigned short animation_speed;
	unsigned short current_frame;
	unsigned short frame_width;
	unsigned short total_frames;

	//sf::Sprite sprite;

	sf::Texture texture;
	std::optional<sf::Sprite> sprite;
public:
	Animation(unsigned short i_animation_speed, unsigned short i_frame_width, const  string& i_texture_location);

	bool change_current_frame();
	bool update();

	void draw(short i_x, short i_y, sf::RenderWindow& i_window, const sf::Color& i_color = sf::Color(255, 255, 255));
	void reset();
};
