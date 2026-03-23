/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sfml
*/

#include "Arcade.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

extern "C" {

    __attribute__((constructor)) void load_lib() {
        std::cout << "[arcade_sfml]: Loading SFML library..." << std::endl;
    }

    __attribute__((destructor)) void unload_lib() {
        std::cout << "[arcade_sfml]: closing SFMl library..." << std::endl;
    }

    LibType getType() {
        return LibType::GRAPHICAL;
    }

    void entryPoint() {
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Arcade - SFML");

        while (window.isOpen()) {
            while (const std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            window.clear();
            window.display();
        }
    }

}
