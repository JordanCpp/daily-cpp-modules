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

constexpr int   SPHERE_ELEMENTS = 18;
constexpr int   DNA_LINKS_COUNT = 45;
constexpr float DNA_RADIUS = 0.8f;
constexpr float DNA_HEIGHT_STEP = 0.07f;

static GLuint sphereListId = 0;
static GLuint cylinderListId = 0;

static void compileSphereList() noexcept
{
    sphereListId = glGenLists(1);
    glNewList(sphereListId, GL_COMPILE);

    for (int i = 0; i <= SPHERE_ELEMENTS; ++i)
    {
        const float lat0 = std::numbers::pi_v<float> *(-0.5f + static_cast<float>(i - 1) / SPHERE_ELEMENTS);
        const float z0 = std::sin(lat0);
        const float zr0 = std::cos(lat0);

        const float lat1 = std::numbers::pi_v<float> *(-0.5f + static_cast<float>(i) / SPHERE_ELEMENTS);
        const float z1 = std::sin(lat1);
        const float zr1 = std::cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= SPHERE_ELEMENTS; ++j)
        {
            const float lng = 2.0f * std::numbers::pi_v<float> *static_cast<float>(j - 1) / SPHERE_ELEMENTS;
            const float x = std::cos(lng);
            const float y = std::sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);

            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
    glEndList();
}

static void compileCylinderList() noexcept
{
    cylinderListId = glGenLists(1);
    glNewList(cylinderListId, GL_COMPILE);

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= SPHERE_ELEMENTS; ++i)
    {
        const float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / SPHERE_ELEMENTS;
        const float x = std::cos(angle);
        const float y = std::sin(angle);

        glNormal3f(x, y, 0.0f);
        glVertex3f(x, y, -0.5f);
        glVertex3f(x, y, 0.5f);
    }
    glEnd();
    glEndList();
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Kinetic DNA Sculpture"))
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
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    constexpr float specMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);

    compileSphereList();
    compileCylinderList();

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
        glClearColor(0.03f, 0.02f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float radius = 5.0f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            1.0f,
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        constexpr float light0_pos[] = { 3.0f, 5.0f, 2.0f, 1.0f };
        constexpr float light0_diff[] = { 0.3f, 0.2f, 0.8f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

        constexpr float light1_pos[] = { -3.0f, -4.0f, -2.0f, 1.0f };
        constexpr float light1_diff[] = { 0.1f, 0.7f, 0.4f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);

        const float totalHeight = static_cast<float>(DNA_LINKS_COUNT) * DNA_HEIGHT_STEP;
        glTranslatef(0.0f, -totalHeight / 2.0f, 0.0f);

        for (int i = 0; i < DNA_LINKS_COUNT; ++i)
        {
            const float fi = static_cast<float>(i);
            const float angle = fi * 0.2f + time * 1.5f;
            const float currentY = fi * DNA_HEIGHT_STEP;

            const float x1 = DNA_RADIUS * std::sin(angle);
            const float z1 = DNA_RADIUS * std::cos(angle);
            const float x2 = -x1;
            const float z2 = -z1;

            glPushMatrix();
            glTranslatef(0.0f, currentY, 0.0f);
            glRotatef(glm::degrees(angle), 0.0f, 1.0f, 0.0f);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glScalef(0.015f, 0.015f, DNA_RADIUS * 2.0f);
            glColor3f(0.4f, 0.4f, 0.5f);
            glCallList(cylinderListId);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(x1, currentY, z1);
            glScalef(0.08f, 0.08f, 0.08f);
            glColor3f(
                0.5f + 0.5f * std::sin(fi * 0.1f + time),
                0.2f,
                0.8f - 0.3f * std::cos(fi * 0.1f)
            );
            glCallList(sphereListId);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(x2, currentY, z2);
            glScalef(0.08f, 0.08f, 0.08f);
            glColor3f(
                0.1f,
                0.6f + 0.4f * std::cos(fi * 0.1f - time),
                0.6f + 0.4f * std::sin(fi * 0.1f)
            );
            glCallList(sphereListId);
            glPopMatrix();
        }
        };

    app.Run();

    if (sphereListId != 0) glDeleteLists(sphereListId, 1);
    if (cylinderListId != 0) glDeleteLists(cylinderListId, 1);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
