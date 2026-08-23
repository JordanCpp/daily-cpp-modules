// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

import App;
import WinLite;
import PixelPainter;
import PixelCopier;
import FpsCounter;

using namespace WinLite;
using namespace Software;

namespace Math {
    constexpr float PI = 3.1415926535f;
}

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Sine Plasma via Pixel API"))
    {
        return -1;
    }

    std::vector<float> xNorm(width);
    for (std::size_t x = 0; x < width; ++x)
    {
        xNorm[x] = static_cast<float>(x) / static_cast<float>(width);
    }

    float elapsed = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 0, 0, 0, 255 });
        painter.Clear();

        float waveTime1 = elapsed * 3.0f;
        float waveTime2 = elapsed * 2.0f;
        float centerX = 0.5f + 0.2f * std::sin(elapsed * 0.8f);
        float centerY = 0.5f + 0.2f * std::cos(elapsed * 0.6f);

        for (std::size_t y = 0; y < height; ++y)
        {
            float fy = static_cast<float>(y) / static_cast<float>(height);

            float dy = fy - centerY;
            float dy_sqr = dy * dy;

            float v_vertical = std::sin(fy * 6.0f + waveTime1);

            for (std::size_t x = 0; x < width; ++x)
            {
                float fx = xNorm[x];

                float dx = fx - centerX;
                float dist = std::sqrt(dx * dx + dy_sqr);
                float v1 = std::sin(dist * 14.0f - waveTime2);

                float v2 = std::sin(fx * 5.0f + waveTime1) + v_vertical;

                float finalValue = (v1 + v2) * 0.5f;

                std::uint8_t r = static_cast<std::uint8_t>(127.5f + 127.5f * std::sin(finalValue * Math::PI));
                std::uint8_t g = static_cast<std::uint8_t>(64.0f + 64.0f * std::cos(finalValue * Math::PI * 2.0f));
                std::uint8_t b = static_cast<std::uint8_t>(180.0f + 75.0f * std::sin(finalValue * Math::PI + waveTime1));

                painter.SetColor(Color{ r, g, b, 255 });
                painter.Pixel(x, y);
            }
        }
        };

    app.Run();

    return 0;
}
