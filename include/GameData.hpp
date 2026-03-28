/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** GameData
*/

#pragma once
#include "bitmap.hpp"
#include <map>

namespace arcade {

    struct GameData {
        std::size_t _x;
        std::size_t _y;
        std::map<std::pair<std::size_t, std::size_t>, ACube> bitmap;
    };

}
