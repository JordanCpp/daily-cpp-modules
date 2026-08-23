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

static float animationTime = 0.0f;
static GLuint fogTextureName = 0;

static void setMatrix(GLenum matrixMode, const glm::mat4& matrix) noexcept
{
    glMatrixMode(matrixMode);
    glLoadMatrixf(glm::value_ptr(matrix));
}

static void createFogTexture() noexcept
{
    constexpr std::size_t texSize = 64;
    unsigned char textureData[texSize * 4ULL];

    for (std::size_t i = 0; i < texSize; ++i)
    {
        const float factor = static_cast<float>(i) / static_cast<float>(texSize - 1ULL);
        const float alpha = 1.0f - (factor * factor);
        const auto byteValue = static_cast<unsigned char>(alpha * 255.0f);
        const std::size_t index = i * 4ULL;
        textureData[index] = 200;
        textureData[index + 1] = 210;
        textureData[index + 2] = 220;
        textureData[index + 3] = byteValue;
    }

    glGenTextures(1, &fogTextureName);
    glBindTexture(GL_TEXTURE_1D, fogTextureName);

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, static_cast<GLsizei>(texSize), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
}

static void drawTerrain() noexcept
{
    constexpr std::size_t segments = 40;
    constexpr float size = 4.0f;
    constexpr float halfSize = size / 2.0f;
    constexpr float step = size / static_cast<float>(segments);

    glColor3f(0.2f, 0.4f, 0.15f);

    for (std::size_t i = 0; i < segments; ++i)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (std::size_t j = 0; j <= segments; ++j)
        {
            const float x1 = -halfSize + static_cast<float>(i) * step;
            const float z = -halfSize + static_cast<float>(j) * step;
            const float y1 = 0.15f * static_cast<float>(std::sin(x1 * 3.0f)) * static_cast<float>(std::cos(z * 3.0f));
            glVertex3f(x1, y1, z);

            const float x2 = -halfSize + static_cast<float>(i + 1ULL) * step;
            const float y2 = 0.15f * static_cast<float>(std::sin(x2 * 3.0f)) * static_cast<float>(std::cos(z * 3.0f));

            glVertex3f(x2, y2, z);
        }
        glEnd();
    }
}

static void drawPillars() noexcept
{
    const float posX[] = { -1.0f,  1.0f, -1.0f, 1.0f };
    const float posZ[] = { -1.0f, -1.0f,  1.0f, 1.0f };

    for (std::size_t i = 0; i < 4ULL; ++i)
    {
        glPushMatrix();
        glTranslatef(posX[i], 0.0f, posZ[i]);
        glBegin(GL_QUADS);
        glColor3f(0.4f, 0.4f, 0.4f);

        glVertex3f(-0.1f, 1.2f, 0.1f);
        glVertex3f(0.1f, 1.2f, 0.1f);
        glVertex3f(0.1f, 0.0f, 0.1f);
        glVertex3f(-0.1f, 0.0f, 0.1f);

        glVertex3f(-0.1f, 1.2f, -0.1f);
        glVertex3f(0.1f, 1.2f, -0.1f);
        glVertex3f(0.1f, 0.0f, -0.1f);
        glVertex3f(-0.1f, 0.0f, -0.1f);

        glVertex3f(-0.1f, 1.2f, -0.1f);
        glVertex3f(-0.1f, 1.2f, 0.1f);
        glVertex3f(-0.1f, 0.0f, 0.1f);
        glVertex3f(-0.1f, 0.0f, -0.1f);

        glVertex3f(0.1f, 1.2f, -0.1f);
        glVertex3f(0.1f, 1.2f, 0.1f);
        glVertex3f(0.1f, 0.0f, 0.1f);
        glVertex3f(0.1f, 0.0f, -0.1f);
        glEnd();

        glPopMatrix();
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Volumetric Height Fog via TexGen"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(55.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        20.0f
    );

    setMatrix(GL_PROJECTION, projectionMatrix);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    createFogTexture();

    app.OnUpdate = [&](float deltaTime) noexcept {
        animationTime += deltaTime * 0.5f;
        if (animationTime > 2.0f * std::numbers::pi_v<float>)
        {
            animationTime -= 2.0f * std::numbers::pi_v<float>;
        }
        };

    app.OnRender = [&]() noexcept {
        const float radius = 3.5f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(animationTime)),
            1.8f,
            radius * static_cast<float>(std::cos(animationTime))
        );
        const glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.4f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        setMatrix(GL_MODELVIEW, viewMatrix);

        drawTerrain();
        drawPillars();

        glEnable(GL_TEXTURE_1D);
        glBindTexture(GL_TEXTURE_1D, fogTextureName);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_TEXTURE_GEN_S);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

        const float fogHeightScale = 1.0f / 0.6f;
        const float sParams[4] = { 0.0f, fogHeightScale, 0.0f, 0.0f };
        glTexGenfv(GL_S, GL_OBJECT_PLANE, sParams);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        drawTerrain();
        drawPillars();

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_1D);
        };

    app.Run();

    glDeleteTextures(1, &fogTextureName);

    return 0;
}
