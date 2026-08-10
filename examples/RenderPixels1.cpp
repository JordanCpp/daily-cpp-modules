// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <span>
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

import WinLite;
import SoftwareRender;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;
    constexpr std::size_t bytesPerPixel = 3;

    auto windowResult = SoftwareWindow::Create(
        static_cast<int>(width),
        static_cast<int>(height),
        "Daily C++ Modules: Combined Demo"
    );

    if (!windowResult)
    {
        std::cout << "Error: " << windowResult.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);

    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    SoftwareRender render(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));

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

        render.SetColor(backgroundColor);
        render.Clear();

        render.SetColor(gridColor);
        for (int x = 0; x < static_cast<int>(width); x += 40)
        {
            render.Line(x, 0, x, static_cast<int>(height));
        }

        for (int y = 0; y < static_cast<int>(height); y += 40)
        {
            render.Line(0, y, static_cast<int>(width), y);
        }

        render.SetColor(rectColor);
        render.Fill(100, 100, 250, 180);

        render.SetColor(Color{ 60, 130, 240 });
        render.Fill(450, 320, 200, 150);

        render.SetColor(Color{ 220, 80, 220 });
        render.Line(40, 40, 760, 560);

        render.SetColor(gridColor);
        render.Line(760, 40, 40 + animationOffset, 560);

        render.SetColor(pixelColor);
        for (int i = 0; i < 150; i += 4)
        {
            std::size_t px = static_cast<std::size_t>(300 + i);
            std::size_t py = static_cast<std::size_t>(200 + animationOffset / 4);
            render.Pixel(px, py);
        }

        animationOffset = (animationOffset + 2) % 600;

        window.Present(
            frameBuffer.data(),
            static_cast<int>(bytesPerPixel),
            static_cast<int>(width),
            static_cast<int>(height)
        );
    }

    return 0;
}
