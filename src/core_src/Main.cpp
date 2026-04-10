/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Main
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"
#include "GameData.hpp"
#include "ArcadeEvents.hpp"
#include "Core.hpp"
#include <iostream>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string>

namespace arcade {
    Core::Core(const std::string &libpath) {
        _lib_path = libpath;
        _guiLoader = std::make_unique<DLLoader>(libpath);
        auto getType = _guiLoader->getSymbol<LibType()>("getType");
        if (!getType || getType() != LibType::GRAPHICAL) {
            throw std::runtime_error(
                "Error: '" + libpath + "' not a graphical library"
            );
        }
        _events.key.push_back(Undefined);
        _events.x = 0;
        _events.y = 0;
        _guiClass = std::unique_ptr<IDisplayModule>(_guiLoader->getInstance<IDisplayModule>());
        _gameData.bitmap = init_bit_map(120, 67);
        _game_path = "./lib/arcade_menu.so";
        _gameLoader = std::make_unique<DLLoader>("./lib/arcade_menu.so");
        _gameClass = std::unique_ptr<IGameModule>(_gameLoader->getInstance<IGameModule>());
    }
}

int main(int ac, char **av) {

    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <graphical_library.so>" << std::endl;
        return 84;
    }

    if (std::strcmp(av[1], "--help") == 0) {
        std::cerr << "help" << std::endl;
        return 0;
    }

    try {
        arcade::Core core(av[1]);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
