// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

export module WinLite.OpenGL1Window;

import std;
import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
    class OpenGL1Window
    {
    private:
        MainWindow _impl;
        GLXContext _glxContext{nullptr};

        OpenGL1Window(MainWindow &&impl, GLXContext glxContext) noexcept : _impl(std::move(impl)),
                                                                           _glxContext(glxContext)
        {
        }

        void ReleaseContexts() noexcept
        {
            Display *display = _impl.GetDisplay();
            if (display)
            {
                if (glXGetCurrentContext() == _glxContext)
                {
                    glXMakeCurrent(display, None, nullptr);
                }

                if (_glxContext)
                {
                    glXDestroyContext(display, _glxContext);
                    _glxContext = nullptr;
                }
            }
        }

    public:
        OpenGL1Window(OpenGL1Window &&other) noexcept : _impl(std::move(other._impl)),
                                                        _glxContext(other._glxContext)
        {
            other._glxContext = nullptr;
        }

        OpenGL1Window &operator=(OpenGL1Window &&other) noexcept
        {
            if (this != &other)
            {
                ReleaseContexts();

                _impl = std::move(other._impl);
                _glxContext = other._glxContext;

                other._glxContext = nullptr;
            }

            return *this;
        }

        OpenGL1Window(const OpenGL1Window &) = delete;
        OpenGL1Window &operator=(const OpenGL1Window &) = delete;

        static std::expected<OpenGL1Window, std::string> Create(std::size_t w, std::size_t h, const std::string &title)
        {
            auto result = MainWindow::Create(w, h, title);
            if (!result.has_value())
            {
                return std::unexpected(result.error());
            }

            MainWindow windowImpl = std::move(*result);
            Display *display = windowImpl.GetDisplay();
            Window window = windowImpl.GetWindow();

            if (!display || !window)
            {
                return std::unexpected("Invalid X11 display or window inside MainWindow.");
            }

            int glxAttributes[] = {
                GLX_RGBA,
                GLX_DOUBLEBUFFER,
                GLX_RED_SIZE, 8,
                GLX_GREEN_SIZE, 8,
                GLX_BLUE_SIZE, 8,
                GLX_DEPTH_SIZE, 16,
                None};

            int screen = DefaultScreen(display);
            XVisualInfo *visualInfo = glXChooseVisual(display, screen, glxAttributes);
            if (!visualInfo)
            {
                return std::unexpected("Failed to choose a suitable X11 Visual for OpenGL.");
            }

            GLXContext glxContext = glXCreateContext(display, visualInfo, nullptr, GL_TRUE);
            XFree(visualInfo);

            if (!glxContext)
            {
                return std::unexpected("Failed to create GLX context.");
            }

            if (!glXMakeCurrent(display, window, glxContext))
            {
                glXDestroyContext(display, glxContext);
                return std::unexpected("Failed to make GLX context current.");
            }

            return OpenGL1Window(std::move(windowImpl), glxContext);
        }

        ~OpenGL1Window()
        {
            ReleaseContexts();
        }

        [[nodiscard]] bool IsRunning() const noexcept
        {
            return _impl.IsRunning();
        }

        void StopEvent() noexcept
        {
            _impl.StopEvent();
        }

        bool GetEvent(Event &event) noexcept
        {
            return _impl.GetEvent(event);
        }

        void SetTitle(const std::string &title)
        {
            _impl.SetTitle(title);
        }

        void Present() noexcept
        {
            Display *display = _impl.GetDisplay();
            Window window = _impl.GetWindow();

            if (display && window && _glxContext)
            {
                glXSwapBuffers(display, window);
            }
        }
    };
}
