// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import App;
import WinLite;
import PixelPainter;
import PixelCopier;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Morphing Julia Fractal"))
    {
        return -1;
    }

    float time = 0.0f;
    constexpr int maxIterations = 60;

    constexpr float minRe = -1.5f;
    constexpr float maxRe = 1.5f;
    constexpr float minIm = -1.2f;
    constexpr float maxIm = 1.2f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        time += deltaTime;
        };

    app.OnRender = [&](PixelPainter& render, PixelCopier&) noexcept {
        float cRe = -0.7f + std::sin(time * 0.3f) * 0.15f;
        float cIm = 0.27015f + std::cos(time * 0.4f) * 0.05f;

        for (std::size_t y = 0; y < height; ++y)
        {
            float zIm = minIm + (static_cast<float>(y) / static_cast<float>(height)) * (maxIm - minIm);

            for (std::size_t x = 0; x < width; ++x)
            {
                float zRe = minRe + (static_cast<float>(x) / static_cast<float>(width)) * (maxRe - minRe);

                float curRe = zRe;
                float curIm = zIm;
                int iteration = 0;

                while (iteration < maxIterations)
                {
                    float zRe2 = curRe * curRe;
                    float zIm2 = curIm * curIm;

                    if (zRe2 + zIm2 > 4.0f)
                    {
                        break;
                    }

                    curIm = 2.0f * curRe * curIm + cIm;
                    curRe = zRe2 - zIm2 + cRe;

                    ++iteration;
                }

                Color pixelColor;
                if (iteration == maxIterations)
                {
                    pixelColor = Color{ 10, 10, 20 };
                }
                else
                {
                    float mu = static_cast<float>(iteration) / static_cast<float>(maxIterations);

                    std::uint8_t r = static_cast<std::uint8_t>(std::sin(mu * 3.14f + 0.0f) * 255.0f);
                    std::uint8_t g = static_cast<std::uint8_t>(std::sin(mu * 3.14f + 1.5f) * 200.0f);
                    std::uint8_t b = static_cast<std::uint8_t>(std::cos(mu * 1.57f) * 255.0f);

                    pixelColor = Color{ r, g, b };
                }

                render.SetColor(pixelColor);
                render.Pixel(x, y);
            }
        }
        };

    app.Run();

    return 0;
}
