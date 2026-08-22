// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <print>
#include <string>
#include <cmath>
#include <chrono>

import GlmLite;
import WinLite;
import OpenGL;
import FpsCounter;

using namespace WinLite;

const float cubeVertices[] = {
    -1.0f, -1.0f,  1.0f,  // 0
     1.0f, -1.0f,  1.0f,  // 1
     1.0f,  1.0f,  1.0f,  // 2
    -1.0f,  1.0f,  1.0f,  // 3
    -1.0f, -1.0f, -1.0f,  // 4
     1.0f, -1.0f, -1.0f,  // 5
     1.0f,  1.0f, -1.0f,  // 6
    -1.0f,  1.0f, -1.0f   // 7
};

const float cubeNormals[] =
{
    0.0f, 0.0f,  1.0f,
    0.0f, 0.0f,  1.0f,
    0.0f, 0.0f,  1.0f,
    0.0f, 0.0f,  1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    1.0f, 0.0f,  0.0f,
    1.0f, 0.0f,  0.0f,
    1.0f, 0.0f,  0.0f,
    1.0f, 0.0f,  0.0f,

    -1.0f, 0.0f,  0.0f,
    -1.0f, 0.0f,  0.0f,
    -1.0f, 0.0f,  0.0f,
    -1.0f, 0.0f,  0.0f,

    0.0f,  1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f
};

const float cubeColors[] = 
{

    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.5f, 0.0f,
    0.5f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.5f, 0.0f,
    0.5f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.5f, 0.0f,
    0.5f, 0.0f, 1.0f
};

const GLubyte indices[] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    1, 5, 6, 2,
    0, 4, 7, 3,
    3, 2, 6, 7,
    0, 1, 5, 4
};

void setMatrix(GLenum matrixMode, const glm::mat4& matrix);

void setMatrix(GLenum matrixMode, const glm::mat4& matrix)
{
    glMatrixMode(matrixMode);
    glLoadMatrixf(glm::value_ptr(matrix));
}

int main()
{
    constexpr std::size_t width  = 800;
    constexpr std::size_t height = 600;

    auto windowResult = OpenGL1Window::Create(width, height,
        "OpenGL 1.2 + GLM - Rotating Color Cube");

    if (!windowResult)
    {
        std::println("Error: {}", windowResult.error());
        return -1;
    }

    OpenGL1Window window = std::move(*windowResult);
    OpenGLLoader loader(1, 2);

    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

    glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(45.0f),                    // FOV
        static_cast<float>(width) / height,     // Aspect ratio
        0.1f,                                   // Near plane
        100.0f                                  // Far plane
    );

    setMatrix(GL_PROJECTION, projectionMatrix);

    glMatrixMode(GL_MODELVIEW);

    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(3.0f, 2.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glLoadMatrixf(glm::value_ptr(viewMatrix));

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
    glNormalPointer(GL_FLOAT, 0, cubeNormals);
    glColorPointer(3, GL_FLOAT, 0, cubeColors);

    FpsCounter counter;
    float angle = 0.0f;

    auto lastTime = std::chrono::steady_clock::now();

    float rotationSpeed = 180.0f;
    const float minSpeed = 30.0f;
    const float maxSpeed = 720.0f;

    while (window.IsRunning())
    {
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        if (deltaTime > 0.1f) deltaTime = 0.1f;

        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }

            if (event.IsKeyPressed(Key::Up))
            {
                rotationSpeed = std::min(rotationSpeed + 30.0f, maxSpeed);
            }
            if (event.IsKeyPressed(Key::Down))
            {
                rotationSpeed = std::max(rotationSpeed - 30.0f, minSpeed);
            }

            if (event.IsKeyPressed(Key::Space))
            {
                rotationSpeed = 180.0f;
            }
        }

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        angle += rotationSpeed * deltaTime;
        if (angle > 360.0f) angle -= 360.0f;
        if (angle < 0.0f) angle += 360.0f;

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle),
            glm::vec3(1.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle * 0.5f),
            glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;

        glLoadMatrixf(glm::value_ptr(modelViewMatrix));

        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

        window.Present();

        if (counter.Update())
        {
            window.SetTitle(
                std::to_string(counter.GetFps()) + " FPS | " +
                "Speed: " + std::to_string(static_cast<int>(rotationSpeed)) + " deg/s | " +
                "[Up/Down] Speed | [Space] Reset"
            );
        }
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    return 0;
}