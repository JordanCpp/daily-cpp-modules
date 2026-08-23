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

class FastRandom {
public:
    static float Range(float min, float max) noexcept {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }
};

void GenerateLightningBranch(PixelPainter& painter, int x0, int y0, int x1, int y1, float displace, float minDisplace) noexcept;

void GenerateLightningBranch(PixelPainter& painter, int x0, int y0, int x1, int y1, float displace, float minDisplace) noexcept {
    if (displace < minDisplace) {
        painter.Line(x0, y0, x1, y1);
        return;
    }

    int midX = (x0 + x1) / 2;
    int midY = (y0 + y1) / 2;

    float deltaX = static_cast<float>(x1 - x0);
    float deltaY = static_cast<float>(y1 - y0);
    float length = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (length > 0.1f) {
        midX += static_cast<int>(((-deltaY / length) * FastRandom::Range(-displace, displace)));
        midY += static_cast<int>(((deltaX / length) * FastRandom::Range(-displace, displace)));
    }

    if (FastRandom::Range(0.0f, 1.0f) < 0.08f) {
        int branchEndX = midX + static_cast<int>(FastRandom::Range(-40.0f, 40.0f));
        int branchEndY = midY + static_cast<int>(FastRandom::Range(-40.0f, 40.0f));

        painter.SetColor(Color{ 80, 130, 255, 120 });
        GenerateLightningBranch(painter, midX, midY, branchEndX, branchEndY, displace * 0.4f, minDisplace);
    }

    GenerateLightningBranch(painter, x0, y0, midX, midY, displace * 0.5f, minDisplace);
    GenerateLightningBranch(painter, midX, midY, x1, y1, displace * 0.5f, minDisplace);
}

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Tesla Lightning Show"))
    {
        return -1;
    }

    const int emitterX = static_cast<int>(width / 2);
    const int emitterY = static_cast<int>(height / 2);

    int targetX = emitterX + 150;
    int targetY = emitterY + 150;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            targetX = event.Mouse.PosX;
            targetY = event.Mouse.PosY;
        }
        };

    app.OnUpdate = [&](float) noexcept {};

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 8, 5, 15, 60 });
        painter.Fill(0, 0, static_cast<int>(width), static_cast<int>(height));

        painter.SetColor(Color{ 255, 100, 50, 255 });
        painter.Circle(emitterX, emitterY, 14);
        painter.SetColor(Color{ 255, 255, 255, 255 });
        painter.Circle(emitterX, emitterY, 6);

        int lightningStrikes = static_cast<int>(FastRandom::Range(1.0f, 3.0f));
        for (int strike = 0; strike < lightningStrikes; ++strike) {
            std::uint8_t r = static_cast<std::uint8_t>(140 + FastRandom::Range(0, 50));
            std::uint8_t g = static_cast<std::uint8_t>(200 + FastRandom::Range(0, 55));
            std::uint8_t b = 255;

            painter.SetColor(Color{ r, g, b, 255 });
            GenerateLightningBranch(painter, emitterX, emitterY, targetX, targetY, 160.0f, 4.0f);
        }

        painter.SetColor(Color{ 255, 255, 200, 255 });
        painter.Circle(targetX, targetY, 4);
        };

    app.Run();

    return 0;
}
