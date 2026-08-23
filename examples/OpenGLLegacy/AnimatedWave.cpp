// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

import std;
import AppGL1;
import GlmLite;
import WinLite;
import OpenGL;

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

void setMatrix(GLenum matrixMode, const glm::mat4& matrix) noexcept;
void initWave(float time) noexcept;
void updateWave(float time) noexcept;

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

void setMatrix(GLenum matrixMode, const glm::mat4& matrix) noexcept
{
    glMatrixMode(matrixMode);
    glLoadMatrixf(glm::value_ptr(matrix));
}

void initWave(float time) noexcept
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

void updateWave(float time) noexcept
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

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Animated Wave (100x100 points)"))
    {
        return -1;
    }

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

    float cameraAngle = 0.0f;
    bool autoRotate = true;

    app.OnEvent = [&](const Event& event) noexcept {
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
            glLoadMatrixf(glm::value_ptr(viewMatrix));
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = deltaTime;
        if (fixedDelta > 0.1f) fixedDelta = 0.1f;

        time += fixedDelta;
        updateWave(time);

        if (autoRotate)
        {
            cameraAngle += fixedDelta * 0.3f;
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
        }
        };

    app.OnRender = [&]() noexcept {
        glLoadMatrixf(glm::value_ptr(viewMatrix));
        glDrawArrays(GL_POINTS, 0, POINTS_COUNT);
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
