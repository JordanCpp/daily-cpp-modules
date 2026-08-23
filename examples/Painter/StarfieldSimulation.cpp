// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import App;
import WinLite;
import PixelPainter;
import PixelCopier;

using namespace WinLite;
using namespace Software;

struct Star
{
    float x;
    float y;
    float z;
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Starfield Simulation"))
    {
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distCoord(-300.0f, 300.0f);
    std::uniform_real_distribution<float> distZ(1.0f, 1000.0f);

    constexpr std::size_t maxStars = 400;
    std::vector<Star> stars(maxStars);

    constexpr float maxDepth = 1000.0f;
    constexpr float speed = 4.5f;
    constexpr float fov = 400.0f;

    const float centerX = static_cast<float>(width) / 2.0f;
    const float centerY = static_cast<float>(height) / 2.0f;

    for (auto& star : stars)
    {
        star.x = distCoord(gen);
        star.y = distCoord(gen);
        star.z = distZ(gen);
    }

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float) noexcept {
        for (auto& star : stars)
        {
            star.z -= speed;

            if (star.z <= 0.0f)
            {
                star.x = distCoord(gen);
                star.y = distCoord(gen);
                star.z = maxDepth;
            }
        }
        };

    app.OnRender = [&](PixelPainter& render, PixelCopier&) noexcept {
        render.SetColor(Color{ 10, 10, 15 });
        render.Clear();

        for (auto& star : stars)
        {
            if (star.z <= 0.0f) continue;

            int screenX = static_cast<int>(centerX + (star.x * fov) / star.z);
            int screenY = static_cast<int>(centerY + (star.y * fov) / star.z);

            if (screenX < 0 || screenX >= static_cast<int>(width) ||
                screenY < 0 || screenY >= static_cast<int>(height))
            {
                star.x = distCoord(gen);
                star.y = distCoord(gen);
                star.z = maxDepth;
                continue;
            }

            float brightnessFactor = 1.0f - (star.z / maxDepth);
            brightnessFactor = std::pow(brightnessFactor, 2.0f);

            auto brightness = static_cast<std::uint8_t>(brightnessFactor * 255.0f);

            std::size_t px = static_cast<std::size_t>(screenX);
            std::size_t py = static_cast<std::size_t>(screenY);

            std::uint8_t r = brightness;
            std::uint8_t g = brightness;
            std::uint8_t b = static_cast<std::uint8_t>(std::min(255.0f, brightness * 1.2f));

            render.SetColor(Color{ r, g, b });
            render.Pixel(px, py);
        }
        };

    app.Run();

    return 0;
}
