// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <span>
#include <cmath>
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

import WinLite;
import SoftwareRender;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 640;
    constexpr std::size_t height = 480;
    constexpr std::size_t bytesPerPixel = 3;

    auto windowResult = SoftwareWindow::Create(
        static_cast<int>(width),
        static_cast<int>(height),
        "Daily C++ Modules: Morphing Julia Fractal"
    );

    if (!windowResult)
    {
        std::cout << "Error: " << windowResult.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);
    SoftwareRender render(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));

    float time = 0.0f;
    constexpr int maxIterations = 60;

    constexpr float minRe = -1.5f;
    constexpr float maxRe = 1.5f;
    constexpr float minIm = -1.2f;
    constexpr float maxIm = 1.2f;

    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if (event.Type == EventType::Quit)
            {
                window.StopEvent();
            }
        }

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

        time += 0.02f;

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);
    }

    return 0;
}
