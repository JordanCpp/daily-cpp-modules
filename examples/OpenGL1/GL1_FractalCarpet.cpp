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

constexpr int TEXTURE_SIZE = 256;
static GLuint carpetTextureId = 0;

static std::uint8_t textureData[TEXTURE_SIZE * TEXTURE_SIZE * 3];

static void generatePlasmaTexture() noexcept
{
    for (int y = 0; y < TEXTURE_SIZE; ++y)
    {
        for (int x = 0; x < TEXTURE_SIZE; ++x)
        {
            const float fx = static_cast<float>(x) / static_cast<float>(TEXTURE_SIZE);
            const float fy = static_cast<float>(y) / static_cast<float>(TEXTURE_SIZE);

            float v = 0.0f;
            v += std::sin(fx * 4.0f * std::numbers::pi_v<float>);
            v += std::sin(fy * 4.0f * std::numbers::pi_v<float>);
            v += std::sin((fx + fy) * 4.0f * std::numbers::pi_v<float>);
            v += std::sin(std::sqrt(fx * fx + fy * fy) * 4.0f * std::numbers::pi_v<float>);
            v /= 4.0f;

            const auto r = static_cast<std::uint8_t>((std::sin(v * std::numbers::pi_v<float>) * 0.5f + 0.5f) * 255.0f);
            const auto g = static_cast<std::uint8_t>((std::cos(v * std::numbers::pi_v<float>) * 0.5f + 0.5f) * 255.0f);
            const auto b = static_cast<std::uint8_t>(255.0f);

            const int index = (y * TEXTURE_SIZE + x) * 3;
            textureData[index] = r;
            textureData[index + 1] = g;
            textureData[index + 2] = b;
        }
    }

    glGenTextures(1, &carpetTextureId);
    glBindTexture(GL_TEXTURE_2D, carpetTextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Psychedelic Fractal Carpet"))
    {
        return -1;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    generatePlasmaTexture();

    float time = 0.0f;

    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = deltaTime;
        if (fixedDelta > 0.1f) fixedDelta = 0.1f;
        time += fixedDelta;
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, carpetTextureId);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(0.5f, 0.5f, 0.0f);
        glRotatef(time * 15.0f, 0.0f, 0.0f, 1.0f);
        const float scale1 = 1.0f + 0.2f * static_cast<float>(std::sin(time * 0.8f));
        glScalef(scale1, scale1, 1.0f);
        glTranslatef(-0.5f + time * 0.05f, -0.5f, 0.0f);

        glMatrixMode(GL_MODELVIEW);
        glColor4f(1.0f, 1.0f, 1.0f, 0.6f);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(2.0f, 0.0f); glVertex2f(1.0f, -1.0f);
        glTexCoord2f(2.0f, 2.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 2.0f); glVertex2f(-1.0f, 1.0f);
        glEnd();

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(0.5f, 0.5f, 0.0f);
        glRotatef(-time * 25.0f, 0.0f, 0.0f, 1.0f);
        const float scale2 = 1.5f + 0.3f * static_cast<float>(std::cos(time * 1.2f));
        glScalef(scale2, scale2, 1.0f);
        glTranslatef(-0.5f - time * 0.08f, -0.5f + time * 0.04f, 0.0f);

        glMatrixMode(GL_MODELVIEW);
        glColor4f(0.8f, 0.5f, 1.0f, 0.5f);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(2.0f, 0.0f); glVertex2f(1.0f, -1.0f);
        glTexCoord2f(2.0f, 2.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 2.0f); glVertex2f(-1.0f, 1.0f);
        glEnd();

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        };

    app.Run();

    if (carpetTextureId != 0) glDeleteTextures(1, &carpetTextureId);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    return 0;
}
