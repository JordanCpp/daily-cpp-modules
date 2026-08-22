// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example simulates an analog vector neon laser show using Lissajous curves.
 * It showcases the PixelPainter::Line API coupled with a screen-fading technique.
 * Instead of resetting the frame buffer instantly via Clear(), a semi-transparent
 * rectangle is layered over the viewport every frame using Fill(), creating an
 * authentic phosphor glow and gradual fade-out trajectory (motion blur tail).
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

namespace Math {
    constexpr float PI = 3.1415926535f;
}

int main()
{
    // Screen setup coordinates and 32-bit pixel mapping configuration
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 4 bytes layout for alpha support

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Lissajous Laser Show");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Bind initialization parameters directly to the engine instance
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    auto startTime = std::chrono::steady_clock::now();

    // Cache center spatial locations
    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);
    const float maxRadius = 320.0f; // Limit boundary size for graphics

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

        /*
         * RETRO LUMINESCENCE EFFECT:
         * Instead of painter.Clear(), we render a full-screen flat rectangle
         * with a small alpha value. This slowly blends the historical render
         * buffers downward into deep black, simulating vector CRT decay fields.
         */
        painter.SetColor(Color{ 10, 12, 18, 40 }); // Low alpha generates long persistent trails
        painter.Fill(0, 0, static_cast<int>(width), static_cast<int>(height));

        // Dynamically shift frequencies across time parameters for variation
        float freqX = 3.0f + std::sin(elapsed * 0.2f) * 2.0f;
        float freqY = 4.0f + std::cos(elapsed * 0.3f) * 2.0f;

        // Multi-phase shift transitions
        float phaseShift = elapsed * 2.5f;

        // Trace evaluation parameters
        constexpr int traceResolution = 300;
        int prevX = 0;
        int prevY = 0;

        for (int i = 0; i <= traceResolution; ++i)
        {
            // Normalize curve position parameters
            float t = (static_cast<float>(i) / static_cast<float>(traceResolution)) * 2.0f * Math::PI;

            // Generate Lissajous coordinate locations
            int xPos = centerX + static_cast<int>(maxRadius * std::sin(freqX * t + phaseShift));
            int yPos = centerY + static_cast<int>(maxRadius * std::sin(freqY * t));

            // Skip initialization step validation to link paths flawlessly
            if (i > 0)
            {
                // Smooth shift across color spectra for neon cyan/green laser colorations
                std::uint8_t r = static_cast<std::uint8_t>(20.0f + 30.0f * std::sin(elapsed + t));
                std::uint8_t g = static_cast<std::uint8_t>(200.0f + 55.0f * std::cos(elapsed * 1.3f + t));
                std::uint8_t b = static_cast<std::uint8_t>(180.0f + 75.0f * std::sin(elapsed * 0.8f + t));

                painter.SetColor(Color{ r, g, b, 255 });
                painter.Line(prevX, prevY, xPos, yPos);
            }

            prevX = xPos;
            prevY = yPos;
        }

        // Draw an explicit decorative laser core point exactly at the focal track tip
        painter.SetColor(Color{ 255, 255, 255, 255 });
        painter.Circle(prevX, prevY, 3);

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Lissajous Oscilloscope Show - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
