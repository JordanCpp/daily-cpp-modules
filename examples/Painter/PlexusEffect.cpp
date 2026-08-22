// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

/*
 * DESCRIPTION:
 * This example implements an Interactive Plexus (Constellation) physics effect.
 * It manages a swarm of autonomous particles moving through screen space.
 * When two particles move close to each other, the PixelPainter::Line API connects them.
 * It showcases nested O(N^2) proximity checks optimized for real-time execution.
 * The mouse cursor acts as a gravitational repeller, pushing nodes away dynamically.
 */

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

import WinLite;
import PixelPainter;
import FpsCounter;

using namespace WinLite;
using namespace Software;

// Particle node configuration for physical movement simulation
struct PlexusNode {
    float x;
    float y;
    float vx;
    float vy;
};

int main()
{
    // Screen resolution and pixel layout definitions
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;
    constexpr std::size_t bytesPerPixel = 4; // 32-bit RGBA/BGRA mode

    auto windowResult = SoftwareWindow::Create(width, height, "Daily C++ Modules: Interactive Plexus Network");

    if (!windowResult)
    {
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);

    // Initialize the PixelPainter abstraction wrapper
    PixelPainter painter(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));
    FpsCounter counter;

    // Set up pseudo-random generator for particle velocity vectors
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDistX(10.0f, static_cast<float>(width) - 10.0f);
    std::uniform_real_distribution<float> posDistY(10.0f, static_cast<float>(height) - 10.0f);
    std::uniform_real_distribution<float> velDist(-1.5f, 1.5f);

    // Instantiate 120 dynamic network nodes (optimal balance for O(N^2) CPU math)
    constexpr std::size_t totalNodes = 120;
    std::vector<PlexusNode> nodes(totalNodes);
    for (auto& node : nodes)
    {
        node.x = posDistX(gen);
        node.y = posDistY(gen);
        node.vx = velDist(gen);
        node.vy = velDist(gen);

        // Prevent completely stationary particles
        if (std::abs(node.vx) < 0.2f) node.vx = 0.5f;
        if (std::abs(node.vy) < 0.2f) node.vy = 0.5f;
    }

    // Default cursor coordinates positioned off-screen initially
    float mouseX = -1000.0f;
    float mouseY = -1000.0f;

    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }

            // Intercept mouse move events to track interactive user input coordinates
            if (event.Type == EventType::MouseMove)
            {
                mouseX = static_cast<float>(event.Mouse.PosX);
                mouseY = static_cast<float>(event.Mouse.PosY);
            }
        }

        // Clean the background layout cleanly via painter state
        painter.SetColor(Color{ 15, 18, 26, 255 });
        painter.Clear();

        // 1. UPDATE PHYSICS & MOUSE FORCE FIELDS
        constexpr float interactionRadius = 110.0f;
        constexpr float mouseRepelRadius = 150.0f;
        constexpr float repelForce = 3.5f;

        for (auto& node : nodes)
        {
            // Apply velocity changes to position coordinates
            node.x += node.vx;
            node.y += node.vy;

            // Strict boundary collision tracking (elastic bouncing walls)
            if (node.x <= 0.0f || node.x >= static_cast<float>(width))  node.vx *= -1.0f;
            if (node.y <= 0.0f || node.y >= static_cast<float>(height)) node.vy *= -1.0f;

            // Clamp inside layout bounds to avoid coordinate overflows
            node.x = std::clamp(node.x, 0.0f, static_cast<float>(width - 1));
            node.y = std::clamp(node.y, 0.0f, static_cast<float>(height - 1));

            // Calculate proximity of cursor to execute force deflection
            float dxMouse = node.x - mouseX;
            float dyMouse = node.y - mouseY;
            float distMouse = std::sqrt(dxMouse * dxMouse + dyMouse * dyMouse);

            if (distMouse < mouseRepelRadius && distMouse > 0.1f)
            {
                // Push particles away smoothly from the active tracking coordinate
                float forceFactor = (1.0f - (distMouse / mouseRepelRadius)) * repelForce;
                node.x += (dxMouse / distMouse) * forceFactor;
                node.y += (dyMouse / distMouse) * forceFactor;
            }
        }

        // 2. RENDER NESTED CONNECTIONS (Using Line API)
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

                    // Alpha-like fade calculation based on physical proximity link strength
                    float fadeRatio = 1.0f - (distance / interactionRadius);
                    std::uint8_t greenIntensity = static_cast<std::uint8_t>(40.0f + 160.0f * fadeRatio);
                    std::uint8_t blueIntensity = static_cast<std::uint8_t>(100.0f + 155.0f * fadeRatio);

                    // Draw connecting webbing links between nearby elements
                    painter.SetColor(Color{ 30, greenIntensity, blueIntensity, 255 });
                    painter.Line(
                        static_cast<int>(nodes[i].x), static_cast<int>(nodes[i].y),
                        static_cast<int>(nodes[j].x), static_cast<int>(nodes[j].y)
                    );
                }
            }
        }

        // 3. RENDER NODE CORE VISUALS (Using Circle & Pixel API)
        for (const auto& node : nodes)
        {
            int ix = static_cast<int>(node.x);
            int iy = static_cast<int>(node.y);

            // Draw a subtle outer halo effect ring
            painter.SetColor(Color{ 80, 180, 240, 80 });
            painter.Circle(ix, iy, 4);

            // Render crisp point core exactly on top
            painter.SetColor(Color{ 255, 255, 255, 255 });
            painter.Pixel(static_cast<std::size_t>(ix), static_cast<std::size_t>(iy));
        }

        // Present completed backbuffer memory straight to the window
        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle("Interactive Plexus Mesh - FPS: " + std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
