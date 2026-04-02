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
        ArcadeEvent event;
        while (event.key != Key::Escape) {
            event = _guiClass->getEvents();
            _gameClass->update(event);

            GameData data = _gameClass->getGameData();

            _guiClass->clear();
            _guiClass->draw(data);
            _guiClass->display();
        }
    }

}