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

#include "GenericEvent.hpp"
#include "Core.hpp"
#include "Arcade.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const std::map<SDL_Keycode, arcade::Key> keyMap = {
    {SDLK_a, arcade::Key::A},
    {SDLK_b, arcade::Key::B},
    {SDLK_c, arcade::Key::C},
    {SDLK_d, arcade::Key::D},
    {SDLK_e, arcade::Key::E},
    {SDLK_f, arcade::Key::F},
    {SDLK_g, arcade::Key::G},
    {SDLK_h, arcade::Key::H},
    {SDLK_i, arcade::Key::I},
    {SDLK_j, arcade::Key::J},
    {SDLK_k, arcade::Key::K},
    {SDLK_l, arcade::Key::L},
    {SDLK_m, arcade::Key::M},
    {SDLK_n, arcade::Key::N},
    {SDLK_o, arcade::Key::O},
    {SDLK_p, arcade::Key::P},
    {SDLK_q, arcade::Key::Q},
    {SDLK_r, arcade::Key::R},
    {SDLK_s, arcade::Key::S},
    {SDLK_t, arcade::Key::T},
    {SDLK_u, arcade::Key::U},
    {SDLK_v, arcade::Key::V},
    {SDLK_w, arcade::Key::W},
    {SDLK_x, arcade::Key::X},
    {SDLK_y, arcade::Key::Y},
    {SDLK_z, arcade::Key::Z},

    {SDLK_0, arcade::Key::Num0},
    {SDLK_1, arcade::Key::Num1},
    {SDLK_2, arcade::Key::Num2},
    {SDLK_3, arcade::Key::Num3},
    {SDLK_4, arcade::Key::Num4},
    {SDLK_5, arcade::Key::Num5},
    {SDLK_6, arcade::Key::Num6},
    {SDLK_7, arcade::Key::Num7},
    {SDLK_8, arcade::Key::Num8},
    {SDLK_9, arcade::Key::Num9},
    {SDLK_KP_0, arcade::Key::Numpad0},
    {SDLK_KP_1, arcade::Key::Numpad1},
    {SDLK_KP_2, arcade::Key::Numpad2},
    {SDLK_KP_3, arcade::Key::Numpad3},
    {SDLK_KP_4, arcade::Key::Numpad4},
    {SDLK_KP_5, arcade::Key::Numpad5},
    {SDLK_KP_6, arcade::Key::Numpad6},
    {SDLK_KP_7, arcade::Key::Numpad7},
    {SDLK_KP_8, arcade::Key::Numpad8},
    {SDLK_KP_9, arcade::Key::Numpad9},

    {SDLK_KP_PLUS, arcade::Key::NumpadAdd},
    {SDLK_KP_MINUS, arcade::Key::NumpadSubtract},
    {SDLK_KP_MULTIPLY, arcade::Key::NumpadMultiply},
    {SDLK_KP_DIVIDE, arcade::Key::NumpadDivide},

    {SDLK_ESCAPE, arcade::Key::Escape},
    {SDLK_LCTRL, arcade::Key::LeftCtrl},
    {SDLK_LSHIFT, arcade::Key::LeftShift},
    {SDLK_LALT, arcade::Key::LeftAlt},
    {SDLK_LGUI, arcade::Key::LeftSuper},
    {SDLK_RCTRL, arcade::Key::RightCtrl},
    {SDLK_RSHIFT, arcade::Key::RightShift},
    {SDLK_RALT, arcade::Key::RightAlt},
    {SDLK_RGUI, arcade::Key::RightSuper},

    {SDLK_LEFTBRACKET, arcade::Key::LeftBracket},
    {SDLK_RIGHTBRACKET, arcade::Key::RightBracket},
    {SDLK_SEMICOLON, arcade::Key::Semicolon},
    {SDLK_COMMA, arcade::Key::Comma},
    {SDLK_PERIOD, arcade::Key::Period},
    {SDLK_QUOTE, arcade::Key::Apostrophe},
    {SDLK_SLASH, arcade::Key::Slash},
    {SDLK_BACKSLASH, arcade::Key::Backslash},
    {SDLK_BACKQUOTE, arcade::Key::Grave},
    {SDLK_EQUALS, arcade::Key::Equal},
    {SDLK_MINUS, arcade::Key::Minus},

    {SDLK_SPACE, arcade::Key::Space},
    {SDLK_RETURN, arcade::Key::Enter},
    {SDLK_BACKSPACE, arcade::Key::Backspace},
    {SDLK_TAB, arcade::Key::Tab},

    {SDLK_PAGEUP, arcade::Key::PageUp},
    {SDLK_PAGEDOWN, arcade::Key::PageDown},
    {SDLK_END, arcade::Key::End},
    {SDLK_HOME, arcade::Key::Home},
    {SDLK_INSERT, arcade::Key::Insert},

    {SDLK_LEFT, arcade::Key::ArrowLeft},
    {SDLK_RIGHT, arcade::Key::ArrowRight},
    {SDLK_UP, arcade::Key::ArrowUp},
    {SDLK_DOWN, arcade::Key::ArrowDown},

    {SDLK_F1, arcade::Key::F1},
    {SDLK_F2, arcade::Key::F2},
    {SDLK_F3, arcade::Key::F3},
    {SDLK_F4, arcade::Key::F4},
    {SDLK_F5, arcade::Key::F5},
    {SDLK_F6, arcade::Key::F6},
    {SDLK_F7, arcade::Key::F7},
    {SDLK_F8, arcade::Key::F8},
    {SDLK_F9, arcade::Key::F9},
    {SDLK_F10, arcade::Key::F10},
    {SDLK_F11, arcade::Key::F11},
    {SDLK_F12, arcade::Key::F12}
};




namespace arcade {
    arcade::ArcadeEvent SDLEvent(SDL_Event e)
{
    arcade::ArcadeEvent ev;
    int x = 0;
    int y = 0;

    ev.key = arcade::Key::Undefined;
    if (e.type == SDL_KEYDOWN) {
        auto it = keyMap.find(e.key.keysym.sym);
        if (it != keyMap.end())
            ev.key = it->second;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (SDL_BUTTON_LEFT == e.button.button)
            ev.key = arcade::Key::LeftClick;
        if (SDL_BUTTON_RIGHT == e.button.button)
            ev.key = arcade::Key::RightClick;
        if (SDL_BUTTON_MIDDLE == e.button.button)
            ev.key = arcade::Key::MiddleClick;
    }
    SDL_GetMouseState(&x, &y);
    ev.x = x;
    ev.y = y;
    return ev;
}

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
                    ev = SDLEvent(event);
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