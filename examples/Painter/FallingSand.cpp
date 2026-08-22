// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a real-time Cellular Automata Falling Sand sandbox simulation.
 * It strictly uses the checked PixelPainter::Pixel API to draw a discrete grid of physical particles.
 * Every frame, a pixel-level update pass runs through the grid matrix: sand grains fall downward
 * under simulated gravity or slide laterally down slopes if obstacles block their path.
 * Interacting via the WinLite::Events API, clicking and holding the Left Mouse Button streams
 * dynamic, color-shifting streams of sand directly from the mouse coordinates.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

// Particle type definitions for grid states
enum class GridCell : std::uint8_t {
    Empty = 0,
    Sand = 1
};

// Structure mapping an RGB color profile for each individual sand grain
struct CellColor {
    std::uint8_t r, g, b;
};

int main()
{
    // Discrete matrix grid simulation scale constraints
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit pixel data array (RGBA/BGRA)

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Falling Sand Sandbox");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize the underlying core painter layer
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Simulation space grid tracking allocations
    std::vector<GridCell> currentGrid(width * height, GridCell::Empty);
    std::vector<GridCell> nextGrid(width * height, GridCell::Empty);
    std::vector<CellColor> colorGrid(width * height, CellColor{ 0, 0, 0 });

    // Setup pseudo-random hue variants for the streaming sand streams
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> colorDist(160, 240);

    bool isMousePressed = false;
    int mouseX = 0;
    int mouseY = 0;

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

            // Capture mouse coordinates matching your exact WinLite.Events structure API
            if (event.Type == EventType::MouseMove)
            {
                mouseX = event.Mouse.PosX;
                mouseY = event.Mouse.PosY;
            }

            // Track standard mouse triggers using explicit WinLite helper methods
            if (event.IsMousePressed(MouseButton::Left))
            {
                isMousePressed = true;
            }
            if (event.IsMouseReleased(MouseButton::Left))
            {
                isMousePressed = false;
            }
        }

        auto currentTime = std::chrono::steady_clock::now();
        float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

        // 1. STREAM NEW PARTICLES VIA USER INTERACTIONS
        if (isMousePressed && mouseX >= 4 && mouseX < static_cast<int>(width) - 4 &&
            mouseY >= 4 && mouseY < static_cast<int>(height) - 4)
        {
            // Spawn a random-scattered cluster around the active coordinate location
            for (int dy = -3; dy <= 3; ++dy)
            {
                for (int dx = -3; dx <= 3; ++dx)
                {
                    if ((dx * dx + dy * dy) <= 9) // Limit to a circular spray brush shape
                    {
                        std::size_t spawnX = static_cast<std::size_t>(mouseX + dx);
                        std::size_t spawnY = static_cast<std::size_t>(mouseY + dy);
                        std::size_t idx = spawnY * width + spawnX;

                        if (currentGrid[idx] == GridCell::Empty)
                        {
                            currentGrid[idx] = GridCell::Sand;

                            // Shift colors smoothly across timelines creating layered rainbow bands
                            std::uint8_t r = static_cast<std::uint8_t>(colorDist(gen));
                            std::uint8_t g = static_cast<std::uint8_t>(100.0f + 100.0f * std::sin(elapsed * 2.0f));
                            std::uint8_t b = static_cast<std::uint8_t>(80.0f + 50.0f * std::cos(elapsed * 1.5f));
                            colorGrid[idx] = CellColor{ r, g, b };
                        }
                    }
                }
            }
        }

        // Reset the calculation buffers cleanly for the physics update pass
        std::fill(nextGrid.begin(), nextGrid.end(), GridCell::Empty);

        // 2. CELLULAR AUTOMATA PHYSICS LOGIC PASS
        // We traverse bottom-to-top to avoid sweeping the same particle down multiple times per tick
        for (int y = static_cast<int>(height) - 1; y >= 0; --y)
        {
            for (int x = 0; x < static_cast<int>(width); ++x)
            {
                std::size_t currentIdx = static_cast<std::size_t>(y * static_cast<int>(width) + x);

                if (currentGrid[currentIdx] == GridCell::Sand)
                {
                    int downY = y + 1;

                    if (downY < static_cast<int>(height))
                    {
                        std::size_t belowIdx = static_cast<std::size_t>(downY * static_cast<int>(width) + x);
                        std::size_t bottomLeftIdx = belowIdx - 1;
                        std::size_t bottomRightIdx = belowIdx + 1;

                        // Rule 1: Fall straight down if the cell below is completely vacant
                        if (currentGrid[belowIdx] == GridCell::Empty && nextGrid[belowIdx] == GridCell::Empty)
                        {
                            nextGrid[belowIdx] = GridCell::Sand;
                            colorGrid[belowIdx] = colorGrid[currentIdx];
                        }
                        // Rule 2: Slide down to the bottom-left corner diagonally
                        else if (x > 0 && currentGrid[bottomLeftIdx] == GridCell::Empty && nextGrid[bottomLeftIdx] == GridCell::Empty)
                        {
                            nextGrid[bottomLeftIdx] = GridCell::Sand;
                            colorGrid[bottomLeftIdx] = colorGrid[currentIdx];
                        }
                        // Rule 3: Slide down to the bottom-right corner diagonally
                        else if (x < static_cast<int>(width) - 1 && currentGrid[bottomRightIdx] == GridCell::Empty && nextGrid[bottomRightIdx] == GridCell::Empty)
                        {
                            nextGrid[bottomRightIdx] = GridCell::Sand;
                            colorGrid[bottomRightIdx] = colorGrid[currentIdx];
                        }
                        // Rule 4: Solidify in place if all movement choices are blocked
                        else
                        {
                            nextGrid[currentIdx] = GridCell::Sand;
                            colorGrid[currentIdx] = colorGrid[currentIdx];
                        }
                    }
                    else
                    {
                        // Stop moving completely upon hitting the viewport floor
                        nextGrid[currentIdx] = GridCell::Sand;
                        colorGrid[currentIdx] = colorGrid[currentIdx];
                    }
                }
            }
        }

        // Fixed: Use high-performance pointer swap instead of deep copying to eliminate GCC stringop-overflow diagnostics
        currentGrid.swap(nextGrid);

        // 3. GRAPHICS RENDERING PASS VIA PIXELPAINTER API
        painter.SetColor(Color{ 18, 20, 26, 255 }); // Dark matte box background tone
        painter.Clear();

        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                std::size_t idx = y * width + x;
                if (currentGrid[idx] == GridCell::Sand)
                {
                    const auto& col = colorGrid[idx];
                    painter.SetColor(Color{ col.r, col.g, col.b, 255 });

                    // Draw each active particle using the strict Pixel format interface
                    painter.Pixel(x, y);
                }
            }
        }

        // Push completed buffer to the viewport display
        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Falling Sand Sandbox Engine - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
