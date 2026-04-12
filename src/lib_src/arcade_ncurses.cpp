/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_ncurses
*/

#include <filesystem>

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include <iostream>
#include "ArcadeEvents.hpp"
#include <ncurses.h>
#include <curses.h>
#include <map>

namespace arcade {

    static const std::map<int, arcade::Key> keyMap = {
    {'a', arcade::Key::A},
    {'b', arcade::Key::B},
    {'c', arcade::Key::C},
    {'d', arcade::Key::D},
    {'e', arcade::Key::E},
    {'f', arcade::Key::F},
    {'g', arcade::Key::G},
    {'h', arcade::Key::H},
    {'i', arcade::Key::I},
    {'j', arcade::Key::J},
    {'k', arcade::Key::K},
    {'l', arcade::Key::L},
    {'m', arcade::Key::M},
    {'n', arcade::Key::N},
    {'o', arcade::Key::O},
    {'p', arcade::Key::P},
    {'q', arcade::Key::Q},
    {'r', arcade::Key::R},
    {'s', arcade::Key::S},
    {'t', arcade::Key::T},
    {'u', arcade::Key::U},
    {'v', arcade::Key::V},
    {'w', arcade::Key::W},
    {'x', arcade::Key::X},
    {'y', arcade::Key::Y},
    {'z', arcade::Key::Z},
    {'0', arcade::Key::Num0},
    {'1', arcade::Key::Num1},
    {'2', arcade::Key::Num2},
    {'3', arcade::Key::Num3},
    {'4', arcade::Key::Num4},
    {'5', arcade::Key::Num5},
    {'6', arcade::Key::Num6},
    {'7', arcade::Key::Num7},
    {'8', arcade::Key::Num8},
    {'9', arcade::Key::Num9},
    {'+',        arcade::Key::NumpadAdd},
    {'-',        arcade::Key::NumpadSubtract},
    {'*',        arcade::Key::NumpadMultiply},
    {'/',        arcade::Key::NumpadDivide},
    {27,         arcade::Key::Escape},
    {'\x01',     arcade::Key::LeftCtrl},
    {KEY_SLEFT,  arcade::Key::LeftShift},
    {'\x1b',     arcade::Key::LeftAlt},
    {'\x01',     arcade::Key::RightCtrl},
    {KEY_SRIGHT, arcade::Key::RightShift},
    {'\x1b',     arcade::Key::RightAlt},
    {'[',        arcade::Key::LeftBracket},
    {']',        arcade::Key::RightBracket},
    {';',        arcade::Key::Semicolon},
    {',',        arcade::Key::Comma},
    {'.',        arcade::Key::Period},
    {'\'',       arcade::Key::Apostrophe},
    {'/',        arcade::Key::Slash},
    {'\\',       arcade::Key::Backslash},
    {'`',        arcade::Key::Grave},
    {'=',        arcade::Key::Equal},
    {'-',        arcade::Key::Minus},
    {' ',        arcade::Key::Space},
    {'\n',       arcade::Key::Enter},
    {'\r',       arcade::Key::Enter},
    {KEY_BACKSPACE, arcade::Key::Backspace},
    {'\t',       arcade::Key::Tab},
    {KEY_PPAGE,  arcade::Key::PageUp},
    {KEY_NPAGE,  arcade::Key::PageDown},
    {KEY_LEFT,   arcade::Key::ArrowLeft},
    {KEY_RIGHT,  arcade::Key::ArrowRight},
    {KEY_UP,     arcade::Key::ArrowUp},
    {KEY_DOWN,   arcade::Key::ArrowDown},
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

        ~NcursesModule() override
        {
            endwin();
        }

        ArcadeEvents getEvents() override {
            ArcadeEvents ev{};
            ev.x = 0;
            ev.y = 0;

            int ch;
            while ((ch = getch()) != ERR) {
                auto it = keyMap.find(ch);
                if (it != keyMap.end()) {
                    ev.key.push_back(it->second);
                }
            }

            return ev;
        }

        void clear() override {
            erase();
        }

        std::string getUsername() override
        {
            std::string username;

            refresh();
            int ch;
            std::string output = "Enter Username: ";
            bool end = false;
            mvprintw(20, 20, "%s",  output.c_str());
            while (!end) {
                while ((ch = getch()) != ERR) {
                    username.push_back(ch);
                    output.push_back(ch);
                    mvprintw(20, 20, "%s",  output.c_str());
                    if (ch == '\n' || ch == '\r') {
                        return username;
                    }
                }
        }
            return username;
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

            int Ytext;
            int XText;
            getmaxyx(stdscr, Ytext, XText);

            for (auto it : data.text) {
                int col = (it.BeginPos.first  * XText) / 1920;
                int row = (it.BeginPos.second * Ytext) / 1080;

                if (row >= Ytext || col >= XText || row < 0 || col < 0)
                    continue;
                mvprintw(row, col, "%s", it.text.c_str());
            }
        }

        void display() override {
            refresh();
            napms(RENDER);
        }
    };


    extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[arcade_ncurses]: Loading ncurses library..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[arcade_ncurses]: closing ncurses library..." << std::endl;
        }

        IDisplayModule *getInstance() {
            return new NcursesModule();
        }

        LibType getType() {
            return LibType::GRAPHICAL;
        }

    }

}
