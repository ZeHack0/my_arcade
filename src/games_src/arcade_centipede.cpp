/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_centipede
*/

#include "../../include/Arcade.hpp"
#include "../../include/DLLoader.hpp"
#include "../../include/GameData.hpp"
#include "../../include/Core.hpp"
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>

#define GO_DOWN 1
#define GO_LEFT 2
#define GO_RIGHT 3

namespace arcade {

    struct Mushroom {
        int pos_x;
        int pos_y;
        int health;
    };

    struct CentipedePart {
        std::vector<std::pair<std::size_t, std::size_t>> segments;
        int dir;
        bool needsToDescend = false;
    };

    class CentipedeGame : public IGameModule {

        public:
            CentipedeGame() {
                initGame();
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
            std::vector<CentipedePart> _parts;

            bool _spaceWasPressed = false;
            int _sizeCentipede = 15;
            int _killedCentipedes = 0;
            int _score = 0;
            int _highScore = 0;

            int get_HighScore();
            void save_HighScore(int score);
            void initGame();
            void spawnCentipede();
            void paintPlayer(int r, int g, int b);
            void paintBullet(int r, int g, int b);
            void drawOutlineMap(int r, int g, int b, int width, int height);
            void drawMushroom(int r, int g, int b);
            void spawnMushrooms(int count);
            bool isMushroomAt(int x, int y) const;
            void drawAllCentipedes();
            void moveAllCentipedes();
            bool checkBulletHitCentipede(std::pair<int,int> &bullet);
            bool checkPlayerHitCentipede() const;
    };

    int CentipedeGame::get_HighScore() {
        std::ifstream file("highscore_centipede.txt");
        int score = 0;
        if (file >> score)
            return score;
        return 0;
    }

    void CentipedeGame::save_HighScore(int score) {
        std::ofstream file("highscore_centipede.txt");
        file << score;
    }

    void CentipedeGame::initGame() {
        for (std::size_t y = 0; y < _height; y++)
            for (std::size_t x = 0; x < _width; x++)
                _data.bitmap[{x, y}] = ACube(0, 0, 0);

        _data._x = _width;
        _data._y = _height;
        _px = _width / 2;
        _py = _height - (_height * 20 / 100) / 2;

        _bullet.clear();
        _mushroom.clear();
        _parts.clear();

        _highScore = get_HighScore();

        paintPlayer(144, 213, 255);

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        spawnMushrooms(30);
        spawnCentipede();
    }

    void CentipedeGame::spawnCentipede() {
        CentipedePart initialPart;
        initialPart.dir = GO_RIGHT;
        initialPart.needsToDescend = false;
        std::size_t center_x = _width / 2;
        for (int i = 0; i < _sizeCentipede; i++)
            initialPart.segments.push_back({center_x - i, 2});
        _parts.push_back(initialPart);
    }

    void CentipedeGame::update(ArcadeEvents ev, clock_t clock) {
        (void)clock;

        paintPlayer(0, 0, 0);
        paintBullet(0, 0, 0);
        drawMushroom(0, 0, 0);
        drawAllCentipedes();

        std::size_t walkableLimit = _height - (_height * 20 / 100);

        auto isPressed = [&ev](Key k) {
            return std::ranges::find(ev.key, k) != ev.key.end();
        };

        if (isPressed(ArrowUp) && _py > walkableLimit && !isMushroomAt(_px, _py - 1))
            _py--;
        if (isPressed(ArrowDown) && _py < _height - 1 && !isMushroomAt(_px, _py + 1))
            _py++;
        if (isPressed(ArrowLeft) && _px > 1 && !isMushroomAt(_px - 1, _py))
            _px--;
        if (isPressed(ArrowRight) && _px < _width - 1 && !isMushroomAt(_px + 1, _py))
            _px++;

        const bool spaceIsPressed = isPressed(Space);
        if (spaceIsPressed && !_spaceWasPressed && _bullet.empty())
            _bullet.push_back({(int)_px, (int)_py});
        _spaceWasPressed = spaceIsPressed;

        for (auto itBullet = _bullet.begin(); itBullet != _bullet.end();) {
            bool bulletDestroyed = false;

            if (itBullet->second > 1) {
                itBullet->second--;

                if (checkBulletHitCentipede(*itBullet))
                    bulletDestroyed = true;

                if (!bulletDestroyed) {
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
                }
            } else
                bulletDestroyed = true;

            if (bulletDestroyed)
                itBullet = _bullet.erase(itBullet);
            else
                ++itBullet;
        }

        for (auto &part : _parts) {
            if (!part.segments.empty() && part.segments[0].second >= _height - 1) {
                _score -= 100;
                part.segments[0].second = 2;
            }
        }

        moveAllCentipedes();

        if (checkPlayerHitCentipede()) {
            _data.GameOver = true;
            return;
        }

        if (_parts.empty()) {
            _killedCentipedes++;
            if (_killedCentipedes >= 20) {
                _killedCentipedes = 0;
                _mushroom.clear();
                spawnMushrooms(30);
            }
            spawnCentipede();
        }

        paintPlayer(144, 213, 255);
        paintBullet(255, 255, 0);
        drawOutlineMap(128, 128, 128, _width, _height);
        drawMushroom(255, 0, 0);

        for (auto &part : _parts) {
            for (std::size_t i = 0; i < part.segments.size(); i++) {
                auto [x, y] = part.segments[i];
                if (i == 0)
                    _data.bitmap[{x, y}] = ACube(255, 165, 0);
                else if (i == part.segments.size() - 1)
                    _data.bitmap[{x, y}] = ACube(255, 80, 80);
                else
                    _data.bitmap[{x, y}] = ACube(0, 150, 0);
            }
        }

    }

    bool CentipedeGame::checkBulletHitCentipede(std::pair<int,int> &bullet) {
        for (auto itPart = _parts.begin(); itPart != _parts.end(); ++itPart) {
            for (std::size_t j = 0; j < itPart->segments.size(); j++) {
                auto [sx, sy] = itPart->segments[j];
                if ((int)sx == bullet.first && (int)sy == bullet.second) {
                    _score += 10;
                    if (_score > _highScore) {
                        _highScore = _score;
                        save_HighScore(_highScore);
                    }
                    _mushroom.push_back({(int)sx, (int)sy, 5});

                    CentipedePart front;
                    front.dir = itPart->dir;
                    front.needsToDescend = false;
                    for (std::size_t k = 0; k < j; k++)
                        front.segments.push_back(itPart->segments[k]);

                    CentipedePart back;
                    back.dir = (itPart->dir == GO_RIGHT) ? GO_LEFT : GO_RIGHT;
                    back.needsToDescend = true;
                    for (std::size_t k = j + 1; k < itPart->segments.size(); k++)
                        back.segments.push_back(itPart->segments[k]);

                    itPart = _parts.erase(itPart);
                    if (!front.segments.empty())
                        itPart = _parts.insert(itPart, front);
                    if (!back.segments.empty())
                        _parts.insert(itPart, back);
                    return true;
                }
            }
        }
        return false;
    }

    void CentipedeGame::moveAllCentipedes() {
        for (auto &part : _parts) {
            if (part.segments.empty())
                continue;

            int head_x = static_cast<int>(part.segments[0].first);
            int head_y = static_cast<int>(part.segments[0].second);
            int next_x = head_x;
            int next_y = head_y;

            if (part.needsToDescend) {
                next_y = head_y + 1;
                part.needsToDescend = false;
            } else {
                next_x = head_x + (part.dir == GO_RIGHT ? 1 : -1);
                if (next_x <= 0 || next_x >= (int)_width - 1 || isMushroomAt(next_x, head_y)) {
                    next_x = head_x;
                    next_y = head_y + 1;
                    part.dir = (part.dir == GO_RIGHT) ? GO_LEFT : GO_RIGHT;
                }
            }

            for (int i = static_cast<int>(part.segments.size()) - 1; i > 0; i--)
                part.segments[i] = part.segments[i - 1];
            part.segments[0] = {static_cast<std::size_t>(next_x), static_cast<std::size_t>(next_y)};
        }

        _parts.erase(
            std::remove_if(_parts.begin(), _parts.end(),
                [](const CentipedePart &p){ return p.segments.empty(); }),
            _parts.end()
        );
    }

    bool CentipedeGame::checkPlayerHitCentipede() const {
        for (auto &part : _parts)
            for (auto [x, y] : part.segments)
                if (x == _px && y == _py)
                    return true;
        return false;
    }

    void CentipedeGame::drawAllCentipedes() {
        for (auto &part : _parts)
            for (auto [x, y] : part.segments)
                _data.bitmap[{x, y}] = ACube(0, 0, 0);
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
        for (int i = 1; i <= height - 1; i++)
            _data.bitmap[{width, i}] = ACube(r, g, b);
    }

    void CentipedeGame::drawMushroom(const int r, const int g, const int b) {
        for (auto &pos : _mushroom) {
            float healthRatio = pos.health / 5.0f;
            int currentR = static_cast<int>(r * healthRatio);
            int currentG = static_cast<int>(g * healthRatio);
            int currentB = static_cast<int>(b * healthRatio);
            _data.bitmap[{pos.pos_x, pos.pos_y}] = ACube(currentR, currentG, currentB);
        }
    }

    void CentipedeGame::spawnMushrooms(int count) {
        for (int i = 0; i < count; i++) {
            int x = std::rand() % (_width - 2) + 1;
            int y = std::rand() % (_height - 2) + 1;
            _mushroom.push_back({x, y, 5});
        }
    }

    bool CentipedeGame::isMushroomAt(int x, int y) const {
        for (auto &m : _mushroom)
            if (m.pos_x == x && m.pos_y == y)
                return true;
        return false;
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