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
    using DisplayFunc       = void(*)() noexcept;
    using ReshapeFunc       = void(*)(int, int) noexcept;
    using KeyboardFunc      = void(*)(unsigned char, int, int) noexcept;
    using IdleFunc          = void(*)() noexcept;
    using MouseFunc         = void(*)(int button, int state, int x, int y) noexcept;
    using MotionFunc        = void(*)(int x, int y) noexcept;
    using PassiveMotionFunc = void(*)(int x, int y) noexcept;

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

        int MouseX{ 0 };
        int MouseY{ 0 };
        bool IsInitialized{ false };
    };

    inline GlutContext context{};

    constexpr int GLUT_LEFT_BUTTON = 0;
    constexpr int GLUT_MIDDLE_BUTTON = 1;
    constexpr int GLUT_RIGHT_BUTTON = 2;
    constexpr int GLUT_DOWN = 0;
    constexpr int GLUT_UP = 1;

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

                if (context.OnKeyboard && event.Type == EventType::Keyboard)
                {
                    if (event.Keyboard.State == ButtonState::Pressed)
                    {
                        unsigned char keyChar = 0;

                        if (event.Keyboard.KeyCode >= Key::A && event.Keyboard.KeyCode <= Key::Z)
                        {
                            keyChar = static_cast<unsigned char>('a' + (static_cast<int>(event.Keyboard.KeyCode) - static_cast<int>(Key::A)));
                        }
                        else if (event.Keyboard.KeyCode == Key::Space)
                        {
                            keyChar = ' ';
                        }

                        if (keyChar != 0)
                        {
                            context.OnKeyboard(keyChar, context.MouseX, context.MouseY);
                        }
                    }
                }

                if (event.Type == EventType::MouseMove)
                {
                    context.MouseX = event.Mouse.PosX;
                    context.MouseY = event.Mouse.PosY;

                    if (event.Mouse.State == ButtonState::Pressed)
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

                if (context.OnMouse && event.Type == EventType::MouseClick)
                {
                    int glutButton = -1;
                    int glutState  = (event.Mouse.State == ButtonState::Pressed) ? GLUT_DOWN : GLUT_UP;

                    if (event.Mouse.Button == MouseButton::Left) glutButton = GLUT_LEFT_BUTTON;
                    else if (event.Mouse.Button == MouseButton::Middle) glutButton = GLUT_MIDDLE_BUTTON;
                    else if (event.Mouse.Button == MouseButton::Right) glutButton = GLUT_RIGHT_BUTTON;

                    if (glutButton != -1)
                    {
                        context.OnMouse(glutButton, glutState, event.Mouse.PosX, event.Mouse.PosY);
                    }
                }

                if (event.Type == EventType::Resize)
                {
                    context.Width  = static_cast<std::size_t>(event.Resize.Width);
                    context.Height = static_cast<std::size_t>(event.Resize.Height);

                    glViewport(0, 0, static_cast<GLsizei>(context.Width), static_cast<GLsizei>(context.Height));

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

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (context.OnDisplay)
            {
                context.OnDisplay();
            }

            window.Present();
        }
    }
}
