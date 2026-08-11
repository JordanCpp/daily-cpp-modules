// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <string>
#include <expected>

export module WinLite.MainWindow;

import WinLite.Queue;
import WinLite.Events;
import WinLite.KeyMapper;

export namespace WinLite
{
    class MainWindow
    {
    public:
        void InitKeyMapper()
        {
        }

        static std::expected<MainWindow, std::string> Create(int w, int h, const std::string& title)
        {
            MainWindow window;

            return window;
        }

        ~MainWindow()
        {
        }

        MainWindow(MainWindow&& other) noexcept :
            _events(std::move(other._events))
        {
            InitKeyMapper();
        }

        MainWindow& operator=(MainWindow&& other) noexcept
        {
            if (this != &other)
            {
                _events = std::move(other._events);
            }

            return *this;
        }

        void PollEvents()
        {
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

        MainWindow(const MainWindow&) = delete;
        MainWindow& operator=(const MainWindow&) = delete;

    private:
        Queue     _events;
        KeyMapper _keyMapper;

        explicit MainWindow()
        {
        }
    };
}
