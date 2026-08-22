// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements a real-time Morphing Julia Fractal generator.
 * It maps complex number mathematics onto screen pixels via PixelPainter::Pixel.
 * Moving the mouse shifts the real and imaginary constants (c_re, c_im) of the
 * fractal equation Z_{n+1} = Z_n^2 + c, morphing the geometry into infinite patterns.
 * To maintain an interactive frame rate on the CPU, the calculation is evaluated
 * in 2x2 pixel blocks with a balanced iteration depth threshold.
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

int main()
{
    // Screen dimensions and pixel array configurations
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit pixel layout array (RGBA/BGRA)

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Morphing Julia Fractal");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Instantiate your native graphics backend abstraction layer
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Default seed parameters for the complex fractal mathematical constant 'c'
    float cRe = -0.7f;
    float cIm = 0.27015f;

    auto startTime = std::chrono::steady_clock::now();

    // Cache complex plane bounding box scales to avoid inline division operations
    constexpr float zoom = 1.2f;
    constexpr float moveX = 0.0f;
    constexpr float moveY = 0.0f;
    constexpr int maxIterations = 32; // Balanced threshold depth for smooth CPU performance

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
                // Map screen space coordinates cleanly to complex plane floating ranges [-1.0, 1.0]
                cRe = (static_cast<float>(event.Mouse.PosX) / static_cast<float>(width)) * 2.0f - 1.0f;
                cIm = (static_cast<float>(event.Mouse.PosY) / static_cast<float>(height)) * 2.0f - 1.0f;
            }
        }

        auto currentTime = std::chrono::steady_clock::now();
        float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

        // Clear display area cleanly before calculating fractal state coordinates
        painter.SetColor(Color{ 0, 0, 0, 255 });
        painter.Clear();

        // Execute hot complex coordinate translation loops
        // We step by 2 pixels to guarantee a highly fluid, responsive interactive experience on CPU
        for (std::size_t y = 0; y < height; y += 2)
        {
            // Map pixel coordinate y onto the imaginary axis of the mathematical field
            float im = 1.5f * (static_cast<float>(y) - static_cast<float>(height) / 2.0f) / (0.5f * zoom * static_cast<float>(height)) + moveY;

            for (std::size_t x = 0; x < width; x += 2)
            {
                // Map pixel coordinate x onto the real axis of the mathematical field
                float re = 1.5f * (static_cast<float>(x) - static_cast<float>(width) / 2.0f) / (0.5f * zoom * static_cast<float>(width)) + moveX;

                float zRe = re;
                float zIm = im;
                int iterCount = 0;

                // Core Mandelbrot/Julia set loop processing path sequences
                while (zRe * zRe + zIm * zIm < 4.0f && iterCount < maxIterations)
                {
                    // Compute Z^2 + c parameters sequentially
                    float nextRe = zRe * zRe - zIm * zIm + cRe;
                    float nextIm = 2.0f * zRe * zIm + cIm;

                    zRe = nextRe;
                    zIm = nextIm;
                    ++iterCount;
                }

                // If coordinates escaped bounding sets, shade color bands gracefully
                if (iterCount < maxIterations)
                {
                    // Map iterations to neon color spectrum shifts combined with runtime clocks
                    float colorRatio = static_cast<float>(iterCount) / static_cast<float>(maxIterations);

                    std::uint8_t r = static_cast<std::uint8_t>(std::sin(colorRatio * 3.0f + elapsed) * 127.5f + 127.5f);
                    std::uint8_t g = static_cast<std::uint8_t>(std::cos(colorRatio * 5.0f - elapsed) * 64.0f + 64.0f);
                    std::uint8_t b = static_cast<std::uint8_t>(colorRatio * 255.0f);

                    painter.SetColor(Color{ r, g, b, 255 });

                    // Render a 2x2 micro structural point block keeping pixel resolution sharp
                    painter.Pixel(x, y);
                    painter.Pixel(x + 1, y);
                    painter.Pixel(x, y + 1);
                    painter.Pixel(x + 1, y + 1);
                }
            }
        }

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Morphing Julia Fractal Engine - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
