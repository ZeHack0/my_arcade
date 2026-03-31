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
            ArcadeEvent event = _gui->getEvents();

            if (event.key == Key::Escape)
                break;

            _game->update(event);

            GameData data = _game->getGameData();

            _gui->clear();
            _gui->draw(data);
            _gui->display();
        }
    }

}