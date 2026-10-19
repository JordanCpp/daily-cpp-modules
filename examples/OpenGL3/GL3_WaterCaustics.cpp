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
};

const Vertex floorVertices[] =
{
    { -2.0f, 0.0f, -2.0f },
    {  2.0f, 0.0f, -2.0f },
    {  2.0f, 0.0f,  2.0f },
    { -2.0f, 0.0f,  2.0f }
};

const unsigned int floorIndices[] =
{
    0, 1, 2,
    2, 3, 0
};

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    out vec2 uv;
    out float depthFog;

    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        gl_Position = projection * view * vec4(aPos, 1.0);
        uv = aPos.xz * 1.5;
        
        float dist = length(view * vec4(aPos, 1.0));
        depthFog = exp(-0.18 * dist);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 uv;
    in float depthFog;

    uniform float time;

    void main() {
        vec2 p = uv * 4.0;
        
        float t1 = time * 0.5;
        float t2 = time * 0.3;
        
        vec2 uv1 = p + vec2(sin(p.y + t1), cos(p.x + t1)) * 0.3;
        vec2 uv2 = p * 1.2 + vec2(sin(p.x - t2), cos(p.y + t2)) * 0.4;
        vec2 uv3 = p * 0.8 + vec2(cos(p.y + t1 * 0.7), sin(p.x - t2 * 1.3)) * 0.5;
        
        float wave1 = sin(uv1.x + uv1.y) * 0.5 + 0.5;
        float wave2 = cos(uv2.x - uv2.y) * 0.5 + 0.5;
        float wave3 = sin(uv3.x * 0.7 + uv3.y * 1.1) * 0.5 + 0.5;
        
        float combined = (wave1 + wave2 + wave3) / 3.0;
        
        float caustics = pow(combined, 7.0) * 4.5;
        caustics += pow(combined, 16.0) * 2.0; 
        
        vec3 baseWater = vec3(0.0, 0.38, 0.55);
        vec3 lightGlays = vec3(0.6, 0.95, 1.0) * caustics;
        
        vec3 waterColor = clamp(baseWater + lightGlays, 0.0, 1.0);
        vec3 deepBlueFog = vec3(0.01, 0.04, 0.12);
        
        vec3 finalColor = mix(deepBlueFog, waterColor, clamp(depthFog, 0.0, 1.0));
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

int main()
{
    constexpr std::size_t width = 1024;
    constexpr std::size_t height = 768;

    AppGL3 app;
    if (!app.Init(width, height, "OpenGL 3.3 Core - Soft Fluid Water Caustics"))
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

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndices), floorIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    int timeLoc = glGetUniformLocation(shaderProgram, "time");

    const glm::mat4 projection = glm::perspective(glm::radians(55.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 20.0f);

    float time = 0.0f;
    float cameraAngle = 0.5f;

    app.OnEvent = [&](const Event&) noexcept {};
    app.OnUpdate = [&](float deltaTime) noexcept {
        float fixedDelta = std::min(deltaTime, 0.1f);
        time += fixedDelta * 0.9f;
        cameraAngle += fixedDelta * 0.12f;
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.01f, 0.04f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        float camX = 3.0f * std::sin(cameraAngle);
        float camZ = 3.0f * std::cos(cameraAngle);
        glm::mat4 view = glm::lookAt(glm::vec3(camX, 1.6f, camZ), glm::vec3(0.0f, -0.2f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(timeLoc, time);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
