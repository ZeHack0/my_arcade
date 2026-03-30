/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sdl2
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include "GenericEvent.hpp"
#include <SDL2/SDL.h>
#include <map>

namespace arcade {

    static const std::map<SDL_Keycode, Key> SDL_KEY_MAP = {
        {SDLK_UP,     Key::ArrowUp},
        {SDLK_DOWN,   Key::ArrowDown},
        {SDLK_LEFT,   Key::ArrowLeft},
        {SDLK_RIGHT,  Key::ArrowRight},
        {SDLK_ESCAPE, Key::Escape},
        {SDLK_r,      Key::R},
        {SDLK_q,      Key::Q},
        {SDLK_SPACE,  Key::Space},
    };

    class Sdl2Module : public IDisplayModule {
        public:
            Sdl2Module() {
                SDL_Init(SDL_INIT_VIDEO);
                SDL_CreateWindowAndRenderer(800, 600, 0, &_window, &_renderer);
                SDL_SetWindowTitle(_window, "Arcade - SDL2");
            }

            ~Sdl2Module() {
                SDL_DestroyRenderer(_renderer);
                SDL_DestroyWindow(_window);
                SDL_Quit();
            }

            ArcadeEvent getEvents() override {
                ArcadeEvent ev{};
                ev.key = Key::Undefined;

                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT)
                        ev.key = Key::Escape;
                    if (event.type == SDL_KEYDOWN) {
                        auto it = SDL_KEY_MAP.find(event.key.keysym.sym);
                        if (it != SDL_KEY_MAP.end())
                            ev.key = it->second;
                    }
                }
                return ev;
            }

            void clear() override {
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                SDL_RenderClear(_renderer);
            }

            void draw(GameData data) override {
                const int CELL = 20;

                for (auto &[pos, cube] : data.bitmap) {
                    if (!cube.getred() && !cube.getgreen() && !cube.getblue())
                        continue;
                    SDL_SetRenderDrawColor(_renderer,
                        cube.getred(), cube.getgreen(), cube.getblue(), 255);
                    SDL_Rect rect{
                        static_cast<int>(pos.first)  * CELL,
                        static_cast<int>(pos.second) * CELL,
                        CELL - 1, CELL - 1
                    };
                    SDL_RenderFillRect(_renderer, &rect);
                }
            }

            void display() override {
                SDL_RenderPresent(_renderer);
            }

        private:
            SDL_Window   *_window   = nullptr;
            SDL_Renderer *_renderer = nullptr;
    };

    extern "C" {
        IDisplayModule *instance() { return new Sdl2Module(); }
        LibType getType()          { return LibType::GRAPHICAL; }
    }

}