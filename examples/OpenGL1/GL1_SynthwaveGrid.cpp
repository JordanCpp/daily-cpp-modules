// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import AppGL1;
import GlmLite;
import WinLite;
import OpenGL;

using namespace WinLite;

constexpr int   GRID_SIZE = 80;
constexpr float GRID_SPACING = 0.12f;
constexpr float SPEED = 2.5f;

static std::vector<float> gridVertices;
static std::vector<float> gridColors;

struct GridPoint {
    glm::vec3 pos;
    glm::vec3 color;
};

static GridPoint computeGridVertex(int i, int j, float time) noexcept
{
    const float fGridHalf = static_cast<float>(GRID_SIZE) / 2.0f;
    const float x = (static_cast<float>(i) - fGridHalf) * GRID_SPACING;
    const float z_orig = (static_cast<float>(j) - fGridHalf) * GRID_SPACING;
    const float z_anim = z_orig + time * SPEED;

    const float distanceFromCenter = std::abs(x);
    float y = 0.0f;
    if (distanceFromCenter > 0.8f)
    {
        const float hillScale = (distanceFromCenter - 0.8f) * 0.6f;
        y = hillScale * (
            static_cast<float>(std::sin(x * 2.0f)) * static_cast<float>(std::cos(z_anim * 1.1f)) +
            static_cast<float>(std::sin(z_anim * 1.5f + x)) * 0.4f
            );
    }

    float r = 0.9f;
    float g = 0.0f;
    float b = 0.7f + 0.3f * static_cast<float>(std::sin(x * 1.5f));

    if (y > 0.1f)
    {
        r += y * 0.2f;
        b += y * 0.1f;
    }

    r = std::min(r, 1.0f);
    b = std::min(b, 1.0f);

    return { glm::vec3(x, y, z_orig), glm::vec3(r, g, b) };
}

static void updateSynthwave(float time) noexcept
{
    gridVertices.clear();
    gridColors.clear();

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            const auto current = computeGridVertex(i, j, time);

            if (i < GRID_SIZE - 1)
            {
                const auto nextX = computeGridVertex(i + 1, j, time);
                gridVertices.insert(gridVertices.end(), { current.pos.x, current.pos.y, current.pos.z, nextX.pos.x, nextX.pos.y, nextX.pos.z });
                gridColors.insert(gridColors.end(), { current.color.x, current.color.y, current.color.z, nextX.color.x, nextX.color.y, nextX.color.z });
            }
            if (j < GRID_SIZE - 1)
            {
                const auto nextZ = computeGridVertex(i, j + 1, time);
                gridVertices.insert(gridVertices.end(), { current.pos.x, current.pos.y, current.pos.z, nextZ.pos.x, nextZ.pos.y, nextZ.pos.z });
                gridColors.insert(gridColors.end(), { current.color.x, current.color.y, current.color.z, nextZ.color.x, nextZ.color.y, nextZ.color.z });
            }
        }
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Synthwave Retro Landscape"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(55.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        15.0f
    );
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));

    glMatrixMode(GL_MODELVIEW);
    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(2.5f, 1.8f, 3.5f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.5f);

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);

    constexpr float fogColor[] = { 0.04f, 0.01f, 0.08f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 2.0f);
    glFogf(GL_FOG_END, 6.5f);
    glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    float time = 0.0f;
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
                glm::vec3(2.5f, 1.8f, 3.5f),
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
        updateSynthwave(time);

        if (autoRotate)
        {
            cameraAngle += fixedDelta * 0.2f;
            if (cameraAngle > 2.0f * std::numbers::pi_v<float>)
            {
                cameraAngle -= 2.0f * std::numbers::pi_v<float>;
            }

            const float radius = 4.5f;
            const float camHeight = 1.6f;

            const glm::vec3 cameraPos(
                radius * static_cast<float>(std::sin(cameraAngle)),
                camHeight + 0.2f * static_cast<float>(std::sin(cameraAngle * 0.5f)),
                radius * static_cast<float>(std::cos(cameraAngle))
            );

            viewMatrix = glm::lookAt(
                cameraPos,
                glm::vec3(0.0f, -0.2f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );
        }
        };

    app.OnRender = [&]() noexcept {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glVertexPointer(3, GL_FLOAT, 0, gridVertices.data());
        glColorPointer(3, GL_FLOAT, 0, gridColors.data());

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(gridVertices.size() / 3));
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_FOG);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
