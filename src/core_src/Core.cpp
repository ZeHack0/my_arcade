/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Core
*/

#include "Core.hpp"

namespace arcade
{

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