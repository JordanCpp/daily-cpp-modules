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

constexpr int MAX_STARS = 3000;

struct Star {
    float x, y, z;
    float prevZ;
    float speed;
    float r, g, b;

    Star() noexcept : x(0.0f), y(0.0f), z(0.0f), prevZ(0.0f), speed(0.0f), r(0.0f), g(0.0f), b(0.0f) {}
};

static std::vector<Star> stars(MAX_STARS);
static std::vector<float> starVertices;
static std::vector<float> starColors;

static void initStars() noexcept {
    std::mt19937 gen(1337);
    std::uniform_real_distribution<float> distCoord(-4.0f, 4.0f);
    std::uniform_real_distribution<float> distZ(-15.0f, 0.0f);
    std::uniform_real_distribution<float> distSpeed(4.0f, 8.0f);
    std::uniform_real_distribution<float> distColor(0.6f, 1.0f);

    for (auto& star : stars) {
        star.x = distCoord(gen);
        star.y = distCoord(gen);
        star.z = distZ(gen);
        star.prevZ = star.z;
        star.speed = distSpeed(gen);
        star.r = distColor(gen) * 0.2f;
        star.g = distColor(gen) * 0.6f;
        star.b = 1.0f;
    }
}

static void updateStars(float deltaTime, bool warp) noexcept {
    starVertices.clear();
    starColors.clear();

    starVertices.reserve(MAX_STARS * 6);
    starColors.reserve(MAX_STARS * 6);

    for (auto& star : stars) {
        star.prevZ = star.z;
        star.z += star.speed * deltaTime * (warp ? 6.0f : 1.0f);

        if (star.z > 4.0f) {
            star.z = -15.0f;
            star.prevZ = -15.0f;
        }

        if (warp) {
            starVertices.insert(starVertices.end(), { star.x, star.y, star.prevZ, star.x, star.y, star.z });
            starColors.insert(starColors.end(), { 0.0f, 0.0f, 0.2f, star.r, star.g, star.b });
        }
        else {
            starVertices.insert(starVertices.end(), { star.x, star.y, star.z - 0.1f, star.x, star.y, star.z });
            starColors.insert(starColors.end(), { star.r, star.g, star.b, star.r, star.g, star.b });
        }
    }
}

int main() {
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Hyperdrive Starfield (Space to Warp)")) return -1;

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(65.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        20.0f
    );
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));

    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_DEPTH_TEST);
    glLineWidth(2.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    initStars();
    bool warpMode = false;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.IsKeyPressed(Key::Space)) {
            warpMode = !warpMode;
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = deltaTime;
        if (fixedDelta > 0.1f) fixedDelta = 0.1f;

        updateStars(fixedDelta, warpMode);
        };

    app.OnRender = [&]() noexcept {
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 viewMatrix = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glLoadMatrixf(glm::value_ptr(viewMatrix));

        glVertexPointer(3, GL_FLOAT, 0, starVertices.data());
        glColorPointer(3, GL_FLOAT, 0, starColors.data());

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(starVertices.size() / 3));
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_BLEND);

    return 0;
}
