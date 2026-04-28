#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "MenuItem.h"

class Menu {
    std::vector<MenuItem> items;
    int selected = 0;
    float startX,startY, spacing;

public:
    Menu(float x, float y, float s);

    void addItem(const std::string& text, std::function<void()> action);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, const sf::Texture& font_texture);


};

