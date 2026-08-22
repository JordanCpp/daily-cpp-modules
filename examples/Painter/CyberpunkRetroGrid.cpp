// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;
    constexpr std::size_t bytesPerPixel = 4;

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Cyberpunk Retro Grid");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    auto startTime = std::chrono::steady_clock::now();

    const int horizonY = static_cast<int>(static_cast<double>(height) * 0.45);
    const int centerX = static_cast<int>(width / 2U);
    const int iWidth = static_cast<int>(width);
    const int iHeight = static_cast<int>(height);

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
        double elapsed = std::chrono::duration<double>(currentTime - startTime).count();

        painter.SetColor(Color{ 10, 0, 20, 255 });
        painter.Clear();

        painter.SetColor(Color{ 255, 20, 147, 255 });
        painter.Circle(centerX, horizonY - 50, 150);

        painter.SetColor(Color{ 10, 0, 20, 255 });
        for (int i = 0; i < 5; ++i)
        {
            int sliceY = (horizonY - 50) + (i * 30) - 60;
            painter.Line(0, sliceY, iWidth, sliceY);
        }

        painter.SetColor(Color{ 0, 255, 255, 255 });
        constexpr int verticalSpacing = 40;
        for (int x = 0; x <= iWidth; x += verticalSpacing)
        {
            painter.Line(centerX, horizonY, x, iHeight);
        }

        painter.SetColor(Color{ 0, 255, 255, 150 });

        constexpr int numLines = 30;
        constexpr float speed = 0.5f;
        float moveOffset = std::fmodf(static_cast<float>(elapsed) * speed, 1.0f);

        for (int i = 0; i < numLines; ++i)
        {
            float z = (static_cast<float>(i) + moveOffset) / static_cast<float>(numLines);

            float perspectiveZ = std::powf(z, 2.0f);

            int y = horizonY + static_cast<int>(perspectiveZ * static_cast<float>(iHeight - horizonY));

            if (y >= horizonY && y < iHeight)
            {
                painter.Line(0, y, iWidth, y);
            }
        }

        window.Present(
            frameBuffer.data(),
            static_cast<int>(bytesPerPixel),
            iWidth,
            iHeight
        );

        if (counter.Update())
        {
            window.SetTitle("Cyberpunk Grid - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
