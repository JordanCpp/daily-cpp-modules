// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a retro-cyberpunk 3D Wireframe Terrain engine.
 * It builds an infinite, moving grid of neon mountains rushing toward the viewer,
 * using the custom PixelPainter::Line API for vector rendering.
 * The algorithm generates a structural vertex mesh on the CPU, transforms its height
 * using layered trigonometric equations, applies standard 3D-to-2D perspective projection,
 * and renders structural segments sequentially to create an authentic 1980s Synthwave visual layout.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>  // for std::size_t

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

namespace Math {
    constexpr float PI = 3.1415926535f;
}

// Global configuration constants for the 3D space projection pipeline
constexpr int gridRows = 30;    // Depth density of the horizon mesh
constexpr int gridCols = 24;    // Lateral width density of the terrain mesh
constexpr float cellSpacing = 40.0f; // Scale distance between structural nodes

int main()
{
    // Viewport configurations and 32-bit layout assignments
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit RGBA/BGRA video layout buffer

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Retro 3D Synthwave Terrain");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize the primary PixelPainter pipeline instance bound to the frame memory span
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Allocate structural 2D cache arrays to keep mathematical projections clean
    // Storing pre-calculated 2D screen coordinate conversions for all grid points
    struct ScreenPoint { int x; int y; bool isValid; };
    std::vector<std::vector<ScreenPoint>> screenMesh(gridRows, std::vector<ScreenPoint>(gridCols));

    // Spatial coordinate center offsets
    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);

    constexpr float cameraHeight = 160.0f;
    constexpr float fovScale = 450.0f;     // Focal magnification scale value
    constexpr float horizonZOffset = 40.0f; // Near plane viewing clipping boundaries

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

        // Clean frame backbuffer area with a deep night cyberpunk tone
        painter.SetColor(Color{ 12, 8, 16, 255 });
        painter.Clear();

        // Calculate discrete forward movement step displacement values over time
        float terrainSpeed = elapsed * 120.0f;
        float forwardOffset = std::fmod(terrainSpeed, cellSpacing);

        // 1. TRANSFORM 3D SPACE VERTEXT DATA INTO 2D PROJECTIONS
        for (int r = 0; r < gridRows; ++r)
        {
            // Calculate absolute spatial distance depth values from camera orientation
            float worldZ = (static_cast<float>(gridRows - r) * cellSpacing) - forwardOffset + horizonZOffset;

            for (int c = 0; c < gridCols; ++c)
            {
                // Calculate absolute spatial lateral width displacement balances
                float worldX = (static_cast<float>(c - gridCols / 2) * cellSpacing);

                /*
                 * PROCEDURAL TERRAIN MOUNTAIN GENERATION:
                 * We model hills on the sides by scaling height based on column distances from center,
                 * leaving a flat driving highway valley right through the middle axis.
                 */
                float distanceFromCenter = std::abs(static_cast<float>(c - gridCols / 2));
                float heightMultiplier = 0.0f;
                if (distanceFromCenter > 3.0f)
                {
                    heightMultiplier = (distanceFromCenter - 3.0f) * 18.0f;
                }

                // Superimpose sinus waves to form complex procedural mountain ranges
                float wave1 = std::sin(worldX * 0.015f + (terrainSpeed * 0.02f)) * std::cos(worldZ * 0.01f);
                float wave2 = std::sin((worldZ + terrainSpeed) * 0.025f) * 0.4f;
                float worldY = (wave1 + wave2) * heightMultiplier + cameraHeight;

                // Execute 3D perspective projection divide step formulas
                if (worldZ > 5.0f)
                {
                    int sX = static_cast<int>((worldX * fovScale) / worldZ) + centerX;
                    int sY = static_cast<int>((worldY * fovScale) / worldZ) + centerY;

                    // Ensure spatial coordinate clamping limits are safe
                    // FIX: Cast r and c to std::size_t to avoid sign-conversion warnings
                    screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = ScreenPoint{ sX, sY, true };
                }
                else
                {
                    // FIX: Cast r and c to std::size_t to avoid sign-conversion warnings
                    screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = ScreenPoint{ 0, 0, false };
                }
            }
        }

        // 2. RENDER THE TRANSFORMED WIREFRAME MESH (Using PixelPainter::Line)
        // We draw rows starting from the horizon line moving forward to handle depth cue lines cleanly
        for (int r = 0; r < gridRows - 1; ++r)
        {
            // Compute exponential atmospheric fog fading intensities based on grid depth rows
            float depthRatio = static_cast<float>(r) / static_cast<float>(gridRows);

            // Bright fluorescent neon pink and violet wireframe colors
            std::uint8_t redIntensity = static_cast<std::uint8_t>(80.0f + 175.0f * depthRatio);
            std::uint8_t greenIntensity = static_cast<std::uint8_t>(20.0f + 30.0f * depthRatio);
            std::uint8_t blueIntensity = static_cast<std::uint8_t>(140.0f + 115.0f * depthRatio);

            painter.SetColor(Color{ redIntensity, greenIntensity, blueIntensity, 255 });

            for (int c = 0; c < gridCols; ++c)
            {
                // FIX: Cast indices to std::size_t when accessing vectors
                const auto& pCurrent = screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];

                if (!pCurrent.isValid) continue;

                // Draw longitudinal lines stretching forward toward the viewer
                if (r < gridRows - 1)
                {
                    // FIX: Cast indices to std::size_t when accessing vectors
                    const auto& pForward = screenMesh[static_cast<std::size_t>(r + 1)][static_cast<std::size_t>(c)];
                    if (pForward.isValid)
                    {
                        painter.Line(pCurrent.x, pCurrent.y, pForward.x, pForward.y);
                    }
                }

                // Draw lateral horizontal cross-lines linking columns across sections
                if (c < gridCols - 1)
                {
                    // FIX: Cast indices to std::size_t when accessing vectors
                    const auto& pRight = screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c + 1)];
                    if (pRight.isValid)
                    {
                        painter.Line(pCurrent.x, pCurrent.y, pRight.x, pRight.y);
                    }
                }
            }
        }

        // Render a large decorative vector horizon grid sun line manually via the primitive APIs
        painter.SetColor(Color{ 255, 180, 0, 255 }); // Radiant synthwave synth orange sun
        painter.Circle(centerX, centerY - 40, 80);

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Synthwave Wireframe 3D Engine - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
