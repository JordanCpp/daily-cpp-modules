// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example demonstrates the usage of the native PixelPainter::Pixel API
 * to render a smooth procedural plasma. To maintain high performance while
 * strictly using the abstraction layer, heavily repetitive math calculations
 * are shifted to the outer loops, and math operations are pre-cached.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

import WinLite;
import PixelPainter;
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
    constexpr std::size_t bytesPerPixel = 4;

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Sine Plasma via Pixel API");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Using your PixelPainter abstraction layer explicitly
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    auto startTime = std::chrono::steady_clock::now();

    // Pre-calculate X-axis normalized coordinates to save CPU cycles inside the hot loop
    std::vector<float> xNorm(width);
    for (std::size_t x = 0; x < width; ++x)
    {
        xNorm[x] = static_cast<float>(x) / static_cast<float>(width);
    }

    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }
        }

        auto currentTime = std::chrono::steady_clock::now();
        float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

        // Clear screens using the API state
        painter.SetColor(Color{ 0, 0, 0, 255 });
        painter.Clear();

        // Animate plasma wave steps outside the inner loops
        float waveTime1 = elapsed * 3.0f;
        float waveTime2 = elapsed * 2.0f;
        float centerX = 0.5f + 0.2f * std::sin(elapsed * 0.8f);
        float centerY = 0.5f + 0.2f * std::cos(elapsed * 0.6f);

        for (std::size_t y = 0; y < height; ++y)
        {
            float fy = static_cast<float>(y) / static_cast<float>(height);

            // Pre-calculate vertical component of distance to moving center
            float dy = fy - centerY;
            float dy_sqr = dy * dy;

            // Pre-calculate vertical sine wave component
            float v_vertical = std::sin(fy * 6.0f + waveTime1);

            for (std::size_t x = 0; x < width; ++x)
            {
                float fx = xNorm[x];

                // Wave 1: Dynamic distance-based distortion from a moving point
                float dx = fx - centerX;
                float dist = std::sqrt(dx * dx + dy_sqr);
                float v1 = std::sin(dist * 14.0f - waveTime2);

                // Wave 2: Fast horizontal component combined with pre-cached vertical component
                float v2 = std::sin(fx * 5.0f + waveTime1) + v_vertical;

                float finalValue = (v1 + v2) * 0.5f;

                // Map mathematical waves into bright neon palette ranges
                std::uint8_t r = static_cast<std::uint8_t>(127.5f + 127.5f * std::sin(finalValue * Math::PI));
                std::uint8_t g = static_cast<std::uint8_t>(64.0f + 64.0f * std::cos(finalValue * Math::PI * 2.0f));
                std::uint8_t b = static_cast<std::uint8_t>(180.0f + 75.0f * std::sin(finalValue * Math::PI + waveTime1));

                // Strictly demonstrating the PixelPainter::Pixel API execution
                painter.SetColor(Color{ r, g, b, 255 });
                painter.Pixel(x, y);
            }
        }

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Plasma Engine (Pixel API) - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
