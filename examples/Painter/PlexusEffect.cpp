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

struct PlexusNode {
    float x;
    float y;
    float vx;
    float vy;
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Interactive Plexus Network"))
    {
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDistX(10.0f, static_cast<float>(width) - 10.0f);
    std::uniform_real_distribution<float> posDistY(10.0f, static_cast<float>(height) - 10.0f);
    std::uniform_real_distribution<float> velDist(-1.5f, 1.5f);

    constexpr std::size_t totalNodes = 120;
    std::vector<PlexusNode> nodes(totalNodes);
    for (auto& node : nodes)
    {
        node.x = posDistX(gen);
        node.y = posDistY(gen);
        node.vx = velDist(gen);
        node.vy = velDist(gen);

        if (std::abs(node.vx) < 0.2f) node.vx = 0.5f;
        if (std::abs(node.vy) < 0.2f) node.vy = 0.5f;
    }

    float mouseX = -1000.0f;
    float mouseY = -1000.0f;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            mouseX = static_cast<float>(event.Mouse.PosX);
            mouseY = static_cast<float>(event.Mouse.PosY);
        }
        };

    app.OnUpdate = [&](float) noexcept {
        constexpr float mouseRepelRadius = 150.0f;
        constexpr float repelForce = 3.5f;

        for (auto& node : nodes)
        {
            node.x += node.vx;
            node.y += node.vy;

            if (node.x <= 0.0f || node.x >= static_cast<float>(width))  node.vx *= -1.0f;
            if (node.y <= 0.0f || node.y >= static_cast<float>(height)) node.vy *= -1.0f;

            node.x = std::clamp(node.x, 0.0f, static_cast<float>(width - 1));
            node.y = std::clamp(node.y, 0.0f, static_cast<float>(height - 1));

            float dxMouse = node.x - mouseX;
            float dyMouse = node.y - mouseY;
            float distMouse = std::sqrt(dxMouse * dxMouse + dyMouse * dyMouse);

            if (distMouse < mouseRepelRadius && distMouse > 0.1f)
            {
                float forceFactor = (1.0f - (distMouse / mouseRepelRadius)) * repelForce;
                node.x += (dxMouse / distMouse) * forceFactor;
                node.y += (dyMouse / distMouse) * forceFactor;
            }
        }
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 15, 18, 26, 255 });
        painter.Clear();

        constexpr float interactionRadius = 110.0f;

        for (std::size_t i = 0; i < totalNodes; ++i)
        {
            for (std::size_t j = i + 1; j < totalNodes; ++j)
            {
                float dx = nodes[i].x - nodes[j].x;
                float dy = nodes[i].y - nodes[j].y;
                float distanceSqr = dx * dx + dy * dy;

                constexpr float maxDistSqr = interactionRadius * interactionRadius;

                if (distanceSqr < maxDistSqr)
                {
                    float distance = std::sqrt(distanceSqr);

                    float fadeRatio = 1.0f - (distance / interactionRadius);
                    std::uint8_t greenIntensity = static_cast<std::uint8_t>(40.0f + 160.0f * fadeRatio);
                    std::uint8_t blueIntensity = static_cast<std::uint8_t>(100.0f + 155.0f * fadeRatio);

                    painter.SetColor(Color{ 30, greenIntensity, blueIntensity, 255 });
                    painter.Line(
                        static_cast<int>(nodes[i].x), static_cast<int>(nodes[i].y),
                        static_cast<int>(nodes[j].x), static_cast<int>(nodes[j].y)
                    );
                }
            }
        }

        for (const auto& node : nodes)
        {
            int ix = static_cast<int>(node.x);
            int iy = static_cast<int>(node.y);

            painter.SetColor(Color{ 80, 180, 240, 80 });
            painter.Circle(ix, iy, 4);

            painter.SetColor(Color{ 255, 255, 255, 255 });
            painter.Pixel(static_cast<std::size_t>(ix), static_cast<std::size_t>(iy));
        }
        };

    app.Run();

    return 0;
}
