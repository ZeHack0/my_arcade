/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_ncurses
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include "ArcadeEvents.hpp"
#include <ncurses.h>
#include <map>

namespace arcade {

    static const std::map<int, Key> NCURSES_KEY_MAP = {
        {KEY_UP,    Key::ArrowUp},
        {KEY_DOWN,  Key::ArrowDown},
        {KEY_LEFT,  Key::ArrowLeft},
        {KEY_RIGHT, Key::ArrowRight},
        {'q',       Key::Q},
        {'r',       Key::R},
        {27,        Key::Escape},   // ESC
        {' ',       Key::Space},
        {'\n',      Key::Enter},
    };


    class NcursesModule : public IDisplayModule {
    public:

        NcursesModule() {
            initscr();
            cbreak();
            noecho();
            keypad(stdscr, TRUE);
            nodelay(stdscr, TRUE);
            curs_set(0);

            if (has_colors()) {
                start_color();
                init_pair(1, COLOR_YELLOW, COLOR_BLACK);
                init_pair(2, COLOR_BLACK, COLOR_BLACK);
            }
        }

        ~NcursesModule() {
            endwin();
        }

        ArcadeEvents getEvents() override {
            ArcadeEvents ev{};
            ev.key.push_back(Key::Undefined);
            ev.x = 0;
            ev.y = 0;

            int ch = getch();
            if (ch == ERR)
                return ev;

            auto it = NCURSES_KEY_MAP.find(ch);
            if (it != NCURSES_KEY_MAP.end())
                ev.key.push_back(it->second);

            return ev;
        }

        void clear() override {
            erase();
        }

        void draw(GameData data) override {
            int maxY, maxX;
            getmaxyx(stdscr, maxY, maxX);

            for (auto& [pos, cube] : data.bitmap) {
                int col = static_cast<int>(pos.first);
                int row = static_cast<int>(pos.second);

                if (row >= maxY || col >= maxX)
                    continue;

                bool lit = cube.getred() || cube.getgreen() || cube.getblue();

                if (lit) {
                    attron(COLOR_PAIR(1));
                    mvaddch(row, col, '#');
                    attroff(COLOR_PAIR(1));
                }
            }
        }

        void display() override {
            refresh();
        }
    };


    extern "C" {

        IDisplayModule *getInstance() {
            return new NcursesModule();
        }

        LibType getType() {
            return LibType::GRAPHICAL;
        }

    }

}
