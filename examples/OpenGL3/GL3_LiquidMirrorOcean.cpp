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

    float getWaveHeight(vec3 p) {
        float wave = sin(p.x * 0.5 + u_time * 0.8) * 0.2;
        wave += cos(p.z * 0.4 + u_time * 0.5) * 0.2;
        wave += sin((p.x + p.z) * 1.2 + u_time) * 0.1;
        return wave;
    }

    float map(vec3 p) {
        return p.y - getWaveHeight(p);
    }

    vec3 calcNormal(vec3 p) {
        vec2 e = vec2(0.005, 0.0);
        return normalize(vec3(
            map(p + e.xyy) - map(p - e.xyy),
            map(p + e.yxy) - map(p - e.yxy),
            map(p + e.yyx) - map(p - e.yyx)
        ));
    }

    void main() {
        vec2 p = uv;
        p.x *= u_resolution.x / u_resolution.y;

        vec3 ro = vec3(0.0, 1.5, -3.0); 
        vec3 lookAt = vec3(0.0, 0.0, 5.0);
        vec3 f = normalize(lookAt - ro);
        vec3 r = normalize(cross(vec3(0, 1, 0), f));
        vec3 u = cross(f, r);
        vec3 rd = normalize(f + p.x * r + p.y * u);

        float t = 0.0;
        bool hit = false;

        for(int i = 0; i < 100; i++) {
            vec3 pos = ro + rd * t;
            float d = map(pos);
            if(d < 0.001 || t > 15.0) {
                if(t < 15.0) hit = true;
                break;
            }
            t += d;
        }

        vec3 skyColor = mix(vec3(0.01, 0.02, 0.05), vec3(0.1, 0.15, 0.2), uv.y * 0.5 + 0.5);
        vec3 color = skyColor;

        if(hit) {
            vec3 pos = ro + rd * t;
            vec3 normal = calcNormal(pos);
            vec3 viewDir = normalize(ro - pos);

            float fresnel = pow(1.0 - max(dot(normal, viewDir), 0.0), 5.0);

            vec3 lightPos = vec3(2.0, 5.0, 2.0);
            vec3 lightDir = normalize(lightPos - pos);
            float spec = pow(max(dot(reflect(-lightDir, normal), viewDir), 0.0), 128.0);

            vec3 liquidColor = mix(vec3(0.0, 0.05, 0.1), vec3(0.1, 0.2, 0.3), normal.y * 0.5 + 0.5);
            
            vec3 reflection = skyColor; 
            color = mix(liquidColor, reflection, fresnel);
            
            color += spec * 0.8;
            
            color += vec3(0.0, 0.1, 0.1) * (1.0 - normal.y);
        }

        color *= 1.0 - dot(uv, uv) * 0.4;
        
        FragColor = vec4(color, 1.0);
    }
)";

unsigned int compileShader(unsigned int type, const char* source);
unsigned int compileShader(unsigned int type, const char* source) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

int main() {
    constexpr std::size_t width = 1280;
    constexpr std::size_t height = 720;

    AppGL3 app;
    if (!app.Init(width, height, "Wow Effect: Liquid Mirror Ocean")) return -1;

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    int timeLoc = glGetUniformLocation(program, "u_time");
    int resLoc = glGetUniformLocation(program, "u_resolution");

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuad), screenQuad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    float totalTime = 0.0f;
    app.OnUpdate = [&](float deltaTime) noexcept {
        totalTime += deltaTime;
        };

    app.OnRender = [&]() noexcept {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glUniform1f(timeLoc, totalTime);
        glUniform2f(resLoc, static_cast<float>(width), static_cast<float>(height));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);

    return 0;
}
