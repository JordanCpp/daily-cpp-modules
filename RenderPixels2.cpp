// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <cstdint>
#include <vector>
#include <iostream>
#include <span>
#include <cmath>

import WinLite;
import SoftwareRender;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr int width = 800;
    constexpr int height = 600;
    constexpr int bytesPerPixel = 3;

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Dynamic Demo");
    if (!windowResult)
    {
        std::cout << "Error: " << windowResult.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);
    SoftwareRender render(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer));

    float time = 0.0f;

    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if (event.Type == EventType::Quit)
            {
                window.StopEvent();
            }
        }

        std::uint8_t bgR = static_cast<std::uint8_t>((std::sin(time * 0.5f) * 0.5f + 0.5f) * 40 + 10);
        std::uint8_t bgG = static_cast<std::uint8_t>((std::sin(time * 0.7f) * 0.5f + 0.5f) * 40 + 10);
        std::uint8_t bgB = static_cast<std::uint8_t>((std::sin(time * 0.9f) * 0.5f + 0.5f) * 50 + 20);
        render.Clear(Color{ bgR, bgG, bgB });

        for (int x = 0; x < width; x += 80)  render.Line(x, 0, x, height, Color{ 50, 50, 70 });
        for (int y = 0; y < height; y += 80) render.Line(0, y, width, y, Color{ 50, 50, 70 });

        int rect1X = static_cast<int>(350 + std::cos(time) * 150);
        int rect1Y = static_cast<int>(220 + std::sin(time) * 100);
        render.Fill(rect1X, rect1Y, 120, 120, Color{ 230, 90, 80 });

        int rect2X = static_cast<int>(370 + std::sin(time * 1.5f) * 200);
        render.Fill(rect2X, 450, 80, 80, Color{ 60, 130, 240 });

        int centerX = width / 2;
        int centerY = height / 2;
        int line1X = static_cast<int>(centerX + std::cos(time * 0.8f) * 200);
        int line1Y = static_cast<int>(centerY + std::sin(time * 0.8f) * 200);
        render.Line(centerX, centerY, line1X, line1Y, Color{ 80, 200, 140 });

        int line2X = static_cast<int>(centerX + std::cos(-time * 1.2f) * 150);
        int line2Y = static_cast<int>(centerY + std::sin(-time * 1.2f) * 150);
        render.Line(centerX, centerY, line2X, line2Y, Color{ 220, 80, 220 });

        for (int i = 0; i < 400; i += 8)
        {
            int pX = static_cast<int>(centerX + std::sin(time * 2.0f + i) * (i + 20));
            int pY = static_cast<int>(centerY + std::cos(time * 2.0f + i) * (i + 20));

            std::uint8_t pR = static_cast<std::uint8_t>(200 + i % 55);
            std::uint8_t pG = static_cast<std::uint8_t>(180 + i % 75);
            render.Pixel(pX, pY, Color{ pR, pG, 50 });
        }

        time += 0.02f;

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);
    }

    return 0;
}
