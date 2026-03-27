/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sfml
*/

#include "Arcade.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "core.hpp"

namespace arcade
{
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

        void entryPoint(AGlobal &glob) {
            sf::RenderWindow window(sf::VideoMode(800, 600), "Arcade - SFML");
            int i = 0;

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                    window.close();
                }
                glob.ModifyMap(std::pair(10, 10), i, i, i);
                i++;
                if (i >= 255)
                    i = -255;
                window.clear();
                display_bitmap(window, glob.getMap());
                window.display();
            }
        }

    }
}
