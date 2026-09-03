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

static float animationTime = 0.0f;
static float pulsarRotation = 0.0f;
static GLuint pulsarTexture = 0;

struct Star {
    float x, y, z;
    float size;
    float phase;
};
static std::vector<Star> stars;

static void setMatrix(GLenum matrixMode, const glm::mat4& matrix) noexcept
{
    glMatrixMode(matrixMode);
    glLoadMatrixf(glm::value_ptr(matrix));
}

static void createPulsarTexture() noexcept
{
    constexpr std::size_t size = 128;
    std::vector<unsigned char> data(size * size * 4);

    for (std::size_t y = 0; y < size; ++y)
    {
        for (std::size_t x = 0; x < size; ++x)
        {
            float fx = static_cast<float>(x) / static_cast<float>(size) - 0.5f;
            float fy = static_cast<float>(y) / static_cast<float>(size) - 0.5f;
            float dist = std::sqrt(fx * fx + fy * fy) * 2.0f;
            float noise = std::sin(dist * 20.0f - animationTime * 2.0f) * 0.5f + 0.5f;

            std::size_t idx = (y * size + x) * 4;
            data[idx] = static_cast<unsigned char>(140.0f + noise * 115.0f);
            data[idx + 1] = static_cast<unsigned char>(180.0f + noise * 75.0f);
            data[idx + 2] = 255;
            data[idx + 3] = 255;
        }
    }

    glGenTextures(1, &pulsarTexture);
    glBindTexture(GL_TEXTURE_2D, pulsarTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
}

static void initSpace() noexcept
{
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> distPos(-40.0f, 40.0f);
    std::uniform_real_distribution<float> distSize(1.0f, 3.0f);
    std::uniform_real_distribution<float> distPhase(0.0f, 2.0f * std::numbers::pi_v<float>);

    stars.resize(300);
    for (auto& star : stars)
    {
        star.x = distPos(gen);
        star.y = distPos(gen);
        star.z = distPos(gen);

        if (std::sqrt(star.x * star.x + star.y * star.y + star.z * star.z) < 10.0f)
        {
            star.x *= 3.0f;
            star.y *= 3.0f;
            star.z *= 3.0f;
        }
        star.size = distSize(gen);
        star.phase = distPhase(gen);
    }
}

static void drawSpaceBackground() noexcept
{
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (const auto& star : stars)
    {
        float brightness = 0.4f + 0.6f * std::sin(animationTime * 3.0f + star.phase);
        glPointSize(star.size);
        glBegin(GL_POINTS);
        glColor4f(0.8f, 0.9f, 1.0f, brightness);
        glVertex3f(star.x, star.y, star.z);
        glEnd();
    }

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

static void drawNebula() noexcept
{
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    constexpr std::size_t segments = 16;
    float rOuter = 15.0f;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.1f, 0.05f, 0.2f, 0.3f);
    glVertex3f(0.0f, 0.0f, -8.0f);

    for (std::size_t i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / static_cast<float>(segments);
        float shift = 1.5f * std::sin(animationTime * 0.5f + angle);

        float rCol = 0.05f + 0.05f * std::sin(animationTime + angle);
        float gCol = 0.02f + 0.02f * std::cos(animationTime * 0.7f);
        float bCol = 0.15f + 0.05f * std::sin(animationTime * 0.4f);

        glColor4f(rCol, gCol, bCol, 0.0f);
        glVertex3f(std::cos(angle) * (rOuter + shift), std::sin(angle) * (rOuter + shift), -8.0f);
    }
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

static void drawSphere(float radius, std::size_t rings, std::size_t sectors) noexcept
{
    const float R = 1.0f / static_cast<float>(rings - 1);
    const float S = 1.0f / static_cast<float>(sectors - 1);

    glBegin(GL_TRIANGLES);
    for (std::size_t r = 0; r < rings - 1; ++r)
    {
        for (std::size_t s = 0; s < sectors - 1; ++s)
        {
            auto getVertex = [&](std::size_t ring, std::size_t sector) {
                float rFloat = static_cast<float>(ring);
                float sFloat = static_cast<float>(sector);

                float x = std::cos(2.0f * std::numbers::pi_v<float> *sFloat * S) * std::sin(std::numbers::pi_v<float> *rFloat * R);
                float y = std::sin(-std::numbers::pi_v<float> / 2.0f + std::numbers::pi_v<float> *rFloat * R);
                float z = std::sin(2.0f * std::numbers::pi_v<float> *sFloat * S) * std::sin(std::numbers::pi_v<float> *rFloat * R);

                glNormal3f(x, y, z);
                glTexCoord2f(sFloat * S, rFloat * R);
                glVertex3f(x * radius, y * radius, z * radius);
                };

            getVertex(r, s);     getVertex(r + 1, s);     getVertex(r, s + 1);
            getVertex(r + 1, s); getVertex(r + 1, s + 1); getVertex(r, s + 1);
        }
    }
    glEnd();
}

static void drawCorona(float radius) noexcept
{
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    constexpr std::size_t segments = 32;
    float outerRadius = radius * (1.5f + 0.2f * std::sin(animationTime * 6.0f));

    float rMod = 0.5f + 0.3f * std::sin(animationTime * 2.0f);
    float gMod = 0.7f + 0.2f * std::cos(animationTime * 3.5f);

    glBegin(GL_TRIANGLE_STRIP);
    for (std::size_t i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / static_cast<float>(segments);
        float c = std::cos(angle);
        float s = std::sin(angle);

        glColor4f(rMod, gMod, 1.0f, 0.8f);
        glVertex3f(c * radius, s * radius, 0.0f);

        glColor4f(0.1f * rMod, 0.2f, 0.8f, 0.0f);
        glVertex3f(c * outerRadius, s * outerRadius, 0.0f);
    }
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

static void drawJets(float length, float width) noexcept
{
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    constexpr std::size_t segments = 16;
    float cycle = std::sin(animationTime * 15.0f);

    float jetR = 0.6f + 0.4f * std::sin(animationTime * 4.0f);
    float jetG = 0.8f + 0.2f * std::cos(animationTime * 2.0f);

    for (float sign : {-1.0f, 1.0f})
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
        glVertex3f(0.0f, 0.0f, 0.0f);

        for (std::size_t i = 0; i <= segments; ++i)
        {
            float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / static_cast<float>(segments);
            float wMod = width * (1.0f + 0.15f * cycle);
            float c = std::cos(angle) * wMod;
            float s = std::sin(angle) * wMod;

            glColor4f(jetR, jetG, 1.0f, 0.0f);
            glVertex3f(c, sign * length, s);
        }
        glEnd();
    }

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

static void drawAccretionDisk(float innerRadius, float outerRadius) noexcept
{
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    constexpr std::size_t segments = 48;

    glBegin(GL_TRIANGLE_STRIP);
    for (std::size_t i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * std::numbers::pi_v<float> *static_cast<float>(i) / static_cast<float>(segments);
        float nextAngle = angle + animationTime * 0.5f;

        float wave = 0.05f * std::sin(angle * 4.0f + animationTime * 10.0f);
        float c = std::cos(nextAngle);
        float s = std::sin(nextAngle);

        float rCol = 0.7f + 0.3f * std::sin(animationTime + angle);
        float gCol = 0.4f + 0.4f * std::cos(animationTime * 1.5f);

        glColor4f(rCol, gCol, 1.0f, 0.7f);
        glVertex3f(c * innerRadius, wave, s * innerRadius);

        glColor4f(0.2f, 0.1f, 0.6f, 0.0f);
        glVertex3f(c * outerRadius, wave, s * outerRadius);
    }
    glEnd();

    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL1 app;
    if (!app.Init(width, height, "OpenGL 1.2 - Cosmic Pulsar Overdrive"))
    {
        return -1;
    }

    const glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        100.0f
    );

    setMatrix(GL_PROJECTION, projectionMatrix);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    createPulsarTexture();
    initSpace();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    std::array<float, 4> lightPos = { 0.0f, 0.0f, 5.0f, 1.0f };
    std::array<float, 4> ambientLight = { 0.2f, 0.3f, 0.5f, 1.0f };
    std::array<float, 4> diffuseLight = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos.data());
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight.data());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight.data());

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    app.OnUpdate = [&](float deltaTime) noexcept {
        animationTime += deltaTime;
        pulsarRotation += deltaTime * 240.0f;
        if (pulsarRotation > 360.0f)
        {
            pulsarRotation -= 360.0f;
        }
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.005f, 0.005f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const glm::mat4 viewMatrix = glm::lookAt(
            glm::vec3(0.0f, 2.5f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));setMatrix(GL_MODELVIEW, viewMatrix);glDepthMask(GL_FALSE);drawSpaceBackground();drawNebula();glDepthMask(GL_TRUE);float pulseScale = 0.8f + 0.2f * std::sin(animationTime * 12.0f);glDepthMask(GL_FALSE);glPushMatrix();drawCorona(pulseScale * 1.15f);glPopMatrix();glDepthMask(GL_TRUE);glPushMatrix();glRotatef(30.0f, 0.0f, 0.0f, 1.0f);glRotatef(pulsarRotation, 0.0f, 1.0f, 0.0f);glEnable(GL_TEXTURE_2D);glBindTexture(GL_TEXTURE_2D, pulsarTexture);glColor3f(1.0f, 1.0f, 1.0f);drawSphere(pulseScale, 32, 32);glDisable(GL_TEXTURE_2D);drawJets(4.5f, 0.5f);glPopMatrix();glPushMatrix();glRotatef(30.0f, 0.0f, 0.0f, 1.0f);glRotatef(animationTime * 20.0f, 0.0f, 1.0f, 0.0f);drawAccretionDisk(1.3f, 3.5f);glPopMatrix();};app.Run();glDeleteTextures(1, &pulsarTexture);return 0;
}