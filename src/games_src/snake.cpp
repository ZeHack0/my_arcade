/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_test
*/

#include "Arcade.hpp"
#include "IGameModule.hpp"
#include "GameData.hpp"

#include "ArcadeEvents.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

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
            //std::size_t snake_size;
            std::size_t fruit_x;
            std::size_t fruit_y;
            std::size_t _score = 0;
            std::size_t _max_Score = (_width * _height - 3) * 100;
            std::size_t _highScore = 0;
            bool _win = false;
            //bool _lose = false;

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
                std::srand(static_cast<unsigned>(std::time(nullptr)));

                _highScore = get_HighScore();
                std::size_t center_x = _width / 2;
                std::size_t center_y = _height / 2;
                _body.push_back({center_x, center_y});
                _body.push_back({center_x - 1, center_y});
                _body.push_back({center_x - 2, center_y});
                paintCell(_body[0].first, _body[0].second, 255, 0, 0);
                paintCell(_body[1].first, _body[1].second, 255, 165, 0);
                paintCell(_body[2].first, _body[2].second, 255, 165, 0);
                spawn_Fruit();
            }


            int get_HighScore() {
                std::ifstream file("highscore_snake.txt");
                std::size_t score = 0;

                if (file >> score)
                    return score;
                return 0;
            }

            void save_HighScore(int score) {
                std::ofstream file("highscore_snake.txt");
                file << score;
            }

            void get_Direction(ArcadeEvents ev) {
                bool arrowUp = false;
                bool arrowDown = false;
                bool arrowLeft = false;
                bool arrowRight = false;

                for (std::size_t i = 0; i < ev.key.size(); i++) {
                    if (ev.key[i] == Key::ArrowUp)
                        arrowUp = true;
                    if (ev.key[i] == Key::ArrowDown)
                      arrowDown = true;
                    if (ev.key[i] == Key::ArrowLeft)
                      arrowLeft = true;
                    if (ev.key[i] == Key::ArrowRight)
                        arrowRight = true;
                }

                if (arrowUp && _dir != Dir::DOWN)
                    _dir = Dir::UP;
                if (arrowDown && _dir != Dir::UP)
                    _dir = Dir::DOWN;
                if (arrowLeft && _dir != Dir::RIGHT)
                    _dir = Dir::LEFT;
                if (arrowRight && _dir != Dir::LEFT)
                    _dir = Dir::RIGHT;
            }

            void move_Snake(){
                std::size_t _actual_head_x = _body[0].first;
                std::size_t _actual_head_y = _body[0].second;

                if (_dir == Dir::UP && _actual_head_y > 0)
                    _actual_head_y--;
                if (_dir == Dir::DOWN && _actual_head_y < _height - 1)
                    _actual_head_y++;
                if (_dir == Dir::LEFT && _actual_head_x > 0)
                    _actual_head_x--;
                if (_dir == Dir::RIGHT && _actual_head_x < _width - 1)
                    _actual_head_x++;

                for (int i = _body.size() - 1; i > 0; i--)
                    _body[i] = _body[i - 1];

                _body[0] = {_actual_head_x, _actual_head_y};
            }

            void clear_Snake() {
                for (auto &seg : _body)
                    _data.bitmap[{seg.first, seg.second}] = ACube(0, 0, 0);
            }

            void draw_Snake() {
                paintCell(_body[0].first, _body[0].second, 255, 0, 0);

                for (std::size_t i = 1; i < _body.size(); i++)
                    paintCell(_body[i].first, _body[i].second, 255, 165, 0);
            }

            bool is_Cell_Filled(std::size_t x, std::size_t y) const {
                for (std::size_t i = 0; i < _body.size(); i++)
                    if (_body[i].first == x && _body[i].second == y)
                        return true;
                return false;
            }

            void spawn_Fruit() {
                fruit_x = std::rand() % _width;
                fruit_y = std::rand() % _height;
                if (is_Cell_Filled(fruit_x, fruit_y) == false) {
                    paintCell(fruit_x, fruit_y, 0, 255, 0);
                } else {
                    spawn_Fruit();
                }
            }

            void checkFruit() {
                if (_body[0].first == fruit_x && _body[0].second == fruit_y) {
                    _body.push_back(_body.back());
                    _score += 100;

                    if (_score >= _max_Score)
                        _win = true;
                    if (_score > _highScore) {
                        _highScore = _score;
                        save_HighScore(_highScore);
                    }
                    spawn_Fruit();
                }
            }

            bool check_collision() {
                std::size_t head_x = _body[0].first;
                std::size_t head_y = _body[0].second;

                for (std::size_t i = 1; i < _body.size(); i++)
                    if (_body[i].first == head_x && _body[i].second == head_y)
                        return true;
                return false;
            }

            void update(ArcadeEvents ev) override {
                if (_win == true)
                    return;
                clear_Snake();
                get_Direction(ev);
                move_Snake();
                checkFruit();
                if (check_collision() == true)
                    return;
                draw_Snake();
            }

            GameData getGameData() override {
                    return _data;
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
