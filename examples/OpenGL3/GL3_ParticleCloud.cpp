// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import AppGL3;
import WinLite;
import OpenGL;
import GlmLite;

using namespace WinLite;

constexpr int PARTICLE_COUNT = 8000;

struct Particle
{
    float x, y, z;
    float r, g, b;
};

static std::vector<Particle> particles(PARTICLE_COUNT);

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 particleColor;

    uniform mat4 view;
    uniform mat4 projection;
    uniform float time;

    void main() {
        float angle = time * (1.5 / (length(aPos.xz) + 0.2));
        mat2 rot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
        
        vec3 pos = aPos;
        pos.xz = rot * pos.xz;
        pos.y += sin(time + length(aPos.xz) * 4.0) * 0.08;

        gl_Position = projection * view * vec4(pos, 1.0);
        
        float dist = length(pos);
        particleColor = aColor * (1.2 / (dist + 0.4));
        
        gl_PointSize = clamp(4.0 / dist, 1.0, 6.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 particleColor;

    void main() {
        FragColor = vec4(particleColor, 1.0);
    }
)";

static unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

static void initParticleCloud() noexcept
{
    std::mt19937 gen(2026);
    std::uniform_real_distribution<float> distRadius(0.1f, 2.5f);
    std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * std::numbers::pi_v<float>);
    std::uniform_real_distribution<float> distY(-0.15f, 0.15f);

    for (auto& p : particles)
    {
        float r = distRadius(gen);
        float angle = distAngle(gen);

        p.x = r * std::cos(angle);
        p.z = r * std::sin(angle);
        p.y = distY(gen) * (2.5f - r);

        p.r = 0.4f + 0.6f * (r / 2.5f);
        p.g = 0.2f + 0.5f * std::sin(angle);
        p.b = 1.0f - 0.4f * (r / 2.5f);
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL3 app;
    if (!app.Init(width, height, "OpenGL 3.3 Core - Cosmic Particle Galaxy"))
    {
        return -1;
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    initParticleCloud();

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(particles.size() * sizeof(Particle)), particles.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    int timeLoc = glGetUniformLocation(shaderProgram, "time");

    const glm::mat4 projection = glm::perspective(glm::radians(55.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 20.0f);

    float time = 0.0f;
    float cameraAngle = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};
    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = std::min(deltaTime, 0.1f);
        time += fixedDelta;
        cameraAngle += fixedDelta * 0.1f;
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.01f, 0.01f, 0.02f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        float camX = 4.0f * std::sin(cameraAngle);
        float camZ = 4.0f * std::cos(cameraAngle);
        glm::mat4 view = glm::lookAt(glm::vec3(camX, 2.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(timeLoc, time);

        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(PARTICLE_COUNT));
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &VBO);

    return 0;
}
