// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

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

        OpenGL3Window(MainWindow&& impl) noexcept :
            _impl(std::move(impl))
        {
        }

        void ReleaseContexts() noexcept
        {
        }

    public:
        OpenGL3Window(OpenGL3Window&& other) noexcept :
            _impl(std::move(other._impl))
        {
        }

        OpenGL3Window& operator=(OpenGL3Window&& other) noexcept
        {
            if (this != &other)
            {
                ReleaseContexts();

                _impl = std::move(other._impl);
            }

            return *this;
        }

        OpenGL3Window(const OpenGL3Window&) = delete;
        OpenGL3Window& operator=(const OpenGL3Window&) = delete;

        static std::expected<OpenGL3Window, std::string> Create(std::size_t w, std::size_t h, const std::string& title)
        {
            auto result = MainWindow::Create(w, h, title);
            if (!result.has_value())
            {
                return std::unexpected(result.error());
            }

            MainWindow windowImpl = std::move(*result);

            return OpenGL3Window(std::move(windowImpl));
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
        }
    };
}
