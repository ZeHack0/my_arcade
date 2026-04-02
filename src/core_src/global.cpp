/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** global
*/

#include "Core.hpp"
#include "bitmap.hpp"

arcade::AGlobal::AGlobal()
{
    bitmap = init_bit_map(640, 480);
    _x = 100;
    _y = 100;
}

void arcade::AGlobal::ModifyMap(std::pair<std::size_t, std::size_t> pos, int r, int g, int b)
{
    bitmap.find(pos)->second.setPixel(r, g, b);
}
