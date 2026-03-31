/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Core
*/

#include "core.hpp"
#include "DLLoader.hpp"
#include "bitmap.hpp"


namespace arcade
{
    Core::Core(const std::string &libpath)
    {
        DLLoader guiLoader = DLLoader(libpath);
        _events = {Undefined, 0, 0};

        _guiClass = std::unique_ptr<IDisplayModule>(guiLoader.getInstance<IDisplayModule>());

        _gameData.bitmap = init_bit_map(100, 100);
    }

    void Core::run() {
        while (true) {
            // 1. getEvents
            ArcadeEvent event = _guiClass->getEvents();

            // 2. update
            _gameClass->update(event);

            // 3. getGameData
            _gameData = _gameClass->getGameData();

            // 4. clear
            _guiClass->clear();

            // 5. draw
            _guiClass->draw(_gameData);

            // 6. display
            _guiClass->display();
        }
    }

}