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
    App app;
    if (!app.Init("Daily C++ Modules: Enhanced Dynamic Demo"))
    {
        return -1;
    }

    float time = 0.0f;
    int mouseX = 0;
    int mouseY = 0;

    const int iWidth = static_cast<int>(app.GetWidth());
    const int iHeight = static_cast<int>(app.GetHeight());
    const int centerX = iWidth / 2;
    const int centerY = iHeight / 2;
    const float fCenterX = static_cast<float>(centerX);
    const float fCenterY = static_cast<float>(centerY);

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            mouseX = event.Mouse.PosX;
            mouseY = event.Mouse.PosY;
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        time += deltaTime;
        };

    app.OnRender = [&](PixelPainter& render, PixelCopier&) noexcept {
        const std::uint8_t bgR = static_cast<std::uint8_t>((std::sinf(time * 0.5f) * 0.5f + 0.5f) * 40.0f + 10.0f);
        const std::uint8_t bgG = static_cast<std::uint8_t>((std::sinf(time * 0.7f) * 0.5f + 0.5f) * 40.0f + 10.0f);
        const std::uint8_t bgB = static_cast<std::uint8_t>((std::sinf(time * 0.9f) * 0.5f + 0.5f) * 50.0f + 20.0f);

        render.SetColor(Color{ bgR, bgG, bgB });
        render.Clear();

        render.SetColor(Color{ 50, 50, 70 });
        for (int x = 0; x < iWidth; x += 80)
        {
            render.Line(x, 0, x, iHeight);
        }
        for (int y = 0; y < iHeight; y += 80)
        {
            render.Line(0, y, iWidth, y);
        }

        if (mouseX >= 0 && mouseX < iWidth && mouseY >= 0 && mouseY < iHeight)
        {
            render.SetColor(Color{ 80, 80, 100, 100 });
            render.Circle(mouseX, mouseY, 40);
        }

        const int rect1X = static_cast<int>(350.0f + std::cosf(time) * 150.0f);
        const int rect1Y = static_cast<int>(220.0f + std::sinf(time) * 100.0f);
        render.SetColor(Color{ 230, 90, 80 });
        render.Fill(rect1X, rect1Y, 120, 120);

        const int rect2X = static_cast<int>(370.0f + std::sinf(time * 1.5f) * 200.0f);
        render.SetColor(Color{ 60, 130, 240 });
        render.Fill(rect2X, 450, 80, 80);

        const int line1X = static_cast<int>(fCenterX + std::cosf(time * 0.8f) * 200.0f);
        const int line1Y = static_cast<int>(fCenterY + std::sinf(time * 0.8f) * 200.0f);
        render.SetColor(Color{ 80, 200, 140 });
        render.Line(centerX, centerY, line1X, line1Y);

        const int line2X = static_cast<int>(fCenterX + std::cosf(-time * 1.2f) * 150.0f);
        const int line2Y = static_cast<int>(fCenterY + std::sinf(-time * 1.2f) * 150.0f);
        render.SetColor(Color{ 220, 80, 220 });
        render.Line(centerX, centerY, line2X, line2Y);

        for (int i = 0; i < 400; i += 8)
        {
            const float radius = static_cast<float>(i + 20);
            const int pX = static_cast<int>(fCenterX + std::sinf(time * 2.0f + static_cast<float>(i)) * radius);
            const int pY = static_cast<int>(fCenterY + std::cosf(time * 2.0f + static_cast<float>(i)) * radius);

            if (pX >= 0 && pX < iWidth && pY >= 0 && pY < iHeight)
            {
                const std::size_t px = static_cast<std::size_t>(pX);
                const std::size_t py = static_cast<std::size_t>(pY);

                const std::uint8_t pR = static_cast<std::uint8_t>(200 + i % 55);
                const std::uint8_t pG = static_cast<std::uint8_t>(180 + i % 75);
                render.SetColor(Color{ pR, pG, 50 });
                render.Pixel(px, py);
            }
        }
        };

    app.Run();

    return 0;
}
