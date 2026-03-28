/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** lib_test
*/

#include "Arcade.hpp"
#include <iostream>

namespace arcade
{
    extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[libtest]: Loading test library..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[libtest]: closing test library..." << std::endl;
        }

        void entryPoint() {
            std::cout << "[libtest]: test library available..." << std::endl;
        }

        LibType getType() {
            return LibType::GRAPHICAL;
        }

    }
}