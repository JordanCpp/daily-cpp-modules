// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <span>
#include <cmath>
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

import WinLite;
import Painter;

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
        "Daily C++ Modules: Dynamic Demo"
    );

    if (!windowResult)
    {
        std::cout << "Error: " << windowResult.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    Painter render(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));

    float time = 0.0f;

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

        std::uint8_t bgR = static_cast<std::uint8_t>((std::sin(time * 0.5f) * 0.5f + 0.5f) * 40 + 10);
        std::uint8_t bgG = static_cast<std::uint8_t>((std::sin(time * 0.7f) * 0.5f + 0.5f) * 40 + 10);
        std::uint8_t bgB = static_cast<std::uint8_t>((std::sin(time * 0.9f) * 0.5f + 0.5f) * 50 + 20);

        render.SetColor(Color{ bgR, bgG, bgB });
        render.Clear();

        render.SetColor(Color{ 50, 50, 70 });

        for (int x = 0; x < static_cast<int>(width); x += 80)
        {
            
            render.Line(x, 0, x, static_cast<int>(height));
        }

        for (int y = 0; y < static_cast<int>(height); y += 80)
        {
            render.Line(0, y, static_cast<int>(width), y);
        }

        int rect1X = static_cast<int>(350 + std::cos(time) * 150);
        int rect1Y = static_cast<int>(220 + std::sin(time) * 100);
        render.SetColor(Color{ 230, 90, 80 });
        render.Fill(rect1X, rect1Y, 120, 120);

        int rect2X = static_cast<int>(370 + std::sin(time * 1.5f) * 200);
        render.SetColor(Color{ 60, 130, 240 });
        render.Fill(rect2X, 450, 80, 80);

        int centerX = static_cast<int>(width) / 2;
        int centerY = static_cast<int>(height) / 2;

        int line1X = static_cast<int>(centerX + std::cos(time * 0.8f) * 200);
        int line1Y = static_cast<int>(centerY + std::sin(time * 0.8f) * 200);
        render.SetColor(Color{ 80, 200, 140 });
        render.Line(centerX, centerY, line1X, line1Y);

        int line2X = static_cast<int>(centerX + std::cos(-time * 1.2f) * 150);
        int line2Y = static_cast<int>(centerY + std::sin(-time * 1.2f) * 150);
        render.SetColor(Color{ 220, 80, 220 });
        render.Line(centerX, centerY, line2X, line2Y);

        for (int i = 0; i < 400; i += 8)
        {
            int pX = static_cast<int>(centerX + std::sin(time * 2.0f + static_cast<float>(i)) * (i + 20));
            int pY = static_cast<int>(centerY + std::cos(time * 2.0f + static_cast<float>(i)) * (i + 20));

            if (pX >= 0 && pY >= 0)
            {
                std::size_t px = static_cast<std::size_t>(pX);
                std::size_t py = static_cast<std::size_t>(pY);

                std::uint8_t pR = static_cast<std::uint8_t>(200 + i % 55);
                std::uint8_t pG = static_cast<std::uint8_t>(180 + i % 75);
                render.SetColor(Color{ pR, pG, 50 });
                render.Pixel(px, py);
            }
        }

        time += 0.02f;

        window.Present(
            frameBuffer.data(),
            static_cast<int>(bytesPerPixel),
            static_cast<int>(width),
            static_cast<int>(height)
        );
    }

    return 0;
}
