// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <memory_resource>
#include <chrono>
#include <iostream>
#include <string_view>

export module HighResTimer;

export namespace Time
{
    class HighResTimer
    {
    private:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;

        TimePoint _startTime;
        TimePoint _endTime;
        bool _running{ false };

    public:
        constexpr HighResTimer() noexcept = default;

        void Start() noexcept
        {
            _startTime = Clock::now();
            _running = true;
        }

        void Stop() noexcept
        {
            _endTime = Clock::now();
            _running = false;
        }

        void Reset() noexcept
        {
            _running = false;
        }

        [[nodiscard]] double ElapsedSeconds() const noexcept
        {
            auto end = _running ? Clock::now() : _endTime;
            std::chrono::duration<double> diff = end - _startTime;
            return diff.count();
        }

        [[nodiscard]] std::uint64_t ElapsedMicroseconds() const noexcept
        {
            auto end = _running ? Clock::now() : _endTime;
            return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(end - _startTime).count());
        }

        [[nodiscard]] std::uint64_t ElapsedNanoseconds() const noexcept
        {
            auto end = _running ? Clock::now() : _endTime;
            return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - _startTime).count());
        }

        [[nodiscard]] bool IsRunning() const noexcept { return _running; }
    };
}
