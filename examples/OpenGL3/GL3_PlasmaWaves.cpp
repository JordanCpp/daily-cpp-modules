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

constexpr int GRID_SIZE = 120;
constexpr float GRID_SPACING = 0.05f;

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

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform float time;

    void main() {
        vec3 pos = aPos;
        
        pos.y = 0.25 * (
            sin(pos.x * 3.0 + time * 2.0) * cos(pos.z * 2.5 + time * 1.5) +
            sin((pos.x + pos.z) * 2.0 + time * 1.1) * 0.5
        );

        gl_Position = projection * view * model * vec4(pos, 1.0);
        localPos = pos;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 localPos;

    uniform float time;

    void main() {
        float r = 0.5 + 0.5 * sin(localPos.x * 2.0 + time);
        float g = 0.5 + 0.5 * cos(localPos.y * 5.0 + time * 1.5);
        float b = 0.5 + 0.5 * sin(localPos.z * 2.0 - time);

        FragColor = vec4(r, g, b, 1.0);
    }
)";

static unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

static void generateGridGeometry() noexcept
{
    gridVertices.clear();
    gridIndices.clear();

    float halfSize = (static_cast<float>(GRID_SIZE) * GRID_SPACING) / 2.0f;

    for (unsigned int i = 0; i < static_cast<unsigned int>(GRID_SIZE); ++i)
    {
        for (unsigned int j = 0; j < static_cast<unsigned int>(GRID_SIZE); ++j)
        {
            float x = static_cast<float>(i) * GRID_SPACING - halfSize;
            float z = static_cast<float>(j) * GRID_SPACING - halfSize;
            gridVertices.push_back({ x, 0.0f, z });
        }
    }

    for (unsigned int i = 0; i < static_cast<unsigned int>(GRID_SIZE - 1); ++i)
    {
        for (unsigned int j = 0; j < static_cast<unsigned int>(GRID_SIZE - 1); ++j)
        {
            unsigned int row1 = i * static_cast<unsigned int>(GRID_SIZE);
            unsigned int row2 = (i + 1u) * static_cast<unsigned int>(GRID_SIZE);

            gridIndices.push_back(row1 + j);
            gridIndices.push_back(row1 + j + 1u);
            gridIndices.push_back(row2 + j);

            gridIndices.push_back(row1 + j + 1u);
            gridIndices.push_back(row2 + j + 1u);
            gridIndices.push_back(row2 + j);
        }
    }
}

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL3 app;
    if (!app.Init(width, height, "OpenGL 3.3 Core - Animated Plasma Waves"))
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

    generateGridGeometry();

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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    int timeLoc = glGetUniformLocation(shaderProgram, "time");

    const glm::mat4 projection = glm::perspective(glm::radians(50.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 20.0f);
    const glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 2.0f, 3.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    float time = 0.0f;
    float rotationAngle = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};
    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = std::min(deltaTime, 0.1f);
        time += fixedDelta;
        rotationAngle += fixedDelta * 0.3f;
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(timeLoc, time);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(gridIndices.size()), GL_UNSIGNED_INT, nullptr);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
