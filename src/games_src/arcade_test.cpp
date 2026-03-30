/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_test
*/

#include "Arcade.hpp"
#include "IGameModule.hpp"
#include "GameData.hpp"
#include  "GenericEvent.hpp"
#include <iostream>

namespace arcade {

    class PixelGame : public IGameModule {

        public:
            PixelGame() {
                for (std::size_t y = 0; y < _height; y++)
                    for (std::size_t x = 0; x < _width; x++)
                        _data.bitmap[{x, y}] = ACube(0, 0, 0);

                _data._x = _width;
                _data._y = _height;

                _px = _width  / 2;
                _py = _height / 2;
                paintPlayer(255, 255, 0);
            }

            void update(ArcadeEvent ev) override {
                    paintPlayer(0, 0, 0);

                    if (ev.key == Key::ArrowUp    && _py > 0)           _py--;
                    if (ev.key == Key::ArrowDown  && _py < _height - 1) _py++;
                    if (ev.key == Key::ArrowLeft  && _px > 0)           _px--;
                    if (ev.key == Key::ArrowRight && _px < _width  - 1) _px++;

                    paintPlayer(255, 255, 0);
                }

            GameData getGameData() override {
                    return _data;
                }

        private:
            static constexpr std::size_t _width  = 40;
            static constexpr std::size_t _height = 30;

            std::size_t _px;
            std::size_t _py;
            GameData    _data;

            void paintPlayer(int r, int g, int b) {
                _data.bitmap[{_px, _py}] = ACube(r, g, b);
            }
    };

    extern "C" {

        IGameModule *instance() {
            return new PixelGame();
        }

        LibType getType() {
            return LibType::GAME;
        }
    }

}