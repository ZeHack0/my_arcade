/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_centipede
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "DLLoader.hpp"
#include "GameData.hpp"
#include "GenericEvent.hpp"
#include "Core.hpp"
#include <iostream>

namespace arcade {

    class CentipedeGame : public IGameModule {

        public:
            CentipedeGame() {
                for (std::size_t y = 0; y < _height; y++)
                    for (std::size_t x = 0; x < _width; x++)
                        _data.bitmap[{x, y}] = ACube(0, 0, 0);

                _data._x = _width;
                _data._y = _height;

                _px = _width  / 2;
                _py = _height / 2;
                paintPlayer(144, 213, 255);
            }

            void update(ArcadeEvent ev) override {
                paintPlayer(0, 0, 0);
                paintBullet(0, 0, 0);

                if (ev.key == ArrowUp    && _py > 0)
                    _py--;
                if (ev.key == ArrowDown  && _py < _height - 1)
                    _py++;
                if (ev.key == ArrowLeft  && _px > 0)
                    _px--;
                if (ev.key == ArrowRight && _px < _width  - 1)
                    _px++;
                if (ev.key == Space) {
                    _bullet.push_back({_px, _py});
                }

                for (auto i = _bullet.begin(); i != _bullet.end();) {
                    if (i->second > 0) {
                        i->second--;
                        ++i;
                    } else {
                        i = _bullet.erase(i);
                    }
                }

                paintPlayer(144, 213, 255);
                paintBullet(255, 255, 0);
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
            std::vector<std::pair<int, int>> _bullet;

            void paintPlayer(int r, int g, int b) {
                _data.bitmap[{_px, _py}] = ACube(r, g, b);
            }

            void paintBullet(int r, int g, int b) {
                for (auto &pos : _bullet) {
                    _data.bitmap[{pos.first, pos.second}] = ACube(r, g, b);
                }
            }

    };

    extern "C" {

        IGameModule *getInstance() {
            return new CentipedeGame();
        }

        LibType getType() {
            return LibType::GAME;
        }

    }

}
