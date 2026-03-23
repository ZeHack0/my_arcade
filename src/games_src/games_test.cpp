/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** lib_test
*/

#include "Arcade.hpp"
#include <iostream>

namespace arcade {
    extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[gametest]: Loading test game..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[gametest]: closing test game..." << std::endl;
        }

        void entryPoint() {
            std::cout << "[gametest]: test game available..." << std::endl;
        }

        LibType getType() {
            return LibType::GAME;
        }

    }
}