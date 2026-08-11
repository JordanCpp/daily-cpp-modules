// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <cstdint>

export module WinLite.KeyEnums;

export namespace WinLite
{
    enum class Key : std::uint8_t
    {
        Unknown = 1,     /**< Unknown or unmapped key.*/
        LSystem,         /**< Left System key (Windows key on Windows, Command key on macOS).*/
        RSystem,         /**< Right System key (Windows key on Windows, Command key on macOS).*/
        Menu,            /**< Menu/App key - opens context menu.*/
        Semicolon,       /**< Semicolon key (;).*/
        Slash,           /**< Slash key (/).*/
        Equal,           /**< Equal key (=).*/
        Hyphen,          /**< Hyphen/Minus key (-).*/
        LBracket,        /**< Left bracket key ([).*/
        RBracket,        /**< Right bracket key (]).*/
        Comma,           /**< Comma key (,).*/
        Period,          /**< Period/Dot key (.).*/
        Quote,           /**< Quote key (').*/
        Backslash,       /**< Backslash key (\).*/
        Tilde,           /**< Tilde/Grave accent key (~).*/
        Escape,          /**< Escape key - typically cancels current operation.*/
        Space,           /**< Spacebar - produces space character.*/
        Enter,           /**< Enter/Return key - confirms input or new line.*/
        Backspace,       /**< Backspace key - deletes previous character.*/
        Tab,             /**< Tab key - moves focus or inserts tab character.*/
        PageUp,          /**< Page Up key - scrolls one page up.*/
        PageDown,        /**< Page Down key - scrolls one page down.*/
        End,             /**< End key - moves cursor to end of line/document.*/
        Home,            /**< Home key - moves cursor to beginning of line/document.*/
        Insert,          /**< Insert key - toggles insert/overwrite mode.*/
        Delete,          /**< Delete key - deletes next character or selection.*/
        Add,             /**< Plus key (+) on keypad.*/
        Subtract,        /**< Minus/Subtraction key (-) on keypad.*/
        Multiply,        /**< Multiplication key (*) on keypad.*/
        Divide,          /**< Division key (/) on keypad.*/
        Pause,           /**< Pause/Break key - pauses execution or scrolling.*/
        F1,              /**< Function key F1 - often used for help.*/
        F2,              /**< Function key F2 - often used for rename.*/
        F3,              /**< Function key F3 - often used for search.*/
        F4,              /**< Function key F4 - often used for address bar or close.*/
        F5,              /**< Function key F5 - often used for refresh.*/
        F6,              /**< Function key F6 - often used for navigation.*/
        F7,              /**< Function key F7 - often used for spell check.*/
        F8,              /**< Function key F8 - often used for startup or safe mode.*/
        F9,              /**< Function key F9 - often used for debugging or mail.*/
        F10,             /**< Function key F10 - often used for menu bar.*/
        F11,             /**< Function key F11 - often used for fullscreen.*/
        F12,             /**< Function key F12 - often used for developer tools.*/
        F13,             /**< Function key F13 - additional function key.*/
        F14,             /**< Function key F14 - additional function key.*/
        F15,             /**< Function key F15 - additional function key.*/
        Left,            /**< Left Arrow key - moves cursor left.*/
        Right,           /**< Right Arrow key - moves cursor right.*/
        Up,              /**< Up Arrow key - moves cursor up.*/
        Down,            /**< Down Arrow key - moves cursor down.*/
        Numpad0,         /**< Numpad 0 key.*/
        Numpad1,         /**< Numpad 1 key.*/
        Numpad2,         /**< Numpad 2 key.*/
        Numpad3,         /**< Numpad 3 key.*/
        Numpad4,         /**< Numpad 4 key.*/
        Numpad5,         /**< Numpad 5 key.*/
        Numpad6,         /**< Numpad 6 key.*/
        Numpad7,         /**< Numpad 7 key.*/
        Numpad8,         /**< Numpad 8 key.*/
        Numpad9,         /**< Numpad 9 key.*/
        A,               /**< 'A' key.*/
        Z,               /**< 'Z' key.*/
        E,               /**< 'E' key.*/
        R,               /**< 'R' key.*/
        T,               /**< 'T' key.*/
        Y,               /**< 'Y' key.*/
        U,               /**< 'U' key.*/
        I,               /**< 'I' key.*/
        O,               /**< 'O' key.*/
        P,               /**< 'P' key.*/
        Q,               /**< 'Q' key.*/
        S,               /**< 'S' key.*/
        D,               /**< 'D' key.*/
        F,               /**< 'F' key.*/
        G,               /**< 'G' key.*/
        H,               /**< 'H' key.*/
        J,               /**< 'J' key.*/
        K,               /**< 'K' key.*/
        L,               /**< 'L' key.*/
        M,               /**< 'M' key.*/
        W,               /**< 'W' key.*/
        X,               /**< 'X' key.*/
        C,               /**< 'C' key.*/
        V,               /**< 'V' key.*/
        B,               /**< 'B' key.*/
        N,               /**< 'N' key.*/
        Num0,            /**< Top-row number 0 key.*/
        Num1,            /**< Top-row number 1 key.*/
        Num2,            /**< Top-row number 2 key.*/
        Num3,            /**< Top-row number 3 key.*/
        Num4,            /**< Top-row number 4 key.*/
        Num5,            /**< Top-row number 5 key.*/
        Num6,            /**< Top-row number 6 key.*/
        Num7,            /**< Top-row number 7 key.*/
        Num8,            /**< Top-row number 8 key.*/
        Num9,            /**< Top-row number 9 key.*/
        LeftShift,       /**< Left Shift key - modifies key behavior.*/
        RightShift,      /**< Right Shift key - modifies key behavior.*/
        LeftControl,     /**< Left Control key - keyboard shortcut modifier.*/
        RightControl     /**< Right Control key - keyboard shortcut modifier.*/
    };
}