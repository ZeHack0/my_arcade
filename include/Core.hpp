/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** core
*/

#pragma once
#include "bitmap.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "ArcadeEvents.hpp"
#include "DLLoader.hpp"
#include <map>
#include <memory>

namespace arcade {

    class AGlobal {

        public:
            AGlobal();
            ~AGlobal() {};

            std::map<std::pair<std::size_t, std::size_t>, ACube> &getMap() { return bitmap; }
            std::size_t get_x() { return _x; }
            std::size_t get_y() { return _y; }

            void ModifyMap(std::pair<std::size_t, std::size_t>, int, int, int);

        private:
            std::size_t _x;
            std::size_t _y;
            std::map<std::pair<std::size_t, std::size_t>, ACube> bitmap;
    };

    class Core {

        public:
            Core(const std::string &libpath);
            void run();
            void change_game(const std::string &);
            void change_lib(const std::string &);
            void check_event(ArcadeEvents);
            void back_to_menu();
            void restart_game();
        private:
            std::unique_ptr<DLLoader>       _guiLoader;
            std::unique_ptr<DLLoader>       _gameLoader;
            std::unique_ptr<IDisplayModule> _guiClass;
            std::unique_ptr<IGameModule>    _gameClass;
            std::string _lib_path;
            std::string _game_path;
            ArcadeEvents                     _events;
            GameData                        _gameData;
            std::string                     _username;

    };

}

std::map<std::pair<std::size_t, std::size_t>, arcade::ACube> init_bit_map(std::size_t, std::size_t);
