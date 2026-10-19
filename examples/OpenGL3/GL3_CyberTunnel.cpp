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

struct Vertex
{
    float x, y, z;
    float r, g, b;
};

constexpr int TUNNEL_SEGMENTS = 40;
constexpr int TUNNEL_SLICES = 20;
constexpr float TUNNEL_RADIUS = 1.0f;
constexpr float SEGMENT_LENGTH = 0.5f;

static std::vector<Vertex> tunnelVertices;
static std::vector<unsigned int> tunnelIndices;

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 ourColor;
    out float fogFactor;

    uniform mat4 view;
    uniform mat4 projection;
    uniform float time;

    void main() {
        vec3 pos = aPos;
        pos.x += sin(pos.z * 0.3 + time * 2.0) * 0.4;
        pos.y += cos(pos.z * 0.2 + time * 1.5) * 0.3;

        gl_Position = projection * view * vec4(pos, 1.0);
        ourColor = aColor;

        float distance = length(view * vec4(pos, 1.0));
        fogFactor = exp(-0.07 * distance);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 ourColor;
    in float fogFactor;

    void main() {
        vec3 fogColor = vec3(0.02, 0.0, 0.05);
        vec3 finalColor = mix(fogColor, ourColor, clamp(fogFactor, 0.0, 1.0));
        FragColor = vec4(finalColor, 1.0);
    }
)";

static unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

static void generateTunnelGeometry() noexcept
{
    tunnelVertices.clear();
    tunnelIndices.clear();

    for (unsigned int i = 0; i < static_cast<unsigned int>(TUNNEL_SEGMENTS); ++i)
    {
        float z = -static_cast<float>(i) * SEGMENT_LENGTH;
        for (unsigned int j = 0; j < static_cast<unsigned int>(TUNNEL_SLICES); ++j)
        {
            float angle = (static_cast<float>(j) / static_cast<float>(TUNNEL_SLICES)) * 2.0f * std::numbers::pi_v<float>;
            float x = TUNNEL_RADIUS * std::cos(angle);
            float y = TUNNEL_RADIUS * std::sin(angle);

            float r = 0.1f + 0.9f * std::abs(std::sin(z * 0.1f));
            float g = 0.0f;
            float b = 0.5f + 0.5f * std::abs(std::cos(angle));

            if (j % 4u == 0u)
            {
                r = 0.0f; g = 1.0f; b = 0.8f;
            }

            tunnelVertices.push_back({ x, y, z, r, g, b });
        }
    }

    for (unsigned int i = 0; i < static_cast<unsigned int>(TUNNEL_SEGMENTS - 1); ++i)
    {
        for (unsigned int j = 0; j < static_cast<unsigned int>(TUNNEL_SLICES); ++j)
        {
            unsigned int next_j = (j + 1u) % static_cast<unsigned int>(TUNNEL_SLICES);

            unsigned int i0 = i * static_cast<unsigned int>(TUNNEL_SLICES) + j;
            unsigned int i1 = i * static_cast<unsigned int>(TUNNEL_SLICES) + next_j;
            unsigned int i2 = (i + 1u) * static_cast<unsigned int>(TUNNEL_SLICES) + j;
            unsigned int i3 = (i + 1u) * static_cast<unsigned int>(TUNNEL_SLICES) + next_j;

            tunnelIndices.push_back(i0); tunnelIndices.push_back(i1); tunnelIndices.push_back(i2);
            tunnelIndices.push_back(i1); tunnelIndices.push_back(i3); tunnelIndices.push_back(i2);
        }
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL3 app;
    if (!app.Init(width, height, "OpenGL 3.3 Core - Cyberpunk Shader Tunnel"))
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

    generateTunnelGeometry();

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(tunnelVertices.size() * sizeof(Vertex)), tunnelVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(tunnelIndices.size() * sizeof(unsigned int)), tunnelIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    int timeLoc = glGetUniformLocation(shaderProgram, "time");

    const glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 30.0f);

    float time = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};
    app.OnUpdate = [&](float deltaTime) noexcept {
        time += std::min(deltaTime, 0.1f);
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.02f, 0.0f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        float tunnelOffset = time * 3.0f;
        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, -tunnelOffset),
            glm::vec3(0.0f, 0.0f, -tunnelOffset - 1.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(timeLoc, time);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(tunnelIndices.size()), GL_UNSIGNED_INT, nullptr);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
