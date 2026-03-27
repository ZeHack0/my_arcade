#pragma once

namespace arcade {
    enum class Key {
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
        Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
        NumpadAdd, NumpadSubtract, NumpadMultiply, NumpadDivide,
        NumpadDecimal, NumpadEnter, NumLock,
        F1,  F2,  F3,  F4,  F5,  F6,
        F7,  F8,  F9,  F10, F11, F12,
        F13, F14, F15, F16, F17, F18,
        F19, F20, F21, F22, F23, F24,
        LeftShift, RightShift,
        LeftClick, RightClick, MiddleClick,
        LeftCtrl,  RightCtrl,
        LeftAlt,   RightAlt,
        LeftSuper, RightSuper,   // Touche Windows / Cmd
        CapsLock,
        AltGr,
        ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
        Home, End, PageUp, PageDown,
        Insert, Delete,

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

    struct ArcadeEvent {
        Key key;
        int x;
        int y;
    };
}