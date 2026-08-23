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
    if (!app.Init(width, height, "Daily C++ Modules: Enhanced Interactive Demo"))
    {
        return -1;
    }

    constexpr Color backgroundColor{ 18, 22, 30 };
    constexpr Color gridColor{ 35, 42, 55 };
    constexpr Color gridHighlightColor{ 50, 80, 120 };
    constexpr Color rectColor{ 230, 90, 80 };
    constexpr Color pixelColor{ 240, 210, 90 };

    float animationTime = 0.0f;
    int mouseX = -100;
    int mouseY = -100;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            mouseX = event.Mouse.PosX;
            mouseY = event.Mouse.PosY;
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        animationTime += deltaTime;
        };

    app.OnRender = [&](PixelPainter& render, PixelCopier&) noexcept {
        render.SetColor(backgroundColor);
        render.Clear();

        constexpr int gridSize = 40;
        int hoverGridX = (mouseX / gridSize) * gridSize;
        int hoverGridY = (mouseY / gridSize) * gridSize;

        for (int x = 0; x < static_cast<int>(width); x += gridSize)
        {
            if (x == hoverGridX || x == hoverGridX + gridSize)
                render.SetColor(gridHighlightColor);
            else
                render.SetColor(gridColor);

            render.Line(x, 0, x, static_cast<int>(height));
        }

        for (int y = 0; y < static_cast<int>(height); y += gridSize)
        {
            if (y == hoverGridY || y == hoverGridY + gridSize)
                render.SetColor(gridHighlightColor);
            else
                render.SetColor(gridColor);

            render.Line(0, y, static_cast<int>(width), y);
        }

        if (mouseX >= 0 && mouseX < static_cast<int>(width) && mouseY >= 0 && mouseY < static_cast<int>(height))
        {
            render.SetColor(Color{ 40, 60, 90 });
            render.Fill(hoverGridX + 1, hoverGridY + 1, gridSize - 1, gridSize - 1);
        }

        render.SetColor(rectColor);
        render.Fill(100, 100, 250, 180);

        render.SetColor(Color{ 60, 130, 240 });
        render.Fill(450, 320, 200, 150);

        int animatedOffset = static_cast<int>((std::sin(animationTime) * 0.5f + 0.5f) * 600.0f);

        render.SetColor(Color{ 220, 80, 220 });
        render.Line(40, 40, 760, 560);

        render.SetColor(Color{ 0, 200, 150 });
        render.Line(760, 40, 40 + animatedOffset, 560);

        render.SetColor(pixelColor);
        for (int i = 0; i < 200; i += 2)
        {
            std::size_t px = static_cast<std::size_t>(300 + i);
            int waveY = static_cast<int>(200.0f + std::sin(animationTime * 5.0f + static_cast<float>(i) * 0.05f) * 20.0f);

            if (waveY >= 0 && waveY < static_cast<int>(height))
            {
                render.Pixel(px, static_cast<std::size_t>(waveY));
            }
        }
        };

    app.Run();

    return 0;
}
