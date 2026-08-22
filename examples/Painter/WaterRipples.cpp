// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This is a highly optimized version of the 2D Water Ripple Displacement engine.
 * It combines PixelCopier and PixelPainter to maximize CPU rendering performance.
 * At the start of the frame, PixelCopier::Copy quickly blits the base un-deformed
 * texture onto the entire backbuffer using fast block memory transfers via std::span handles.
 * The heavy per-pixel refraction math and PixelPainter::Pixel calls are executed
 * EXCLUSIVELY for pixels where the local wave amplitude exceeds a minimum threshold.
 * Static or fully dampened water regions bypass the shader math completely, yielding massive FPS gains.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <print>
#include <span>

import WinLite;
import PixelPainter;
import PixelCopier;
import BmpLoader;
import FpsCounter;

using namespace WinLite;
using namespace Software;

int main()
{
    // Viewport layout definitions and 32-bit pixel mapping scales
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit buffer space

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Optimized Water Displacement");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize the primary abstraction layer instances
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    PixelCopier copier(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Load the background texture image via your native BmpLoader module
    auto bmpResult = BmpLoader::Load("files/water_texture.bmp");
    if (!bmpResult)
    {
        std::println("Warning: files/water_texture.bmp missing. Rendering in standalone procedural generation mode.");
    }

    // Generate a fallback texture vector in case the BMP file is missing to keep the copier pipeline valid
    std::vector<std::uint8_t> fallbackTexture;
    constexpr std::size_t fallbackW = 800;
    constexpr std::size_t fallbackH = 800;
    constexpr std::size_t fallbackBpp = 3;
    if (!bmpResult)
    {
        fallbackTexture.resize(fallbackW * fallbackH * fallbackBpp);
        for (std::size_t y = 0; y < fallbackH; ++y)
        {
            for (std::size_t x = 0; x < fallbackW; ++x)
            {
                std::size_t idx = (y * fallbackW + x) * fallbackBpp;
                // Procedural blue-green tile patterns grid
                std::uint8_t pattern = ((x / 32) + (y / 32)) % 2 == 0 ? 180 : 120;
                fallbackTexture[idx + 0] = 20;           // R
                fallbackTexture[idx + 1] = pattern;       // G
                fallbackTexture[idx + 2] = pattern + 40;  // B
            }
        }
    }

    // Allocate two separate scalar buffers to simulate the physical wave equations (current and previous states)
    std::vector<float> waveBuffer1(width * height, 0.0f);
    std::vector<float> waveBuffer2(width * height, 0.0f);

    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }

            // Capture mouse movements to continuously disturb the fluid plane
            if (event.Type == EventType::MouseMove)
            {
                int mx = event.Mouse.PosX;
                int my = event.Mouse.PosY;

                // Safely drop energy drops inside structural viewport boundaries
                if (mx > 2 && mx < static_cast<int>(width) - 2 &&
                    my > 2 && my < static_cast<int>(height) - 2)
                {
                    // Inject a localized peak drop splash signature into the physics grid
                    std::size_t idx = static_cast<std::size_t>(my * static_cast<int>(width) + mx);
                    waveBuffer1[idx] = 16.0f; // Height peak splash amplitude value
                    waveBuffer1[idx - 1] = 8.0f;
                    waveBuffer1[idx + 1] = 8.0f;
                    waveBuffer1[idx - width] = 8.0f;
                    waveBuffer1[idx + width] = 8.0f;
                }
            }
        }

        // --------------------------------------------------------------------
        // OPTIMIZATION STEP 1: FAST FULL-SCREEN BACKGROUND COPY BLIT
        // --------------------------------------------------------------------
        // We copy the background buffer using safe std::span parameters over the source pixel arrays
        if (bmpResult)
        {
            const auto& img = bmpResult.value();

            // Explicitly pass data pointer and total layout size to the span constructor
            std::span<const std::uint8_t> srcSpan(img.pixels.data(), img.width * img.height * img.bpp);

            copier.Copy(0, 0, img.width, img.height, img.bpp, srcSpan);
        }
        else
        {
            // Explicit span construction for the fallback vector layout buffer
            std::span<const std::uint8_t> srcSpan(fallbackTexture.data(), fallbackTexture.size());
            copier.Copy(0, 0, fallbackW, fallbackH, fallbackBpp, srcSpan);
        }


        // 1. WAVE PROPAGATION PHYSICS SOLVER PASS (Discrete Wave Equation)
        for (int y = 1; y < static_cast<int>(height) - 1; ++y)
        {
            for (int x = 1; x < static_cast<int>(width) - 1; ++x)
            {
                std::size_t idx = static_cast<std::size_t>(y * static_cast<int>(width) + x);

                float neighborhoodSum =
                    waveBuffer1[idx - 1] +
                    waveBuffer1[idx + 1] +
                    waveBuffer1[idx - width] +
                    waveBuffer1[idx + width];

                float newWaveHeight = (neighborhoodSum * 0.5f) - waveBuffer2[idx];
                newWaveHeight *= 0.982f; // Damping value

                waveBuffer2[idx] = newWaveHeight;
            }
        }

        waveBuffer1.swap(waveBuffer2);

        // --------------------------------------------------------------------
        // OPTIMIZATION STEP 2: CONDITIONAL PER-PIXEL REFRACTION RENDERING
        // --------------------------------------------------------------------
        // We evaluate spatial derivatives, but only update memory if an active delta exists
        constexpr float waveActiveThreshold = 0.005f;

        for (std::size_t y = 1; y < height - 1; ++y)
        {
            for (std::size_t x = 1; x < width - 1; ++x)
            {
                std::size_t idx = y * width + x;
                float currentWaveHeight = waveBuffer1[idx];

                // SKIP CRITERIA: If the absolute wave displacement is zero, bypass completely!
                if (std::abs(currentWaveHeight) < waveActiveThreshold)
                {
                    continue;
                }

                // Compute directional spatial derivatives (X and Y coordinate slopes)
                float xSlope = waveBuffer1[idx + 1] - waveBuffer1[idx - 1];
                float ySlope = waveBuffer1[idx + width] - waveBuffer1[idx - width];

                int uOffset = static_cast<int>(xSlope * 32.0f);
                int vOffset = static_cast<int>(ySlope * 32.0f);

                int srcX = std::clamp<int>(static_cast<int>(x) + uOffset, 0, static_cast<int>(width) - 1);
                int srcY = std::clamp<int>(static_cast<int>(y) + vOffset, 0, static_cast<int>(height) - 1);

                if (bmpResult)
                {
                    const auto& img = bmpResult.value();

                    std::size_t texX = static_cast<std::size_t>(std::clamp(srcX, 0, static_cast<int>(img.width - 1)));
                    std::size_t texY = static_cast<std::size_t>(std::clamp(srcY, 0, static_cast<int>(img.height - 1)));

                    std::size_t bmpIdx = (texY * img.width + texX) * img.bpp;

                    std::uint8_t r = img.pixels[bmpIdx + 0];
                    std::uint8_t g = img.pixels[bmpIdx + 1];
                    std::uint8_t b = img.pixels[bmpIdx + 2];

                    // Volumetric refraction lighting distortion shifts
                    std::uint8_t finalR = static_cast<std::uint8_t>(std::clamp(r * 0.85f, 0.0f, 255.0f));
                    std::uint8_t finalG = static_cast<std::uint8_t>(std::clamp(g * 0.95f + 10.0f, 0.0f, 255.0f));
                    std::uint8_t finalB = static_cast<std::uint8_t>(std::clamp(b * 1.0f + 25.0f, 0.0f, 255.0f));

                    painter.SetColor(Color{ finalR, finalG, finalB, 255 });
                }
                else
                {
                    std::uint8_t dynamicBlue = static_cast<std::uint8_t>(std::clamp(140.0f + currentWaveHeight * 80.0f, 0.0f, 255.0f));
                    std::uint8_t dynamicGreen = static_cast<std::uint8_t>(std::clamp(80.0f + currentWaveHeight * 40.0f, 0.0f, 255.0f));

                    painter.SetColor(Color{ 20, dynamicGreen, dynamicBlue, 255 });
                }

                // Rewrite ONLY the distorted pixel over the previously blitted background surface
                painter.Pixel(x, y);
            }
        }

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Highly Optimized Water Displacement - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
