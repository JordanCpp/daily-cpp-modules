// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a real-time Mathematical Vector Magnetic Field simulation.
 * It populates the screen with a discrete grid of needle-like vector directional lines.
 * Two magnetic monopoles (one positive, one negative) exert a spatial force field based on Coulomb's law.
 * The active positive attractor pole is bound to the cursor position (PosX, PosY).
 * The PixelPainter::Line API is utilized to draw the dynamically calculated force vectors
 * across the 2D layout.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

// Structure holding structural attributes of a magnetic field charge node
struct MagnetPole {
    float x;
    float y;
    float charge; // Positive value attracts vectors, negative repels them
};

int main()
{
    // Screen geometry setup values and 32-bit pixel allocation bounds
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit RGBA/BGRA video layout buffer

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Magnetic Vector Field");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize the fundamental underlying graphics painter context layout
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Define two opposite magnetic poles inside world space
    MagnetPole movingPole{ 400.0f, 400.0f, 1.0f };  // Dynamic positive attractor linked to mouse
    MagnetPole staticPole{ 400.0f, 250.0f, -1.0f }; // Stationary negative repeller anchor

    // Structural needle field parameters
    constexpr int fieldResolution = 30; // Grid density spacing step
    constexpr float maxNeedleLength = 14.0f;

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

            // Bind the active attractor position updates matching your WinLite event loop structures
            if (event.Type == EventType::MouseMove)
            {
                movingPole.x = static_cast<float>(event.Mouse.PosX);
                movingPole.y = static_cast<float>(event.Mouse.PosY);
            }
        }

        auto currentTime = std::chrono::steady_clock::now();
        float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

        // Animate the static repeller pole in a gentle mathematical circle path over time
        staticPole.x = 400.0f + std::sin(elapsed * 1.0f) * 180.0f;
        staticPole.y = 400.0f + std::cos(elapsed * 0.8f) * 140.0f;

        // Clean screen space completely using dark navy graphite tones
        painter.SetColor(Color{ 10, 14, 22, 255 });
        painter.Clear();

        // Execute grid traversal to compute local mathematical magnetic field indices
        for (int y = fieldResolution / 2; y < static_cast<int>(height); y += fieldResolution)
        {
            for (int x = fieldResolution / 2; x < static_cast<int>(width); x += fieldResolution)
            {
                float fx = static_cast<float>(x);
                float fy = static_cast<float>(y);

                // Force Vector Component accumulation initialization step
                float totalForceX = 0.0f;
                float totalForceY = 0.0f;

                // 1. Calculate force vectors from Pole 1 (Moving Attractor)
                float dx1 = movingPole.x - fx;
                float dy1 = movingPole.y - fy;
                float distSqr1 = dx1 * dx1 + dy1 * dy1 + 1000.0f; // Add a soften factor to bypass divide-by-zero anomalies
                float dist1 = std::sqrt(distSqr1);

                // Coulomb force projection equation mapping
                totalForceX += (dx1 / dist1) * (movingPole.charge * 20000.0f / distSqr1);
                totalForceY += (dy1 / dist1) * (movingPole.charge * 20000.0f / distSqr1);

                // 2. Calculate force vectors from Pole 2 (Static Repeller)
                float dx2 = static_cast<float>(staticPole.x) - fx;
                float dy2 = static_cast<float>(staticPole.y) - fy;
                float distSqr2 = dx2 * dx2 + dy2 * dy2 + 1000.0f;
                float dist2 = std::sqrt(distSqr2);

                totalForceX += (dx2 / dist2) * (staticPole.charge * 20000.0f / distSqr2);
                totalForceY += (dy2 / dist2) * (staticPole.charge * 20000.0f / distSqr2);

                // Compute directional vector properties and clip length bounds safely
                float fieldIntensity = std::sqrt(totalForceX * totalForceX + totalForceY * totalForceY);

                if (fieldIntensity > 0.001f)
                {
                    float normX = totalForceX / fieldIntensity;
                    float normY = totalForceY / fieldIntensity;

                    // Bound vector needle dimension metrics based on local field strength
                    float actualLength = std::min(fieldIntensity * 8.0f, maxNeedleLength);

                    // Compute the symmetrical beginning and ending coordinates of the layout line
                    int startX = static_cast<int>(fx - normX * (actualLength * 0.5f));
                    int startY = static_cast<int>(fy - normY * (actualLength * 0.5f));
                    int endX = static_cast<int>(fx + normX * (actualLength * 0.5f));
                    int endY = static_cast<int>(fy + normY * (actualLength * 0.5f));

                    // Map intensity data levels to vivid neon electric emerald color gradients
                    std::uint8_t r = static_cast<std::uint8_t>(std::clamp(fieldIntensity * 45.0f, 30.0f, 100.0f));
                    std::uint8_t g = static_cast<std::uint8_t>(std::clamp(fieldIntensity * 90.0f, 120.0f, 255.0f));
                    std::uint8_t b = static_cast<std::uint8_t>(std::clamp(fieldIntensity * 70.0f, 80.0f, 200.0f));

                    painter.SetColor(Color{ r, g, b, 255 });
                    painter.Line(startX, startY, endX, endY);
                }
            }
        }

        // Draw explicit glowing markers representing the spatial location of the core charges
        // Attractor indicator (Bright electric cyan)
        painter.SetColor(Color{ 0, 200, 255, 255 });
        painter.Circle(static_cast<int>(movingPole.x), static_cast<int>(movingPole.y), 6);

        // Repeller indicator (Bright ruby coral pink)
        painter.SetColor(Color{ 255, 60, 100, 255 });
        painter.Circle(static_cast<int>(staticPole.x), static_cast<int>(staticPole.y), 6);

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Magnetic Field Simulation - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
