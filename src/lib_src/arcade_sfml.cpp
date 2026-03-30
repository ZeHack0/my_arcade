/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sfml
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include "GenericEvent.hpp"
#include "bitmap.hpp"
#include <SFML/Graphics.hpp>
#include <map>

namespace arcade {

    static const std::map<sf::Keyboard::Key, Key> SFML_KEY_MAP = {
        {sf::Keyboard::Up,     Key::ArrowUp},
        {sf::Keyboard::Down,   Key::ArrowDown},
        {sf::Keyboard::Left,   Key::ArrowLeft},
        {sf::Keyboard::Right,  Key::ArrowRight},
        {sf::Keyboard::Escape, Key::Escape},
        {sf::Keyboard::R,      Key::R},
        {sf::Keyboard::Q,      Key::Q},
        {sf::Keyboard::Space,  Key::Space},
    };

    class SfmlModule : public IDisplayModule {
        public:
            SfmlModule() : _window(sf::VideoMode(800, 600), "Arcade - SFML") {
                _window.setFramerateLimit(60);
            }

            ArcadeEvent getEvents() override {
                ArcadeEvent ev{};
                ev.key = Key::Undefined;

                sf::Event event;
                while (_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        ev.key = Key::Escape;
                    if (event.type == sf::Event::KeyPressed) {
                        auto it = SFML_KEY_MAP.find(event.key.code);
                        if (it != SFML_KEY_MAP.end())
                            ev.key = it->second;
                    }
                }
                return ev;
            }

            void clear() override {
                _window.clear(sf::Color::Black);
            }

            void draw(GameData data) override {
                const float CELL = 20.0f;
                sf::RectangleShape cell(sf::Vector2f(CELL - 1, CELL - 1));

                for (auto &[pos, cube] : data.bitmap) {
                    if (!cube.getred() && !cube.getgreen() && !cube.getblue())
                        continue;
                    cell.setPosition(pos.first * CELL, pos.second * CELL);
                    cell.setFillColor(sf::Color(
                        cube.getred(),
                        cube.getgreen(),
                        cube.getblue()
                    ));
                    _window.draw(cell);
                }
            }

            void display() override {
                _window.display();
            }

        private:
            sf::RenderWindow _window;
    };

    extern "C" {
        IDisplayModule *instance() { return new SfmlModule(); }
        LibType getType()          { return LibType::GRAPHICAL; }
    }

}