#include "bitmap.hpp"
#include <map>


std::map<std::pair<std::size_t, std::size_t>, arcade::ACube> init_bit_map(std::size_t line, std::size_t col)
{
    std::map<std::pair<std::size_t, std::size_t>, arcade::ACube> m;
    for (std::size_t i = 0; i < line; i++)
        for (std::size_t j = 0; j < col; j++)
            m[{j, i}] = arcade::ACube(0, 0, 0);
    return m;
}
