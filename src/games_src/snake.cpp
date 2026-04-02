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
#include <vector>

namespace arcade {

    class PixelGame : public IGameModule {

        private:
            static constexpr std::size_t _width  = 40;
            static constexpr std::size_t _height = 30;

            enum class Dir {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };

            std::vector<std::pair<std::size_t, std::size_t>> _body;
            std::size_t snake_size;
            std::size_t fruit_x;
            std::size_t fruit_y;

            Dir _dir;
            GameData _data;

            void paintCell(std::size_t x, std::size_t y, int r, int g, int b) {
                _data.bitmap[{x, y}] = ACube(r, g, b);
            }


        public:
            PixelGame() {
                for (std::size_t y = 0; y < _height; y++)
                    for (std::size_t x = 0; x < _width; x++)
                        _data.bitmap[{x, y}] = ACube(0, 0, 0);

                _data._x = _width;
                _data._y = _height;
                _dir = Dir::UP;

                std::size_t center_x = _width  / 2;
                std::size_t center_y = _height / 2;
                _body.push_back({center_x, center_y});
                _body.push_back({center_x - 1, center_y});
                _body.push_back({center_x - 2, center_y});
                paintCell(_body[0].first, _body[0].second, 255, 0, 0);
                paintCell(_body[1].first, _body[1].second, 255, 165, 0);
                paintCell(_body[2].first, _body[2].second, 255, 165, 0);
            }

            void update(ArcadeEvent ev) override {
                for (auto &seg : _body)
                    _data.bitmap[{seg.first, seg.second}] = ACube(0, 0, 0);

                std::size_t _actual_head_x = _body[0].first;
                std::size_t _actual_head_y = _body[0].second;

                if (ev.key == Key::ArrowUp && _dir != Dir::DOWN)
                    _dir = Dir::UP;
                if (ev.key == Key::ArrowDown && _dir != Dir::UP)
                    _dir = Dir::DOWN;
                if (ev.key == Key::ArrowLeft && _dir != Dir::RIGHT)
                    _dir = Dir::LEFT;
                if (ev.key == Key::ArrowRight && _dir != Dir::LEFT)
                    _dir = Dir::RIGHT;

                if (ev.key == Dir::UP && _actual_head_y > 0)
                    _actual_head_y--;
                if (ev.key == Dir::DOWN && _actual_head_y < _height - 1)
                    _actual_head_y++;
                if (ev.key == Dir::LEFT && _actual_head_x > 0)
                    _actual_head_x--;
                if (ev.key == Dir::RIGHT && _actual_head_x < _width - 1)
                    _actual_head_x++;

                for (int i = _body.size() - 1; i > 0; i--)
                    _body[i] = _body[i - 1];

                _body[0] = {_actual_head_x, _actual_head_y};
                paintCell(_body[0].first, _body[0].second, 255, 0, 0);

                for (std::size_t i = 1; i < _body.size(); i++)
                    paintCell(_body[i].first, _body[i].second, 255, 165, 0);
            }

            GameData getGameData() override {
                    return _data;
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