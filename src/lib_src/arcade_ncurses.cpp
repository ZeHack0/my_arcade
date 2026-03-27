/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_ncurses
*/

#include "Arcade.hpp"
#include <iostream>
#include <ncurses.h>

namespace arcade
{
    extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[libtest]: Loading test library..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[libtest]: closing test library..." << std::endl;
        }

        LibType getType() {
            return LibType::GRAPHICAL;
        }

        WINDOW *create_newwin(int height, int width, int starty, int startx)
        {	WINDOW *local_win;

            local_win = newwin(height, width, starty, startx);
            box(local_win, 0 , 0);
            wrefresh(local_win);

            return local_win;
        }

        void destroy_win(WINDOW *local_win)
        {
            wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
            wrefresh(local_win);
            delwin(local_win);
        }

        void entryPoint() {
            WINDOW *window;
            int startx, starty, width, height;
            int ch;

            initscr();
            cbreak();

            keypad(stdscr, TRUE);

            height = 3;
            width = 10;
            starty = (LINES - height) / 2;
            startx = (COLS - width) / 2;

            printw("Press \"ESC\" to exit");
            refresh();
            window = create_newwin(height, width, starty, startx);

            while((ch = getch()) != KEY_F(1)) {
                switch(ch) {
                    case KEY_LEFT:
                        destroy_win(window);
                        window = create_newwin(height, width, starty,--startx);
                        break;
                case KEY_RIGHT:
                    destroy_win(window);
                    window = create_newwin(height, width, starty,++startx);
                    break;
                case KEY_UP:
                    destroy_win(window);
                    window = create_newwin(height, width, --starty,startx);
                    break;
                case KEY_DOWN:
                    destroy_win(window);
                    window = create_newwin(height, width, ++starty,startx);
                    break;
                }
            }
            endwin();
        }

    }
}