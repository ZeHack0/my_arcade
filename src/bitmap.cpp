#include "bitmap.hpp"
#include <map>


std::map<arcade::ACube, std::pair<std::size_t, std::size_t>> init_bit_map(std::size_t line, std::size_t column)
{
    std::map<arcade::ACube, std::pair<std::size_t, std::size_t>> m;
    std::pair<std::size_t, std::size_t> p;
    for (int i = 0;  i <= line; i++) {
        for (int j = 0; j <= column; j++) {
            p.first = j;
            p.second = i;
            m.insert({arcade::ACube(0, 0, 0), p});
        }
    }
    return m;
}