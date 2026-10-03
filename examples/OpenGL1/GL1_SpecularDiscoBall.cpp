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

static std::vector<float> sphereVertices;
static std::vector<float> sphereNormals;
static std::vector<float> sphereColors;

static void generateDiscoBall(int stacks, int slices) noexcept
{
    sphereVertices.clear();
    sphereNormals.clear();
    sphereColors.clear();

    for (int i = 0; i < stacks; ++i) {
        float lat0 = std::numbers::pi_v<float> *(-0.5f + static_cast<float>(i) / stacks);
        float z0 = std::sin(lat0);
        float zr0 = std::cos(lat0);

        float lat1 = std::numbers::pi_v<float> *(-0.5f + static_cast<float>(i + 1) / stacks);
        float z1 = std::sin(lat1);
        float zr1 = std::cos(lat1);

        for (int j = 0; j <= slices; ++j) {
            float lng = 2.0f * std::numbers::pi_v<float> *static_cast<float>(j) / slices;
            float x = std::cos(lng);
            float y = std::sin(lng);

            float mirrorShade = 0.7f + 0.3f * static_cast<float>(j % 2);

            sphereNormals.insert(sphereNormals.end(), { x * zr0, y * zr0, z0 });
            sphereVertices.insert(sphereVertices.end(), { x * zr0, y * zr0, z0 });
            sphereColors.insert(sphereColors.end(), { mirrorShade, mirrorShade, mirrorShade });

            sphereNormals.insert(sphereNormals.end(), { x * zr1, y * zr1, z1 });
            sphereVertices.insert(sphereVertices.end(), { x * zr1, y * zr1, z1 });
            sphereColors.insert(sphereColors.end(), { mirrorShade, mirrorShade, mirrorShade });
        }
    }
}

int main() {
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Specular Disco Ball & Dynamic Lights")) return -1;

    const glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 10.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    float specMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    generateDiscoBall(30, 30);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, sphereVertices.data());
    glNormalPointer(GL_FLOAT, 0, sphereNormals.data());
    glColorPointer(3, GL_FLOAT, 0, sphereColors.data());

    float time = 0.0f;

    app.OnUpdate = [&](float deltaTime) noexcept {
        time += std::min(deltaTime, 0.1f);
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        float light0_pos[] = { 2.0f * std::sin(time), 1.0f, 2.0f * std::cos(time), 1.0f };
        float light0_color[] = { 1.0f, 0.1f, 0.1f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0_color);

        float light1_pos[] = { -2.0f * std::cos(time * 1.3f), -1.0f, 2.0f * std::sin(time * 1.3f), 1.0f };
        float light1_color[] = { 0.1f, 0.4f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_color);

        glm::mat4 modelMatrix = glm::rotate(viewMatrix, time * 0.5f, glm::vec3(0.0f, 1.0f, 0.2f));
        glLoadMatrixf(glm::value_ptr(modelMatrix));

        glDrawArrays(GL_QUAD_STRIP, 0, static_cast<GLsizei>(sphereVertices.size() / 3));
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    return 0;
}
