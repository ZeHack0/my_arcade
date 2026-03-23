#pragma once
#include "bitmap.hpp"
#include <map>

namespace arcade {
    class AGlobal {
        private:
        std::map<ACube, std::pair<std::size_t, std::size_t>> bitmap;
        public:
        AGlobal();
    };
}

std::map<arcade::ACube, std::pair<std::size_t, std::size_t>> init_bit_map(std::size_t, std::size_t);