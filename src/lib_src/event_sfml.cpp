#include "mapkey.hpp"
#include "core.hpp"
#include "Arcade.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

static const std::map<sf::Keyboard::Key, arcade::Key> keyMap = {
    {sf::Keyboard::A, arcade::Key::A},
    {sf::Keyboard::B, arcade::Key::B},
    {sf::Keyboard::C, arcade::Key::C},
    {sf::Keyboard::D, arcade::Key::D},
    {sf::Keyboard::E, arcade::Key::E},
    {sf::Keyboard::F, arcade::Key::F},
    {sf::Keyboard::G, arcade::Key::G},
    {sf::Keyboard::H, arcade::Key::H},
    {sf::Keyboard::I, arcade::Key::I},
    {sf::Keyboard::J, arcade::Key::J},
    {sf::Keyboard::K, arcade::Key::K},
    {sf::Keyboard::L, arcade::Key::L},
    {sf::Keyboard::M, arcade::Key::M},
    {sf::Keyboard::N, arcade::Key::N},
    {sf::Keyboard::O, arcade::Key::O},
    {sf::Keyboard::P, arcade::Key::P},
    {sf::Keyboard::Q, arcade::Key::Q},
    {sf::Keyboard::R, arcade::Key::R},
    {sf::Keyboard::S, arcade::Key::S},
    {sf::Keyboard::T, arcade::Key::T},
    {sf::Keyboard::U, arcade::Key::U},
    {sf::Keyboard::V, arcade::Key::V},
    {sf::Keyboard::W, arcade::Key::W},
    {sf::Keyboard::X, arcade::Key::X},
    {sf::Keyboard::Y, arcade::Key::Y},
    {sf::Keyboard::Z, arcade::Key::Z},

    {sf::Keyboard::Num0, arcade::Key::Num0},
    {sf::Keyboard::Num1, arcade::Key::Num1},
    {sf::Keyboard::Num2, arcade::Key::Num2},
    {sf::Keyboard::Num3, arcade::Key::Num3},
    {sf::Keyboard::Num4, arcade::Key::Num4},
    {sf::Keyboard::Num5, arcade::Key::Num5},
    {sf::Keyboard::Num6, arcade::Key::Num6},
    {sf::Keyboard::Num7, arcade::Key::Num7},
    {sf::Keyboard::Num8, arcade::Key::Num8},
    {sf::Keyboard::Num9, arcade::Key::Num9},
    {sf::Keyboard::Numpad0, arcade::Key::Numpad0},
    {sf::Keyboard::Numpad1, arcade::Key::Numpad1},
    {sf::Keyboard::Numpad2, arcade::Key::Numpad2},
    {sf::Keyboard::Numpad3, arcade::Key::Numpad3},
    {sf::Keyboard::Numpad4, arcade::Key::Numpad4},
    {sf::Keyboard::Numpad5, arcade::Key::Numpad5},
    {sf::Keyboard::Numpad6, arcade::Key::Numpad6},
    {sf::Keyboard::Numpad7, arcade::Key::Numpad7},
    {sf::Keyboard::Numpad8, arcade::Key::Numpad8},
    {sf::Keyboard::Numpad9, arcade::Key::Numpad9},

    {sf::Keyboard::Add,      arcade::Key::NumpadAdd},
    {sf::Keyboard::Subtract, arcade::Key::NumpadSubtract},
    {sf::Keyboard::Multiply, arcade::Key::NumpadMultiply},
    {sf::Keyboard::Divide,   arcade::Key::NumpadDivide},

    {sf::Keyboard::Escape,   arcade::Key::Escape},
    {sf::Keyboard::LControl, arcade::Key::LeftCtrl},
    {sf::Keyboard::LShift,   arcade::Key::LeftShift},
    {sf::Keyboard::LAlt,     arcade::Key::LeftAlt},
    {sf::Keyboard::LSystem,  arcade::Key::LeftSuper},
    {sf::Keyboard::RControl, arcade::Key::RightCtrl},
    {sf::Keyboard::RShift,   arcade::Key::RightShift},
    {sf::Keyboard::RAlt,     arcade::Key::RightAlt},
    {sf::Keyboard::RSystem,  arcade::Key::RightSuper},
    {sf::Keyboard::LBracket, arcade::Key::LeftBracket},
    {sf::Keyboard::RBracket, arcade::Key::RightBracket},
    {sf::Keyboard::SemiColon, arcade::Key::Semicolon},
    {sf::Keyboard::Comma, arcade::Key::Comma},
    {sf::Keyboard::Period, arcade::Key::Period},
    {sf::Keyboard::Quote, arcade::Key::Apostrophe},
    {sf::Keyboard::Slash, arcade::Key::Slash},
    {sf::Keyboard::BackSlash, arcade::Key::Backslash},
    {sf::Keyboard::Tilde, arcade::Key::Grave},
    {sf::Keyboard::Equal, arcade::Key::Equal},
    {sf::Keyboard::Dash, arcade::Key::Minus},

    {sf::Keyboard::Space, arcade::Key::Space},
    {sf::Keyboard::Return, arcade::Key::Enter},
    {sf::Keyboard::BackSpace, arcade::Key::Backspace},
    {sf::Keyboard::Tab, arcade::Key::Tab},
    {sf::Keyboard::PageUp, arcade::Key::PageUp},
    {sf::Keyboard::PageDown, arcade::Key::PageDown},
    {sf::Keyboard::End, arcade::Key::End},
    {sf::Keyboard::Home, arcade::Key::Home},
    {sf::Keyboard::Insert, arcade::Key::Insert},

    {sf::Keyboard::Left, arcade::Key::ArrowLeft},
    {sf::Keyboard::Right, arcade::Key::ArrowRight},
    {sf::Keyboard::Up, arcade::Key::ArrowUp},
    {sf::Keyboard::Down, arcade::Key::ArrowDown},

    {sf::Keyboard::F1, arcade::Key::F1},
    {sf::Keyboard::F2, arcade::Key::F1},
    {sf::Keyboard::F3, arcade::Key::F1},
    {sf::Keyboard::F4, arcade::Key::F1},
    {sf::Keyboard::F5, arcade::Key::F1},
    {sf::Keyboard::F6, arcade::Key::F1},
    {sf::Keyboard::F7, arcade::Key::F1},
    {sf::Keyboard::F8, arcade::Key::F1},
    {sf::Keyboard::F9, arcade::Key::F1},
    {sf::Keyboard::F10, arcade::Key::F10},
    {sf::Keyboard::F11, arcade::Key::F11},
    {sf::Keyboard::F12, arcade::Key::F12}
};

arcade::ArcadeEvent SFMLEvent(sf::Event event)
{
    arcade::ArcadeEvent ev;

    ev.key = arcade::Key::Undefined;
    if (event.type == sf::Event::KeyPressed) {
        auto it = keyMap.find(event.key.code);
        if (it != keyMap.end())
            ev.key = it->second;
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right)
            ev.key = arcade::Key::RightClick;
        if (event.mouseButton.button == sf::Mouse::Left)
            ev.key = arcade::Key::LeftClick;
        if (event.mouseButton.button == sf::Mouse::Middle)
            ev.key = arcade::Key::MiddleClick;
    }
    ev.x = sf::Mouse::getPosition().x;
    ev.y = sf::Mouse::getPosition().y;
    return ev;
}