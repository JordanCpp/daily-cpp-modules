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

struct RainDrop
{
    float x;
    float y;
    float speed;
    std::vector<float> tail;
    std::size_t max_tail;
};

int main()
{
    constexpr int iWidth = 800;
    constexpr int iHeight = 600;
    constexpr int iColumnSpacing = 15;
    constexpr int iColumnCount = iWidth / iColumnSpacing;

    App app;
    if (!app.Init(iWidth, iHeight, "Daily C++ Modules: Cyberpunk Matrix"))
    {
        return -1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distSpeed(2.0f, 5.0f);
    std::uniform_int_distribution<int> distTailLen(5, 15);

    std::vector<RainDrop> drops;
    drops.reserve(iColumnCount);

    for (int i = 0; i < iColumnCount; ++i)
    {
        float startY = static_cast<float>(i * 50);
        drops.push_back(RainDrop{
            static_cast<float>(i * iColumnSpacing + iColumnSpacing / 2),
            startY,
            distSpeed(rng),
            {},
            static_cast<std::size_t>(distTailLen(rng))
            });
    }

    int mouseX = iWidth / 2;
    int mouseY = iHeight / 2;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            mouseX = event.Mouse.PosX;
            mouseY = event.Mouse.PosY;
        }
        };

    app.OnUpdate = [&](float) noexcept {
        float fSpeedMultiplier = 0.5f + (static_cast<float>(mouseX) / iWidth) * 3.0f;

        for (auto& drop : drops)
        {
            drop.y += drop.speed * fSpeedMultiplier;
            drop.tail.push_back(drop.y);

            if (drop.tail.size() > drop.max_tail)
            {
                drop.tail.erase(drop.tail.begin());
            }

            if (drop.y > static_cast<float>(iHeight))
            {
                drop.y = -20.0f;
                drop.tail.clear();
            }
        }
        };

    app.OnRender = [&](PixelPainter& render, PixelCopier&) noexcept {
        render.SetColor(Color{ 0, 0, 0 });
        render.Clear();

        float fColorShift = static_cast<float>(mouseY) / iHeight;

        auto GetDropColor = [&](float fAlpha) -> Color {
            float r = fAlpha * (fColorShift > 0.5f ? 255.0f : 0.0f);
            float g = fAlpha * 255.0f;
            float b = fAlpha * (fColorShift < 0.5f ? 0.0f : 255.0f);

            if (fAlpha > 0.9f) { r = 255; g = 255; b = 255; }

            return Color{
                static_cast<std::uint8_t>(std::clamp(r, 0.0f, 255.0f)),
                static_cast<std::uint8_t>(std::clamp(g, 0.0f, 255.0f)),
                static_cast<std::uint8_t>(std::clamp(b, 0.0f, 255.0f))
            };
            };

        for (const auto& drop : drops)
        {
            for (std::size_t i = 0; i < drop.tail.size(); ++i)
            {
                float fAlpha = static_cast<float>(i) / static_cast<float>(drop.tail.size());

                float posY = drop.tail[i];

                if (posY >= 0 && posY < iHeight)
                {
                    render.SetColor(GetDropColor(fAlpha));
                    render.Pixel(static_cast<std::size_t>(drop.x), static_cast<std::size_t>(posY));
                }
            }

            if (drop.y >= 0 && drop.y < iHeight)
            {
                render.SetColor(GetDropColor(1.0f));
                render.Pixel(static_cast<std::size_t>(drop.x), static_cast<std::size_t>(drop.y));
            }
        }

        render.SetColor(Color{ 0, 0, 0, 100 });
        render.Fill(0, 0, iWidth, 20);
        render.Fill(0, iHeight - 20, iWidth, 20);
        };

    app.Run();

    return 0;
}
