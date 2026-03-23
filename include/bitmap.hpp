#pragma once
#include <cstdio>

class ACube {
    private:
    int _red;
    int _blue;
    int _green;

    public:
    ACube(int, int, int);
    ~ACube() {};
    int getblue();
    int getred();
    int getgreen();
    void setblue(int);
    void setred(int);
    void setgreen(int);
};