// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a real-time 3D Point Cloud Engine rendering a double helix DNA structure.
 * It demonstrates how to perform manual 3D matrix transformations and perspective projections
 * using only the strict PixelPainter::Pixel and PixelPainter::Circle APIs.
 * To convey depth, particles are depth-sorted conceptually: points closer to the viewer (lower Z)
 * are rendered with heightened brightness and larger radius parameters, while distant points fade out.
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

namespace Math {
    constexpr float PI = 3.1415926535f;
}

// Internal node structure representing a fixed coordinate position in 3D global space
struct Point3D {
    float x;
    float y;
    float z;
    std::uint8_t baseColorR;
    std::uint8_t baseColorG;
    std::uint8_t baseColorB;
};

int main()
{
    // Screen resolution geometry constraints and 32-bit pixel mapping layouts
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit buffer array

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: 3D DNA Point Cloud");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Bind initialization parameters directly to the engine instance layout
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Generate static point coordinates forming a full double-stranded DNA chain
    std::vector<Point3D> dnaPoints;
    constexpr int totalNodesPerStrand = 180;
    constexpr float helixRadius = 120.0f;
    constexpr float helixLength = 500.0f;

    for (int i = 0; i < totalNodesPerStrand; ++i)
    {
        // Normalize linear position ratio along the vertical spine of the chain
        float progress = static_cast<float>(i) / static_cast<float>(totalNodesPerStrand);
        float angle = progress * 6.0f * Math::PI; // Complete three full structural spirals
        float yPos = (progress * helixLength) - (helixLength / 2.0f); // Center along world origin coordinate Y

        // Strand 1 generation (Adenine / Thymine color signature)
        float x1 = std::cos(angle) * helixRadius;
        float z1 = std::sin(angle) * helixRadius;
        dnaPoints.push_back(Point3D{ x1, yPos, z1, 255, 80, 80 });

        // Strand 2 generation: exact 180-degree phase shift (Cytosine / Guanine color signature)
        float x2 = std::cos(angle + Math::PI) * helixRadius;
        float z2 = std::sin(angle + Math::PI) * helixRadius;
        dnaPoints.push_back(Point3D{ x2, yPos, z2, 80, 160, 255 });

        // Structural cross-linking rungs connecting matching strand strands
        if (i % 6 == 0)
        {
            constexpr int rungDensity = 8;
            for (int r = 1; r < rungDensity; ++r)
            {
                float interpolationFactor = static_cast<float>(r) / static_cast<float>(rungDensity);
                float rx = x1 + (x2 - x1) * interpolationFactor;
                float rz = z1 + (z2 - z1) * interpolationFactor;
                dnaPoints.push_back(Point3D{ rx, yPos, rz, 200, 200, 200 });
            }
        }
    }

    auto startTime = std::chrono::steady_clock::now();

    // Constant parameters for camera positioning matrices
    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);
    constexpr float fovProjectionScale = 600.0f;
    constexpr float cameraZDistance = 650.0f; // Offset along viewing axis to avoid near clipping boundaries

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

        // Clear view area cleanly using deep slate profile tones
        painter.SetColor(Color{ 12, 14, 20, 255 });
        painter.Clear();

        // Dynamically compute angular transformation matrices based on timeline
        float angleY = elapsed * 0.8f;  // Continuous rotation along the vertical axis
        float angleX = std::sin(elapsed * 0.4f) * 0.4f; // Subtle oscillating pitch swing

        float cosY = std::cos(angleY);
        float sinY = std::sin(angleY);
        float cosX = std::cos(angleX);
        float sinX = std::sin(angleX);

        for (const auto& point : dnaPoints)
        {
            // Step 1: Execute manual Y-axis matrix spin formulas
            float rotY_X = point.x * cosY - point.z * sinY;
            float rotY_Z = point.x * sinY + point.z * cosY;

            // Step 2: Execute manual X-axis matrix tilt formulas
            float rotX_Y = point.y * cosX - rotY_Z * sinX;
            float rotX_Z = point.y * sinX + rotY_Z * cosX;

            // Step 3: Shift points safely into forward viewing frustum lines
            float finalZ = rotX_Z + cameraZDistance;

            // Simple safety boundary evaluation to bypass near zero division anomalies
            if (finalZ > 10.0f)
            {
                // Standard 3D matrix perspective calculation pipelines
                int screenX = static_cast<int>(rotY_X * fovProjectionScale / finalZ) + centerX;
                int screenY = static_cast<int>(rotX_Y * fovProjectionScale / finalZ) + centerY;

                // Clip projection calculations matching monitor boundary edge buffers
                if (static_cast<std::size_t>(screenX) < width &&
                    static_cast<std::size_t>(screenY) < height)
                {
                    // Linear fog fading interpolation scaling: closer points shine intensely
                    float depthRatio = std::clamp(1.0f - ((finalZ - (cameraZDistance - helixRadius)) / (helixRadius * 2.0f)), 0.1f, 1.0f);

                    std::uint8_t finalR = static_cast<std::uint8_t>(point.baseColorR * depthRatio);
                    std::uint8_t finalG = static_cast<std::uint8_t>(point.baseColorG * depthRatio);
                    std::uint8_t finalB = static_cast<std::uint8_t>(point.baseColorB * depthRatio);

                    painter.SetColor(Color{ finalR, finalG, finalB, 255 });

                    // Nodes sweeping close to view plane lines are expanded to circles via depth ratio
                    if (depthRatio > 0.75f)
                    {
                        painter.Circle(screenX, screenY, 2);
                    }
                    else
                    {
                        // Distant point nodes fall back strictly to fast atomic single pixel spots
                        painter.Pixel(static_cast<std::size_t>(screenX), static_cast<std::size_t>(screenY));
                    }
                }
            }
        }

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("3D DNA Point Cloud Engine - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
