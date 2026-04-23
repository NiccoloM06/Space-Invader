#pragma once
#include <functional>
#include <string>
#include <SFML/Graphics/Rect.hpp>


struct MenuItem {
    std::string text;
    std::function<void()> action;
    sf::FloatRect bounds;
    bool hovered = false;

};




