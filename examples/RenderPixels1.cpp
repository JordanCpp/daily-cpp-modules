// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <span>
#include <vector>
#include <cstdint>
#include <iostream>

import WinLite;
import SoftwareRender;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr int width = 800;
    constexpr int height = 600;
    constexpr int bytesPerPixel = 3;

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Combined Demo");

    if (!windowResult)
    {
        std::cout << "Error: " << windowResult.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);

    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    SoftwareRender<bytesPerPixel> render(width, height, std::span<std::uint8_t>(frameBuffer));

    constexpr Color backgroundColor{ 24, 28, 36 };
    constexpr Color gridColor{ 46, 54, 66 };
    constexpr Color rectColor{ 230, 90, 80 };
    constexpr Color lineColor{ 80, 200, 140 };
    constexpr Color pixelColor{ 240, 210, 90 };

    int animationOffset = 0;

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

        render.Clear(backgroundColor);

        for (int x = 0; x < width; x += 40)
        {
            render.Line(x, 0, x, height, gridColor);
        }
        for (int y = 0; y < height; y += 40)
        {
            render.Line(0, y, width, y, gridColor);
        }

        render.Fill(100, 100, 250, 180, rectColor);
        render.Fill(450, 320, 200, 150, Color{ 60, 130, 240 });

        render.Line(40, 40, 760, 560, lineColor);
        render.Line(760, 40, 40 + animationOffset, 560, Color{ 220, 80, 220 });

        for (int i = 0; i < 150; i += 4)
        {
            render.Pixel(300 + i, 200 + animationOffset / 4, pixelColor);
        }

        animationOffset = (animationOffset + 2) % 600;

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);
    }

    return 0;
}
