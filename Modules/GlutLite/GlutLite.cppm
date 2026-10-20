// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module GlutLite;

import std;
import WinLite;
import OpenGL;

using namespace WinLite;

export namespace glut
{
    constexpr unsigned int GLUT_RGB = 0x0000;
    constexpr unsigned int GLUT_RGBA = 0x0000;
    constexpr unsigned int GLUT_INDEX = 0x0001;
    constexpr unsigned int GLUT_SINGLE = 0x0000;
    constexpr unsigned int GLUT_DOUBLE = 0x0002;
    constexpr unsigned int GLUT_ACCUM = 0x0004;
    constexpr unsigned int GLUT_ALPHA = 0x0008;
    constexpr unsigned int GLUT_DEPTH = 0x0010;
    constexpr unsigned int GLUT_STENCIL = 0x0020;

    constexpr int GLUT_KEY_F1 = 1;
    constexpr int GLUT_KEY_F2 = 2;
    constexpr int GLUT_KEY_F3 = 3;
    constexpr int GLUT_KEY_F4 = 4;
    constexpr int GLUT_KEY_F5 = 5;
    constexpr int GLUT_KEY_F6 = 6;
    constexpr int GLUT_KEY_F7 = 7;
    constexpr int GLUT_KEY_F8 = 8;
    constexpr int GLUT_KEY_F9 = 9;
    constexpr int GLUT_KEY_F10 = 10;
    constexpr int GLUT_KEY_F11 = 11;
    constexpr int GLUT_KEY_F12 = 12;
    constexpr int GLUT_KEY_LEFT = 100;
    constexpr int GLUT_KEY_UP = 101;
    constexpr int GLUT_KEY_RIGHT = 102;
    constexpr int GLUT_KEY_DOWN = 103;
    constexpr int GLUT_KEY_PAGE_UP = 104;
    constexpr int GLUT_KEY_PAGE_DOWN = 105;
    constexpr int GLUT_KEY_HOME = 106;
    constexpr int GLUT_KEY_END = 107;
    constexpr int GLUT_KEY_INSERT = 108;

    constexpr int GLUT_LEFT_BUTTON = 0;
    constexpr int GLUT_MIDDLE_BUTTON = 1;
    constexpr int GLUT_RIGHT_BUTTON = 2;
    constexpr int GLUT_DOWN = 0;
    constexpr int GLUT_UP = 1;

    using DisplayFunc       = void(*)() noexcept;
    using ReshapeFunc       = void(*)(int, int) noexcept;
    using KeyboardFunc      = void(*)(unsigned char, int, int) noexcept;
    using IdleFunc          = void(*)() noexcept;
    using MouseFunc         = void(*)(int button, int state, int x, int y) noexcept;
    using MotionFunc        = void(*)(int x, int y) noexcept;
    using PassiveMotionFunc = void(*)(int x, int y) noexcept;
    using SpecialFunc       = void(*)(int key, int x, int y) noexcept;
    using KeyboardUpFunc    = void(*)(unsigned char key, int x, int y) noexcept;
    using SpecialUpFunc     = void(*)(int key, int x, int y) noexcept;
    using TimerFunc         = void(*)(int value) noexcept;

    void glutInit(int* argc, char** argv) noexcept;
    void glutInitWindowSize(int width, int height) noexcept;
    void glutInitDisplayMode(unsigned int mode) noexcept;
    int  glutCreateWindow(const char* title) noexcept;

    void glutDisplayFunc(DisplayFunc func) noexcept;
    void glutReshapeFunc(ReshapeFunc func) noexcept;
    void glutKeyboardFunc(KeyboardFunc func) noexcept;
    void glutIdleFunc(IdleFunc func) noexcept;
    void glutMouseFunc(MouseFunc func) noexcept;
    void glutMotionFunc(MotionFunc func) noexcept;
    void glutPassiveMotionFunc(PassiveMotionFunc func) noexcept;

    void glutPostRedisplay() noexcept;
    void glutMainLoop() noexcept;

    void glutSpecialFunc(SpecialFunc func) noexcept;
    void glutKeyboardUpFunc(KeyboardUpFunc func) noexcept;
    void glutSpecialUpFunc(SpecialUpFunc func) noexcept;
    void glutTimerFunc(unsigned int msecs, TimerFunc func, int value) noexcept;

    void glutSwapBuffers() noexcept;

    [[nodiscard]] constexpr unsigned char MapKeyToAscii(Key key) noexcept
    {
        switch (key)
        {
        case Key::A: return 'a';
        case Key::Z: return 'z';
        case Key::E: return 'e';
        case Key::R: return 'r';
        case Key::T: return 't';
        case Key::Y: return 'y';
        case Key::U: return 'u';
        case Key::I: return 'i';
        case Key::O: return 'o';
        case Key::P: return 'p';
        case Key::Q: return 'q';
        case Key::S: return 's';
        case Key::D: return 'd';
        case Key::F: return 'f';
        case Key::G: return 'g';
        case Key::H: return 'h';
        case Key::J: return 'j';
        case Key::K: return 'k';
        case Key::L: return 'l';
        case Key::M: return 'm';
        case Key::W: return 'w';
        case Key::X: return 'x';
        case Key::C: return 'c';
        case Key::V: return 'v';
        case Key::B: return 'b';
        case Key::N: return 'n';

        case Key::Num0: return '0';
        case Key::Num1: return '1';
        case Key::Num2: return '2';
        case Key::Num3: return '3';
        case Key::Num4: return '4';
        case Key::Num5: return '5';
        case Key::Num6: return '6';
        case Key::Num7: return '7';
        case Key::Num8: return '8';
        case Key::Num9: return '9';

        case Key::Space:     return ' ';
        case Key::Enter:     return '\r';
        case Key::Escape:    return 27;
        case Key::Backspace: return 8;
        case Key::Tab:       return '\t';

        default: return 0;
        }
    }

    [[nodiscard]] constexpr int MapKeyToSpecial(Key key) noexcept
    {
        switch (key)
        {
        case Key::Left:  return GLUT_KEY_LEFT;
        case Key::Right: return GLUT_KEY_RIGHT;
        case Key::Up:    return GLUT_KEY_UP;
        case Key::Down:  return GLUT_KEY_DOWN;

        case Key::F1:  return GLUT_KEY_F1;
        case Key::F2:  return GLUT_KEY_F2;
        case Key::F3:  return GLUT_KEY_F3;
        case Key::F4:  return GLUT_KEY_F4;
        case Key::F5:  return GLUT_KEY_F5;
        case Key::F6:  return GLUT_KEY_F6;
        case Key::F7:  return GLUT_KEY_F7;
        case Key::F8:  return GLUT_KEY_F8;
        case Key::F9:  return GLUT_KEY_F9;
        case Key::F10: return GLUT_KEY_F10;
        case Key::F11: return GLUT_KEY_F11;
        case Key::F12: return GLUT_KEY_F12;

        case Key::PageUp:   return GLUT_KEY_PAGE_UP;
        case Key::PageDown: return GLUT_KEY_PAGE_DOWN;
        case Key::Home:     return GLUT_KEY_HOME;
        case Key::End:      return GLUT_KEY_END;
        case Key::Insert:   return GLUT_KEY_INSERT;

        default: return -1;
        }
    }

    struct TimerInfo
    {
        std::chrono::steady_clock::time_point TriggerTime;
        TimerFunc Callback;
        int Value;
    };

    struct GlutContext
    {
        std::optional<OpenGL1Window> Window{ std::nullopt };
        std::optional<OpenGLLoader>  Loader{ std::nullopt };

        std::size_t Width{ 800 };
        std::size_t Height{ 600 };
        std::string Title{ "GLUT Window" };

        DisplayFunc       OnDisplay{ nullptr };
        ReshapeFunc       OnReshape{ nullptr };
        KeyboardFunc      OnKeyboard{ nullptr };
        IdleFunc          OnIdle{ nullptr };
        MouseFunc         OnMouse{ nullptr };
        MotionFunc        OnMotion{ nullptr };
        PassiveMotionFunc OnPassiveMotion{ nullptr };
        SpecialFunc       OnSpecial{ nullptr };
        KeyboardUpFunc    OnKeyboardUp{ nullptr };
        SpecialUpFunc     OnSpecialUp{ nullptr };

        int MouseX{ 0 };
        int MouseY{ 0 };
        bool IsInitialized{ false };

        std::vector<TimerInfo> Timers{};
    };

    GlutContext context{};

    inline void ProcessKeyboardEvent(const WinLite::Keyboard& keyboard, int mouseX, int mouseY) noexcept
    {
        const bool isPressed = (keyboard.State == ButtonState::Pressed);

        if (unsigned char keyChar = MapKeyToAscii(keyboard.KeyCode); keyChar != 0)
        {
            if (isPressed)
            {
                if (context.OnKeyboard) context.OnKeyboard(keyChar, mouseX, mouseY);
            }
            else
            {
                if (context.OnKeyboardUp) context.OnKeyboardUp(keyChar, mouseX, mouseY);
            }
            return;
        }

        if (int specialKey = MapKeyToSpecial(keyboard.KeyCode); specialKey != -1)
        {
            if (isPressed)
            {
                if (context.OnSpecial) context.OnSpecial(specialKey, mouseX, mouseY);
            }
            else
            {
                if (context.OnSpecialUp) context.OnSpecialUp(specialKey, mouseX, mouseY);
            }
        }
    }

    inline void ProcessMouseMove(const WinLite::Mouse& mouse) noexcept
    {
        context.MouseX = mouse.PosX;
        context.MouseY = mouse.PosY;

        if (mouse.State == ButtonState::Pressed)
        {
            if (context.OnMotion)
            {
                context.OnMotion(context.MouseX, context.MouseY);
            }
        }
        else
        {
            if (context.OnPassiveMotion)
            {
                context.OnPassiveMotion(context.MouseX, context.MouseY);
            }
        }
    }

    inline void ProcessMouseClick(const WinLite::Mouse& mouse) noexcept
    {
        if (!context.OnMouse) return;

        int glutButton = -1;
        int glutState = (mouse.State == ButtonState::Pressed) ? GLUT_DOWN : GLUT_UP;

        if (mouse.Button == MouseButton::Left)        glutButton = GLUT_LEFT_BUTTON;
        else if (mouse.Button == MouseButton::Middle) glutButton = GLUT_MIDDLE_BUTTON;
        else if (mouse.Button == MouseButton::Right)  glutButton = GLUT_RIGHT_BUTTON;

        if (glutButton != -1)
        {
            context.OnMouse(glutButton, glutState, mouse.PosX, mouse.PosY);
        }
    }

    void glutInit(int* argc, char** argv) noexcept
    {
        (void)argc;
        (void)argv;
        context.IsInitialized = true;
    }

    void glutInitWindowSize(int width, int height) noexcept
    {
        if (width > 0 && height > 0)
        {
            context.Width = static_cast<std::size_t>(width);
            context.Height = static_cast<std::size_t>(height);
        }
    }

    void glutInitDisplayMode(unsigned int mode) noexcept
    {
        (void)mode;
    }

    int glutCreateWindow(const char* title) noexcept
    {
        if (!context.IsInitialized) [[unlikely]]
        {
            std::println("Error: glutCreateWindow called before glutInit.");
            return 0;
        }

        if (title != nullptr)
        {
            context.Title = title;
        }

        constexpr std::size_t glLimit = static_cast<std::size_t>(std::numeric_limits<GLsizei>::max());
        if (context.Width > glLimit || context.Height > glLimit) [[unlikely]]
        {
            std::println("Error: Window sizes exceed OpenGL GLsizei limits.");
            return 0;
        }

        auto windowResult = OpenGL1Window::Create(context.Width, context.Height, context.Title);
        if (!windowResult) [[unlikely]]
        {
            std::println("Error creating GLUT window: {}", windowResult.error());
            return 0;
        }

        context.Window.emplace(std::move(*windowResult));
        context.Loader.emplace(1, 2);

        glViewport(0, 0, static_cast<GLsizei>(context.Width), static_cast<GLsizei>(context.Height));

        return 1;
    }

    void glutDisplayFunc(DisplayFunc func) noexcept { context.OnDisplay = func; }
    void glutReshapeFunc(ReshapeFunc func) noexcept { context.OnReshape = func; }
    void glutKeyboardFunc(KeyboardFunc func) noexcept { context.OnKeyboard = func; }
    void glutIdleFunc(IdleFunc func) noexcept { context.OnIdle = func; }
    void glutMouseFunc(MouseFunc func) noexcept { context.OnMouse = func; }
    void glutMotionFunc(MotionFunc func) noexcept { context.OnMotion = func; }
    void glutPassiveMotionFunc(PassiveMotionFunc func) noexcept { context.OnPassiveMotion = func; }
    void glutSpecialFunc(SpecialFunc func) noexcept { context.OnSpecial = func; }
    void glutKeyboardUpFunc(KeyboardUpFunc func) noexcept { context.OnKeyboardUp = func; }
    void glutSpecialUpFunc(SpecialUpFunc func) noexcept { context.OnSpecialUp = func; }

    void glutSwapBuffers() noexcept
    {
        if (context.Window.has_value()) [[likely]]
        {
            context.Window->Present();
        }
    }

    void glutTimerFunc(unsigned int msecs, TimerFunc func, int value) noexcept
    {
        if (!func) return;

        auto triggerTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(msecs);
        context.Timers.push_back(TimerInfo{ triggerTime, func, value });
    }

    inline void ProcessTimers() noexcept
    {
        if (context.Timers.empty()) return;

        auto now = std::chrono::steady_clock::now();

        std::vector<TimerInfo> expiredTimers;

        auto it = std::remove_if(context.Timers.begin(), context.Timers.end(), [&](const TimerInfo& timer) {
            if (now >= timer.TriggerTime) 
            {
                expiredTimers.push_back(timer);
                return true;
            }
            return false;
            });
        context.Timers.erase(it, context.Timers.end());

        for (const auto& timer : expiredTimers)
        {
            timer.Callback(timer.Value);
        }
    }

    void glutPostRedisplay() noexcept {}

    void glutMainLoop() noexcept
    {
        if (!context.Window.has_value()) [[unlikely]]
        {
            return;
        }

        auto& window = *context.Window;

        while (window.IsRunning())
        {
            Event event;
            while (window.GetEvent(event))
            {
                if (event.Type == EventType::Quit || event.IsKeyPressed(Key::Escape))
                {
                    window.StopEvent();
                }
                else if (event.Type == EventType::Keyboard)
                {
                    ProcessKeyboardEvent(event.Keyboard, context.MouseX, context.MouseY);
                }
                else if (event.Type == EventType::MouseMove)
                {
                    ProcessMouseMove(event.Mouse);
                }
                else if (event.Type == EventType::MouseClick)
                {
                    ProcessMouseClick(event.Mouse);
                }
                else if (event.Type == EventType::Resize)
                {
                    context.Width = static_cast<std::size_t>(event.Resize.Width);
                    context.Height = static_cast<std::size_t>(event.Resize.Height);

                    if (context.OnReshape)
                    {
                        context.OnReshape(static_cast<int>(context.Width), static_cast<int>(context.Height));
                    }
                }
            }

            if (context.OnIdle)
            {
                context.OnIdle();
            }

            if (context.OnDisplay)
            {
                context.OnDisplay();
            }

            //window.Present();

            ProcessTimers();
        }
    }
}
