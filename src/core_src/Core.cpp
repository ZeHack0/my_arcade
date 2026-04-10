/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <ncurses.h>
#include <time.h>

namespace arcade
{

    void Core::run() {
        clock_t begin = clock();
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
            check_event(event);
            _gameClass->update(event, begin);
            GameData data = _gameClass->getGameData();
            if (data.GameOver == true)
                back_to_menu();
            _guiClass->clear();
            _guiClass->draw(data);
            _guiClass->display();
        }
    }

}