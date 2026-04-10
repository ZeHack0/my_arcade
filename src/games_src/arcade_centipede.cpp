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
#include <time.h>
#include <algorithm>
#include <iostream>

#define GO_DOWN 1
#define GO_LEFT 2
#define GO_RIGHT 3

namespace arcade {

    struct Mushroom {
        int pos_x;
        int pos_y;
        int health;
    };

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
                _dir = GO_RIGHT;

                paintPlayer(144, 213, 255);

                std::srand(static_cast<unsigned>(std::time(nullptr)));
                spawnMushrooms(30);


                std::size_t center_x = _width / 2;

                _centipede.emplace_back(center_x, 2);
                paintCellCentipede(_centipede[0].first, _centipede[0].second, 255, 165, 0);
                for (int i = 1; i < _sizeCentipede; i++)
                    _centipede.emplace_back(center_x, 2);
                for (int i = 1; i < _sizeCentipede; i++)
                    paintCellCentipede(_centipede[i].first, _centipede[i].second, 255, 165, 0);

            }

            void update(ArcadeEvents ev, clock_t) override;

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
            std::vector<Mushroom> _mushroom;
            std::vector<std::pair<std::size_t, std::size_t>> _centipede;

            bool _spaceWasPressed = false;
            int _sizeCentipede = 15;
            int _dir;

            void paintPlayer(int r, int g, int b);
            void paintBullet(int r, int g, int b);

            void drawOutlineMap(int r, int g, int b, int width, int height);

            void drawMushroom(int r, int g, int b);
            void spawnMushrooms(int count);
            bool isMushroomAt(int x, int y) const;

            void drawCentipede(int r, int g, int b);
            void paintCellCentipede(std::size_t x, std::size_t y, int r, int g, int b);
            void moveCentipede();
    };

    void CentipedeGame::update(ArcadeEvents ev, clock_t clock) {
        (void)clock;
        paintPlayer(0, 0, 0);
        paintBullet(0, 0, 0);
        drawMushroom(0, 0, 0);
        drawCentipede(0, 0, 0);

        std::size_t walkableLimit = _height - (_height * 0.20);

        auto isPressed = [&ev](Key k) {
            return std::ranges::find(ev.key, k) != ev.key.end();
        };
        if (isPressed(ArrowUp) && _py > walkableLimit && !isMushroomAt(_px, _py - 1))
            _py--;
        if (isPressed(ArrowDown) && _py < _height - 1 && !isMushroomAt(_px, _py + 1))
            _py++;
        if (isPressed(ArrowLeft) && _px > 1 && !isMushroomAt(_px - 1, _py))
            _px--;
        if (isPressed(ArrowRight) && _px < _width  - 1 && !isMushroomAt(_px + 1, _py))
            _px++;

        const bool spaceIsPressed = isPressed(Space);
        if (spaceIsPressed && !_spaceWasPressed && _bullet.empty()) {
            _bullet.push_back({_px, _py});
        }
        _spaceWasPressed = spaceIsPressed;

        for (auto itBullet = _bullet.begin(); itBullet != _bullet.end();) {
            bool bulletDestroyed = false;

            if (itBullet->second > 1) {
                itBullet->second--;

                for (auto itMush = _mushroom.begin(); itMush != _mushroom.end();) {
                    if (itBullet->first == itMush->pos_x && itBullet->second == itMush->pos_y) {
                        itMush->health--;
                        bulletDestroyed = true;

                        if (itMush->health <= 0)
                            itMush = _mushroom.erase(itMush);
                        break;
                    } else
                        ++itMush;
                }
            } else
                bulletDestroyed = true;

            if (bulletDestroyed)
                itBullet = _bullet.erase(itBullet);
            else
                ++itBullet;
        }

        if (_centipede[0].second == 50 - 1)
            throw std::runtime_error("reset score");

        moveCentipede();

        paintPlayer(144, 213, 255);
        paintBullet(255, 255, 0);
        drawOutlineMap(128, 128, 128, _width, _height);
        drawMushroom(255, 0, 0);
        drawCentipede(0, 150, 0);
    }

    void CentipedeGame::paintPlayer(int r, int g, int b) {
        _data.bitmap[{_px, _py}] = ACube(r, g, b);
    }

    void CentipedeGame::paintBullet(const int r, const int g, const int b) {
        for (auto &pos : _bullet)
            _data.bitmap[{pos.first, pos.second}] = ACube(r, g, b);
    }

    void CentipedeGame::drawOutlineMap(const int r, const int g, const int b, const int width, const int height) {
        for (int i = 0; i <= width; i++)
            _data.bitmap[{i, 0}] = ACube(r, g, b);
        for (int i = 1; i <= height - 1; i++)
            _data.bitmap[{0, i}] = ACube(r, g, b);
        for (int i = 0; i <= width; i++)
            _data.bitmap[{i, height}] = ACube(r, g, b);
        for (int i = 1; i <= height - 1; i ++)
                                 _data.bitmap[{width, i}] = ACube(r, g, b)      ;
     }

    void CentipedeGame::drawMushroom(const int r, const int g, const int b) {
        for (auto &pos : _mushroom)
        {
            float healthRatio = pos.health / 5.0f;

            int currentR = static_cast<int>(r * healthRatio);
            int currentG = static_cast<int>(g * healthRatio);
            int currentB = static_cast<int>(b * healthRatio);

            _data.bitmap[{pos.pos_x, pos.pos_y}] = ACube(currentR, currentG, currentB);
        }
    }

    void CentipedeGame::spawnMushrooms(int count) {
        for (int i = 0; i < count; i++) {
            int x = std::rand() % (_width - 1) + 1;
            int y = std::rand() % (_height - 1) + 1;

            _mushroom.push_back({x, y, 5});
        }
    }

    bool CentipedeGame::isMushroomAt(int x, int y) const
    {
        for (auto &m : _mushroom) {
            if (m.pos_x == x && m.pos_y == y)
                return true;
        }
        return false;
    }

    void CentipedeGame::paintCellCentipede(std::size_t x, std::size_t y, int r, int g, int b) {
        _data.bitmap[{x, y}] = ACube(r, g, b);
    }

    void CentipedeGame::drawCentipede(int r, int g, int b) {
        paintCellCentipede(_centipede[0].first, _centipede[0].second, 255, 165, 0);

        for (std::size_t i = 1; i < _centipede.size(); i++)
            paintCellCentipede(_centipede[i].first, _centipede[i].second, r, g, b);
    }

    void CentipedeGame::moveCentipede() {
        int next_x = static_cast<int>(_centipede[0].first);
        int next_y = static_cast<int>(_centipede[0].second);

        if (_dir == GO_RIGHT)
            next_x++;
        else if (_dir == GO_LEFT)
            next_x--;

        if (next_x <= 0 || next_x >= (int)_width - 1 || isMushroomAt(next_x, next_y)) {
            next_x = _centipede[0].first;
            next_y = _centipede[0].second + 1;

            _dir = (_dir == GO_RIGHT) ? GO_LEFT : GO_RIGHT;
        }
        for (int i = static_cast<int>(_centipede.size()) - 1; i > 0; i--)
            _centipede[i] = _centipede[i - 1];
        _centipede[0] = {static_cast<std::size_t>(next_x), static_cast<std::size_t>(next_y)};
    }

    extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[arcade_centipede]: Loading centipede game..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[arcade_centipede]: closing centipede game..." << std::endl;
        }

        IGameModule *getInstance() {
            return new CentipedeGame();
        }

        LibType getType() {
            return LibType::GAME;
        }

    }

}
