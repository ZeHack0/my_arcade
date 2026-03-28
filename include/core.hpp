/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** core
*/

#pragma once
#include "bitmap.hpp"
#include "IDisplayModule.hpp"
#include <map>
#include <iostream>
#include <memory>

namespace arcade {

    class AGlobal {

        private:
        std::size_t _x;
        std::size_t _y;
        std::map<std::pair<std::size_t, std::size_t>, ACube> bitmap;
        public:
        AGlobal();
        ~AGlobal() {};
        std::map<std::pair<std::size_t, std::size_t>, ACube> &getMap() {
            return bitmap;
        };
        std::size_t get_x() {
            return _x;
        }
        std::size_t get_y() {
            return _y;
        }
        void ModifyMap(std::pair<std::size_t, std::size_t>, int, int, int);
    };

    class Core {

        private:
            std::unique_ptr<IDisplayModule>_guiClass;
            //std::unique_ptr<IGameModule>_gameClass;

            //ArcadeEvent _events;
            //GameData _gameData;


    };

}

std::map<std::pair<std::size_t, std::size_t>, arcade::ACube> init_bit_map(std::size_t, std::size_t);
