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
    float nx, ny, nz;
    float shade;
};

static std::vector<Vertex> sphereVertices;
static std::vector<unsigned int> sphereIndices;

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    layout (location = 2) in float aShade;

    out vec3 FragPos;
    out vec3 Normal;
    out float MirrorShade;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        FragPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
        MirrorShade = aShade;
        
        gl_Position = projection * view * vec4(FragPos, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    in vec3 FragPos;
    in vec3 Normal;
    in float MirrorShade;

    uniform vec3 viewPos;
    uniform vec3 light0Pos;
    uniform vec3 light0Color;
    uniform vec3 light1Pos;
    uniform vec3 light1Color;

    vec3 calcLight(vec3 lightPos, vec3 lightColor, vec3 normal, vec3 fragPos, vec3 viewDir) {
        vec3 lightDir = normalize(lightPos - fragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), 128.0);
        
        vec3 ambient = 0.08 * lightColor;
        vec3 diffuse = diff * lightColor * 0.6;
        vec3 specular = spec * vec3(1.0) * 1.5;
        
        return (ambient + diffuse + specular);
    }

    void main() {
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);

        vec3 result = calcLight(light0Pos, light0Color, norm, FragPos, viewDir);
        result += calcLight(light1Pos, light1Color, norm, FragPos, viewDir);
        
        result *= MirrorShade;

        FragColor = vec4(result, 1.0);
    }
)";

static unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

static void generateDiscoBallGeometry(unsigned int stacks, unsigned int slices) noexcept
{
    sphereVertices.clear();
    sphereIndices.clear();

    for (unsigned int i = 0; i <= stacks; ++i) {
        float lat = std::numbers::pi_v<float> *(-0.5f + static_cast<float>(i) / static_cast<float>(stacks));
        float z = std::sin(lat);
        float zr = std::cos(lat);

        for (unsigned int j = 0; j <= slices; ++j) {
            float lng = 2.0f * std::numbers::pi_v<float> *static_cast<float>(j) / static_cast<float>(slices);
            float x = std::cos(lng) * zr;
            float y = std::sin(lng) * zr;

            float nx = x;
            float ny = y;
            float nz = z;

            float mirrorShade = 0.7f + 0.3f * static_cast<float>((j + i) % 2u);

            sphereVertices.push_back({ x, y, z, nx, ny, nz, mirrorShade });
        }
    }

    for (unsigned int i = 0; i < stacks; ++i) {
        for (unsigned int j = 0; j < slices; ++j) {
            unsigned int p0 = i * (slices + 1u) + j;
            unsigned int p1 = p0 + 1u;
            unsigned int p2 = (i + 1u) * (slices + 1u) + j;
            unsigned int p3 = p2 + 1u;

            sphereIndices.push_back(p0); sphereIndices.push_back(p2); sphereIndices.push_back(p1);
            sphereIndices.push_back(p1); sphereIndices.push_back(p2); sphereIndices.push_back(p3);
        }
    }
}

int main() {
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL3 app;
    if (!app.Init(width, height, "OpenGL 3.3 Core - Specular Disco Ball Shader")) return -1;

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    generateDiscoBallGeometry(40u, 40u);

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sphereVertices.size() * sizeof(Vertex)), sphereVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sphereIndices.size() * sizeof(unsigned int)), sphereIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projLoc = glGetUniformLocation(shaderProgram, "projection");

    int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    int l0PosLoc = glGetUniformLocation(shaderProgram, "light0Pos");
    int l0ColLoc = glGetUniformLocation(shaderProgram, "light0Color");
    int l1PosLoc = glGetUniformLocation(shaderProgram, "light1Pos");
    int l1ColLoc = glGetUniformLocation(shaderProgram, "light1Color");

    const glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 10.0f);
    const glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    const glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    float time = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};
    app.OnUpdate = [&](float deltaTime) noexcept {
        time += std::min(deltaTime, 0.1f);
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.03f, 0.03f, 0.04f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::vec3 light0Pos = glm::vec3(2.2f * std::sin(time * 1.2f), 1.0f, 2.2f * std::cos(time * 1.2f));
        glm::vec3 light0Color = glm::vec3(1.0f, 0.15f, 0.15f);

        glm::vec3 light1Pos = glm::vec3(-2.2f * std::cos(time * 0.9f), -1.0f, 2.2f * std::sin(time * 0.9f));
        glm::vec3 light1Color = glm::vec3(0.15f, 0.45f, 1.0f);

        glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));
        glUniform3fv(l0PosLoc, 1, glm::value_ptr(light0Pos));
        glUniform3fv(l0ColLoc, 1, glm::value_ptr(light0Color));
        glUniform3fv(l1PosLoc, 1, glm::value_ptr(light1Pos));
        glUniform3fv(l1ColLoc, 1, glm::value_ptr(light1Color));

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * 0.4f, glm::vec3(0.0f, 1.0f, 0.1f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sphereIndices.size()), GL_UNSIGNED_INT, nullptr);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
