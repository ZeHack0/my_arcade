/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_centipede
*/

#include "Arcade.hpp"
#include "DLLoader.hpp"
#include "GameData.hpp"
#include "Core.hpp"
#include <algorithm>

namespace arcade {

    class CentipedeGame : public IGameModule {

        public:
            CentipedeGame() {
                for (std::size_t y = 0; y < _height; y++)
                    for (std::size_t x = 0; x < _width; x++)
                        _data.bitmap[{x, y}] = ACube(0, 0, 0);

                _data._x = _width;
                _data._y = _height;

                _px = _width / 2;
                _py = _height - (_height * 0.20) / 2;

                paintPlayer(144, 213, 255);
            }

            void update(ArcadeEvents ev) override {
                paintPlayer(0, 0, 0);
                paintBullet(0, 0, 0);

                std::size_t walkableLimit = _height - (_height * 0.20);

                auto isPressed = [&ev](Key k) {
                    return std::ranges::find(ev.key, k) != ev.key.end();
                };

                if (isPressed(ArrowUp) && _py > walkableLimit)
                    _py--;
                if (isPressed(ArrowDown) && _py < _height - 1)
                    _py++;
                if (isPressed(ArrowLeft) && _px > 1)
                    _px--;
                if (isPressed(ArrowRight) && _px < _width  - 1)
                    _px++;

                const bool spaceIsPressed = isPressed(Space);

                if (spaceIsPressed && !_spaceWasPressed && _bullet.empty()) {
                    _bullet.push_back({_px, _py});
                }

                _spaceWasPressed = spaceIsPressed;

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

                drawOutlineMap(128, 128, 128, _width, _height);
            }

            GameData getGameData() override {
                return _data;
            }

        private:
            static constexpr std::size_t _width  = 70;
            static constexpr std::size_t _height = 50;

            std::size_t _px;
            std::size_t _py;
            GameData    _data;
            std::vector<std::pair<int, int>> _bullet;

            bool _spaceWasPressed = false;

            void paintPlayer(int r, int g, int b) {
                _data.bitmap[{_px, _py}] = ACube(r, g, b);
            }

            void paintBullet(const int r, const int g, const int b) {
                for (auto &pos : _bullet)
                    _data.bitmap[{pos.first, pos.second}] = ACube(r, g, b);
            }

            void drawOutlineMap(const int r, const int g, const int b, const int width, const int height) {
                for (int i = 0; i <= width; i++)
                    _data.bitmap[{i, 0}] = ACube(r, g, b);
                for (int i = 1; i <= height - 1; i++)
                    _data.bitmap[{0, i}] = ACube(r, g, b);
                for (int i = 0; i <= width; i++)
                    _data.bitmap[{i, height}] = ACube(r, g, b);
                for (int i = 1; i <= height - 1; i++)
                    _data.bitmap[{width, i}] = ACube(r, g, b);
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
