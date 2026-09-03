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

struct Star
{
    float x;
    float y;
    float z;
    Color color;
};

int main()
{
    constexpr int iWidth = 800;
    constexpr int iHeight = 600;
    constexpr int iStarCount = 1000;

    App app;
    if (!app.Init(iWidth, iHeight, "Daily C++ Modules: Starfield Warp"))
    {
        return -1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distPos(-1.0f, 1.0f);
    std::uniform_real_distribution<float> distZ(0.1f, 1.0f);
    std::uniform_int_distribution<int> distColor(0, 255);

    std::vector<Star> stars;
    stars.reserve(iStarCount);

    for (int i = 0; i < iStarCount; ++i)
    {
        Color starColor;
        int type = i % 3;
        if (type == 0) starColor = Color{ 150, 200, 255 };
        else if (type == 1) starColor = Color{ 255, 150, 255 };
        else starColor = Color{ 255, 255, 255 };

        stars.push_back(Star{
            distPos(rng),
            distPos(rng),
            distZ(rng),
            starColor
            });
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
        render.SetColor(Color{ 0, 0, 0 });
        render.Clear();

        float fSpeed = 0.005f + (static_cast<float>(mouseX) / iWidth) * 0.045f;
        float fFOV = 200.0f + (static_cast<float>(mouseY) / iHeight) * 600.0f;

        const float fCenterX = static_cast<float>(iWidth) / 2.0f;
        const float fCenterY = static_cast<float>(iHeight) / 2.0f;

        for (auto& s : stars)
        {
            s.z -= fSpeed;

            if (s.z <= 0.01f)
            {
                s.z = 1.0f;
                s.x = distPos(rng);
                s.y = distPos(rng);
            }

            float fProjX = (s.x / s.z) * fFOV + fCenterX;
            float fProjY = (s.y / s.z) * fFOV + fCenterY;

            if (fProjX >= 0 && fProjX < iWidth && fProjY >= 0 && fProjY < iHeight)
            {
                float fPrevZ = s.z + fSpeed * 2.0f;
                float fPrevX = (s.x / fPrevZ) * fFOV + fCenterX;
                float fPrevY = (s.y / fPrevZ) * fFOV + fCenterY;

                float fBrightness = std::clamp(1.5f - s.z, 0.3f, 1.0f);

                render.SetColor(Color{
                    static_cast<std::uint8_t>(s.color.r * fBrightness),
                    static_cast<std::uint8_t>(s.color.g * fBrightness),
                    static_cast<std::uint8_t>(s.color.b * fBrightness)
                    });

                render.Line(
                    static_cast<int>(fProjX),
                    static_cast<int>(fProjY),
                    static_cast<int>(fPrevX),
                    static_cast<int>(fPrevY)
                );
            }
        }

        render.SetColor(Color{ 20, 20, 40, 50 });
        render.Circle(static_cast<int>(fCenterX), static_cast<int>(fCenterY), 100);
        };

    app.Run();

    return 0;
}
