/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_test
*/

#include "../../include/Arcade.hpp"
#include "../../include/IGameModule.hpp"
#include "../../include/GameData.hpp"
#include  "../../include/ArcadeEvents.hpp"
#include "../../include/DLLoader.hpp"
#include <time.h>
#include <iostream>
#include <filesystem>


namespace arcade {

    std::vector<std::string> get_games()
    {
        std::vector<std::string> all_games;
        for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
            std::string path = entry.path().string();
            DLLoader loader(path);
            auto getType = loader.getSymbol<LibType()>("getType");
            if (getType && getType() == LibType::GAME) {
                for (int i = 0; i != 3 || path.empty(); i++)
                    path.pop_back();
                all_games.push_back(path);
            }
        }
        return all_games;
    }

    class PixelGame : public IGameModule {

        public:
            PixelGame(){
                for (std::size_t y = 0; y < 50; y++)
                    for (std::size_t x = 0; x < 70; x++)
                        _data.bitmap[{x, y}] = ACube(0, 0, 0);
                ArcadeText title;
                title.PathPolicy = "./assets/DejaVuSans.ttf";
                title.BeginPos = {700, 70};
                title.color = {255, 0, 0};
                title.text = "WELCOME TO THE ARCADE !";
                title.TextSize = 50;
                _data.text.push_back(title);
                int y = 350;
                for (auto it : get_games()) {
                    ArcadeText games;
                    games.color = {255, 0, 0};
                    games.PathPolicy = "./assets/snake.ttf";
                    games.BeginPos = {70, y};
                    games.text = it;
                    games.TextSize = 35;
                    _data.text.push_back(games);
                    y += 100;
                }
                ArcadeText title_games;
                title_games.PathPolicy = "./assets/DejaVuSans.ttf";
                title_games.BeginPos = {70, 200};
                title_games.color = {255, 0, 0};
                title_games.text = "AVAILABLE GAMES :";
                title_games.TextSize = 35;
                _data.text.push_back(title_games);
                ArcadeText instruct2;
                title_games.PathPolicy = "./assets/DejaVuSans.ttf";
                title_games.BeginPos = {960, 600};
                title_games.color = {255, 0, 0};
                title_games.text = "Press '2' to load next Games!";
                title_games.TextSize = 35;
                _data.text.push_back(title_games);

                ArcadeText instruct3;
                instruct3.PathPolicy = "./assets/DejaVuSans.ttf";
                instruct3.BeginPos = {960, 700};
                instruct3.color = {255, 0, 0};
                instruct3.text = "Press '3' to switch to next graphical mode !";
                instruct3.TextSize = 35;
                _data.text.push_back(instruct3);
                ArcadeText instructr;
                instructr.PathPolicy = "./assets/DejaVuSans.ttf";
                instructr.BeginPos = {960, 800};
                instructr.color = {255, 0, 0};
                instructr.text = "Press 'r' to restart game!";
                instructr.TextSize = 35;
                _data.text.push_back(instructr);
                ArcadeText instruct1;
                instruct1.PathPolicy = "./assets/DejaVuSans.ttf";
                instruct1.BeginPos = {960, 900};
                instruct1.color = {255, 0, 0};
                instruct1.text = "Press '1' to go back to Menu!";
                instruct1.TextSize = 35;
                _data.text.push_back(instruct1);
                ArcadeText instructEchap;
                instruct1.PathPolicy = "./assets/DejaVuSans.ttf";
                instruct1.BeginPos = {960, 300};
                instruct1.color = {255, 0, 0};
                instruct1.text = "Press 'Echap' to Exit!";
                instruct1.TextSize = 35;
                _data.text.push_back(instruct1);
            }

            void update(ArcadeEvents ev, clock_t clock) override {
                (void)clock;
                (void)ev;
            }

            GameData getGameData() override {
                    return _data;
                }

        private:
            GameData    _data;

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