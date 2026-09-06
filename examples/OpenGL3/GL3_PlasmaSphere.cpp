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

    float smin(float a, float b, float k) {
        float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
        return mix(b, a, h) - k * h * (1.0 - h);
    }

    mat2 rot(float a) {
        float s = sin(a), c = cos(a);
        return mat2(c, -s, s, c);
    }

    float sdSphere(vec3 p, float s) {
        return length(p) - s;
    }

    float map(vec3 p) {
        p.xz *= rot(u_time * 0.3);
        p.xy *= rot(u_time * 0.2);

        float d = sdSphere(p, 1.2);

        for(float i = 0.0; i < 4.0; i++) {
            float t = u_time * 0.5 + i * 1.5;
            vec3 pos = vec3(
                sin(t) * 0.7,
                cos(t * 0.7) * 0.7,
                sin(t * 0.3) * 0.7
            );
            d = smin(d, sdSphere(p - pos, 0.6), 0.5);
        }

        float displacement = sin(p.x * 4.0 + u_time) * sin(p.y * 4.0 + u_time) * sin(p.z * 4.0 + u_time) * 0.15;
        return d + displacement;
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

        vec3 ro = vec3(0.0, 0.0, -4.0); // Ray Origin
        vec3 rd = normalize(vec3(p, 1.8)); // Ray Direction

        float t = 0.0;
        float glow = 0.0;

        for(int i = 0; i < 80; i++) {
            vec3 pos = ro + rd * t;
            float d = map(pos);
            
            glow += 0.01 / (0.1 + d); 
            
            if(d < 0.001 || t > 10.0) break;
            t += d;
        }

        vec3 color = vec3(0.02, 0.02, 0.05);

        if(t < 10.0) {
            vec3 pos = ro + rd * t;
            vec3 normal = calcNormal(pos);
            vec3 lightDir = normalize(vec3(5.0, 5.0, -5.0));
            
            float diff = max(dot(normal, lightDir), 0.0);
            float spec = pow(max(dot(reflect(-lightDir, normal), -rd), 0.0), 64.0);
            
            vec3 objColor = 0.5 + 0.5 * cos(u_time + pos.xyx + vec3(0, 2, 4));
            objColor *= vec3(0.2, 0.5, 1.0);

            color = objColor * diff + spec;
            
            float ao = clamp(1.0 - t/10.0, 0.0, 1.0);
            color *= ao;
        }

        vec3 glowColor = vec3(0.1, 0.4, 1.0) * glow * 0.05;
        color += glowColor;

        color *= 1.0 - dot(uv, uv) * 0.2;

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
    if (!app.Init(width, height, "Wow Effect: Plasma Sphere")) return -1;

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
