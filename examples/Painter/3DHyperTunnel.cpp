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

struct Star3D {
    float x;
    float y;
    float z;
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: 3D Hyper-Tunnel"))
    {
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> coordDist(-400.0f, 400.0f);
    std::uniform_real_distribution<float> depthDist(1.0f, 1000.0f);

    constexpr std::size_t maxStars = 250;
    std::vector<Star3D> stars(maxStars);
    for (auto& star : stars)
    {
        star.x = coordDist(gen);
        star.y = coordDist(gen);
        star.z = depthDist(gen);
    }

    float elapsed = 0.0f;

    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;

        for (auto& star : stars)
        {
            star.z -= 6.0f;

            if (star.z <= 0.0f)
            {
                star.z = 1000.0f;
                star.x = coordDist(gen);
                star.y = coordDist(gen);
            }
        }
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 4, 4, 10, 255 });
        painter.Clear();

        int tunnelOffsetX = static_cast<int>(std::sin(elapsed * 1.2f) * 50.0f);
        int tunnelOffsetY = static_cast<int>(std::cos(elapsed * 0.9f) * 40.0f);

        constexpr int totalRings = 16;
        float tunnelSpeed = elapsed * 60.0f;

        for (int i = 0; i < totalRings; ++i)
        {
            float rawRadius = (static_cast<float>(i) * 35.0f) - std::fmod(tunnelSpeed, 35.0f);
            if (rawRadius < 0.0f)
            {
                rawRadius += (totalRings * 35.0f);
            }

            float depthFactor = rawRadius / 500.0f;
            int projectedRadius = static_cast<int>(rawRadius * (1.0f + depthFactor));

            if (projectedRadius < static_cast<int>(width))
            {
                std::uint8_t colorIntensity = static_cast<std::uint8_t>(std::clamp((rawRadius / 500.0f) * 200.0f, 0.0f, 255.0f));

                painter.SetColor(Color{ 0, colorIntensity, static_cast<std::uint8_t>(colorIntensity / 2), 255 });
                painter.Circle(centerX + tunnelOffsetX, centerY + tunnelOffsetY, projectedRadius);
            }
        }

        for (const auto& star : stars)
        {
            float fovMultiplier = 400.0f;
            int screenX = static_cast<int>((star.x * fovMultiplier) / star.z) + centerX;
            int screenY = static_cast<int>((star.y * fovMultiplier) / star.z) + centerY;

            if (static_cast<std::size_t>(screenX) < width &&
                static_cast<std::size_t>(screenY) < height)
            {
                std::uint8_t starBrightness = static_cast<std::uint8_t>((1.0f - (star.z / 1000.0f)) * 255.0f);
                painter.SetColor(Color{ starBrightness, starBrightness, starBrightness, 255 });

                if (star.z < 250.0f)
                {
                    int trailingScreenX = static_cast<int>((star.x * fovMultiplier) / (star.z + 18.0f)) + centerX;
                    int trailingScreenY = static_cast<int>((star.y * fovMultiplier) / (star.z + 18.0f)) + centerY;

                    painter.Line(screenX, screenY, trailingScreenX, trailingScreenY);
                }
                else
                {
                    painter.Pixel(static_cast<std::size_t>(screenX), static_cast<std::size_t>(screenY));
                }
            }
        }
        };

    app.Run();

    return 0;
}
