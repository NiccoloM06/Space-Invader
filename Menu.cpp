#include "Menu.h"

#include <utility>
#include <SFML/Graphics/Texture.hpp>

#include "DrawText.h"
#include "GameState.h"

Menu::Menu(float x, float y, float s) : startX(x),
                                        startY(y),
                                        spacing(s) {
}

void Menu::addItem(const std::string &text, std::function<void()> action) {
    MenuItem item;
    item.text = text;
    item.action = std::move(action);
    items.push_back(item);
}

void Menu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.is<sf::Event::KeyPressed>()) {
        auto key = event.getIf<sf::Event::KeyPressed>()->code;
        if (key == sf::Keyboard::Key::Up) {
            selected = (selected - 1) % items.size();
        }
        else if (key == sf::Keyboard::Key::Down) {
            selected = (selected + 1) % items.size();
        }
        else if (key == sf::Keyboard::Key::Enter) {
            items[selected].action();
        }
    }
    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        for (auto& item : items) {
            if (item.bounds.contains(mouse)) {
                item.action();
            }
        }
    }
}

void Menu::update(const sf::RenderWindow& window) {
    auto mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (size_t i = 0; i < items.size(); i++) {
        items[i].hovered = items[i].bounds.contains(mouse);
        if (items[i].hovered) {
            selected = i;
        }
    }
}

void Menu::draw(sf::RenderWindow& window, const sf::Texture& font_texture) {
    for (size_t i = 0; i < items.size(); i++) {
        std::string text = (i == size_t(selected)) ? "> " + items[i].text : " " + items[i].text;
        float y = startY + i * spacing;

        unsigned char char_width = font_texture.getSize().x / 96;
        unsigned char char_height = font_texture.getSize().y;
        items[i].bounds = sf::FloatRect(
            {startX, y},
            {static_cast<float>(text.size()*char_width), static_cast<float>(char_height)}
            );
        draw_text(startX,y,text,window,font_texture);
    }
}
