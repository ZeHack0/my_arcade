/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** mapkey
*/

#pragma once
#include <vector>

namespace arcade {

    enum Key {
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        NumpadAdd, NumpadSubtract, NumpadMultiply, NumpadDivide,
        NumpadDecimal, NumpadEnter, NumLock,
        LeftShift, RightShift,
        LeftClick, RightClick, MiddleClick,
        LeftCtrl,  RightCtrl,
        LeftAlt,   RightAlt,
        CapsLock,
        AltGr,
        ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
        PageUp, PageDown,

        Enter, Backspace, Tab, Space, Escape,

        Grave,        // `  ~
        Minus,        // -  _
        Equal,        // =  +
        LeftBracket,  // [  {
        RightBracket, // ]  }
        Backslash,    // \  |
        Semicolon,    // ;  :
        Apostrophe,   // '  "
        Comma,        // ,
        Period,       // .  >
        Slash,        // /  ?
        Undefined
    };

    struct ArcadeEvents {
        std::vector <Key> key;
        int x;
        int y;
    };
}