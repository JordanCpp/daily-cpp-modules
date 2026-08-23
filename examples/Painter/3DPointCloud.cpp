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

struct Point3D {
    float x;
    float y;
    float z;
    std::uint8_t baseColorR;
    std::uint8_t baseColorG;
    std::uint8_t baseColorB;
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: 3D DNA Point Cloud"))
    {
        return -1;
    }

    std::vector<Point3D> dnaPoints;
    constexpr int totalNodesPerStrand = 180;
    constexpr float helixRadius = 120.0f;
    constexpr float helixLength = 500.0f;

    for (int i = 0; i < totalNodesPerStrand; ++i)
    {
        float progress = static_cast<float>(i) / static_cast<float>(totalNodesPerStrand);
        float angle = progress * 6.0f * Math::PI;
        float yPos = (progress * helixLength) - (helixLength / 2.0f);

        float x1 = std::cos(angle) * helixRadius;
        float z1 = std::sin(angle) * helixRadius;
        dnaPoints.push_back(Point3D{ x1, yPos, z1, 255, 80, 80 });

        float x2 = std::cos(angle + Math::PI) * helixRadius;
        float z2 = std::sin(angle + Math::PI) * helixRadius;
        dnaPoints.push_back(Point3D{ x2, yPos, z2, 80, 160, 255 });

        if (i % 6 == 0)
        {
            constexpr int rungDensity = 8;
            for (int r = 1; r < rungDensity; ++r)
            {
                float interpolationFactor = static_cast<float>(r) / static_cast<float>(rungDensity);
                float rx = x1 + (x2 - x1) * interpolationFactor;
                float rz = z1 + (z2 - z1) * interpolationFactor;
                dnaPoints.push_back(Point3D{ rx, yPos, rz, 200, 200, 200 });
            }
        }
    }

    const int centerX = static_cast<int>(width / 2);
    const int centerY = static_cast<int>(height / 2);
    constexpr float fovProjectionScale = 600.0f;
    constexpr float cameraZDistance = 650.0f;

    float elapsed = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 12, 14, 20, 255 });
        painter.Clear();

        float angleY = elapsed * 0.8f;
        float angleX = std::sin(elapsed * 0.4f) * 0.4f;

        float cosY = std::cos(angleY);
        float sinY = std::sin(angleY);
        float cosX = std::cos(angleX);
        float sinX = std::sin(angleX);

        for (const auto& point : dnaPoints)
        {
            float rotY_X = point.x * cosY - point.z * sinY;
            float rotY_Z = point.x * sinY + point.z * cosY;

            float rotX_Y = point.y * cosX - rotY_Z * sinX;
            float rotX_Z = point.y * sinX + rotY_Z * cosX;

            float finalZ = rotX_Z + cameraZDistance;

            if (finalZ > 10.0f)
            {
                int screenX = static_cast<int>(rotY_X * fovProjectionScale / finalZ) + centerX;
                int screenY = static_cast<int>(rotX_Y * fovProjectionScale / finalZ) + centerY;

                if (static_cast<std::size_t>(screenX) < width &&
                    static_cast<std::size_t>(screenY) < height)
                {
                    float depthRatio = std::clamp(1.0f - ((finalZ - (cameraZDistance - helixRadius)) / (helixRadius * 2.0f)), 0.1f, 1.0f);

                    std::uint8_t finalR = static_cast<std::uint8_t>(point.baseColorR * depthRatio);
                    std::uint8_t finalG = static_cast<std::uint8_t>(point.baseColorG * depthRatio);
                    std::uint8_t finalB = static_cast<std::uint8_t>(point.baseColorB * depthRatio);

                    painter.SetColor(Color{ finalR, finalG, finalB, 255 });

                    if (depthRatio > 0.75f)
                    {
                        painter.Circle(screenX, screenY, 2);
                    }
                    else
                    {
                        painter.Pixel(static_cast<std::size_t>(screenX), static_cast<std::size_t>(screenY));
                    }
                }
            }
        }
        };

    app.Run();

    return 0;
}
