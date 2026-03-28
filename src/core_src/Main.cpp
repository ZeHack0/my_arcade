/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Main
*/

#include "Arcade.hpp"
#include <iostream>
#include <vector>
#include <dlfcn.h>
#include "core.hpp"


namespace arcade
{
    int main(int ac, char **av) {
        if (ac != 2) {
            std::cerr << "Usage: " << av[0] << " <library_path>" << std::endl;
            return 84;
        }

        void *handle = dlopen(av[1], RTLD_LAZY);
        if (!handle) {
            std::cerr << "Error: " << dlerror() << std::endl;
            return 84;
        }

        auto getType = (LibType (*)())(dlsym(handle, "getType"));
        if (!getType) {
            std::cerr << "Error: " << dlerror() << std::endl;
            dlclose(handle);
            return 84;
        }

        if (getType() == LibType::GAME) {
            std::cerr << "Error: The provided library is a game, but a graphical library is required." << std::endl;
            dlclose(handle);
            return 84;
        }

        auto entryPoint = (void (*)())(dlsym(handle, "entryPoint"));
        if (!entryPoint) {
            std::cerr << "Error: " << dlerror() << std::endl;
            dlclose(handle);
            return 84;
        }

        entryPoint();
        dlclose(handle);

        return 0;
    }
}
