/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_test
*/

#include "Arcade.hpp"
#include "IGameModule.hpp"
#include "GameData.hpp"
#include  "ArcadeEvents.hpp"
#include <time.h>
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

            void update(ArcadeEvents ev, clock_t clock) override {
                    (void)clock;
                    paintPlayer(0, 0, 0);
                    for (Key n : ev.key) {
                        if (n == Key::ArrowUp    && _py > 0)
                            _py--;
                        if (n == Key::ArrowDown  && _py < _height - 1)
                            _py++;
                        if (n == Key::ArrowLeft  && _px > 0)
                            _px--;
                        if (n == Key::ArrowRight && _px < _width  - 1)
                            _px++;
                        if (n == Key::K) {
                            ArcadeText text;
                            text.PathPolicy = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
                            text.BeginPos = {20, 20};
                            text.color = {255, 0, 0};
                            text.text = "test de text tex mex";
                            text.TextSize = 24;
                            _data.text.push_back(text);
                        }
                    }
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

        IGameModule *getInstance() {
            return new PixelGame();
        }

        LibType getType() {
            return LibType::GAME;
        }
    }

}