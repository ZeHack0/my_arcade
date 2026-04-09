/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <ncurses.h>
namespace arcade
{

    void Core::run() {
        ArcadeEvents event;
        while (true) {
            event = _guiClass->getEvents();
            for (Key n : event.key) {
                if (n == Key::Escape) {
                    endwin();
                    return;
                }
            }
            if (_username.empty())
                _username = _guiClass->getUsername();
            _gameClass->update(event);
            GameData data = _gameClass->getGameData();
            _guiClass->clear();
            _guiClass->draw(data);
            _guiClass->display();
            check_event(event);
        }
    }

}