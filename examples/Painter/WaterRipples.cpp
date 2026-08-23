// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import App;
import WinLite;
import PixelPainter;
import PixelCopier;
import BmpLoader;
import FpsCounter;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Optimized Water Displacement"))
    {
        return -1;
    }

    auto bmpResult = BmpLoader::Load("files/water_texture.bmp");
    if (!bmpResult)
    {
        std::println("Warning: files/water_texture.bmp missing. Rendering in standalone procedural generation mode.");
    }

    std::vector<float> waveBuffer1(width * height, 0.0f);
    std::vector<float> waveBuffer2(width * height, 0.0f);

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            int mx = event.Mouse.PosX;
            int my = event.Mouse.PosY;

            if (mx > 2 && mx < static_cast<int>(width) - 2 &&
                my > 2 && my < static_cast<int>(height) - 2)
            {
                std::size_t idx = static_cast<std::size_t>(my) * width + static_cast<std::size_t>(mx);
                waveBuffer1[idx] = 32.0f;
                waveBuffer1[idx - 1] = 16.0f;
                waveBuffer1[idx + 1] = 16.0f;
                waveBuffer1[idx - width] = 16.0f;
                waveBuffer1[idx + width] = 16.0f;
            }
        }
        };

    app.OnUpdate = [&](float) noexcept {
        for (std::size_t y = 1; y < height - 1; ++y)
        {
            std::size_t rowOffset = y * width;
            for (std::size_t x = 1; x < width - 1; ++x)
            {
                std::size_t idx = rowOffset + x;

                float neighborhoodSum =
                    waveBuffer1[idx - 1] +
                    waveBuffer1[idx + 1] +
                    waveBuffer1[idx - width] +
                    waveBuffer1[idx + width];

                float newWaveHeight = (neighborhoodSum * 0.5f) - waveBuffer2[idx];
                newWaveHeight *= 0.985f;

                waveBuffer2[idx] = newWaveHeight;
            }
        }

        waveBuffer1.swap(waveBuffer2);
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        constexpr float waveActiveThreshold = 0.005f;
        const bool hasBmp = bmpResult.has_value();
        const auto* imgPtr = hasBmp ? &bmpResult.value() : nullptr;

        for (std::size_t y = 0; y < height; ++y)
        {
            std::size_t rowOffset = y * width;

            for (std::size_t x = 0; x < width; ++x)
            {
                std::size_t idx = rowOffset + x;

                std::size_t srcX = x;
                std::size_t srcY = y;

                if (y > 0 && y < height - 1 && x > 0 && x < width - 1)
                {
                    float currentWaveHeight = waveBuffer1[idx];

                    if (std::abs(currentWaveHeight) >= waveActiveThreshold)
                    {
                        float xSlope = waveBuffer1[idx + 1] - waveBuffer1[idx - 1];
                        float ySlope = waveBuffer1[idx + width] - waveBuffer1[idx - width];

                        int uOffset = static_cast<int>(xSlope * 32.0f);
                        int vOffset = static_cast<int>(ySlope * 32.0f);

                        int clampedX = std::clamp<int>(static_cast<int>(x) + uOffset, 0, static_cast<int>(width) - 1);
                        int clampedY = std::clamp<int>(static_cast<int>(y) + vOffset, 0, static_cast<int>(height) - 1);

                        srcX = static_cast<std::size_t>(clampedX);
                        srcY = static_cast<std::size_t>(clampedY);
                    }
                }

                if (hasBmp)
                {
                    std::size_t texX = std::clamp<std::size_t>(srcX, 0, imgPtr->width - 1);
                    std::size_t texY = std::clamp<std::size_t>(srcY, 0, imgPtr->height - 1);
                    std::size_t bmpIdx = (texY * imgPtr->width + texX) * imgPtr->bpp;

                    std::uint8_t r = imgPtr->pixels[bmpIdx + 0];
                    std::uint8_t g = imgPtr->pixels[bmpIdx + 1];
                    std::uint8_t b = imgPtr->pixels[bmpIdx + 2];

                    float waveFactor = waveBuffer1[idx] * 5.0f;

                    std::uint8_t finalR = static_cast<std::uint8_t>(std::clamp(static_cast<float>(r) * 0.85f + waveFactor, 0.0f, 255.0f));
                    std::uint8_t finalG = static_cast<std::uint8_t>(std::clamp(static_cast<float>(g) * 0.95f + 10.0f + waveFactor, 0.0f, 255.0f));
                    std::uint8_t finalB = static_cast<std::uint8_t>(std::clamp(static_cast<float>(b) * 1.0f + 25.0f + waveFactor * 2.0f, 0.0f, 255.0f));

                    painter.SetColor(Color{ finalR, finalG, finalB, 255 });
                }
                else
                {
                    std::uint8_t pattern = ((srcX / 32) + (srcY / 32)) % 2 == 0 ? static_cast<std::uint8_t>(180) : static_cast<std::uint8_t>(120);

                    float waveFactor = waveBuffer1[idx] * 8.0f;

                    std::uint8_t finalR = 20;
                    std::uint8_t finalG = static_cast<std::uint8_t>(std::clamp(static_cast<float>(pattern) + waveFactor, 0.0f, 255.0f));
                    std::uint8_t finalB = static_cast<std::uint8_t>(std::clamp(static_cast<float>(pattern) + 40.0f + waveFactor * 2.0f, 0.0f, 255.0f));

                    painter.SetColor(Color{ finalR, finalG, finalB, 255 });
                }
                painter.Pixel(x, y);
            }
        }
        };

    app.Run();

    return 0;
}
