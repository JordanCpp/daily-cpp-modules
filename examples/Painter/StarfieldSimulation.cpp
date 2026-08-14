// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <span>
#include <vector>
#include <cstdint>
#include <iostream>
#include <random>
#include <algorithm>

import WinLite;
import Painter;

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
    constexpr std::size_t bytesPerPixel = 3;

    auto windowResult = SoftwareWindow::Create(
        static_cast<int>(width),
        static_cast<int>(height),
        "Daily C++ Modules: Starfield Simulation"
    );

    if (!windowResult)
    {
        std::cout << "Error: " << windowResult.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);
    Painter render(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));

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

        render.SetColor(Color{ 10, 10, 15 });
        render.Clear();

        for (auto& star : stars)
        {
            star.z -= speed;

            if (star.z <= 0.0f)
            {
                star.x = distCoord(gen);
                star.y = distCoord(gen);
                star.z = maxDepth;
                continue;
            }

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

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);
    }

    return 0;
}
