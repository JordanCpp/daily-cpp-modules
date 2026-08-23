// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import App;
import WinLite;
import PixelPainter;
import PixelCopier;
import FpsCounter;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Morphing Julia Fractal"))
    {
        return -1;
    }

    float cRe = -0.7f;
    float cIm = 0.27015f;
    float elapsed = 0.0f;

    constexpr float zoom = 1.2f;
    constexpr float moveX = 0.0f;
    constexpr float moveY = 0.0f;
    constexpr int maxIterations = 32;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            cRe = (static_cast<float>(event.Mouse.PosX) / static_cast<float>(width)) * 2.0f - 1.0f;
            cIm = (static_cast<float>(event.Mouse.PosY) / static_cast<float>(height)) * 2.0f - 1.0f;
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 0, 0, 0, 255 });
        painter.Clear();

        for (std::size_t y = 0; y < height; y += 2)
        {
            float im = 1.5f * (static_cast<float>(y) - static_cast<float>(height) / 2.0f) / (0.5f * zoom * static_cast<float>(height)) + moveY;

            for (std::size_t x = 0; x < width; x += 2)
            {
                float re = 1.5f * (static_cast<float>(x) - static_cast<float>(width) / 2.0f) / (0.5f * zoom * static_cast<float>(width)) + moveX;

                float zRe = re;
                float zIm = im;
                int iterCount = 0;

                while (zRe * zRe + zIm * zIm < 4.0f && iterCount < maxIterations)
                {
                    float nextRe = zRe * zRe - zIm * zIm + cRe;
                    float nextIm = 2.0f * zRe * zIm + cIm;

                    zRe = nextRe;
                    zIm = nextIm;
                    ++iterCount;
                }

                if (iterCount < maxIterations)
                {
                    float colorRatio = static_cast<float>(iterCount) / static_cast<float>(maxIterations);

                    std::uint8_t r = static_cast<std::uint8_t>(std::sin(colorRatio * 3.0f + elapsed) * 127.5f + 127.5f);
                    std::uint8_t g = static_cast<std::uint8_t>(std::cos(colorRatio * 5.0f - elapsed) * 64.0f + 64.0f);
                    std::uint8_t b = static_cast<std::uint8_t>(colorRatio * 255.0f);

                    painter.SetColor(Color{ r, g, b, 255 });

                    painter.Pixel(x, y);
                    painter.Pixel(x + 1, y);
                    painter.Pixel(x, y + 1);
                    painter.Pixel(x + 1, y + 1);
                }
            }
        }
        };

    app.Run();

    return 0;
}
