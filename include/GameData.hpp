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

    struct ArcadeColor {
        int R;
        int G;
        int B;
    };

    struct ArcadeText {
        std::string PathPolicy;
        std::pair<int, int> BeginPos;
        std::string text;
        int TextSize;
        ArcadeColor color;
    };
    struct GameData {
        std::size_t _x;
        std::size_t _y;
        std::map<std::pair<std::size_t, std::size_t>, ACube> bitmap;
        std::vector<ArcadeText> text;
    };

}
