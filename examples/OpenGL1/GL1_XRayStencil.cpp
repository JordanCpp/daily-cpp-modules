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

static void drawWireframeInside(float size) noexcept
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);

    for (float scale = 1.0f; scale > 0.2f; scale -= 0.25f)
    {
        glPushMatrix();
        glScalef(scale, scale, scale);
        drawSolidCube(size);
        glPopMatrix();
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void drawScannerDisk(float radius, int segments) noexcept
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i)
    {
        const float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / segments;
        glVertex3f(radius * std::cos(angle), radius * std::sin(angle), 0.0f);
    }
    glEnd();
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - X-Ray Stencil Scanner"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(50.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        20.0f
    );

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    constexpr float lightPos[] = { 3.0f, 4.0f, 5.0f, 1.0f };
    constexpr float lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    constexpr float lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

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
            cameraAngle += fixedDelta * 0.3f;
            if (cameraAngle > 2.0f * std::numbers::pi_v<float>)
            {
                cameraAngle -= 2.0f * std::numbers::pi_v<float>;
            }
        }
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.05f, 0.05f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        const float radius = 4.0f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            1.8f,
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glPushMatrix();
        glRotatef(time * 20.0f, 0.5f, 1.0f, 0.0f);

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glDisable(GL_LIGHTING);

        glPushMatrix();
        const float scannerY = 1.2f * static_cast<float>(std::sin(time * 1.5f));
        glTranslatef(0.0f, scannerY, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        drawScannerDisk(1.5f, 32);
        glPopMatrix();

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);

        glStencilFunc(GL_EQUAL, 0, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        glEnable(GL_LIGHTING);
        glColor3f(0.4f, 0.45f, 0.5f);
        drawSolidCube(1.2f);

        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glDisable(GL_LIGHTING);

        glColor3f(0.0f, 1.0f, 0.4f);
        drawWireframeInside(1.15f);

        glPushMatrix();
        const float edgeY = 1.2f * static_cast<float>(std::sin(time * 1.5f));
        glTranslatef(0.0f, edgeY, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(3.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        drawScannerDisk(1.21f, 32);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();

        glPopMatrix();
        glDisable(GL_STENCIL_TEST);
        };

    app.Run();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
