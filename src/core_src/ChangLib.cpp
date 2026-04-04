/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** core
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
#include <filesystem>

namespace arcade {
    void Core::change_game(const std::string &path)
    {
        _game_path = path;
        _gameClass.reset();
        _gameLoader.reset();
        _gameLoader = std::make_unique<DLLoader>(path);
        auto getType = _gameLoader->getSymbol<LibType()>("getType");
        if (!getType || getType() != LibType::GAME)
            throw std::runtime_error("Error: '" + path + "' not a game");
        _gameClass = std::unique_ptr<IGameModule>(_gameLoader->getInstance<IGameModule>());
    }

    void Core::change_lib(const std::string &path)
    {
        std::cout << "path = " << path << std::endl;
        _lib_path = path;
        _guiClass.reset();
        _guiLoader.reset();
        _guiLoader = std::make_unique<DLLoader>(path);
        auto getType = _guiLoader->getSymbol<LibType()>("getType");
        if (!getType || getType() != LibType::GRAPHICAL)
            throw std::runtime_error("Error: '" + path + "' not a graphical library");
        _guiClass = std::unique_ptr<IDisplayModule>(_guiLoader->getInstance<IDisplayModule>());
    }

    std::string get_next_game(std::string &current_game_path)
    {
        std::vector<std::string> games;
        for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
            std::string path = entry.path().string();
            DLLoader loader(path);
            auto getType = loader.getSymbol<LibType()>("getType");
            if (getType && getType() == LibType::GAME)
                games.push_back(path);
        }
        auto it = std::find(games.begin(), games.end(), current_game_path);
        if (it == games.end() || std::next(it) == games.end()) {
            return games[0];
        }
        return *std::next(it);
    }

    std::string get_next_lib(std::string &current_lib_path)
    {
        std::vector<std::string> lib;
        for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
            std::string path = entry.path().string();
            DLLoader loader(path);
            auto getType = loader.getSymbol<LibType()>("getType");
            if (getType && getType() == LibType::GRAPHICAL)
                lib.push_back(path);
        }
        auto it = std::find(lib.begin(), lib.end(), current_lib_path);
        if (it == lib.end() || std::next(it) == lib.end()) {
            return lib[0];
        }
        return *std::next(it);
    }

    void Core::back_to_menu()
    {
        std::string menu_path = "./lib/arcade_menu.so";
        _game_path = menu_path;
        _gameClass.reset();
        _gameLoader.reset();
        _gameLoader = std::make_unique<DLLoader>(menu_path);
        _gameClass = std::unique_ptr<IGameModule>(_gameLoader->getInstance<IGameModule>());
    }

    void Core::restart_game()
    {
        change_game(_game_path);
    }

    void Core::check_event(ArcadeEvents event)
    {
        for (Key n : event.key) {
            if (n == Num2)
                change_game(get_next_game(_game_path));
            if (n == Num3)
                change_lib(get_next_lib(_lib_path));
            if (n == Num1)
                back_to_menu();
            if (n == R)
                restart_game();
        }
    }
}
