#pragma once
#include "bitmap.hpp"
#include <map>

namespace arcade {
    class AGlobal {
        private:
        std::map<std::pair<std::size_t, std::size_t>, ACube> bitmap;
        public:
        AGlobal();
        ~AGlobal() {};
        std::map<std::pair<std::size_t, std::size_t>, ACube> &getMap() {
            return bitmap;
        };
        void ModifyMap(std::pair<std::size_t, std::size_t>, int, int, int);
    };
}

std::map<std::pair<std::size_t, std::size_t>, arcade::ACube> init_bit_map(std::size_t, std::size_t);