// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <X11/Xlib.h>
#include <X11/Xutil.h>

export module WinLite.MainWindow;

import std;

import WinLite.Queue;
import WinLite.Events;
import WinLite.KeyEnums;
import WinLite.KeyMapper;

export namespace WinLite
{
    class MainWindow
    {
    public:
        void InitKeyMapper()
        {
            _keyMapper.Add(XK_Super_L, Key::LSystem);
            _keyMapper.Add(XK_Super_R, Key::RSystem);
            _keyMapper.Add(XK_Menu, Key::Menu);

            _keyMapper.Add(XK_semicolon, Key::Semicolon);
            _keyMapper.Add(XK_slash, Key::Slash);
            _keyMapper.Add(XK_equal, Key::Equal);
            _keyMapper.Add(XK_minus, Key::Hyphen);
            _keyMapper.Add(XK_bracketleft, Key::LBracket);
            _keyMapper.Add(XK_bracketright, Key::RBracket);
            _keyMapper.Add(XK_comma, Key::Comma);
            _keyMapper.Add(XK_period, Key::Period);
            _keyMapper.Add(XK_apostrophe, Key::Quote);
            _keyMapper.Add(XK_backslash, Key::Backslash);
            _keyMapper.Add(XK_grave, Key::Tilde);

            _keyMapper.Add(XK_Escape, Key::Escape);
            _keyMapper.Add(XK_space, Key::Space);
            _keyMapper.Add(XK_Return, Key::Enter);
            _keyMapper.Add(XK_BackSpace, Key::Backspace);
            _keyMapper.Add(XK_Tab, Key::Tab);

            _keyMapper.Add(XK_Prior, Key::PageUp);
            _keyMapper.Add(XK_Next, Key::PageDown);
            _keyMapper.Add(XK_End, Key::End);
            _keyMapper.Add(XK_Home, Key::Home);
            _keyMapper.Add(XK_Insert, Key::Insert);
            _keyMapper.Add(XK_Delete, Key::Delete);

            _keyMapper.Add(XK_Left, Key::Left);
            _keyMapper.Add(XK_Right, Key::Right);
            _keyMapper.Add(XK_Up, Key::Up);
            _keyMapper.Add(XK_Down, Key::Down);

            _keyMapper.Add(XK_F1, Key::F1);
            _keyMapper.Add(XK_F2, Key::F2);
            _keyMapper.Add(XK_F3, Key::F3);
            _keyMapper.Add(XK_F4, Key::F4);
            _keyMapper.Add(XK_F5, Key::F5);
            _keyMapper.Add(XK_F6, Key::F6);
            _keyMapper.Add(XK_F7, Key::F7);
            _keyMapper.Add(XK_F8, Key::F8);
            _keyMapper.Add(XK_F9, Key::F9);
            _keyMapper.Add(XK_F10, Key::F10);
            _keyMapper.Add(XK_F11, Key::F11);
            _keyMapper.Add(XK_F12, Key::F12);
            _keyMapper.Add(XK_F13, Key::F13);
            _keyMapper.Add(XK_F14, Key::F14);
            _keyMapper.Add(XK_F15, Key::F15);

            _keyMapper.Add(XK_KP_0, Key::Numpad0);
            _keyMapper.Add(XK_KP_1, Key::Numpad1);
            _keyMapper.Add(XK_KP_2, Key::Numpad2);
            _keyMapper.Add(XK_KP_3, Key::Numpad3);
            _keyMapper.Add(XK_KP_4, Key::Numpad4);
            _keyMapper.Add(XK_KP_5, Key::Numpad5);
            _keyMapper.Add(XK_KP_6, Key::Numpad6);
            _keyMapper.Add(XK_KP_7, Key::Numpad7);
            _keyMapper.Add(XK_KP_8, Key::Numpad8);
            _keyMapper.Add(XK_KP_9, Key::Numpad9);

            _keyMapper.Add(XK_KP_Add, Key::Add);
            _keyMapper.Add(XK_KP_Subtract, Key::Subtract);
            _keyMapper.Add(XK_KP_Multiply, Key::Multiply);
            _keyMapper.Add(XK_KP_Divide, Key::Divide);

            _keyMapper.Add(XK_Pause, Key::Pause);

            _keyMapper.Add(XK_a, Key::A);
            _keyMapper.Add(XK_b, Key::B);
            _keyMapper.Add(XK_c, Key::C);
            _keyMapper.Add(XK_d, Key::D);
            _keyMapper.Add(XK_e, Key::E);
            _keyMapper.Add(XK_f, Key::F);
            _keyMapper.Add(XK_g, Key::G);
            _keyMapper.Add(XK_h, Key::H);
            _keyMapper.Add(XK_i, Key::I);
            _keyMapper.Add(XK_j, Key::J);
            _keyMapper.Add(XK_k, Key::K);
            _keyMapper.Add(XK_l, Key::L);
            _keyMapper.Add(XK_m, Key::M);
            _keyMapper.Add(XK_n, Key::N);
            _keyMapper.Add(XK_o, Key::O);
            _keyMapper.Add(XK_p, Key::P);
            _keyMapper.Add(XK_q, Key::Q);
            _keyMapper.Add(XK_r, Key::R);
            _keyMapper.Add(XK_s, Key::S);
            _keyMapper.Add(XK_t, Key::T);
            _keyMapper.Add(XK_u, Key::U);
            _keyMapper.Add(XK_v, Key::V);
            _keyMapper.Add(XK_w, Key::W);
            _keyMapper.Add(XK_x, Key::X);
            _keyMapper.Add(XK_y, Key::Y);
            _keyMapper.Add(XK_z, Key::Z);
        }

        static std::expected<MainWindow, std::string> Create(std::size_t w, std::size_t h, const std::string &title)
        {
            if (w == 0 || h == 0)
            {
                return std::unexpected("Window dimensions cannot be zero.");
            }

            Display *display = XOpenDisplay(nullptr);
            if (!display)
            {
                return std::unexpected("Failed to open X display.");
            }

            int screen = DefaultScreen(display);
            Window root = RootWindow(display, screen);

            Window window = XCreateSimpleWindow(
                display, root,
                0, 0, static_cast<unsigned int>(w), static_cast<unsigned int>(h),
                0, 0, 0);

            if (!window)
            {
                XCloseDisplay(display);
                return std::unexpected("Failed to create X11 window.");
            }

            XSetWindowBackgroundPixmap(display, window, None);
            XSelectInput(display, window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask | FocusChangeMask);

            Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
            XSetWMProtocols(display, window, &wmDeleteMessage, 1);

            XMapWindow(display, window);
            XFlush(display);

            MainWindow win;
            win._display = display;
            win._window = window;
            win._wmDeleteMessage = wmDeleteMessage;

            win.SetTitle(title);
            win.InitKeyMapper();

            return win;
        }

        ~MainWindow()
        {
            Destroy();
        }

        MainWindow(MainWindow &&other) noexcept : _events(std::move(other._events)),
                                                  _keyMapper(std::move(other._keyMapper)),
                                                  _display(other._display),
                                                  _window(other._window),
                                                  _wmDeleteMessage(other._wmDeleteMessage)
        {
            other._display = nullptr;
            other._window = 0;
        }

        MainWindow &operator=(MainWindow &&other) noexcept
        {
            if (this != &other)
            {
                Destroy();

                _events = std::move(other._events);
                _keyMapper = std::move(other._keyMapper);
                _display = other._display;
                _window = other._window;
                _wmDeleteMessage = other._wmDeleteMessage;

                other._display = nullptr;
                other._window = 0;
            }
            return *this;
        }

        void PollEvents()
        {
            if (!_display)
                return;

            while (XPending(_display))
            {
                XEvent xev;
                XNextEvent(_display, &xev);

                Event event{};

                switch (xev.type)
                {
                case Expose:
                    XFlush(_display);
                    break;

                case MotionNotify:
                    event.Type = EventType::MouseMove;
                    event.Mouse.PosX = static_cast<short>(xev.xmotion.x);
                    event.Mouse.PosY = static_cast<short>(xev.xmotion.y);
                    _events.Push(event);
                    break;

                case ButtonPress:
                case ButtonRelease:
                {
                    unsigned int button = xev.xbutton.button;

                    if (button == Button4 || button == Button5)
                    {
                        if (xev.type == ButtonPress)
                        {
                            event.Type = EventType::MouseScroll;
                            event.Mouse.Delta = (button == Button4) ? static_cast<short>(120) : static_cast<short>(-120);
                            event.Mouse.Scroll = MouseScroll::Vertical;
                            event.Mouse.PosX = static_cast<short>(xev.xbutton.x);
                            event.Mouse.PosY = static_cast<short>(xev.xbutton.y);
                            _events.Push(event);
                        }
                        break;
                    }

                    if (button == 6 || button == 7)
                    {
                        if (xev.type == ButtonPress)
                        {
                            event.Type = EventType::MouseScroll;
                            event.Mouse.Delta = (button == 6) ? static_cast<short>(120) : static_cast<short>(-120);
                            event.Mouse.Scroll = MouseScroll::Horizontal;
                            event.Mouse.PosX = static_cast<short>(xev.xbutton.x);
                            event.Mouse.PosY = static_cast<short>(xev.xbutton.y);
                            _events.Push(event);
                        }
                        break;
                    }

                    event.Type = EventType::MouseClick;
                    event.Mouse.PosX = static_cast<short>(xev.xbutton.x);
                    event.Mouse.PosY = static_cast<short>(xev.xbutton.y);
                    event.Mouse.State = (xev.type == ButtonPress) ? ButtonState::Pressed : ButtonState::Released;

                    if (button == Button1)
                    {
                        event.Mouse.Button = MouseButton::Left;
                    }
                    else if (button == Button3)
                    {
                        event.Mouse.Button = MouseButton::Right;
                    }
                    else if (button == Button2)
                    {
                        event.Mouse.Button = MouseButton::Middle;
                    }
                    else
                    {
                        break;
                    }

                    _events.Push(event);
                    break;
                }

                case ConfigureNotify:
                    event.Type = EventType::Resize;
                    event.Resize.Width = static_cast<std::size_t>(xev.xconfigure.width);
                    event.Resize.Height = static_cast<std::size_t>(xev.xconfigure.height);
                    _events.Push(event);
                    break;

                case ClientMessage:
                    if (static_cast<Atom>(xev.xclient.data.l[0]) == _wmDeleteMessage)
                    {
                        event.Type = EventType::Quit;
                        _events.Push(event);
                        StopEvent();
                    }
                    break;

                case KeyPress:
                case KeyRelease:
                {
                    event.Type = EventType::Keyboard;
                    event.Keyboard.State = (xev.type == KeyPress) ? ButtonState::Pressed : ButtonState::Released;

                    KeySym keysym = XLookupKeysym(&xev.xkey, 0);

                    event.Keyboard.KeyCode = _keyMapper.FindKey(static_cast<std::uint32_t>(keysym));
                    _events.Push(event);
                    break;
                }

                case FocusIn:
                    event.Type = EventType::GainedFocus;
                    _events.Push(event);
                    break;

                case FocusOut:
                    event.Type = EventType::LostFocus;
                    _events.Push(event);
                    break;

                default:
                    break;
                }
            }
        }

        bool GetEvent(Event &event)
        {
            if (!_events.Empty())
            {
                return _events.Pop(event);
            }

            PollEvents();

            if (!_events.Empty())
            {
                return _events.Pop(event);
            }

            return false;
        }

        void StopEvent()
        {
            _events.Stop();
        }

        bool IsRunning() const
        {
            return _events.IsRunning();
        }

        void SetTitle(const std::string &title)
        {
            if (_display && _window && !title.empty())
            {
                XStoreName(_display, _window, title.c_str());
                XFlush(_display);
            }
        }

        Display *GetDisplay() const { return _display; }
        Window GetWindow() const { return _window; }

        MainWindow(const MainWindow &) = delete;
        MainWindow &operator=(const MainWindow &) = delete;

    private:
        Queue _events;
        KeyMapper _keyMapper;
        Display *_display{nullptr};
        Window _window{0};
        Atom _wmDeleteMessage{0};

        explicit MainWindow() : _events{},
                                _keyMapper{}
        {
        }

        void Destroy()
        {
            if (_display)
            {
                if (_window)
                {
                    XDestroyWindow(_display, _window);
                }
                
                XCloseDisplay(_display);
                _display = nullptr;
                _window = 0;
            }
        }
    };
}
