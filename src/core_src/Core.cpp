/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Core
*/

#include "Core.hpp"

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
            ArcadeEvent event = _guiClass->getEvents();

            if (event.key == Key::Escape)
                break;

            _gameClass->update(event);

            GameData data = _gameClass->getGameData();

            _guiClass->clear();
            _guiClass->draw(data);
            _guiClass->display();
        }
    }

}