/*
 EPITECH PROJECT, 2026
 arcade
 File description:
 lib_test
*/

#include "Arcade.hpp"
#include "GenericEvent.hpp"
#include "bitmap.hpp"
#include "core.hpp"
#include <iostream>

namespace arcade {
    /*extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[gametest]: Loading test game..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[gametest]: closing test game..." << std::endl;
        }
*/
        static std::size_t player_y = map_x / 2;
        static std::size_t player_x = map_y / 2;

        void init(AGlobal& global) {
            auto& map = global.getMap();

            for (std::size_t y = 0; y < global.get_y(); y++)
                for (std::size_t x = 0; x < global.get_x(); x++)
                    global.ModifyMap(std::pair(player_x, player_y), 0, 0, 0);
            player_x = global.get_x() / 2;
            player_y = global.get_y() / 2;
            global.ModifyMap(std::pair(player_x, player_y), 255, 0, 0);
        }

        void update(AGlobal& global, struct ArcadeEvent ev) {
            auto& map = global.getMap();

            global.ModifyMap(std::pair(player_x, player_y), 0, 0, 0);

            if (ev.key == Key::ArrowUp && player_y > 0)
                player_y--;
            if (ev.key == Key::ArrowDown && player_y < global.get_y() - 1)
                player_y++;
            if (ev.key == Key::ArrowLeft && player_x > 0)
                player_x--;
            if (ev.key == Key::ArrowRight && player_x < global.get_x() - 1)
                player_x++;

            global.ModifyMap(std::pair(player_x, player_y), 255, 0, 0);
        }
        LibType getType() {
            return LibType::GAME;
        }

    }
/*}*/