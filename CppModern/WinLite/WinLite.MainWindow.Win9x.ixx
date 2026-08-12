// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <string>
#include <expected>
#include <Windows.h>

export module WinLite.MainWindow;

import WinLite.Queue;
import WinLite.Events;
import WinLite.KeyMapper;

export namespace WinLite
{
    const char ClassName[] = "MainWindow";

    class MainWindow
    {
    public:
        void InitKeyMapper()
        {
            _keyMapper.Add(VK_LWIN, Key::LSystem);
            _keyMapper.Add(VK_RWIN, Key::RSystem);
            _keyMapper.Add(VK_APPS, Key::Menu);

            _keyMapper.Add(VK_OEM_1, Key::Semicolon);
            _keyMapper.Add(VK_OEM_2, Key::Slash);
            _keyMapper.Add(VK_OEM_PLUS, Key::Equal);
            _keyMapper.Add(VK_OEM_MINUS, Key::Hyphen);
            _keyMapper.Add(VK_OEM_4, Key::LBracket);
            _keyMapper.Add(VK_OEM_6, Key::RBracket);
            _keyMapper.Add(VK_OEM_COMMA, Key::Comma);
            _keyMapper.Add(VK_OEM_PERIOD, Key::Period);
            _keyMapper.Add(VK_OEM_7, Key::Quote);
            _keyMapper.Add(VK_OEM_5, Key::Backslash);
            _keyMapper.Add(VK_OEM_3, Key::Tilde);

            _keyMapper.Add(VK_ESCAPE, Key::Escape);
            _keyMapper.Add(VK_SPACE, Key::Space);
            _keyMapper.Add(VK_RETURN, Key::Enter);
            _keyMapper.Add(VK_BACK, Key::Backspace);
            _keyMapper.Add(VK_TAB, Key::Tab);

            _keyMapper.Add(VK_PRIOR, Key::PageUp);
            _keyMapper.Add(VK_NEXT, Key::PageDown);
            _keyMapper.Add(VK_END, Key::End);
            _keyMapper.Add(VK_HOME, Key::Home);
            _keyMapper.Add(VK_INSERT, Key::Insert);
            _keyMapper.Add(VK_DELETE, Key::Delete);

            _keyMapper.Add(VK_LEFT, Key::Left);
            _keyMapper.Add(VK_RIGHT, Key::Right);
            _keyMapper.Add(VK_UP, Key::Up);
            _keyMapper.Add(VK_DOWN, Key::Down);

            _keyMapper.Add(VK_F1, Key::F1);
            _keyMapper.Add(VK_F2, Key::F2);
            _keyMapper.Add(VK_F3, Key::F3);
            _keyMapper.Add(VK_F4, Key::F4);
            _keyMapper.Add(VK_F5, Key::F5);
            _keyMapper.Add(VK_F6, Key::F6);
            _keyMapper.Add(VK_F7, Key::F7);
            _keyMapper.Add(VK_F8, Key::F8);
            _keyMapper.Add(VK_F9, Key::F9);
            _keyMapper.Add(VK_F10, Key::F10);
            _keyMapper.Add(VK_F11, Key::F11);
            _keyMapper.Add(VK_F12, Key::F12);
            _keyMapper.Add(VK_F13, Key::F13);
            _keyMapper.Add(VK_F14, Key::F14);
            _keyMapper.Add(VK_F15, Key::F15);

            _keyMapper.Add(VK_NUMPAD0, Key::Numpad0);
            _keyMapper.Add(VK_NUMPAD1, Key::Numpad1);
            _keyMapper.Add(VK_NUMPAD2, Key::Numpad2);
            _keyMapper.Add(VK_NUMPAD3, Key::Numpad3);
            _keyMapper.Add(VK_NUMPAD4, Key::Numpad4);
            _keyMapper.Add(VK_NUMPAD5, Key::Numpad5);
            _keyMapper.Add(VK_NUMPAD6, Key::Numpad6);
            _keyMapper.Add(VK_NUMPAD7, Key::Numpad7);
            _keyMapper.Add(VK_NUMPAD8, Key::Numpad8);
            _keyMapper.Add(VK_NUMPAD9, Key::Numpad9);

            _keyMapper.Add(VK_ADD, Key::Add);
            _keyMapper.Add(VK_SUBTRACT, Key::Subtract);
            _keyMapper.Add(VK_MULTIPLY, Key::Multiply);
            _keyMapper.Add(VK_DIVIDE, Key::Divide);

            _keyMapper.Add(VK_PAUSE, Key::Pause);

            _keyMapper.Add('A', Key::A);
            _keyMapper.Add('Z', Key::Z);
            _keyMapper.Add('E', Key::E);
            _keyMapper.Add('R', Key::R);
            _keyMapper.Add('T', Key::T);
            _keyMapper.Add('Y', Key::Y);
            _keyMapper.Add('U', Key::U);
            _keyMapper.Add('I', Key::I);
            _keyMapper.Add('O', Key::O);
            _keyMapper.Add('P', Key::P);
            _keyMapper.Add('Q', Key::Q);
            _keyMapper.Add('S', Key::S);
            _keyMapper.Add('D', Key::D);
            _keyMapper.Add('F', Key::F);
            _keyMapper.Add('G', Key::G);
            _keyMapper.Add('H', Key::H);
            _keyMapper.Add('J', Key::J);
            _keyMapper.Add('K', Key::K);
            _keyMapper.Add('W', Key::W);
            _keyMapper.Add('B', Key::B);
            _keyMapper.Add('C', Key::C);
            _keyMapper.Add('L', Key::L);
            _keyMapper.Add('M', Key::M);
            _keyMapper.Add('N', Key::N);
            _keyMapper.Add('V', Key::V);
            _keyMapper.Add('X', Key::X);

        }

        static std::expected<MainWindow, std::string> Create(int w, int h, const std::string& title)
        {
            HINSTANCE instance = GetModuleHandleA(nullptr);
            if (instance == nullptr)
            {
                return std::unexpected("GetModuleHandleA failed");
            }

            WNDCLASSEXA windowClass   = { sizeof(WNDCLASSEXA) };
            windowClass.hInstance     = instance;
            windowClass.lpszClassName = ClassName;
            windowClass.lpfnWndProc   = WndProc;
            windowClass.style         = CS_HREDRAW | CS_VREDRAW;
            windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            windowClass.hIcon         = LoadIconA(nullptr, IDI_APPLICATION);
            windowClass.hCursor       = LoadCursorA(nullptr, IDC_ARROW);

            if (!GetClassInfoExA(instance, ClassName, &windowClass))
            {
                if (RegisterClassExA(&windowClass) == 0)
                {
                    return std::unexpected("RegisterClassExA failed");
                }
            }

            RECT  rect  = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };
            DWORD style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

            AdjustWindowRect(&rect, style, FALSE);

            int width  = rect.right  - rect.left;
            int height = rect.bottom - rect.top;

            int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);

            int posX = (screenWidth  - width)  / 2;
            int posY = (screenHeight - height) / 2;

            HWND hwnd  = CreateWindowA(ClassName, title.c_str(), WS_OVERLAPPED | WS_SYSMENU, posX, posY, width, height, nullptr, nullptr, instance, nullptr);

            if (hwnd == nullptr)
            {
                return std::unexpected("CreateWindowA failed");
            }

            MainWindow window(hwnd);

            SetLastError(0);
#ifdef _WIN64
            LONG_PTR setWindow = SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window));
#else
            LONG setWindow = SetWindowLongA(hwnd, GWL_USERDATA, reinterpret_cast<LONG>(&window));
#endif  
            if (setWindow == 0 && GetLastError() != 0)
            {
                DestroyWindow(hwnd);
                return std::unexpected("SetWindowLongPtrA failed");
            }

            window._hdc = GetDC(hwnd);
            if (window._hdc == nullptr)
            {
                DestroyWindow(hwnd);
                return std::unexpected("GetDC failed");
            }

            ShowWindow(hwnd, SW_SHOW);
            UpdateWindow(hwnd);

            return window;
        }

        ~MainWindow()
        {
            if (_hdc && _hwnd)
            {
                ReleaseDC(_hwnd, _hdc);
            }

            if (_hwnd)
            {
                DestroyWindow(_hwnd);
            }
        }

        MainWindow(MainWindow&& other) noexcept : 
            _hwnd(other._hwnd), 
            _hdc(other._hdc),
            _events(std::move(other._events))
        {
            other._hwnd = nullptr;
            other._hdc  = nullptr;

            InitKeyMapper();

            if (_hwnd)
            {
#ifdef _WIN64
                SetWindowLongPtrA(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
#else
                SetWindowLongA(_hwnd, GWL_USERDATA, reinterpret_cast<LONG>(this));
#endif
            }
        }

        MainWindow& operator=(MainWindow&& other) noexcept
        {
            if (this != &other)
            {
                if (_hdc && _hwnd)
                {
                    ReleaseDC(_hwnd, _hdc);
                }
                
                if (_hwnd)
                {
                    DestroyWindow(_hwnd);
                }

                _hwnd       = other._hwnd;
                _hdc        = other._hdc;
                _events     = std::move(other._events);
                other._hwnd = nullptr;
                other._hdc  = nullptr;

                if (_hwnd)
                {
#ifdef _WIN64
                    SetWindowLongPtrA(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
#else
                    SetWindowLongA(_hwnd, GWL_USERDATA, reinterpret_cast<LONG>(this));
#endif
                }
            }

            return *this;
        }

        void PollEvents()
        {
            MSG msg;

            while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }

        bool GetEvent(Event& event)
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

        HWND GetHwnd()
        {
            return _hwnd;
        }

        HDC GetHdc()
        {
            return _hdc;
        }

        MainWindow(const MainWindow&) = delete;
        MainWindow& operator=(const MainWindow&) = delete;

    private:
        HWND      _hwnd = nullptr;
        HDC       _hdc  = nullptr;
        Queue     _events;
        KeyMapper _keyMapper;

        explicit MainWindow(HWND hwnd) : 
            _hwnd(hwnd) 
        {
        }

        LRESULT CALLBACK Handler(UINT message, WPARAM WParam, LPARAM LParam)
        {
            Event event = {};

            ZeroMemory(&event, sizeof(event));

            switch (message)
            {
            case WM_PAINT:
                break;

            case WM_DESTROY:
                break;

            case WM_MOUSEMOVE:
                event.Type       = EventType::MouseMove;
                event.Mouse.PosX = LOWORD(LParam);
                event.Mouse.PosY = HIWORD(LParam);
                _events.Push(event);
                break;

            case WM_LBUTTONDOWN: case WM_LBUTTONUP:
            case WM_RBUTTONDOWN: case WM_RBUTTONUP:
            case WM_MBUTTONDOWN: case WM_MBUTTONUP:
            {
                event.Type       = EventType::MouseClick;
                event.Mouse.PosX = LOWORD(LParam);
                event.Mouse.PosY = HIWORD(LParam);

                event.Mouse.State = (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN) ? ButtonState::Pressed : ButtonState::Released;

                if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP)
                {
                    event.Mouse.Button = MouseButton::Left;
                }
                else if (message == WM_RBUTTONDOWN || message == WM_RBUTTONUP)
                {
                    event.Mouse.Button = MouseButton::Right;
                }
                else
                {
                    event.Mouse.Button = MouseButton::Middle;
                }

                _events.Push(event);
                break;
            }

            case WM_SIZE:
                event.Type = EventType::Resize;
                event.Resize.Width = LOWORD(LParam);
                event.Resize.Height = HIWORD(LParam);
                _events.Push(event);
                break;

            case WM_CLOSE:
                event.Type = EventType::Quit;
                _events.Push(event);
                PostQuitMessage(0);
                break;

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                event.Type           = EventType::Keyboard;
                event.Keyboard.State = ButtonState::Pressed;
                event.Keyboard.Key   = _keyMapper.FindKey(WParam);
                _events.Push(event);
                break;

            case WM_KEYUP:
            case WM_SYSKEYUP:
                event.Type           = EventType::Keyboard;
                event.Keyboard.State = ButtonState::Released;
                event.Keyboard.Key   = _keyMapper.FindKey(WParam);
                _events.Push(event);
                break;

            case WM_SETFOCUS:
                event.Type = EventType::GainedFocus;
                _events.Push(event);
                break;

            case WM_KILLFOCUS:
                event.Type = EventType::LostFocus;
                _events.Push(event);
                break;

            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
            {
                event.Type = EventType::MouseScroll;
                event.Mouse.PosX = LOWORD(LParam);
                event.Mouse.PosY = HIWORD(LParam);
                event.Mouse.Delta = static_cast<short>(HIWORD(WParam));
                event.Mouse.Scroll = (message == WM_MOUSEWHEEL) ? MouseScroll::Vertical : MouseScroll::Horizontal;
                _events.Push(event);
                break;
            }
            }

            return DefWindowProcA(_hwnd, message, WParam, LParam);
        }

        static LRESULT CALLBACK WndProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
        {
#ifdef _WIN64
            MainWindow* This = reinterpret_cast<MainWindow*>(GetWindowLongPtrA(Hwnd, GWLP_USERDATA));
#else
            MainWindow* This = reinterpret_cast<MainWindow*>(GetWindowLongA(Hwnd, GWL_USERDATA));
#endif  

            if (This != nullptr)
            {
                return This->Handler(Message, WParam, LParam);
            }

            return DefWindowProcA(Hwnd, Message, WParam, LParam);
        }
    };
}
