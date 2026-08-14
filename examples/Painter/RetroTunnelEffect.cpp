// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
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

void DrawCenteredSquare(Painter& render, int centerX, int centerY, int size, Color color) noexcept
{
    if (size <= 0) return;

    int half = size / 2;
    int x0 = centerX - half;
    int y0 = centerY - half;
    int x1 = centerX + half;
    int y1 = centerY + half;

    render.SetColor(color);
    render.Line(x0, y0, x1, y0);
    render.Line(x0, y1, x1, y1);
    render.Line(x0, y0, x0, y1);
    render.Line(x1, y0, x1, y1);
}

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;
    constexpr std::size_t bytesPerPixel = 3;

    auto windowResult = SoftwareWindow::Create(
        static_cast<int>(width),
        static_cast<int>(height),
        "Daily C++ Modules: Retro Tunnel Effect"
    );

    if (!windowResult)
    {
        std::cout << "Error: " << windowResult.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);
    Painter render(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));

    const int centerX = static_cast<int>(width) / 2;
    const int centerY = static_cast<int>(height) / 2;

    float time = 0.0f;

    constexpr int numRings = 30;

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

        render.SetColor(Color{ 10, 5, 15 });
        render.Clear();

        float motionOffset = std::fmod(time * 0.5f, 1.0f);

        for (int i = 0; i < numRings; ++i)
        {
            float progress = (static_cast<float>(i) + motionOffset) / static_cast<float>(numRings);

            float sizeFactor = std::pow(progress, 3.0f);
            int size = static_cast<int>(sizeFactor * 1000.0f);

            if (size <= 2 || size > 1200) continue;

            float colorParam = progress * 6.28f - time * 2.0f;

            std::uint8_t r = static_cast<std::uint8_t>((std::sin(colorParam) * 0.5f + 0.5f) * 200 + 55);
            std::uint8_t g = static_cast<std::uint8_t>((std::sin(colorParam + 2.0f) * 0.5f + 0.5f) * 200 + 55);
            std::uint8_t b = static_cast<std::uint8_t>((std::cos(colorParam * 0.5f) * 0.5f + 0.5f) * 255);

            if (progress < 0.2f)
            {
                float fade = progress / 0.2f;
                r = static_cast<std::uint8_t>(r * fade);
                g = static_cast<std::uint8_t>(g * fade);
                b = static_cast<std::uint8_t>(b * fade);
            }

            DrawCenteredSquare(render, centerX, centerY, size, Color{ r, g, b });
        }

        time += 0.03f;

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);
    }

    return 0;
}
