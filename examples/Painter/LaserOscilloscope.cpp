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

namespace Math {
    constexpr float PI = 3.1415926535f;
}

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Lissajous Laser Show"))
    {
        return -1;
    }

    float elapsed = 0.0f;

    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);
    const float maxRadius = 320.0f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 10, 12, 18, 40 });
        painter.Fill(0, 0, static_cast<int>(width), static_cast<int>(height));

        float freqX = 3.0f + std::sin(elapsed * 0.2f) * 2.0f;
        float freqY = 4.0f + std::cos(elapsed * 0.3f) * 2.0f;

        float phaseShift = elapsed * 2.5f;

        constexpr int traceResolution = 300;
        int prevX = 0;
        int prevY = 0;

        for (int i = 0; i <= traceResolution; ++i)
        {
            float t = (static_cast<float>(i) / static_cast<float>(traceResolution)) * 2.0f * Math::PI;

            int xPos = centerX + static_cast<int>(maxRadius * std::sin(freqX * t + phaseShift));
            int yPos = centerY + static_cast<int>(maxRadius * std::sin(freqY * t));

            if (i > 0)
            {
                std::uint8_t r = static_cast<std::uint8_t>(20.0f + 30.0f * std::sin(elapsed + t));
                std::uint8_t g = static_cast<std::uint8_t>(200.0f + 55.0f * std::cos(elapsed * 1.3f + t));
                std::uint8_t b = static_cast<std::uint8_t>(180.0f + 75.0f * std::sin(elapsed * 0.8f + t));

                painter.SetColor(Color{ r, g, b, 255 });
                painter.Line(prevX, prevY, xPos, yPos);
            }

            prevX = xPos;
            prevY = yPos;
        }

        painter.SetColor(Color{ 255, 255, 255, 255 });
        painter.Circle(prevX, prevY, 3);
        };

    app.Run();

    return 0;
}
