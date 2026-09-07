// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

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
    private:
    public:
        void InitKeyMapper()
        {
        }

        static std::expected<MainWindow, std::string> Create(std::size_t w, std::size_t h, const std::string& title)
        {
            MainWindow window;

            if (w == 0)
            {
                return std::unexpected("");
            }

            if (h == 0)
            {
                return std::unexpected("");
            }

            window.SetTitle(title);

            return window;
        }

        ~MainWindow()
        {
        }

        MainWindow(MainWindow&& other) noexcept :
            _events(std::move(other._events)),
            _keyMapper{}
        {

            InitKeyMapper();
        }

        MainWindow& operator=(MainWindow&& other) noexcept
        {
            if (this != &other)
            {
                _events = std::move(other._events);
                _keyMapper = std::move(other._keyMapper);
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

        void SetTitle(const std::string& title)
        {
            if (!title.empty())
            {
            }
        }

        MainWindow(const MainWindow&) = delete;
        MainWindow& operator=(const MainWindow&) = delete;

    private:
        Queue     _events;
        KeyMapper _keyMapper;

        explicit MainWindow() :
            _events{},
            _keyMapper{}
        {
        }
    };
}
