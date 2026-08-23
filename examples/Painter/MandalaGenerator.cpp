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
    constexpr double PI = 3.14159265358979323846;
}

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Mandala Generator"))
    {
        return -1;
    }

    float elapsed = 0.0f;

    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);

    constexpr int symmetrySteps = 12;
    constexpr double angleStep = (2.0 * Math::PI) / symmetrySteps;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 5, 5, 15, 255 });
        painter.Clear();

        for (int i = 0; i < symmetrySteps; ++i)
        {
            double currentAngle = i * angleStep + (static_cast<double>(elapsed) * 0.2);

            double radius = 150.0 + 50.0 * std::sin(static_cast<double>(elapsed) * 1.5);

            int xEnd = centerX + static_cast<int>(radius * std::cos(currentAngle));
            int yEnd = centerY + static_cast<int>(radius * std::sin(currentAngle));

            painter.SetColor(Color{
                static_cast<std::uint8_t>(127 + 127 * std::sin(static_cast<double>(elapsed) + i)),
                static_cast<std::uint8_t>(127 + 127 * std::cos(static_cast<double>(elapsed) * 0.5)),
                255,
                255
                });

            painter.Line(centerX, centerY, xEnd, yEnd);
        }

        for (int i = 0; i < symmetrySteps; ++i)
        {
            double currentAngle = i * angleStep - (static_cast<double>(elapsed) * 0.5);
            double radius = 200.0 + 20.0 * std::cos(static_cast<double>(elapsed) * 2.0);

            int xPos = centerX + static_cast<int>(radius * std::cos(currentAngle));
            int yPos = centerY + static_cast<int>(radius * std::sin(currentAngle));

            painter.SetColor(Color{ 255, 255, 255, 255 });
            painter.Circle(xPos, yPos, 8);

            painter.SetColor(Color{ 255, 100, 100, 255 });
            painter.Circle(xPos, yPos, 3);
        }

        for (int i = 0; i < symmetrySteps * 2; ++i)
        {
            double currentAngle = i * (Math::PI / symmetrySteps) + (static_cast<double>(elapsed) * 0.8);
            double r1 = 100.0;
            double r2 = 250.0;

            int x1 = centerX + static_cast<int>(r1 * std::cos(currentAngle));
            int y1 = centerY + static_cast<int>(r1 * std::sin(currentAngle));
            int x2 = centerX + static_cast<int>(r2 * std::cos(currentAngle + Math::PI));
            int y2 = centerY + static_cast<int>(r2 * std::sin(currentAngle + Math::PI));

            painter.SetColor(Color{ 50, 255, 150, 150 });
            painter.Line(x1, y1, x2, y2);
        }
        };

    app.Run();

    return 0;
}
