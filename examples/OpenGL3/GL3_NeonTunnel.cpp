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

    mat2 rot(float a) {
        float s = sin(a), c = cos(a);
        return mat2(c, -s, s, c);
    }

    float sdBox(vec3 p, vec3 b) {
        vec3 q = abs(p) - b;
        return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
    }

    float map(vec3 p) {
        float scale = 1.0;
        
        p.z += u_time * 2.0; 
        p = mod(p, 4.0) - 2.0;

        for(int i = 0; i < 4; i++) {
            p = abs(p) - 0.5;
            p.xy *= rot(u_time * 0.1 + float(i));
            p.xz *= rot(u_time * 0.05);
            
            float s = 1.5;
            p *= s;
            scale *= s;
        }

        return sdBox(p, vec3(0.5)) / scale;
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

        vec3 ro = vec3(0.0, 0.0, -1.0); 
        vec3 rd = normalize(vec3(p, 1.0));

        float t = 0.0;
        float glow = 0.0;

        for(int i = 0; i < 80; i++) {
            vec3 pos = ro + rd * t;
            float d = map(pos);
            
            glow += 0.005 / (0.05 + d); 
            
            if(d < 0.001 || t > 20.0) break;
            t += d;
        }

        vec3 color = vec3(0.01, 0.01, 0.02);

        if(t < 20.0) {
            vec3 pos = ro + rd * t;
            vec3 normal = calcNormal(pos);
            vec3 lightDir = normalize(vec3(1.0, 1.0, -1.0));
            
            float diff = max(dot(normal, lightDir), 0.0);
            float spec = pow(max(dot(reflect(-lightDir, normal), -rd), 0.0), 64.0);
            
            vec3 neonColor = 0.5 + 0.5 * cos(u_time + pos.xyx * 0.5 + vec3(0, 2, 4));
            neonColor = mix(vec3(0.0, 1.0, 1.0), vec3(1.0, 0.0, 1.0), sin(u_time * 0.5) * 0.5 + 0.5);

            color = neonColor * diff + spec;
        }

        vec3 glowColor = vec3(0.2, 0.6, 1.0) * glow * 0.15;
        color += glowColor;

        float noise = fract(sin(dot(uv, vec2(12.9898, 78.233))) * 43758.5453);
        color += noise * 0.02;
        color *= 1.0 - dot(uv, uv) * 0.5;

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
    if (!app.Init(width, height, "Wow Effect: Fractal Neon Tunnel")) return -1;

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
