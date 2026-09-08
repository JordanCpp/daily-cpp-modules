// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

export module WinLite.OpenGL3Window;

import std;
import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
    class OpenGL3Window
    {
    private:
        MainWindow _impl;
        GLXContext _glxContext{nullptr};

        OpenGL3Window(MainWindow &&impl, GLXContext glxContext) noexcept : _impl(std::move(impl)),
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
        OpenGL3Window(OpenGL3Window &&other) noexcept : _impl(std::move(other._impl)),
                                                        _glxContext(other._glxContext)
        {
            other._glxContext = nullptr;
        }

        OpenGL3Window &operator=(OpenGL3Window &&other) noexcept
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

        OpenGL3Window(const OpenGL3Window &) = delete;
        OpenGL3Window &operator=(const OpenGL3Window &) = delete;

        static std::expected<OpenGL3Window, std::string> Create(std::size_t w, std::size_t h, const std::string &title)
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

            int screen = DefaultScreen(display);

            int fbAttributes[] = {
                GLX_RENDER_TYPE, GLX_RGBA_BIT,
                GLX_DOUBLEBUFFER, True,
                GLX_RED_SIZE, 8,
                GLX_GREEN_SIZE, 8,
                GLX_BLUE_SIZE, 8,
                GLX_DEPTH_SIZE, 24,
                None};

            int numConfigs = 0;
            GLXFBConfig *fbConfigs = glXChooseFBConfig(display, screen, fbAttributes, &numConfigs);
            if (!fbConfigs || numConfigs == 0)
            {
                return std::unexpected("Failed to find suitable GLX Framebuffer configuration.");
            }
            GLXFBConfig bestConfig = fbConfigs[0];
            XFree(fbConfigs);

            auto glXCreateContextAttribsARB = std::bit_cast<PFNGLXCREATECONTEXTATTRIBSARBPROC>(
                std::bit_cast<void *>(glXGetProcAddressARB(reinterpret_cast<const unsigned char *>("glXCreateContextAttribsARB"))));

            if (!glXCreateContextAttribsARB)
            {
                return std::unexpected("GLX_ARB_create_context extension is not supported by your GPU driver.");
            }

            int contextAttributes[] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                GLX_CONTEXT_MINOR_VERSION_ARB, 3,
                GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                None};

            GLXContext glxContext = glXCreateContextAttribsARB(display, bestConfig, nullptr, True, contextAttributes);
            if (!glxContext)
            {
                return std::unexpected("Failed to create OpenGL 3.3 Core Profile context.");
            }

            if (!glXMakeCurrent(display, window, glxContext))
            {
                glXDestroyContext(display, glxContext);
                return std::unexpected("Failed to make OpenGL 3.3 context current.");
            }

            return OpenGL3Window(std::move(windowImpl), glxContext);
        }

        ~OpenGL3Window()
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
