// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import App;
import WinLite;
import PixelPainter;
import PixelCopier;
import FpsCounter;

using namespace WinLite;
using namespace Software;

namespace Math {
    constexpr float PI = 3.1415926535f;
}

constexpr int gridRows = 30;
constexpr int gridCols = 24;
constexpr float cellSpacing = 40.0f;

struct ScreenPoint { int x; int y; bool isValid; };

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Retro 3D Synthwave Terrain"))
    {
        return -1;
    }

    std::vector<std::vector<ScreenPoint>> screenMesh(gridRows, std::vector<ScreenPoint>(gridCols));

    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);

    constexpr float cameraHeight = 160.0f;
    constexpr float fovScale = 450.0f;
    constexpr float horizonZOffset = 40.0f;

    float elapsed = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 12, 8, 16, 255 });
        painter.Clear();

        float terrainSpeed = elapsed * 120.0f;
        float forwardOffset = std::fmod(terrainSpeed, cellSpacing);

        for (int r = 0; r < gridRows; ++r)
        {
            float worldZ = (static_cast<float>(gridRows - r) * cellSpacing) - forwardOffset + horizonZOffset;

            for (int c = 0; c < gridCols; ++c)
            {
                float worldX = (static_cast<float>(c - gridCols / 2) * cellSpacing);
                float distanceFromCenter = std::abs(static_cast<float>(c - gridCols / 2));
                float heightMultiplier = 0.0f;
                if (distanceFromCenter > 3.0f)
                {
                    heightMultiplier = (distanceFromCenter - 3.0f) * 18.0f;
                }

                float wave1 = std::sin(worldX * 0.015f + (terrainSpeed * 0.02f)) * std::cos(worldZ * 0.01f);
                float wave2 = std::sin((worldZ + terrainSpeed) * 0.025f) * 0.4f;
                float worldY = (wave1 + wave2) * heightMultiplier + cameraHeight;

                if (worldZ > 5.0f)
                {
                    int sX = static_cast<int>((worldX * fovScale) / worldZ) + centerX;
                    int sY = static_cast<int>((worldY * fovScale) / worldZ) + centerY;

                    screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = ScreenPoint{ sX, sY, true };
                }
                else
                {
                    screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = ScreenPoint{ 0, 0, false };
                }
            }
        }

        for (int r = 0; r < gridRows - 1; ++r)
        {
            float depthRatio = static_cast<float>(r) / static_cast<float>(gridRows);

            std::uint8_t redIntensity = static_cast<std::uint8_t>(80.0f + 175.0f * depthRatio);
            std::uint8_t greenIntensity = static_cast<std::uint8_t>(20.0f + 30.0f * depthRatio);
            std::uint8_t blueIntensity = static_cast<std::uint8_t>(140.0f + 115.0f * depthRatio);

            painter.SetColor(Color{ redIntensity, greenIntensity, blueIntensity, 255 });

            for (int c = 0; c < gridCols; ++c)
            {
                const auto& pCurrent = screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];

                if (!pCurrent.isValid) continue;

                if (r < gridRows - 1)
                {
                    const auto& pForward = screenMesh[static_cast<std::size_t>(r + 1)][static_cast<std::size_t>(c)];
                    if (pForward.isValid)
                    {
                        painter.Line(pCurrent.x, pCurrent.y, pForward.x, pForward.y);
                    }
                }

                if (c < gridCols - 1)
                {
                    const auto& pRight = screenMesh[static_cast<std::size_t>(r)][static_cast<std::size_t>(c + 1)];
                    if (pRight.isValid)
                    {
                        painter.Line(pCurrent.x, pCurrent.y, pRight.x, pRight.y);
                    }
                }
            }
        }

        painter.SetColor(Color{ 255, 180, 0, 255 });
        painter.Circle(centerX, centerY - 40, 80);
        };

    app.Run();

    return 0;
}
