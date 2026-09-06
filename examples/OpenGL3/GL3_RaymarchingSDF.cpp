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

const float screenQuad[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
};

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    out vec2 uv;
    void main() {
        uv = aPos;
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 uv;

    uniform float u_time;
    uniform vec2 u_resolution;

    float sdSphere(vec3 p, float s) {
        return length(p) - s;
    }

    float sdTorus(vec3 p, vec2 t) {
        vec2 q = vec2(length(p.xz) - t.x, p.y);
        return length(q) - t.y;
    }

    float map(vec3 p) {
        float s = sin(u_time * 0.5);
        float c = cos(u_time * 0.5);
        mat2 rot = mat2(c, -s, s, c);
        p.xz *= rot;
        p.xy *= rot;

        float torus = sdTorus(p, vec2(1.2, 0.4));
        
        float sphere = sdSphere(p, 0.5 + 0.2 * sin(u_time * 2.0));
        
        return min(torus, sphere);
    }

    vec3 calcNormal(vec3 p) {
        vec2 e = vec2(0.001, 0.0);
        return normalize(vec3(
            map(p + e.xyy) - map(p - e.xyy),
            map(p + e.yxy) - map(p - e.yxy),
            map(p + e.yyx) - map(p - e.yyx)
        ));
    }

    void main() {
        vec2 p = uv;
        p.x *= u_resolution.x / u_resolution.y;

        vec3 ro = vec3(0.0, 0.0, -4.0);
        vec3 rd = normalize(vec3(p, 1.5));

        float t = 0.0;
        for(int i = 0; i < 100; i++) {
            vec3 pos = ro + rd * t;
            float d = map(pos);
            if(d < 0.001 || t > 20.0) break;
            t += d;
        }

        vec3 color = vec3(0.05, 0.05, 0.1);

        if(t < 20.0) {
            vec3 pos = ro + rd * t;
            vec3 normal = calcNormal(pos);
            
            vec3 lightPos = vec3(2.0, 3.0, -3.0);
            vec3 lightDir = normalize(lightPos - pos);
            
            float diff = max(dot(normal, lightDir), 0.0);
            float spec = pow(max(dot(reflect(-lightDir, normal), -rd), 0.0), 32.0);
            
            vec3 objColor = 0.5 + 0.5 * cos(u_time + pos.xyx + vec3(0, 2, 4));
            
            color = objColor * diff + spec;
            
            color = mix(color, vec3(0.05, 0.05, 0.1), 1.0 - exp(-0.05 * t));
        }

        FragColor = vec4(color, 1.0);
    }
)";

unsigned int compileShader(unsigned int type, const char* source);

unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

int main()
{
    constexpr std::size_t width = 1280;
    constexpr std::size_t height = 720;

    AppGL3 app;
    if (!app.Init(width, height, "Demo 01: Raymarching SDF"))
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

    int timeLoc = glGetUniformLocation(shaderProgram, "u_time");
    int resLoc = glGetUniformLocation(shaderProgram, "u_resolution");

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuad), screenQuad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    app.OnEvent = [&](const Event&) noexcept {};

    float totalTime = 0.0f;
    app.OnUpdate = [&](float deltaTime) noexcept {
        totalTime += deltaTime;
        };

    app.OnRender = [&]() noexcept {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glUniform1f(timeLoc, totalTime);
        glUniform2f(resLoc, static_cast<float>(width), static_cast<float>(height));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
