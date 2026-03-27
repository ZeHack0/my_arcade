/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sfml
*/

#include "Arcade.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace arcade
{
    extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[arcade_sdl2]: Loading SDL2 library..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[arcade_sdl2]: closing SDL2 library..." << std::endl;
        }

        LibType getType() {
            return LibType::GRAPHICAL;
        }

        void entryPoint() {
            SDL_Window* window = nullptr;
            SDL_Renderer* renderer = nullptr;

            if (SDL_Init(SDL_INIT_VIDEO) < 0)
                return;
            SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
            SDL_RenderSetScale(renderer, 1, 1);

            bool running = true;
            SDL_Event event;

            while (running)
            {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT)
                        running = false;
                }

                SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
            }
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

    }
}
