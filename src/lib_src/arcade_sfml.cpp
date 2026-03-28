/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sfml
*/

#include "Arcade.hpp"
#include "core.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

namespace arcade
{

    class SfmlModule : public IDisplayModule{

        public:
            SfmlModule(): _window(sf::VideoMode(800, 600), "Arcade") {}

            ArcadeEvent getEvents() override {
                sf::Event event;
                ArcadeEvent arcEvent{};
                arcEvent.key = Undefined;

                while (_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        _window.close();
                }
                return arcEvent;
            }
            void clear() override { _window.clear(); }
            void draw(GameData data) override {
                display_bitmap(_window, data.bitmap);
            }
            void display() override { _window.display(); }

        private:
            sf::RenderWindow _window;

    };

    extern "C" IDisplayModule *instantiate() {
        return new SfmlModule();
    }

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

        void entryPoint(AGlobal &glob)
        {
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
