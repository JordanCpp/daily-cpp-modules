// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

import std;

export module FpsCounter;

export class FpsCounter
{
public:
    FpsCounter() noexcept :
        _lastTime(std::chrono::steady_clock::now())
    {
    }

    bool Update() noexcept
    {
        _frameCount++;
        const auto now = std::chrono::steady_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastTime);

        if (elapsed.count() >= 1000)
        {
            _fps        = _frameCount;
            _frameCount = 0;
            _lastTime  += std::chrono::duration_cast<std::chrono::steady_clock::duration>(elapsed);

            return true;
        }

        return false;

    }

    [[nodiscard]] std::uint32_t GetFps() const noexcept
    {
        return _fps;
    }

private:
    std::chrono::steady_clock::time_point _lastTime;
    std::uint32_t _frameCount{ 0 };
    std::uint32_t _fps{ 0 };
};
