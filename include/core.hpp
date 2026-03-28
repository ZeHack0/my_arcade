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

namespace arcade {

    class AGlobal {

        private:
            std::map<ACube, std::pair<std::size_t, std::size_t>> bitmap;
            public:
            AGlobal();

    };

    class Core {

        private:
            std::unique_ptr<IDisplayModule>_guiClass;
            std::unique_ptr<IGameModule>_gameClass;

            ArcadeEvent _events;
            GameData _gameData;


    };

}

std::map<arcade::ACube, std::pair<std::size_t, std::size_t>> init_bit_map(std::size_t, std::size_t);