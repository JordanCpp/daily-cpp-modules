// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

import App;
import WinLite;
import PixelPainter;
import PixelCopier;
import FpsCounter;

using namespace WinLite;
using namespace Software;

struct MagnetPole {
    float x;
    float y;
    float charge;
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Magnetic Vector Field"))
    {
        return -1;
    }

    MagnetPole movingPole{ 400.0f, 400.0f, 1.0f };
    MagnetPole staticPole{ 400.0f, 250.0f, -1.0f };

    constexpr int fieldResolution = 30;
    constexpr float maxNeedleLength = 14.0f;

    float elapsed = 0.0f;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            movingPole.x = static_cast<float>(event.Mouse.PosX);
            movingPole.y = static_cast<float>(event.Mouse.PosY);
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;

        staticPole.x = 400.0f + std::sin(elapsed * 1.0f) * 180.0f;
        staticPole.y = 400.0f + std::cos(elapsed * 0.8f) * 140.0f;
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 10, 14, 22, 255 });
        painter.Clear();

        for (int y = fieldResolution / 2; y < static_cast<int>(height); y += fieldResolution)
        {
            for (int x = fieldResolution / 2; x < static_cast<int>(width); x += fieldResolution)
            {
                float fx = static_cast<float>(x);
                float fy = static_cast<float>(y);

                float totalForceX = 0.0f;
                float totalForceY = 0.0f;

                float dx1 = movingPole.x - fx;
                float dy1 = movingPole.y - fy;
                float distSqr1 = dx1 * dx1 + dy1 * dy1 + 1000.0f;
                float dist1 = std::sqrt(distSqr1);

                totalForceX += (dx1 / dist1) * (movingPole.charge * 20000.0f / distSqr1);
                totalForceY += (dy1 / dist1) * (movingPole.charge * 20000.0f / distSqr1);

                float dx2 = static_cast<float>(staticPole.x) - fx;
                float dy2 = static_cast<float>(staticPole.y) - fy;
                float distSqr2 = dx2 * dx2 + dy2 * dy2 + 1000.0f;
                float dist2 = std::sqrt(distSqr2);

                totalForceX += (dx2 / dist2) * (staticPole.charge * 20000.0f / distSqr2);
                totalForceY += (dy2 / dist2) * (staticPole.charge * 20000.0f / distSqr2);

                float fieldIntensity = std::sqrt(totalForceX * totalForceX + totalForceY * totalForceY);

                if (fieldIntensity > 0.001f)
                {
                    float normX = totalForceX / fieldIntensity;
                    float normY = totalForceY / fieldIntensity;

                    float actualLength = std::min(fieldIntensity * 8.0f, maxNeedleLength);

                    int startX = static_cast<int>(fx - normX * (actualLength * 0.5f));
                    int startY = static_cast<int>(fy - normY * (actualLength * 0.5f));
                    int endX = static_cast<int>(fx + normX * (actualLength * 0.5f));
                    int endY = static_cast<int>(fy + normY * (actualLength * 0.5f));

                    std::uint8_t r = static_cast<std::uint8_t>(std::clamp(fieldIntensity * 45.0f, 30.0f, 100.0f));
                    std::uint8_t g = static_cast<std::uint8_t>(std::clamp(fieldIntensity * 90.0f, 120.0f, 255.0f));
                    std::uint8_t b = static_cast<std::uint8_t>(std::clamp(fieldIntensity * 70.0f, 80.0f, 200.0f));

                    painter.SetColor(Color{ r, g, b, 255 });
                    painter.Line(startX, startY, endX, endY);
                }
            }
        }

        painter.SetColor(Color{ 0, 200, 255, 255 });
        painter.Circle(static_cast<int>(movingPole.x), static_cast<int>(movingPole.y), 6);

        painter.SetColor(Color{ 255, 60, 100, 255 });
        painter.Circle(static_cast<int>(staticPole.x), static_cast<int>(staticPole.y), 6);
        };

    app.Run();

    return 0;
}
