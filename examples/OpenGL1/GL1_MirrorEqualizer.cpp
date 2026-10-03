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

constexpr int BAR_ROWS = 7;
constexpr int BAR_COLS = 7;
constexpr float BAR_SPACING = 0.3f;
constexpr float BAR_WIDTH = 0.18f;

static float barHeights[BAR_ROWS * BAR_COLS];

static void initEqualizer() noexcept
{
    std::fill(std::begin(barHeights), std::end(barHeights), 0.0f);
}

static void updateEqualizer(float time) noexcept
{
    for (int r = 0; r < BAR_ROWS; ++r)
    {
        for (int c = 0; c < BAR_COLS; ++c)
        {
            const int index = r * BAR_COLS + c;
            const float fr = static_cast<float>(r);
            const float fc = static_cast<float>(c);

            float h = 0.2f + 0.8f * (
                static_cast<float>(std::sin(fr * 0.5f + time * 2.5f)) *
                static_cast<float>(std::cos(fc * 0.4f + time * 1.8f)) +
                static_cast<float>(std::sin((fr + fc) * 0.3f + time * 3.1f)) * 0.3f
                );

            barHeights[index] = std::clamp(std::abs(h), 0.05f, 1.5f);
        }
    }
}

static void drawBar(float height, float r, float g, float b) noexcept
{
    const float w = BAR_WIDTH * 0.5f;

    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex3f(-w, 0.0f, w); glVertex3f(w, 0.0f, w);
    glColor3f(r * 0.5f, g * 0.5f, b * 0.5f);
    glVertex3f(w, height, w); glVertex3f(-w, height, w);

    glColor3f(r * 0.3f, g * 0.3f, b * 0.3f);
    glVertex3f(-w, 0.0f, -w); glVertex3f(-w, height, -w);
    glVertex3f(w, height, -w); glVertex3f(w, 0.0f, -w);

    glColor3f(r * 1.2f, g * 1.2f, b * 1.2f);
    glVertex3f(-w, height, w); glVertex3f(w, height, w);
    glVertex3f(w, height, -w); glVertex3f(-w, height, -w);

    glColor3f(r * 0.6f, g * 0.6f, b * 0.6f);
    glVertex3f(w, 0.0f, w); glVertex3f(w, 0.0f, -w);
    glVertex3f(w, height, -w); glVertex3f(w, height, w);

    glVertex3f(-w, 0.0f, -w); glVertex3f(-w, 0.0f, w);
    glVertex3f(-w, height, w); glVertex3f(-w, height, -w);
    glEnd();
}

static void drawEqualizerGrid() noexcept
{
    const float rowHalf = static_cast<float>(BAR_ROWS) / 2.0f;
    const float colHalf = static_cast<float>(BAR_COLS) / 2.0f;

    for (int r = 0; r < BAR_ROWS; ++r)
    {
        for (int c = 0; c < BAR_COLS; ++c)
        {
            const float h = barHeights[r * BAR_COLS + c];

            glPushMatrix();
            const float x = (static_cast<float>(r) - rowHalf) * BAR_SPACING;
            const float z = (static_cast<float>(c) - colHalf) * BAR_SPACING;
            glTranslatef(x, 0.0f, z);

            const float redComp = static_cast<float>(r) / BAR_ROWS;
            const float blueComp = static_cast<float>(c) / BAR_COLS;

            drawBar(h, redComp, 1.0f - redComp, blueComp);
            glPopMatrix();
        }
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Mirror Equalizer 3D"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(52.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        20.0f
    );

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);

    float time = 0.0f;
    float cameraAngle = 0.4f;
    bool autoRotate = true;

    initEqualizer();

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.IsKeyPressed(Key::Space))
        {
            autoRotate = !autoRotate;
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = deltaTime;
        if (fixedDelta > 0.1f) fixedDelta = 0.1f;

        time += fixedDelta;
        updateEqualizer(time);

        if (autoRotate)
        {
            cameraAngle += fixedDelta * 0.2f;
            if (cameraAngle > 2.0f * std::numbers::pi_v<float>)
            {
                cameraAngle -= 2.0f * std::numbers::pi_v<float>;
            }
        }
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.02f, 0.01f, 0.04f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float radius = 3.8f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            1.6f,
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.3f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glPushMatrix();
        glScalef(1.0f, -1.0f, 1.0f);
        glFrontFace(GL_CW);
        drawEqualizerGrid();
        glFrontFace(GL_CCW);
        glPopMatrix();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);

        glColor4f(0.05f, 0.03f, 0.08f, 0.72f);
        glBegin(GL_QUADS);
        glVertex3f(-2.0f, 0.0f, -2.0f);
        glVertex3f(2.0f, 0.0f, -2.0f);
        glVertex3f(2.0f, 0.0f, 2.0f);
        glVertex3f(-2.0f, 0.0f, 2.0f);
        glEnd();

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

        drawEqualizerGrid();
        };

    app.Run();

    glDisable(GL_DEPTH_TEST);
    return 0;
}
