// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a real-time, interactive Tesla Coil Lightning Generator.
 * It uses the Midpoint Displacement algorithm to recursively fracture a straight line
 * into jagged, branching electrical arcs. The lightning path dynamic targets the user's
 * mouse cursor positions (PosX, PosY). To capture the plasma ionization afterglow,
 * the screen uses a slow alpha fade-out technique via PixelPainter::Fill instead of a hard Clear().
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

// Lightweight static random generator context to prevent heap allocations inside frames
class FastRandom {
public:
    static float Range(float min, float max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }
};

void GenerateLightningBranch(PixelPainter& painter, int x0, int y0, int x1, int y1, float displace, float minDisplace);

// Global graphics context helper to isolate the recursive displacement stack
void GenerateLightningBranch(PixelPainter& painter, int x0, int y0, int x1, int y1, float displace, float minDisplace) {
    if (displace < minDisplace) {
        painter.Line(x0, y0, x1, y1);
        return;
    }

    // Compute the absolute midpoints of the structural line segments
    int midX = (x0 + x1) / 2;
    int midY = (y0 + y1) / 2;

    // Calculate perpendicular offset vectors based on displacement factors
    float deltaX = static_cast<float>(x1 - x0);
    float deltaY = static_cast<float>(y1 - y0);
    float length = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (length > 0.1f) {
        // Displace the midpoint perpendicular to the original line segment vector layout
        midX += static_cast<int>(((-deltaY / length) * FastRandom::Range(-displace, displace)));
        midY += static_cast<int>(((deltaX / length) * FastRandom::Range(-displace, displace)));
    }

    // Secondary structural branching probability triggers
    if (FastRandom::Range(0.0f, 1.0f) < 0.08f) {
        int branchEndX = midX + static_cast<int>(FastRandom::Range(-40.0f, 40.0f));
        int branchEndY = midY + static_cast<int>(FastRandom::Range(-40.0f, 40.0f));

        // Render sub-branches with reduced thickness/intensity attributes
        painter.SetColor(Color{ 80, 130, 255, 120 });
        GenerateLightningBranch(painter, midX, midY, branchEndX, branchEndY, displace * 0.4f, minDisplace);
    }

    // Recursively divide both halves of the newly fractured path structures
    GenerateLightningBranch(painter, x0, y0, midX, midY, displace * 0.5f, minDisplace);
    GenerateLightningBranch(painter, midX, midY, x1, y1, displace * 0.5f, minDisplace);
}

int main()
{
    // Screen viewport bounding areas and pixel allocation configuration blocks
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit pixel data array (RGBA/BGRA)

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Tesla Lightning Show");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize your native graphics abstraction wrapper context cleanly
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Track the static base emitter node directly in the viewport center coordinates
    const int emitterX = static_cast<int>(width / 2);
    const int emitterY = static_cast<int>(height / 2);

    // Set initial target cursor values safely off-screen
    int targetX = emitterX + 150;
    int targetY = emitterY + 150;

    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }

            // Bind spatial trace metrics directly to your WinLite API structures
            if (event.Type == EventType::MouseMove)
            {
                targetX = event.Mouse.PosX;
                targetY = event.Mouse.PosY;
            }
        }

        /*
         * PLASMA GLOW TRAILING EFFECT:
         * Layering a faint, alpha-transparent dark rectangle leaves residual
         * light signatures on the video plane, mimicking intense ion discharge.
         */
        painter.SetColor(Color{ 8, 5, 15, 60 });
        painter.Fill(0, 0, static_cast<int>(width), static_cast<int>(height));

        // Draw decorative central Tesla core emitter rings
        painter.SetColor(Color{ 255, 100, 50, 255 });
        painter.Circle(emitterX, emitterY, 14);
        painter.SetColor(Color{ 255, 255, 255, 255 });
        painter.Circle(emitterX, emitterY, 6);

        // Generate multiple striking lightning bolts to create a raw energy look
        int lightningStrikes = static_cast<int>(FastRandom::Range(1.0f, 3.0f));
        for (int strike = 0; strike < lightningStrikes; ++strike) {

            // Neon cyan core with random intensity flickers
            std::uint8_t r = static_cast<std::uint8_t>(140 + FastRandom::Range(0, 50));
            std::uint8_t g = static_cast<std::uint8_t>(200 + FastRandom::Range(0, 55));
            std::uint8_t b = 255;

            painter.SetColor(Color{ r, g, b, 255 });

            // Execute structural line fractals recursively down the path trajectory
            GenerateLightningBranch(painter, emitterX, emitterY, targetX, targetY, 160.0f, 4.0f);
        }

        // Draw a bright plasma impact core sphere exactly at the cursor intercept point
        painter.SetColor(Color{ 255, 255, 200, 255 });
        painter.Circle(targetX, targetY, 4);

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Tesla Plasma Generator - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
