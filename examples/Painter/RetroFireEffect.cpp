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

struct FireColor {
    std::uint8_t r, g, b;
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Retro Fire Showcase"))
    {
        return -1;
    }

    auto bmpResult = BmpLoader::Load("files/logo_silhouette.bmp");
    if (!bmpResult)
    {
        std::println("Warning: files/logo_silhouette.bmp missing. Falling back to bottom-line ignition.");
    }

    std::vector<std::uint8_t> heatBuffer(width * height, 0);

    std::vector<FireColor> firePalette(256);
    for (std::size_t i = 0; i < firePalette.size(); ++i)
    {
        if (i < 64)
        {
            firePalette[i] = FireColor{ static_cast<std::uint8_t>(i * 4), 0, 0 };
        }
        else if (i < 128)
        {
            firePalette[i] = FireColor{ 255, static_cast<std::uint8_t>((i - 64) * 4), 0 };
        }
        else if (i < 192)
        {
            firePalette[i] = FireColor{ 255, 255, static_cast<std::uint8_t>((i - 128) * 4) };
        }
        else
        {
            firePalette[i] = FireColor{ 255, 255, 255 };
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> sparkDist(0, 255);
    std::uniform_int_distribution<int> driftDist(-1, 1);

    float elapsed = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;

        float sparkModulation = 0.5f + 0.5f * std::sin(elapsed * 0.5f);
        int sparkThreshold = static_cast<int>(40 + 20 * sparkModulation);

        std::size_t bottomRowOffset = (height - 1) * width;
        for (std::size_t x = 0; x < width; ++x)
        {
            heatBuffer[bottomRowOffset + x] = (sparkDist(gen) > sparkThreshold) ? 255 : 0;
        }

        if (bmpResult)
        {
            const auto& img = bmpResult.value();
            std::size_t startX = (width - img.width) / 2;
            std::size_t startY = (height - img.height) / 2;

            for (std::size_t y = 0; y < std::min<std::size_t>(img.height, height); ++y)
            {
                for (std::size_t x = 0; x < std::min<std::size_t>(img.width, width); ++x)
                {
                    std::size_t bmpIdx = (y * img.width + x) * img.bpp;

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

        for (std::size_t y = 0; y < height - 1; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                int driftX = driftDist(gen);
                int xInt = static_cast<int>(x);
                int sourceXInt = xInt + driftX;
                sourceXInt = std::max(0, std::min(sourceXInt, static_cast<int>(width) - 1));
                std::size_t sourceX = static_cast<std::size_t>(sourceXInt);

                std::size_t sourceIdx = (y + 1) * width + sourceX;
                std::uint8_t belowHeat = heatBuffer[sourceIdx];

                std::uint8_t decay = (sparkDist(gen) % 3 == 0) ? 1 : 0;
                std::uint8_t newHeat = (belowHeat > decay) ? (belowHeat - decay) : 0;

                heatBuffer[y * width + x] = newHeat;
            }
        }
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                std::uint8_t currentHeat = heatBuffer[y * width + x];
                const auto& colorProfile = firePalette[currentHeat];

                painter.SetColor(Color{ colorProfile.r, colorProfile.g, colorProfile.b, 255 });
                painter.Pixel(x, y);
            }
        }
        };

    app.Run();

    return 0;
}
