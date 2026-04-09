/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sfml
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include "ArcadeEvents.hpp"
#include "bitmap.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

static const std::map<sf::Keyboard::Key, arcade::Key> keyMap = {
    {sf::Keyboard::A, arcade::Key::A},
    {sf::Keyboard::B, arcade::Key::B},
    {sf::Keyboard::C, arcade::Key::C},
    {sf::Keyboard::D, arcade::Key::D},
    {sf::Keyboard::E, arcade::Key::E},
    {sf::Keyboard::F, arcade::Key::F},
    {sf::Keyboard::G, arcade::Key::G},
    {sf::Keyboard::H, arcade::Key::H},
    {sf::Keyboard::I, arcade::Key::I},
    {sf::Keyboard::J, arcade::Key::J},
    {sf::Keyboard::K, arcade::Key::K},
    {sf::Keyboard::L, arcade::Key::L},
    {sf::Keyboard::M, arcade::Key::M},
    {sf::Keyboard::N, arcade::Key::N},
    {sf::Keyboard::O, arcade::Key::O},
    {sf::Keyboard::P, arcade::Key::P},
    {sf::Keyboard::Q, arcade::Key::Q},
    {sf::Keyboard::R, arcade::Key::R},
    {sf::Keyboard::S, arcade::Key::S},
    {sf::Keyboard::T, arcade::Key::T},
    {sf::Keyboard::U, arcade::Key::U},
    {sf::Keyboard::V, arcade::Key::V},
    {sf::Keyboard::W, arcade::Key::W},
    {sf::Keyboard::X, arcade::Key::X},
    {sf::Keyboard::Y, arcade::Key::Y},
    {sf::Keyboard::Z, arcade::Key::Z},

    {sf::Keyboard::Num0, arcade::Key::Num0},
    {sf::Keyboard::Num1, arcade::Key::Num1},
    {sf::Keyboard::Num2, arcade::Key::Num2},
    {sf::Keyboard::Num3, arcade::Key::Num3},
    {sf::Keyboard::Num4, arcade::Key::Num4},
    {sf::Keyboard::Num5, arcade::Key::Num5},
    {sf::Keyboard::Num6, arcade::Key::Num6},
    {sf::Keyboard::Num7, arcade::Key::Num7},
    {sf::Keyboard::Num8, arcade::Key::Num8},
    {sf::Keyboard::Num9, arcade::Key::Num9},

    {sf::Keyboard::Add,      arcade::Key::NumpadAdd},
    {sf::Keyboard::Subtract, arcade::Key::NumpadSubtract},
    {sf::Keyboard::Multiply, arcade::Key::NumpadMultiply},
    {sf::Keyboard::Divide,   arcade::Key::NumpadDivide},

    {sf::Keyboard::Escape,   arcade::Key::Escape},
    {sf::Keyboard::LControl, arcade::Key::LeftCtrl},
    {sf::Keyboard::LShift,   arcade::Key::LeftShift},
    {sf::Keyboard::LAlt,     arcade::Key::LeftAlt},
    {sf::Keyboard::RControl, arcade::Key::RightCtrl},
    {sf::Keyboard::RShift,   arcade::Key::RightShift},
    {sf::Keyboard::RAlt,     arcade::Key::RightAlt},
    {sf::Keyboard::LBracket, arcade::Key::LeftBracket},
    {sf::Keyboard::RBracket, arcade::Key::RightBracket},
    {sf::Keyboard::SemiColon, arcade::Key::Semicolon},
    {sf::Keyboard::Comma, arcade::Key::Comma},
    {sf::Keyboard::Period, arcade::Key::Period},
    {sf::Keyboard::Quote, arcade::Key::Apostrophe},
    {sf::Keyboard::Slash, arcade::Key::Slash},
    {sf::Keyboard::BackSlash, arcade::Key::Backslash},
    {sf::Keyboard::Tilde, arcade::Key::Grave},
    {sf::Keyboard::Equal, arcade::Key::Equal},
    {sf::Keyboard::Dash, arcade::Key::Minus},

    {sf::Keyboard::Space, arcade::Key::Space},
    {sf::Keyboard::Return, arcade::Key::Enter},
    {sf::Keyboard::BackSpace, arcade::Key::Backspace},
    {sf::Keyboard::Tab, arcade::Key::Tab},
    {sf::Keyboard::PageUp, arcade::Key::PageUp},
    {sf::Keyboard::PageDown, arcade::Key::PageDown},

    {sf::Keyboard::Left, arcade::Key::ArrowLeft},
    {sf::Keyboard::Right, arcade::Key::ArrowRight},
    {sf::Keyboard::Up, arcade::Key::ArrowUp},
    {sf::Keyboard::Down, arcade::Key::ArrowDown},
};

namespace arcade {

    void display_bitmap(sf::RenderWindow &wind, std::map<std::pair<std::size_t, std::size_t>, ACube> &bitmap)
    {
        sf::RectangleShape pixel(sf::Vector2f(1, 1));

        for (auto &[key, val] : bitmap) {
            pixel.setPosition(static_cast<float>(key.first), static_cast<float>(key.second));
            pixel.setFillColor(sf::Color(val.getred(), val.getgreen(), val.getred()));
            wind.draw(pixel);
        }
    }

    class SfmlModule : public IDisplayModule {
        public:
            SfmlModule() : _window(sf::VideoMode(1920, 1072), "Arcade - SFML") {
                _window.setFramerateLimit(30);
            }

            ArcadeEvents getEvents() override {
                ArcadeEvents ev{};

                sf::Event event;
                while (_window.pollEvent(event)) {
                    _event = event;
                    if (event.type == sf::Event::Closed)
                        _window.close();
                }

                for (auto const& [sfKey, arcKey] : keyMap) {
                    if (sf::Keyboard::isKeyPressed(sfKey)) {
                        ev.key.push_back(arcKey);
                    }
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    ev.key.push_back(RightClick);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    ev.key.push_back(LeftClick);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
                    ev.key.push_back(MiddleClick);

                ev.x = sf::Mouse::getPosition().x;
                ev.y = sf::Mouse::getPosition().y;

                return ev;
            }

            void clear() override {
                _window.clear(sf::Color::Black);
            }

            void draw(GameData data) override {
                const float CELL = 16.0f;
                float offsetX = (_window.getSize().x - (data._x * CELL)) / 2.0f;
                float offsetY = (_window.getSize().y - (data._y * CELL)) / 2.0f;
                sf::Font font;
                sf::Text text;

                sf::RectangleShape cell(sf::Vector2f(CELL, CELL));


                for (auto &[pos, cube] : data.bitmap) {
                    if (!cube.getred() && !cube.getgreen() && !cube.getblue())
                        continue;
                    cell.setPosition(offsetX + (pos.first * CELL), offsetY + (pos.second * CELL));
                    cell.setFillColor(sf::Color(
                        cube.getred(),
                        cube.getgreen(),
                        cube.getblue()
                    ));
                    _window.draw(cell);
                }

                for (auto it : data.text) {
                    if (!font.loadFromFile(it.PathPolicy))
                        throw(std::runtime_error(it.PathPolicy + ": Policy cant be loaded\n"));
                    text.setFont(font);
                    text.setString(it.text);
                    text.setCharacterSize(26);
                    text.setFillColor(sf::Color(it.color.R, it.color.G, it.color.B));
                    text.setRotation(90.f);
                    text.move(it.BeginPos.first, it.BeginPos.second);
                    _window.draw(text);
                }
            }

            std::string getUsername() override {
                sf::Font font;
                font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
                sf::Text prompt("Enter USERNAME: ", font, 24);
                prompt.setPosition(500, 500);
                sf::Text input("", font, 24);
                input.setPosition(500, 540);
                sf::Color coulor = {255, 0, 0};
                std::string username;

                while (_window.isOpen()) {
                    sf::Event event;
                    while (_window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            return "player1";
                        if (event.type == sf::Event::TextEntered) {
                            char c = event.text.unicode;
                            if (c == '\r' || c == '\n') {
                                if (username.empty()) {
                                    username = "player1";
                                }
                                return username;
                            }
                            else if (c == '\b')
                                if (!username.empty())
                                    username.pop_back();
                            username.push_back(c);
                            input.setFillColor(coulor);
                            input.setString(username);
                        }
                    }
                    _window.clear(sf::Color::Black);
                    _window.draw(prompt);
                    _window.draw(input);
                    _window.display();
                }
                return username;
}

            void display() override {
                _window.display();
            }

        private:
            sf::RenderWindow _window;
            sf::Event _event;

    };

    extern "C" IDisplayModule *getInstance() {
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
    }

}