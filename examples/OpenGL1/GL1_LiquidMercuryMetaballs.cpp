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

constexpr int MAX_METABALLS = 6;
constexpr int METABALL_SLICES = 16;

struct Metaball {
    glm::vec3 pos;
    glm::vec3 vel;
    float radius;

    Metaball() noexcept : pos(), vel(), radius(0.0f) {}
};

static std::vector<Metaball> balls(MAX_METABALLS);
static std::vector<float> ballVertices;
static std::vector<float> ballColors;

static void initMetaballs() noexcept
{
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> distPos(-0.8f, 0.8f);
    std::uniform_real_distribution<float> distVel(-1.2f, 1.2f);

    for (auto& ball : balls)
    {
        ball.pos = glm::vec3(distPos(gen), distPos(gen), distPos(gen));
        ball.vel = glm::vec3(distVel(gen), distVel(gen), distVel(gen));
        ball.radius = 0.5f;
    }
}

static void updateMetaballs(float deltaTime) noexcept
{
    constexpr float boxSize = 1.2f;
    for (auto& ball : balls)
    {
        ball.pos += ball.vel * deltaTime;

        if (std::abs(ball.pos.x) > boxSize) { ball.vel.x *= -1.0f; ball.pos.x = std::signbit(ball.pos.x) ? -boxSize : boxSize; }
        if (std::abs(ball.pos.y) > boxSize) { ball.vel.y *= -1.0f; ball.pos.y = std::signbit(ball.pos.y) ? -boxSize : boxSize; }
        if (std::abs(ball.pos.z) > boxSize) { ball.vel.z *= -1.0f; ball.pos.z = std::signbit(ball.pos.z) ? -boxSize : boxSize; }
    }
}

static void buildBallGeometry(const glm::vec3& center, float radius) noexcept
{
    for (int i = 0; i < METABALL_SLICES; ++i)
    {
        const float angle0 = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / METABALL_SLICES;
        const float angle1 = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i + 1) / METABALL_SLICES;

        const float x0 = radius * std::sin(angle0);
        const float y0 = radius * std::cos(angle0);
        const float x1 = radius * std::sin(angle1);
        const float y1 = radius * std::cos(angle1);

        ballVertices.insert(ballVertices.end(), { center.x, center.y, center.z });
        ballColors.insert(ballColors.end(), { 0.8f, 0.85f, 0.9f, 1.0f });

        ballVertices.insert(ballVertices.end(), { center.x + x0, center.y + y0, center.z });
        ballColors.insert(ballColors.end(), { 0.3f, 0.4f, 0.5f, 0.0f });

        ballVertices.insert(ballVertices.end(), { center.x + x1, center.y + y1, center.z });
        ballColors.insert(ballColors.end(), { 0.3f, 0.4f, 0.5f, 0.0f });
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Liquid Mercury Metaballs"))
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

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.65f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    initMetaballs();

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
        updateMetaballs(fixedDelta);

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
        glClearColor(0.04f, 0.04f, 0.06f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        const float radius = 4.0f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            0.5f,
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        ballVertices.clear();
        ballColors.clear();
        for (const auto& ball : balls)
        {
            buildBallGeometry(ball.pos, ball.radius);
        }

        glVertexPointer(3, GL_FLOAT, 0, ballVertices.data());
        glColorPointer(4, GL_FLOAT, 0, ballColors.data());

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(ballVertices.size() / 3));
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);

    return 0;
}
