#include "mapkey.hpp"
#include "core.hpp"
#include "Arcade.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

static const std::map<arcade::Key, sf::Keyboard::Key> keyMap = {
    { sf::Keyboard::A,         arcade::Key::A },
};

arcade::ArcadeEvent SFMLEvent(sf::Event event)
{
    arcade::ArcadeEvent ev;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            ev.key = arcade::Key::A;
            ev.x = 0;
            ev.y = 0;
            return ev;
        }
    }
    return ev;
}