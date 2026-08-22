// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a legendary Oldschool Demoparty Fire Effect using PixelCopier.
 * It combines texture masking with a cellular heat-conduction simulation on the CPU.
 * A loaded black-and-white BMP silhouette acts as an ignition source.
 * Every frame, the engine reads pixels from the row below, applies a random horizontal shift,
 * averages the neighborhood values to simulate heat diffusion, and dampens the intensity.
 * The resulting scalar heat map is indexed into a vibrant fire palette array.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <print>
#include <cstddef>  // for std::size_t

import WinLite;
import PixelPainter;
import PixelCopier;
import BmpLoader;
import FpsCounter;

using namespace WinLite;
using namespace Software;

// Global structure for fire gradient mapping definitions
struct FireColor {
    std::uint8_t r, g, b;
};

int main()
{
    // Screen geometry setup values and 32-bit pixel allocation bounds
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit RGBA/BGRA format

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Retro Fire Showcase");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize your native graphics abstraction modules
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    PixelCopier copier(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Load the ignition mask silhouette texture via your native BmpLoader module
    auto bmpResult = BmpLoader::Load("files/logo_silhouette.bmp");
    if (!bmpResult)
    {
        std::println("Warning: files/logo_silhouette.bmp missing. Falling back to bottom-line ignition.");
    }

    // Allocate a dedicated single-channel scalar buffer to store current heat intensity maps
    std::vector<std::uint8_t> heatBuffer(width * height, 0);

    // Pre-calculate a 256-color smooth fire spectrum palette (Black -> Red -> Orange -> Yellow -> White)
    std::vector<FireColor> firePalette(256);
    // FIX: Use std::size_t for loop index to avoid sign-conversion
    for (std::size_t i = 0; i < firePalette.size(); ++i)
    {
        // Allocation ranges defining smooth thermal transition spectrum states
        if (i < 64) // Black to deep Red
        {
            firePalette[i] = FireColor{ static_cast<std::uint8_t>(i * 4), 0, 0 };
        }
        else if (i < 128) // Red to bright Orange
        {
            firePalette[i] = FireColor{ 255, static_cast<std::uint8_t>((i - 64) * 4), 0 };
        }
        else if (i < 192) // Orange to intense Yellow
        {
            firePalette[i] = FireColor{ 255, 255, static_cast<std::uint8_t>((i - 128) * 4) };
        }
        else // Yellow to pure hot White
        {
            firePalette[i] = FireColor{ 255, 255, 255 };
        }
    }

    // Setup pseudo-random uniform distributions for physical spark variations
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> sparkDist(0, 255);
    std::uniform_int_distribution<int> driftDist(-1, 1);

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

        // Use elapsed for spark intensity variation over time
        // This creates a pulsing effect in the fire
        float sparkModulation = 0.5f + 0.5f * std::sin(elapsed * 0.5f);
        int sparkThreshold = static_cast<int>(40 + 20 * sparkModulation);

        // 1. INJECT HEAT FIELDS (Ignition Phase)
        // Seed the absolute bottom row of the screen with intense chaotic sparks
        std::size_t bottomRowOffset = (height - 1) * width;
        for (std::size_t x = 0; x < width; ++x)
        {
            heatBuffer[bottomRowOffset + x] = (sparkDist(gen) > sparkThreshold) ? 255 : 0;
        }

        // If the mask image loaded successfully, burn its edges into the heat field grid
        if (bmpResult)
        {
            const auto& img = bmpResult.value();
            // Bound to the central viewport matching dimensions safely
            std::size_t startX = (width - img.width) / 2;
            std::size_t startY = (height - img.height) / 2;

            for (std::size_t y = 0; y < std::min<std::size_t>(img.height, height); ++y)
            {
                for (std::size_t x = 0; x < std::min<std::size_t>(img.width, width); ++x)
                {
                    // Read data assuming a standard 3-byte (24-bit RGB) texture structure from BmpLoader
                    std::size_t bmpIdx = (y * img.width + x) * img.bpp;

                    // High-contrast check: black pixels act as pure thermal fuel sources
                    if (img.pixels[bmpIdx] < 128)
                    {
                        std::size_t targetGridIdx = (startY + y) * width + (startX + x);
                        if (targetGridIdx < heatBuffer.size())
                        {
                            heatBuffer[targetGridIdx] = static_cast<std::uint8_t>(sparkDist(gen));
                        }
                    }
                }
            }
        }

        // 2. SIMULATE THERMAL CONDUCTION AND CONVECTIVE UPWARD DRIFT
        // Process pixels from top to bottom, updating physics equations on the CPU
        for (std::size_t y = 0; y < height - 1; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                // Generate a random sideways drift step vector (-1, 0, or 1 pixel offset)
                int driftX = driftDist(gen);

                // FIX: Use std::size_t for sourceX with proper bounds checking
                // Convert to int for arithmetic, then clamp, then cast back to std::size_t
                int xInt = static_cast<int>(x);
                int sourceXInt = xInt + driftX;
                // Clamp to valid range [0, width-1]
                sourceXInt = std::max(0, std::min(sourceXInt, static_cast<int>(width) - 1));
                std::size_t sourceX = static_cast<std::size_t>(sourceXInt);

                // Read the temperature directly below the current spatial cell location
                std::size_t sourceIdx = (y + 1) * width + sourceX;
                std::uint8_t belowHeat = heatBuffer[sourceIdx];

                // Apply cooling dissipation factor (loss of energy as flame rises up rows)
                std::uint8_t decay = (sparkDist(gen) % 3 == 0) ? 1 : 0;
                std::uint8_t newHeat = (belowHeat > decay) ? (belowHeat - decay) : 0;

                // Store the calculated state into the active coordinate index
                heatBuffer[y * width + x] = newHeat;
            }
        }

        // 3. COLOR METRIC CONVERSIONS AND BUFFER COPIER TRANSFER STRATEGIES
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                std::uint8_t currentHeat = heatBuffer[y * width + x];
                const auto& colorProfile = firePalette[currentHeat];

                // Direct color mapping inside your PixelPainter configuration array
                painter.SetColor(Color{ colorProfile.r, colorProfile.g, colorProfile.b, 255 });
                painter.Pixel(x, y);
            }
        }

        // Blit backbuffer memory blocks straight to the active native system screen context
        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Oldschool Demoparty Fire - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
