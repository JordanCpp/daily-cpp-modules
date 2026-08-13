// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <memory_resource>
#include <cstdint>
#include <chrono>

export module FpsCounter;

export class FpsCounter 
{
public:
    FpsCounter() : 
        _lastTime(std::chrono::steady_clock::now()) 
    {
    }

    bool Update()
    {
        _frameCount++;

        auto now     = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastTime);

        if (elapsed.count() >= 1000) 
        {
            _fps        = _frameCount;
            _frameCount = 0;
            _lastTime   = now;

            return true;
        }

        return false;
    }

    [[nodiscard]] unsigned int GetFps() const noexcept 
    {
        return _fps;
    }

private:
    std::chrono::steady_clock::time_point _lastTime;
    std::size_t _frameCount{ 0 };
    std::size_t _fps{ 0 };
};
