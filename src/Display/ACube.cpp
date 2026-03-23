#include "bitmap.hpp"

ACube::ACube(int r, int g, int b)
{
    _red = r;
    _green = g;
    _blue = b;
}

int ACube::getblue()
{
    return _blue;
}

int ACube::getred()
{
    return _red;
}

int ACube::getgreen()
{
    return _green;
}
void ACube::setblue(int b)
{
    _blue = b;
}

void ACube::setred(int r)
{
    _red = r;
}

void ACube::setgreen(int g)
{
    _green = g;
}