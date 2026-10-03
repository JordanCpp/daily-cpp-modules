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

constexpr int   RADAR_GRID_SIZE = 60;
constexpr float RADAR_SPACING = 0.08f;

static std::vector<float> radarVertices;
static std::vector<float> radarColors;

static glm::vec4 computeRadarPoint(int i, int j, float time) noexcept
{
    const float fGridHalf = static_cast<float>(RADAR_GRID_SIZE) / 2.0f;
    const float x = (static_cast<float>(i) - fGridHalf) * RADAR_SPACING;
    const float z = (static_cast<float>(j) - fGridHalf) * RADAR_SPACING;

    const float distanceToCenter = std::sqrt(x * x + z * z);

    float y = 0.2f * (
        static_cast<float>(std::sin(x * 3.0f)) * static_cast<float>(std::cos(z * 2.5f)) +
        static_cast<float>(std::sin(z * 4.0f + time)) * 0.3f
        );

    constexpr float waveSpeed = 2.5f;
    constexpr float waveLength = 1.2f;
    const float waveInertia = std::fmod(time * waveSpeed, 4.0f);

    float intensity = 0.1f;
    if (std::abs(distanceToCenter - waveInertia) < waveLength)
    {
        const float factor = 1.0f - (std::abs(distanceToCenter - waveInertia) / waveLength);
        intensity += factor * 0.9f;
        y += factor * 0.15f;
    }

    return glm::vec4(x, y, z, intensity);
}

static void updateRadar(float time) noexcept
{
    radarVertices.clear();
    radarColors.clear();

    radarVertices.reserve(RADAR_GRID_SIZE * RADAR_GRID_SIZE * 6);
    radarColors.reserve(RADAR_GRID_SIZE * RADAR_GRID_SIZE * 6);

    for (int i = 0; i < RADAR_GRID_SIZE; ++i)
    {
        for (int j = 0; j < RADAR_GRID_SIZE; ++j)
        {
            const auto vCurrent = computeRadarPoint(i, j, time);

            if (i < RADAR_GRID_SIZE - 1)
            {
                const auto vNextX = computeRadarPoint(i + 1, j, time);
                radarVertices.insert(radarVertices.end(), { vCurrent.x, vCurrent.y, vCurrent.z, vNextX.x, vNextX.y, vNextX.z });
                radarColors.insert(radarColors.end(), { 0.0f, vCurrent.w, vCurrent.w * 0.3f, 0.0f, vNextX.w, vNextX.w * 0.3f });
            }
            if (j < RADAR_GRID_SIZE - 1)
            {
                const auto vNextZ = computeRadarPoint(i, j + 1, time);
                radarVertices.insert(radarVertices.end(), { vCurrent.x, vCurrent.y, vCurrent.z, vNextZ.x, vNextZ.y, vNextZ.z });
                radarColors.insert(radarColors.end(), { 0.0f, vCurrent.w, vCurrent.w * 0.3f, 0.0f, vNextZ.w, vNextZ.w * 0.3f });
            }
        }
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Holographic Sci-Fi Radar"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(50.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        15.0f
    );

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.5f);

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);

    constexpr float fogColor[] = { 0.01f, 0.03f, 0.01f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 2.0f);
    glFogf(GL_FOG_END, 5.0f);
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
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = deltaTime;
        if (fixedDelta > 0.1f) fixedDelta = 0.1f;

        time += fixedDelta;
        updateRadar(time);

        if (autoRotate)
        {
            cameraAngle += fixedDelta * 0.25f;
            if (cameraAngle > 2.0f * std::numbers::pi_v<float>)
            {
                cameraAngle -= 2.0f * std::numbers::pi_v<float>;
            }
        }
        };

    app.OnRender = [&]() noexcept {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float radius = 3.5f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            1.8f,
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, -0.2f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glPushMatrix();
        glTranslatef(0.0f, -0.1f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.4f, 0.1f);
        glBegin(GL_LINE_LOOP);
        for (int a = 0; a < 64; ++a)
        {
            const float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(a) / 64.0f;
            glVertex2f(1.8f * std::sin(angle), 1.8f * std::cos(angle));
        }
        glEnd();
        glPopMatrix();

        glVertexPointer(3, GL_FLOAT, 0, radarVertices.data());
        glColorPointer(3, GL_FLOAT, 0, radarColors.data());
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(radarVertices.size() / 3));
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_FOG);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
