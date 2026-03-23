#pragma once
#include <cstdio>

namespace arcade {
    class ACube {
        private:
        int _red;
        int _blue;
        int _green;

        public:
        ACube();
        ACube(int, int, int);
        ~ACube() {};
        int getblue();
        int getred();
        int getgreen();
        void setPixel(int, int, int);
        void setblue(int);
        void setred(int);
        void setgreen(int);
    };
}
