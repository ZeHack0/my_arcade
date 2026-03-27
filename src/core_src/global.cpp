#include "core.hpp"
#include "bitmap.hpp"

arcade::AGlobal::AGlobal()
{
    bitmap = init_bit_map(300, 300);
}

void arcade::AGlobal::ModifyMap(std::pair<std::size_t, std::size_t> pos, int r, int g, int b)
{
    bitmap.find(pos)->second.setPixel(r, g, b);
}