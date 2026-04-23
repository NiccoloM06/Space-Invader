#include <SFML/Graphics.hpp>

#include "DrawText.h"

using namespace std;

void draw_text(short i_x, short i_y, const  string& i_text, sf::RenderWindow& i_window, const sf::Texture& i_font_texture)
{
	short character_x = i_x;
	short character_y = i_y;

	unsigned char character_height = i_font_texture.getSize().y;
	unsigned char character_width = i_font_texture.getSize().x / 96;

	sf::Sprite character_sprite(i_font_texture);

	for ( string::const_iterator a = i_text.begin(); a != i_text.end(); a++) //il ciclo continua finche' 'a' non raggiunge la fine della stringa, "string::const_iterator a"  consente l'iterazione di una stringa senza modificaela (legge soltato il contenuto).
	{
		if ('\n' == *a)
		{
			character_x = i_x;
			character_y += character_height;

		}

		character_sprite.setPosition({static_cast<float>(character_x), static_cast<float>(character_y)});
		character_sprite.setTextureRect(sf::IntRect({character_width * (*a - 32), 0},{ character_width, character_height}));

		character_x += character_width; //sposta il carattere a destra

		i_window.draw(character_sprite); 
	}
}
