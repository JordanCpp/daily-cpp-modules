// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include <memory_resource>
#include <cmath>
#include <chrono>
#include <format>
#include <iostream>
#include <random>
#include <string>
#include <numbers>
#include <print>

import GlmLite;
import WinLite;
import OpenGL;
import FpsCounter;

using namespace WinLite;

constexpr int   GRID_SIZE = 100;
constexpr int   POINTS_COUNT = GRID_SIZE * GRID_SIZE;
constexpr float GRID_SPACING = 0.04f;
constexpr float WAVE_AMPLITUDE = 0.5f;
constexpr float WAVE_SPEED = 2.0f;

float waveVertices[POINTS_COUNT * 3];
float waveColors[POINTS_COUNT * 3];

struct WavePoint {
    float y;
    float r, g, b;
};

static WavePoint computeWavePoint(int i, int j, float time) noexcept
{
    const float fi = static_cast<float>(i);
    const float fj = static_cast<float>(j);
    const float fGridHalf = static_cast<float>(GRID_SIZE) / 2.0f;

    const float x = (fi - fGridHalf) * GRID_SPACING;
    const float z = (fj - fGridHalf) * GRID_SPACING;

    const float y = WAVE_AMPLITUDE * (
        static_cast<float>(std::sin(x * 2.0f + time * WAVE_SPEED)) *
        static_cast<float>(std::cos(z * 1.5f + time * 1.3f)) +
        static_cast<float>(std::sin((x + z) * 1.2f + time * 0.7f)) * 0.5f +
        static_cast<float>(std::cos(x * 1.8f - z * 2.0f + time * 1.1f)) * 0.3f
        );

    const float normalizedHeight = (y / WAVE_AMPLITUDE) * 0.5f + 0.5f;

    float r = normalizedHeight;
    float g = 0.5f + 0.5f * static_cast<float>(std::sin(normalizedHeight * std::numbers::pi_v<float>));
    float b = 1.0f - normalizedHeight;

    const float twinkle = 0.8f + 0.2f * static_cast<float>(std::sin(x * 5.0f + z * 7.0f + time * 3.0f));

    return { y, r * twinkle, g * twinkle, b * twinkle };
}

void setMatrix(GLenum matrixMode, const glm::mat4& matrix)
{
    glMatrixMode(matrixMode);
    glLoadMatrixf(glm::value_ptr(matrix));
}

void initWave(float time)
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            const int index = (i * GRID_SIZE + j) * 3;
            const auto [y, r, g, b] = computeWavePoint(i, j, time);

            const float fi = static_cast<float>(i);
            const float fj = static_cast<float>(j);
            const float fGridHalf = static_cast<float>(GRID_SIZE) / 2.0f;

            waveVertices[index] = (fi - fGridHalf) * GRID_SPACING;
            waveVertices[index + 1] = y;
            waveVertices[index + 2] = (fj - fGridHalf) * GRID_SPACING;

            waveColors[index] = r;
            waveColors[index + 1] = g;
            waveColors[index + 2] = b;
        }
    }
}

void updateWave(float time)
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            const int index = (i * GRID_SIZE + j) * 3;
            const auto [y, r, g, b] = computeWavePoint(i, j, time);

            waveVertices[index + 1] = y;
            waveColors[index] = r;
            waveColors[index + 1] = g;
            waveColors[index + 2] = b;
        }
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    auto windowResult = OpenGL1Window::Create(width, height, "OpenGL 1.2 - Animated Wave (100x100 points)");

    if (!windowResult)
    {
        std::println("Error: {}", windowResult.error());
        return -1;
    }

    OpenGL1Window window = std::move(*windowResult);
    OpenGLLoader loader(1, 2);

    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(50.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        20.0f
    );

    setMatrix(GL_PROJECTION, projectionMatrix);
    glMatrixMode(GL_MODELVIEW);

    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(2.0f, 1.5f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glLoadMatrixf(glm::value_ptr(viewMatrix));
    glEnable(GL_DEPTH_TEST);
    glPointSize(2.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    float time = 0.0f;
    initWave(time);

    glVertexPointer(3, GL_FLOAT, 0, waveVertices);
    glColorPointer(3, GL_FLOAT, 0, waveColors);

    auto lastTime = std::chrono::steady_clock::now();
    float cameraAngle = 0.0f;
    bool autoRotate = true;

    FpsCounter counter;

    while (window.IsRunning())
    {
        const auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = static_cast<float>(std::chrono::duration<float>(currentTime - lastTime).count());
        lastTime = currentTime;

        if (deltaTime > 0.1f) deltaTime = 0.1f;

        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }

            if (event.IsKeyPressed(Key::Space))
            {
                autoRotate = !autoRotate;
            }

            if (event.IsKeyPressed(Key::R))
            {
                cameraAngle = 0.0f;
                viewMatrix = glm::lookAt(
                    glm::vec3(2.0f, 1.5f, 3.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f)
                );
            }
        }

        time += deltaTime;
        updateWave(time);

        glClearColor(0.0f, 0.02f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (autoRotate)
        {
            cameraAngle += deltaTime * 0.3f;
            if (cameraAngle > 2.0f * std::numbers::pi_v<float>)
            {
                cameraAngle -= 2.0f * std::numbers::pi_v<float>;
            }

            const float radius = 3.5f;
            const float camHeight = 1.8f;

            const glm::vec3 cameraPos(
                radius * static_cast<float>(std::sin(cameraAngle)),
                camHeight + 0.3f * static_cast<float>(std::sin(cameraAngle * 0.7f)),
                radius * static_cast<float>(std::cos(cameraAngle))
            );

            viewMatrix = glm::lookAt(
                cameraPos,
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );

            glLoadMatrixf(glm::value_ptr(viewMatrix));
        }

        glDrawArrays(GL_POINTS, 0, POINTS_COUNT);
        window.Present();

        if (counter.Update())
        {
            const std::string title = std::format("{} FPS | Points: {} | {} | [Space] Toggle Rotation | [R] Reset", counter.GetFps(), POINTS_COUNT, autoRotate ? "[Auto Rotate ON]" : "[Auto Rotate OFF]");
            window.SetTitle(title);
        }
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
