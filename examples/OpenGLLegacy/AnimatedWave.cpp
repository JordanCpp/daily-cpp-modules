// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <print>
#include <string>
#include <cmath>
#include <chrono>
#include <random>

import GlmLite;
import WinLite;
import OpenGL;
import FpsCounter;

using namespace WinLite;

constexpr int   GRID_SIZE      = 100;
constexpr int   POINTS_COUNT   = GRID_SIZE * GRID_SIZE;
constexpr float GRID_SPACING   = 0.04f;
constexpr float WAVE_AMPLITUDE = 0.5f;
constexpr float WAVE_SPEED     = 2.0f;

float waveVertices[POINTS_COUNT * 3];
float waveColors[POINTS_COUNT * 3];

void setMatrix(GLenum matrixMode, const glm::mat4& matrix)
{
    glMatrixMode(matrixMode);
    glLoadMatrixf(glm::value_ptr(matrix));
}

glm::vec3 randomColor()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    return glm::vec3(dis(gen), dis(gen), dis(gen));
}

void initWave(float time)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            int index = (i * GRID_SIZE + j) * 3;

            float x = (i - GRID_SIZE / 2.0f) * GRID_SPACING;
            float z = (j - GRID_SIZE / 2.0f) * GRID_SPACING;

            float y = WAVE_AMPLITUDE * (
                sin(x * 2.0f + time * WAVE_SPEED) *
                cos(z * 1.5f + time * 1.3f) +
                sin((x + z) * 1.2f + time * 0.7f) * 0.5f +
                cos(x * 1.8f - z * 2.0f + time * 1.1f) * 0.3f
                );

            waveVertices[index] = x;
            waveVertices[index + 1] = y;
            waveVertices[index + 2] = z;

            float normalizedHeight = (y / WAVE_AMPLITUDE) * 0.5f + 0.5f;

            waveColors[index] = normalizedHeight;
            waveColors[index + 1] = 0.5f + 0.5f * sin(normalizedHeight * 3.14f);
            waveColors[index + 2] = 1.0f - normalizedHeight;

            float twinkle = 0.8f + 0.2f * sin(x * 5.0f + z * 7.0f + time * 3.0f);
            waveColors[index] *= twinkle;
            waveColors[index + 1] *= twinkle;
            waveColors[index + 2] *= twinkle;
        }
    }
}

void updateWave(float time)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            int index = (i * GRID_SIZE + j) * 3;

            float x = (i - GRID_SIZE / 2.0f) * GRID_SPACING;
            float z = (j - GRID_SIZE / 2.0f) * GRID_SPACING;

            float y = WAVE_AMPLITUDE * (
                sin(x * 2.0f + time * WAVE_SPEED) *
                cos(z * 1.5f + time * 1.3f) +
                sin((x + z) * 1.2f + time * 0.7f) * 0.5f +
                cos(x * 1.8f - z * 2.0f + time * 1.1f) * 0.3f
                );

            waveVertices[index + 1] = y;

            float normalizedHeight = (y / WAVE_AMPLITUDE) * 0.5f + 0.5f;
            waveColors[index] = normalizedHeight;
            waveColors[index + 1] = 0.5f + 0.5f * sin(normalizedHeight * 3.14f);
            waveColors[index + 2] = 1.0f - normalizedHeight;

            float twinkle = 0.8f + 0.2f * sin(x * 5.0f + z * 7.0f + time * 3.0f);
            waveColors[index] *= twinkle;
            waveColors[index + 1] *= twinkle;
            waveColors[index + 2] *= twinkle;
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

    glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(50.0f),
        static_cast<float>(width) / height,
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
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
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
            if (cameraAngle > 2.0f * 3.14159f) cameraAngle -= 2.0f * 3.14159f;

            float radius = 3.5f;
            float height = 1.8f;
            glm::vec3 cameraPos(
                radius * sin(cameraAngle),
                height + 0.3f * sin(cameraAngle * 0.7f),
                radius * cos(cameraAngle)
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
            std::string title =
                std::to_string(counter.GetFps()) + " FPS | " +
                "Points: " + std::to_string(POINTS_COUNT) + " | " +
                (autoRotate ? "[Auto Rotate ON]" : "[Auto Rotate OFF]") + " | " +
                "[Space] Toggle Rotation | [R] Reset";
            window.SetTitle(title);
        }
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_DEPTH_TEST);

    return 0;
}