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

constexpr int MAX_SPARKS = 600;

struct Spark {
    glm::vec3 pos;
    glm::vec3 vel;
    float r, g, b;

    Spark() noexcept : pos(), vel(), r(0.0f), g(0.0f), b(0.0f) {}
};

static std::vector<Spark> sparks(MAX_SPARKS);
static std::vector<float> vectorVertices;
static std::vector<float> vectorColors;

static void initExplosion() noexcept
{
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> distSpeed(-2.5f, 2.5f);
    std::uniform_real_distribution<float> distColor(0.5f, 1.0f);

    for (auto& spark : sparks)
    {
        spark.pos = glm::vec3(0.0f, 0.0f, 0.0f);

        spark.vel = glm::vec3(distSpeed(gen), distSpeed(gen), distSpeed(gen));
        if (glm::length(spark.vel) < 0.2f) {
            spark.vel = glm::vec3(1.0f, 0.0f, 0.0f);
        }

        spark.r = distColor(gen);
        spark.g = distColor(gen) * 0.2f;
        spark.b = distColor(gen);
    }
}

static void updateExplosion(float deltaTime, float totalTime) noexcept
{
    vectorVertices.clear();
    vectorColors.clear();

    vectorVertices.reserve(MAX_SPARKS * 6);
    vectorColors.reserve(MAX_SPARKS * 6);

    for (auto& spark : sparks)
    {
        spark.pos += spark.vel * deltaTime;

        spark.pos.x += std::sin(totalTime * 2.0f + spark.vel.z) * 0.01f;
        spark.pos.y += std::cos(totalTime * 1.5f + spark.vel.x) * 0.01f;

        if (glm::length(spark.pos) > 5.0f)
        {
            spark.pos = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        vectorVertices.insert(vectorVertices.end(), { 0.0f, 0.0f, 0.0f });
        vectorVertices.insert(vectorVertices.end(), { spark.pos.x, spark.pos.y, spark.pos.z });

        vectorColors.insert(vectorColors.end(), { 0.1f, 0.0f, 0.2f });
        vectorColors.insert(vectorColors.end(), { spark.r, spark.g, spark.b });
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Vector XOR Explosion"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(60.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        20.0f
    );

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_DEPTH_TEST);
    glLineWidth(2.0f);

    glEnable(GL_COLOR_LOGIC_OP);
    glLogicOp(GL_XOR);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    initExplosion();

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
            initExplosion();
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = deltaTime;
        if (fixedDelta > 0.1f) fixedDelta = 0.1f;

        time += fixedDelta;
        updateExplosion(fixedDelta, time);

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        const float radius = 4.0f;
        const glm::vec3 cameraPos(
            radius * static_cast<float>(std::sin(cameraAngle)),
            1.5f * static_cast<float>(std::cos(cameraAngle * 0.5f)),
            radius * static_cast<float>(std::cos(cameraAngle))
        );

        glm::mat4 viewMatrix = glm::lookAt(
            cameraPos,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glPushMatrix();
        glRotatef(time * 10.0f, 1.0f, 0.5f, 0.0f);

        glVertexPointer(3, GL_FLOAT, 0, vectorVertices.data());
        glColorPointer(3, GL_FLOAT, 0, vectorColors.data());

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vectorVertices.size() / 3));

        glPopMatrix();
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_COLOR_LOGIC_OP);

    return 0;
}
