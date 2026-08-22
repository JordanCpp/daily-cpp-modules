// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <iostream>

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

namespace Math {
    constexpr double PI = 3.14159265358979323846;
}

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4;

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Mandala Generator");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

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
        double elapsed = std::chrono::duration<double>(currentTime - startTime).count();

        painter.SetColor(Color{ 5, 5, 15, 255 });
        painter.Clear();

        const int centerX = static_cast<int>(width / 2);
        const int centerY = static_cast<int>(height / 2);

        const int symmetrySteps = 12;
        const double angleStep = (2.0 * Math::PI) / symmetrySteps;

        for (int i = 0; i < symmetrySteps; ++i)
        {
            double currentAngle = i * angleStep + (elapsed * 0.2);

            double radius = 150.0 + 50.0 * std::sin(elapsed * 1.5);

            int xEnd = centerX + static_cast<int>(radius * std::cos(currentAngle));
            int yEnd = centerY + static_cast<int>(radius * std::sin(currentAngle));

            painter.SetColor(Color{
                static_cast<uint8_t>(127 + 127 * std::sin(elapsed + i)),
                static_cast<uint8_t>(127 + 127 * std::cos(elapsed * 0.5)),
                255,
                255
                });

            painter.Line(centerX, centerY, xEnd, yEnd);
        }

        for (int i = 0; i < symmetrySteps; ++i)
        {
            double currentAngle = i * angleStep - (elapsed * 0.5);
            double radius = 200.0 + 20.0 * std::cos(elapsed * 2.0);

            int xPos = centerX + static_cast<int>(radius * std::cos(currentAngle));
            int yPos = centerY + static_cast<int>(radius * std::sin(currentAngle));

            painter.SetColor(Color{ 255, 255, 255, 255 });
            painter.Circle(xPos, yPos, 8);

            painter.SetColor(Color{ 255, 100, 100, 255 });
            painter.Circle(xPos, yPos, 3);
        }

        for (int i = 0; i < symmetrySteps * 2; ++i)
        {
            double currentAngle = i * (Math::PI / symmetrySteps) + (elapsed * 0.8);
            double r1 = 100.0;
            double r2 = 250.0;

            int x1 = centerX + static_cast<int>(r1 * std::cos(currentAngle));
            int y1 = centerY + static_cast<int>(r1 * std::sin(currentAngle));
            int x2 = centerX + static_cast<int>(r2 * std::cos(currentAngle + Math::PI));
            int y2 = centerY + static_cast<int>(r2 * std::sin(currentAngle + Math::PI));

            painter.SetColor(Color{ 50, 255, 150, 150 });
            painter.Line(x1, y1, x2, y2);
        }

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Mandala Generator - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
