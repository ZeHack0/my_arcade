/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_ncurses
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include "GenericEvent.hpp"
#include <ncurses.h>
#include <map>

namespace arcade {

// ─── table de conversion touches ncurses → arcade::Key ───────────────────────
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

// ─── classe principale ────────────────────────────────────────────────────────
class NcursesModule : public IDisplayModule {
public:

    NcursesModule() {
        initscr();             // démarre ncurses
        cbreak();              // pas besoin d'appuyer sur Entrée
        noecho();              // n'affiche pas les touches tapées
        keypad(stdscr, TRUE);  // active les touches spéciales (flèches, F1…)
        nodelay(stdscr, TRUE); // getch() non-bloquant : retourne ERR si rien
        curs_set(0);           // cache le curseur

        // Initialise les couleurs si le terminal le supporte
        if (has_colors()) {
            start_color();
            // pair 1 = blanc sur noir (cellule allumée)
            init_pair(1, COLOR_YELLOW, COLOR_BLACK);
            // pair 2 = noir sur noir  (cellule éteinte)
            init_pair(2, COLOR_BLACK, COLOR_BLACK);
        }
    }

    ~NcursesModule() {
        endwin(); // restitue le terminal à son état normal
    }

    // ── getEvents ─────────────────────────────────────────────────────────────
    // Appelé une fois par frame. Retourne l'événement courant (ou Undefined).
    ArcadeEvent getEvents() override {
        ArcadeEvent ev{};
        ev.key = Key::Undefined;
        ev.x = 0;
        ev.y = 0;

        int ch = getch(); // non-bloquant grâce à nodelay
        if (ch == ERR)
            return ev;   // aucune touche appuyée

        auto it = NCURSES_KEY_MAP.find(ch);
        if (it != NCURSES_KEY_MAP.end())
            ev.key = it->second;

        return ev;
    }

    // ── clear ─────────────────────────────────────────────────────────────────
    // Efface l'écran logique (pas encore visible).
    void clear() override {
        erase(); // plus rapide que clear(), évite le flash
    }

    // ── draw ──────────────────────────────────────────────────────────────────
    // Parcourt la bitmap et affiche chaque cellule non-noire.
    void draw(GameData data) override {
        int maxY, maxX;
        getmaxyx(stdscr, maxY, maxX); // taille réelle du terminal

        for (auto& [pos, cube] : data.bitmap) {
            int col = static_cast<int>(pos.first);
            int row = static_cast<int>(pos.second);

            // Ne dessine pas hors de l'écran
            if (row >= maxY || col >= maxX)
                continue;

            bool lit = cube.getred() || cube.getgreen() || cube.getblue();

            if (lit) {
                attron(COLOR_PAIR(1));
                mvaddch(row, col, '#'); // caractère "pixel allumé"
                attroff(COLOR_PAIR(1));
            }
            // Les cellules noires : on ne dessine rien (erase() a déjà tout vidé)
        }
    }

    // ── display ───────────────────────────────────────────────────────────────
    // Envoie le buffer logique à l'écran (double buffering ncurses).
    void display() override {
        refresh();
    }
};

// ─── point d'entrée chargé via dlsym ─────────────────────────────────────────
extern "C" {

    IDisplayModule *instance() {
        return new NcursesModule();
    }

    LibType getType() {
        return LibType::GRAPHICAL;
    }

}

}
