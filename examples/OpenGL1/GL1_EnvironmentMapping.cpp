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

constexpr int CUBE_TEX_RES = 128;
static GLuint cubeTextureId = 0;

static void generateCubeFace(GLenum face, float r_bg, float g_bg, float b_bg, float r_line, float g_line, float b_line) noexcept
{
    std::vector<std::uint8_t> faceData(CUBE_TEX_RES * CUBE_TEX_RES * 3);

    for (int y = 0; y < CUBE_TEX_RES; ++y)
    {
        for (int x = 0; x < CUBE_TEX_RES; ++x)
        {
            bool isGrid = (x % 32 < 2) || (y % 32 < 2) || ((x + y) % 64 == 0);

            const std::size_t idx = (static_cast<std::size_t>(y) * CUBE_TEX_RES + static_cast<std::size_t>(x)) * 3;
            if (isGrid)
            {
                faceData[idx] = static_cast<std::uint8_t>(r_line * 255.0f);
                faceData[idx + 1] = static_cast<std::uint8_t>(g_line * 255.0f);
                faceData[idx + 2] = static_cast<std::uint8_t>(b_line * 255.0f);
            }
            else
            {
                faceData[idx] = static_cast<std::uint8_t>(r_bg * 255.0f);
                faceData[idx + 1] = static_cast<std::uint8_t>(g_bg * 255.0f);
                faceData[idx + 2] = static_cast<std::uint8_t>(b_bg * 255.0f);
            }
        }
    }

    glTexImage2D(face, 0, GL_RGB, CUBE_TEX_RES, CUBE_TEX_RES, 0, GL_RGB, GL_UNSIGNED_BYTE, faceData.data());
}

static void initCubeMap() noexcept
{
    glGenTextures(1, &cubeTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureId);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    generateCubeFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0.02f, 0.0f, 0.05f, 1.0f, 0.0f, 0.5f);
    generateCubeFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0.02f, 0.0f, 0.05f, 0.0f, 0.8f, 1.0f);
    generateCubeFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0.01f, 0.01f, 0.02f, 0.2f, 0.2f, 0.3f);
    generateCubeFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0.04f, 0.04f, 0.06f, 0.5f, 0.5f, 0.5f);
    generateCubeFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0.02f, 0.0f, 0.05f, 0.0f, 1.0f, 0.4f);
    generateCubeFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0.02f, 0.0f, 0.05f, 0.9f, 0.9f, 0.0f);
}

static void drawReflectiveSphere(float radius, int subdivisions) noexcept
{
    for (int i = 0; i <= subdivisions; ++i)
    {
        const float lat0 = std::numbers::pi_v<float> *(-0.5f + static_cast<float>(i - 1) / subdivisions);
        const float z0 = std::sin(lat0);
        const float zr0 = std::cos(lat0);

        const float lat1 = std::numbers::pi_v<float> *(-0.5f + static_cast<float>(i) / subdivisions);
        const float z1 = std::sin(lat1);
        const float zr1 = std::cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= subdivisions; ++j)
        {
            const float lng = 2.0f * std::numbers::pi_v<float> *static_cast<float>(j) / subdivisions;
            const float x = std::cos(lng);
            const float y = std::sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0 * radius, y * zr0 * radius, z0 * radius);

            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1 * radius, y * zr1 * radius, z1 * radius);
        }
        glEnd();
    }
}

static void drawOuterSkybox(float size) noexcept
{
    const float h = size * 0.5f;
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);   glVertex3f(-h, -h, -h); glVertex3f(h, -h, -h); glVertex3f(h, h, -h); glVertex3f(-h, h, -h);
    glNormal3f(0.0f, 0.0f, -1.0f);  glVertex3f(h, -h, h); glVertex3f(-h, -h, h); glVertex3f(-h, h, h); glVertex3f(h, h, h);
    glNormal3f(1.0f, 0.0f, 0.0f);   glVertex3f(-h, -h, h); glVertex3f(-h, -h, -h); glVertex3f(-h, h, -h); glVertex3f(-h, h, h);
    glNormal3f(-1.0f, 0.0f, 0.0f);  glVertex3f(h, -h, -h); glVertex3f(h, -h, h); glVertex3f(h, h, h); glVertex3f(h, h, -h);
    glEnd();
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.3 - Chrome Sphere Environment Mapping"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(55.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        20.0f
    );

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);

    initCubeMap();

    float time = 0.0f;
    float cameraAngle = 0.0f;
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
            cameraAngle += fixedDelta * 0.25f;
            if (cameraAngle > 2.0f * std::numbers::pi_v<float>)
            {
                cameraAngle -= 2.0f * std::numbers::pi_v<float>;
            }
        }
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.02f, 0.01f, 0.04f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float radius = 3.5f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            0.8f,
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glDisable(GL_TEXTURE_GEN_S); glDisable(GL_TEXTURE_GEN_T); glDisable(GL_TEXTURE_GEN_R);
        glDisable(GL_TEXTURE_CUBE_MAP);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1.0f);
        glColor3f(0.15f, 0.1f, 0.3f);
        drawOuterSkybox(7.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glEnable(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureId);

        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glEnable(GL_TEXTURE_GEN_R);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
        glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

        glPushMatrix();
        glTranslatef(0.0f, 0.2f * std::sin(time * 1.5f), 0.0f);
        glRotatef(time * 15.0f, 0.2f, 1.0f, 0.0f);

        glColor3f(1.0f, 1.0f, 1.0f);
        drawReflectiveSphere(0.8f, 32);
        glPopMatrix();

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_GEN_R);
        glDisable(GL_TEXTURE_CUBE_MAP);
        };

    app.Run();

    if (cubeTextureId != 0) glDeleteTextures(1, &cubeTextureId);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
