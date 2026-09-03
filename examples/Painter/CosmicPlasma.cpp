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
    constexpr int iWidth = 800;
    constexpr int iHeight = 600;

    App app;
    if (!app.Init(iWidth, iHeight, "Daily C++ Modules: Cosmic Plasma"))
    {
        return -1;
    }

    float time = 0.0f;
    int mouseX = iWidth / 2;
    int mouseY = iHeight / 2;

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
        const float fMouseInfluence = 0.001f + (static_cast<float>(mouseX) / iWidth) * 0.04f;

        for (int y = 0; y < iHeight; ++y)
        {
            for (int x = 0; x < iWidth; ++x)
            {
                float fVal = std::sinf(static_cast<float>(x) * fMouseInfluence + time) +
                             std::sinf(static_cast<float>(y) * fMouseInfluence + time) +
                             std::sinf((static_cast<float>(x) + static_cast<float>(y)) * fMouseInfluence * 0.5f + time);

                float fDist = std::sqrt(std::pow(static_cast<float>(x) - iWidth / 2.0f, 2.0f) + std::pow(static_cast<float>(y) - iHeight / 2.0f, 2.0f));
                fVal += std::sinf(fDist * 0.02f - time * 2.0f);

                const std::uint8_t r = static_cast<std::uint8_t>((std::sinf(fVal + 0.0f) * 0.5f + 0.5f) * 255);
                const std::uint8_t g = static_cast<std::uint8_t>((std::sinf(fVal + 2.0f) * 0.5f + 0.5f) * 255);
                const std::uint8_t b = static_cast<std::uint8_t>((std::sinf(fVal + 4.0f) * 0.5f + 0.5f) * 255);

                render.SetColor(Color{ r, g, b });
                render.Pixel(static_cast<std::size_t>(x), static_cast<std::size_t>(y));
            }
        }

        render.SetColor(Color{ 255, 255, 255, 40 });
        render.Circle(mouseX, mouseY, 50);
        };

    app.Run();

    return 0;
}
