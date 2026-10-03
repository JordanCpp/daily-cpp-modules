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

constexpr int TEX_RES = 256;
static GLuint glassTextureId = 0;

static void generateStainedGlassTexture() noexcept
{
    std::vector<std::uint8_t> texData(TEX_RES * TEX_RES * 3);
    const float halfRes = static_cast<float>(TEX_RES) / 2.0f;

    for (int y = 0; y < TEX_RES; ++y)
    {
        for (int x = 0; x < TEX_RES; ++x)
        {
            const float dx = static_cast<float>(x) - halfRes;
            const float dy = static_cast<float>(y) - halfRes;
            const float dist = std::sqrt(dx * dx + dy * dy);
            const float angle = std::atan2(dy, dx);

            const int sector = static_cast<int>((angle + std::numbers::pi_v<float>) * 4.0f);
            const int ring = static_cast<int>(dist / 20.0f);

            std::uint8_t r = 0, g = 0, b = 0;
            if (dist < halfRes)
            {
                r = static_cast<std::uint8_t>((sector % 2 == 0 ? 240 : 30));
                g = static_cast<std::uint8_t>((ring % 2 == 0 ? 150 : 40));
                b = static_cast<std::uint8_t>((sector % 3 == 0 ? 255 : 20));

                if (std::fmod(dist, 20.0f) < 2.0f || std::fmod(angle + std::numbers::pi_v<float>, 0.4f) < 0.04f)
                {
                    r = g = b = 15;
                }
            }
            else
            {
                r = g = b = 0;
            }

            const std::size_t idx = (static_cast<std::size_t>(y) * TEX_RES + static_cast<std::size_t>(x)) * 3;
            texData[idx] = r;
            texData[idx + 1] = g;
            texData[idx + 2] = b;
        }
    }

    glGenTextures(1, &glassTextureId);
    glBindTexture(GL_TEXTURE_2D, glassTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_RES, TEX_RES, 0, GL_RGB, GL_UNSIGNED_BYTE, texData.data());
}

static void drawColumn(float x, float z, float height, float radius) noexcept
{
    constexpr int segments = 12;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i)
    {
        const float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / segments;
        const float cosA = std::cos(angle);
        const float sinA = std::sin(angle);

        glNormal3f(cosA, 0.0f, sinA);
        glVertex3f(x + cosA * radius, -1.0f, z + sinA * radius);
        glVertex3f(x + cosA * radius, -1.0f + height, z + sinA * radius);
    }
    glEnd();
}

static void drawSolidCube(float size) noexcept
{
    const float h = size * 0.5f;
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-h, -h, h); glVertex3f(h, -h, h); glVertex3f(h, h, h); glVertex3f(-h, h, h);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-h, -h, -h); glVertex3f(-h, h, -h); glVertex3f(h, h, -h); glVertex3f(h, -h, -h);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-h, h, -h); glVertex3f(-h, h, h); glVertex3f(h, h, h); glVertex3f(h, h, -h);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-h, -h, -h); glVertex3f(h, -h, -h); glVertex3f(h, -h, h); glVertex3f(-h, -h, h);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(h, -h, -h); glVertex3f(h, h, -h); glVertex3f(h, h, h); glVertex3f(h, -h, h);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-h, -h, -h); glVertex3f(-h, -h, h); glVertex3f(-h, h, h); glVertex3f(-h, h, -h);
    glEnd();
}

static void draw3DScene(float time) noexcept
{
    constexpr float s = 2.5f;

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-s, -1.0f, -s); glVertex3f(-s, -1.0f, s);
    glVertex3f(s, -1.0f, s); glVertex3f(s, -1.0f, -s);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-s, 2.0f, -s); glVertex3f(s, 2.0f, -s);
    glVertex3f(s, 2.0f, s); glVertex3f(-s, 2.0f, s);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-s, -1.0f, -s); glVertex3f(s, -1.0f, -s);
    glVertex3f(s, 2.0f, -s); glVertex3f(-s, 2.0f, -s);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-s, -1.0f, s); glVertex3f(-s, -1.0f, -s);
    glVertex3f(-s, 2.0f, -s); glVertex3f(-s, 2.0f, s);
    glEnd();

    drawColumn(-1.5f, -1.5f, 3.0f, 0.15f);
    drawColumn(1.5f, -1.5f, 3.0f, 0.15f);
    drawColumn(-1.5f, 1.5f, 3.0f, 0.15f);
    drawColumn(1.5f, 1.5f, 3.0f, 0.15f);

    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    glRotatef(time * 30.0f, 0.0f, 1.0f, 0.5f);
    drawSolidCube(0.6f);
    glPopMatrix();
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Volumetric 3D Stained Glass Hall"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(55.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        25.0f
    );

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);

    generateStainedGlassTexture();

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    constexpr float fogColor[] = { 0.015f, 0.01f, 0.025f, 1.0f };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 1.5f);
    glFogf(GL_FOG_END, 7.0f);

    float time = 0.0f;
    float cameraAngle = 0.8f;
    bool autoRotate = true;

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

        if (autoRotate)
        {
            cameraAngle += fixedDelta * 0.15f;
            if (cameraAngle > 2.0f * std::numbers::pi_v<float>)
            {
                cameraAngle -= 2.0f * std::numbers::pi_v<float>;
            }
        }
        };

    app.OnRender = [&]() noexcept {
        glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float radius = 4.2f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            1.5f,
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.2f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glDisable(GL_TEXTURE_2D);
        glColor3f(0.12f, 0.12f, 0.15f);
        draw3DScene(time);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, glassTextureId);

        const float sunX = 1.6f * static_cast<float>(std::sin(time * 0.4f));
        const float sunY = 2.8f;
        const float sunZ = 1.6f * static_cast<float>(std::cos(time * 0.4f));

        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glEnable(GL_TEXTURE_GEN_R);
        glEnable(GL_TEXTURE_GEN_Q);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

        const float planeS[] = { 1.0f, 0.0f, 0.0f, -sunX };
        const float planeT[] = { 0.0f, 0.0f, 1.0f, -sunZ };
        const float planeR[] = { 0.0f, 1.0f, 0.0f, -sunY };
        const float planeQ[] = { 0.0f, 0.4f, 0.0f, 1.0f };

        glTexGenfv(GL_S, GL_EYE_PLANE, planeS);
        glTexGenfv(GL_T, GL_EYE_PLANE, planeT);
        glTexGenfv(GL_R, GL_EYE_PLANE, planeR);
        glTexGenfv(GL_Q, GL_EYE_PLANE, planeQ);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(0.5f, 0.5f, 0.0f);
        glScalef(0.5f, 0.5f, 1.0f);
        glMatrixMode(GL_MODELVIEW);

        glColor3f(1.0f, 1.0f, 1.0f);
        draw3DScene(time);

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_GEN_R);
        glDisable(GL_TEXTURE_GEN_Q);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);

        glPushMatrix();
        glTranslatef(sunX, sunY - 0.9f, sunZ);
        glScalef(0.25f, 0.25f, 0.25f);
        glColor3f(1.0f, 0.95f, 0.9f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);
        for (int a = 0; a <= 20; ++a) {
            float ang = 2.0f * std::numbers::pi_v<float> *static_cast<float>(a) / 20.0f;
            glVertex3f(std::sin(ang), 0.0f, std::cos(ang));
        }
        glEnd();
        glPopMatrix();
        };

    app.Run();

    if (glassTextureId != 0) glDeleteTextures(1, &glassTextureId);
    glDisable(GL_FOG);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
