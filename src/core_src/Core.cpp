/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Core
*/

#include "core.hpp"

namespace arcade
{
    void Core::run() {
        while (true) {
            // 1. getEvents
            ArcadeEvent event = _gui->getEvents();

            // 2. update
            _game->update(event);

            // 3. getGameData
            _gameData = _game->getGameData();

            // 4. clear
            _gui->clear();

            // 5. draw
            _gui->draw(_gameData);

            // 6. display
            _gui->display();
        }
    }

}