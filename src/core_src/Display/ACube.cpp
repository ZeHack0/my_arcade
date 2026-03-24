#include "bitmap.hpp"

arcade::ACube::ACube()
{
    _red = 0;
    _green = 0;
    _blue = 0;
}

arcade::ACube::ACube(int r, int g, int b)
{
    _red = r;
    _green = g;
    _blue = b;
}

void arcade::ACube::setPixel(int r, int g, int b)
{
    _red = r;
    _green = g;
    _blue = b;
}

int arcade::ACube::getblue()
{
    return _blue;
}

int arcade::ACube::getred()
{
    return _red;
}

int arcade::ACube::getgreen()
{
    return _green;
}
void arcade::ACube::setblue(int b)
{
    _blue = b;
}

void arcade::ACube::setred(int r)
{
    _red = r;
}

void arcade::ACube::setgreen(int g)
{
    _green = g;
}