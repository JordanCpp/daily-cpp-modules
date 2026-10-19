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

constexpr int RADAR_GRID_SIZE = 80;
constexpr float RADAR_SPACING = 0.06f;

struct Vertex
{
    float x, y, z;
};

static std::vector<Vertex> gridVertices;
static std::vector<unsigned int> gridIndices;

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    out vec3 localPos;
    out float waveIntensity;
    out float distanceEdge;

    uniform mat4 view;
    uniform mat4 projection;
    uniform float time;

    void main() {
        vec3 pos = aPos;
        float distToCenter = length(pos.xz);

        pos.y = 0.15 * (
            sin(pos.x * 4.0) * cos(pos.z * 3.5) +
            sin(pos.z * 5.0 + time * 0.5) * 0.2
        );

        float waveSpeed = 2.0;
        float waveLength = 0.8;
        float currentRadius = mod(time * waveSpeed, 3.5);
        
        float distDiff = abs(distToCenter - currentRadius);
        if (distDiff < waveLength) {
            float factor = 1.0 - (distDiff / waveLength);
            waveIntensity = factor * 1.0;
            pos.y += factor * 0.1;
        } else {
            waveIntensity = 0.0;
        }

        gl_Position = projection * view * vec4(pos, 1.0);
        localPos = pos;
        distanceEdge = exp(-1.2 * distToCenter);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    
    in vec3 localPos;
    in float waveIntensity;
    in float distanceEdge;

    void main() {
        float baseGridGrid = 0.15;
        float finalGreen = baseGridGrid + waveIntensity * 0.85;
        
        vec3 neonGreen = vec3(0.0, finalGreen, finalGreen * 0.2);
        
        if (waveIntensity > 0.8) {
            neonGreen += vec3(0.4, 0.4, 0.0);
        }

        vec3 finalColor = neonGreen * clamp(distanceEdge, 0.0, 1.0);
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

static void generateRadarGeometry() noexcept
{
    gridVertices.clear();
    gridIndices.clear();

    float halfSize = (static_cast<float>(RADAR_GRID_SIZE) * RADAR_SPACING) / 2.0f;

    for (unsigned int i = 0; i < static_cast<unsigned int>(RADAR_GRID_SIZE); ++i)
    {
        for (unsigned int j = 0; j < static_cast<unsigned int>(RADAR_GRID_SIZE); ++j)
        {
            float x = static_cast<float>(i) * RADAR_SPACING - halfSize;
            float z = static_cast<float>(j) * RADAR_SPACING - halfSize;
            gridVertices.push_back({ x, 0.0f, z });
        }
    }

    for (unsigned int i = 0; i < static_cast<unsigned int>(RADAR_GRID_SIZE); ++i)
    {
        for (unsigned int j = 0; j < static_cast<unsigned int>(RADAR_GRID_SIZE); ++j)
        {
            if (i < static_cast<unsigned int>(RADAR_GRID_SIZE - 1))
            {
                gridIndices.push_back(i * static_cast<unsigned int>(RADAR_GRID_SIZE) + j);
                gridIndices.push_back((i + 1u) * static_cast<unsigned int>(RADAR_GRID_SIZE) + j);
            }
            if (j < static_cast<unsigned int>(RADAR_GRID_SIZE - 1))
            {
                gridIndices.push_back(i * static_cast<unsigned int>(RADAR_GRID_SIZE) + j);
                gridIndices.push_back(i * static_cast<unsigned int>(RADAR_GRID_SIZE) + j + 1u);
            }
        }
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL3 app;
    if (!app.Init(width, height, "OpenGL 3.3 Core - Holographic Sci-Fi Radar"))
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

    generateRadarGeometry();

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(gridVertices.size() * sizeof(Vertex)), gridVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(gridIndices.size() * sizeof(unsigned int)), gridIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    int timeLoc = glGetUniformLocation(shaderProgram, "time");

    const glm::mat4 projection = glm::perspective(glm::radians(50.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 20.0f);

    float time = 0.0f;
    float cameraAngle = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};
    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = std::min(deltaTime, 0.1f);
        time += fixedDelta;
        cameraAngle += fixedDelta * 0.2f;
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.005f, 0.015f, 0.005f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        float camX = 3.5f * std::sin(cameraAngle);
        float camZ = 3.5f * std::cos(cameraAngle);
        glm::mat4 view = glm::lookAt(glm::vec3(camX, 1.7f, camZ), glm::vec3(0.0f, -0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(timeLoc, time);

        glBindVertexArray(VAO);
        glDrawElements(GL_LINES, static_cast<GLsizei>(gridIndices.size()), GL_UNSIGNED_INT, nullptr);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
