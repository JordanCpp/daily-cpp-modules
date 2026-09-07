// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#ifdef __GNUC__
#include <bits/c++config.h>
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

export module WinLite.OpenGL3Window;

import std;
import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
    constexpr std::uint32_t WGL_CONTEXT_MAJOR_VERSION_ARB    = 0x2091;
    constexpr std::uint32_t WGL_CONTEXT_MINOR_VERSION_ARB    = 0x2092;
    constexpr std::uint32_t WGL_CONTEXT_PROFILE_MASK_ARB     = 0x2093;
    constexpr std::uint32_t WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 0x00000001;

    typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARB)(HDC hdc, HGLRC HGLRCShare, int* attribs);

    class OpenGL3Window
    {
    private:
        MainWindow _impl;
        HDC        _hdc = nullptr;
        HGLRC      _hglrc = nullptr;

        OpenGL3Window(MainWindow&& impl, HDC hdc, HGLRC hglrc) noexcept :
            _impl(std::move(impl)),
            _hdc(hdc),
            _hglrc(hglrc)
        {
        }

        void ReleaseContexts() noexcept
        {
            if (_hglrc)
            {
                if (wglGetCurrentContext() == _hglrc)
                {
                    wglMakeCurrent(nullptr, nullptr);
                }

                wglDeleteContext(_hglrc);
                _hglrc = nullptr;
            }

            if (_hdc)
            {
                ReleaseDC(_impl.GetHwnd(), _hdc);
                _hdc = nullptr;
            }
        }

    public:
        OpenGL3Window(OpenGL3Window&& other) noexcept :
            _impl(std::move(other._impl)),
            _hdc(std::exchange(other._hdc, nullptr)),
            _hglrc(std::exchange(other._hglrc, nullptr))
        {
        }

        OpenGL3Window& operator=(OpenGL3Window&& other) noexcept
        {
            if (this != &other)
            {
                ReleaseContexts();

                _impl = std::move(other._impl);
                _hdc = std::exchange(other._hdc, nullptr);
                _hglrc = std::exchange(other._hglrc, nullptr);
            }

            return *this;
        }

        OpenGL3Window(const OpenGL3Window&) = delete;
        OpenGL3Window& operator=(const OpenGL3Window&) = delete;

        static std::expected<OpenGL3Window, std::string> Create(std::size_t w, std::size_t h, const std::string& title, float majorVersion = 3.3f, float minorVersion = 0.0f)
        {
            auto result = MainWindow::Create(w, h, title);
            if (!result.has_value())
            {
                return std::unexpected(result.error());
            }

            MainWindow windowImpl = std::move(*result);
            HDC hdc = windowImpl.GetHdc();
            if (!hdc)
            {
                return std::unexpected("Failed to get HDC from MainWindow");
            }

            PIXELFORMATDESCRIPTOR pfd{};
            pfd.nSize = sizeof(pfd);
            pfd.nVersion = 1;
            pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
            pfd.iPixelType = PFD_TYPE_RGBA;
            pfd.cColorBits = 32;
            pfd.cDepthBits = 24;
            pfd.cStencilBits = 8;
            pfd.iLayerType = PFD_MAIN_PLANE;

            int format = ChoosePixelFormat(hdc, &pfd);
            if (format == 0)
            {
                return std::unexpected("Failed to choose pixel format");
            }

            if (!SetPixelFormat(hdc, format, &pfd))
            {
                return std::unexpected("Failed to set pixel format");
            }

            HGLRC dummyContext = wglCreateContext(hdc);
            if (!dummyContext)
            {
                return std::unexpected("Failed to create dummy context");
            }

            wglMakeCurrent(hdc, dummyContext);
            auto wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARB>(reinterpret_cast<void(*)()>(wglGetProcAddress("wglCreateContextAttribsARB")));

            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(dummyContext);

            if (!wglCreateContextAttribsARB)
            {
                return std::unexpected("wglCreateContextAttribsARB not supported by driver");
            }

            int major = static_cast<int>(majorVersion);
            int minor = static_cast<int>(minorVersion);

            int attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, major,
                WGL_CONTEXT_MINOR_VERSION_ARB, minor,
                WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
            };

            HGLRC hglrc = wglCreateContextAttribsARB(hdc, nullptr, attribs);
            if (!hglrc)
            {
                return std::unexpected("Failed to create modern OpenGL context (Core Profile)");
            }

            if (!wglMakeCurrent(hdc, hglrc))
            {
                wglDeleteContext(hglrc);
                return std::unexpected("Failed to make modern OpenGL context current");
            }

            return OpenGL3Window(std::move(windowImpl), hdc, hglrc);
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

        bool GetEvent(Event& event) noexcept
        {
            return _impl.GetEvent(event);
        }

        void SetTitle(const std::string& title)
        {
            _impl.SetTitle(title);
        }

        void Present() noexcept
        {
            if (_hdc)
            {
                SwapBuffers(_hdc);
            }
        }
    };
}
