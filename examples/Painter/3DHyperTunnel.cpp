// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a real-time 3D Hyper-Tunnel and Starfield simulation.
 * It demonstrates the efficiency of the PixelPainter geometric primitives API
 * (Circle, Line, and Pixel) by projecting pseudo-3D mathematical coordinates
 * into 2D screen space. The tunnel effect is created using concentric expanding
 * circles with time-based offsets and spatial center distortion.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <random>

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

namespace Math {
    constexpr float PI = 3.1415926535f;
}

// Structure to hold individual star data for the 3D space projection
struct Star3D {
    float x;
    float y;
    float z;
};

int main()
{
    // Screen resolution and pixel layout definitions
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit RGBA/BGRA mode

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: 3D Hyper-Tunnel");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize the internal PixelPainter engine state
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Set up a lightweight random number generator for initial star positions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> coordDist(-400.0f, 400.0f);
    std::uniform_real_distribution<float> depthDist(1.0f, 1000.0f);

    // Pre-allocate space for 250 dynamic space stars
    constexpr std::size_t maxStars = 250;
    std::vector<Star3D> stars(maxStars);
    for (auto& star : stars)
    {
        star.x = coordDist(gen);
        star.y = coordDist(gen);
        star.z = depthDist(gen);
    }

    auto startTime = std::chrono::steady_clock::now();

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

        auto currentTime = std::chrono::steady_clock::now();
        float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

        // Clear the backbuffer using the core painter API with deep space color
        painter.SetColor(Color{ 4, 4, 10, 255 });
        painter.Clear();

        // Screen center point calculations for geometric alignment
        const int centerX = static_cast<int>(width / 2);
        const int centerY = static_cast<int>(height / 2);

        // Calculate dynamic wave-like camera movement offsets over time
        int tunnelOffsetX = static_cast<int>(std::sin(elapsed * 1.2f) * 50.0f);
        int tunnelOffsetY = static_cast<int>(std::cos(elapsed * 0.9f) * 40.0f);

        // 1. RENDER PERSPECTIVE TUNNEL (Using the Circle API)
        constexpr int totalRings = 16;
        float tunnelSpeed = elapsed * 60.0f;

        for (int i = 0; i < totalRings; ++i)
        {
            // Linear ring radius calculation with a wrap-around check
            float rawRadius = (static_cast<float>(i) * 35.0f) - std::fmod(tunnelSpeed, 35.0f);
            if (rawRadius < 0.0f)
            {
                rawRadius += (totalRings * 35.0f);
            }

            // Exponential scaling to simulate perspective projection depth
            float depthFactor = rawRadius / 500.0f;
            int projectedRadius = static_cast<int>(rawRadius * (1.0f + depthFactor));

            if (projectedRadius < static_cast<int>(width))
            {
                // Deeper rings appear darker to naturally simulate distance fogging
                std::uint8_t colorIntensity = static_cast<std::uint8_t>(std::clamp((rawRadius / 500.0f) * 200.0f, 0.0f, 255.0f));

                // Set color and execute the internal geometric algorithm
                painter.SetColor(Color{ 0, colorIntensity, static_cast<std::uint8_t>(colorIntensity / 2), 255 });
                painter.Circle(centerX + tunnelOffsetX, centerY + tunnelOffsetY, projectedRadius);
            }
        }

        // 2. RENDER WARPING STARFIELD (Using the Line and Pixel APIs)
        for (auto& star : stars)
        {
            // Move stars closer to the viewer along the Z-axis
            star.z -= 6.0f;

            // Respawn stars instantly behind the clipping plane if they fly past the screen
            if (star.z <= 0.0f)
            {
                star.z = 1000.0f;
                star.x = coordDist(gen);
                star.y = coordDist(gen);
            }

            // Standard perspective divide equations (3D to 2D projection)
            float fovMultiplier = 400.0f;
            int screenX = static_cast<int>((star.x * fovMultiplier) / star.z) + centerX;
            int screenY = static_cast<int>((star.y * fovMultiplier) / star.z) + centerY;

            // Render only if the projected coordinates fit inside viewport margins
            if (static_cast<std::size_t>(screenX) < width &&
                static_cast<std::size_t>(screenY) < height)
            {
                // Calculate brightness based on depth (closer stars are brighter)
                std::uint8_t starBrightness = static_cast<std::uint8_t>((1.0f - (star.z / 1000.0f)) * 255.0f);
                painter.SetColor(Color{ starBrightness, starBrightness, starBrightness, 255 });

                // Render stars as stretching streaks (motion blur) when they get very close
                if (star.z < 250.0f)
                {
                    int trailingScreenX = static_cast<int>((star.x * fovMultiplier) / (star.z + 18.0f)) + centerX;
                    int trailingScreenY = static_cast<int>((star.y * fovMultiplier) / (star.z + 18.0f)) + centerY;

                    painter.Line(screenX, screenY, trailingScreenX, trailingScreenY);
                }
                else
                {
                    // Regular distant stars are rendered as crisp single points
                    painter.Pixel(static_cast<std::size_t>(screenX), static_cast<std::size_t>(screenY));
                }
            }
        }

        // Present backbuffer frames to the window display surface
        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("3D Hyper-Tunnel Engine - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
