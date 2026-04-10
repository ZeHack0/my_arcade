/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** arcade_sdl2
*/

#include "Arcade.hpp"
#include "IDisplayModule.hpp"
#include "GameData.hpp"
#include "ArcadeEvents.hpp"
#include <map>

#include "Core.hpp"
#include "Arcade.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

    {SDLK_KP_PLUS, arcade::Key::NumpadAdd},
    {SDLK_KP_MINUS, arcade::Key::NumpadSubtract},
    {SDLK_KP_MULTIPLY, arcade::Key::NumpadMultiply},
    {SDLK_KP_DIVIDE, arcade::Key::NumpadDivide},

    {SDLK_ESCAPE, arcade::Key::Escape},
    {SDLK_LCTRL, arcade::Key::LeftCtrl},
    {SDLK_LSHIFT, arcade::Key::LeftShift},
    {SDLK_LALT, arcade::Key::LeftAlt},
    {SDLK_RCTRL, arcade::Key::RightCtrl},
    {SDLK_RSHIFT, arcade::Key::RightShift},
    {SDLK_RALT, arcade::Key::RightAlt},

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

    {SDLK_LEFT, arcade::Key::ArrowLeft},
    {SDLK_RIGHT, arcade::Key::ArrowRight},
    {SDLK_UP, arcade::Key::ArrowUp},
    {SDLK_DOWN, arcade::Key::ArrowDown},
};

namespace arcade {

    class Sdl2Module : public IDisplayModule {

        public:
            Sdl2Module() {
                SDL_Init(SDL_INIT_VIDEO);
                SDL_CreateWindowAndRenderer(640, 480, 0, &_window, &_renderer);
                SDL_SetWindowTitle(_window, "Arcade - SDL2");
                SDL_SetWindowFullscreen(_window, 1);
            }

            ~Sdl2Module() {
                SDL_DestroyRenderer(_renderer);
                SDL_DestroyWindow(_window);
                SDL_Quit();
            }

            ArcadeEvents getEvents() override {
                SDL_Event event;
                ArcadeEvents totalEv;


                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        // handle quit if necessary, or just rely on core doing it
                    }
                }

                const Uint8* state = SDL_GetKeyboardState(NULL);

                for (auto const& [sdlKey, arcKey] : keyMap) {
                    SDL_Scancode scancode = SDL_GetScancodeFromKey(sdlKey);
                    if (state[scancode]) {
                        totalEv.key.push_back(arcKey);
                    }
                }

                int x, y;
                Uint32 mouseState = SDL_GetMouseState(&x, &y);

                if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
                    totalEv.key.push_back(LeftClick);
                if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
                    totalEv.key.push_back(RightClick);
                if (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE))
                    totalEv.key.push_back(MiddleClick);

                totalEv.x = x;
                totalEv.y = y;

                return totalEv;
            }

            void clear() override {
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                SDL_RenderClear(_renderer);
            }

            std::string getUsername() override
            {

                bool end = false;
                TTF_Init();
                std::string username;
                std::string output;
                SDL_StartTextInput();
                int width = 0;
                int height = 0;
                SDL_Event ev;
                TTF_Font *pfont = TTF_OpenFont("./assets/DejaVuSans.ttf", 24);

                while (!end) {
                    while(SDL_PollEvent(&ev)) {
                        if (ev.type == SDL_QUIT) {
                            end = true;
                        }
                        if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN) {
                            if (ev.type == SDL_KEYDOWN) {
                                if (ev.key.keysym.sym == SDLK_BACKSPACE && username.length() > 0)
                                    username.pop_back();
                                if (ev.key.keysym.sym == SDLK_RETURN)
                                    end = true;
                            }
                            else if (ev.type == SDL_TEXTINPUT)
                                username += ev.text.text;
                        }
                    }
                    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                    SDL_RenderClear(_renderer);
                    SDL_Color couleur = {255, 255, 255, 255};
                    output = "Enter Username :" + username;
                    SDL_Surface *PSurfTxt = TTF_RenderText_Blended(pfont, output.c_str(), couleur);
                    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(_renderer, PSurfTxt);
                    width = PSurfTxt->w;
                    height = PSurfTxt->h;
                    SDL_FreeSurface(PSurfTxt);
                    SDL_Rect rect{20, 20, width, height};
                    SDL_RenderCopy(_renderer, pTexture, nullptr, &rect);
                    SDL_DestroyTexture(pTexture);
                    SDL_RenderPresent(_renderer);
                    SDL_Delay(RENDER);
                }
                    TTF_CloseFont(pfont);
                    SDL_StopTextInput();
                    return username;
            }

            void draw(GameData data) override {
                const int CELL = 16;

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
                for (auto it : data.text) {
                    TTF_Init();
                    TTF_Font *pfont = TTF_OpenFont(it.PathPolicy.c_str(), it.TextSize);
                    SDL_Color couleur = {(Uint8)it.color.R, (Uint8)it.color.G, (Uint8)it.color.B, 0};
                    SDL_Surface * PSurfTxt = TTF_RenderText_Blended(pfont, it.text.c_str(), couleur);
                    TTF_CloseFont(pfont);
                    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(_renderer, PSurfTxt);
                    SDL_FreeSurface(PSurfTxt);
                    SDL_Rect rect {it.BeginPos.first, it.BeginPos.second, PSurfTxt->w, PSurfTxt->h};
                    SDL_RenderCopy(_renderer, pTexture, nullptr, &rect);
                }
            }

            void display() override {
                SDL_RenderPresent(_renderer);
                SDL_Delay(RENDER);
            }

        private:
            SDL_Window   *_window;
            SDL_Renderer *_renderer;
            //bool _isfullscreen;
    };

    extern "C" {

        __attribute__((constructor)) void load_lib() {
            std::cout << "[arcade_sdl2]: Loading SDL2 library..." << std::endl;
        }

        __attribute__((destructor)) void unload_lib() {
            std::cout << "[arcade_sdl2]: closing SDL2 library..." << std::endl;
        }

        IDisplayModule *getInstance() {
            return new Sdl2Module();
        }

        LibType getType() {
            return LibType::GRAPHICAL;
        }
    }

}