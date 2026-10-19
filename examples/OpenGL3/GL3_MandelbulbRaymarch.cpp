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

static const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    out vec2 vUV;
    void main() {
        vUV = aPos * 0.5 + 0.5;
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

static const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 vUV;
    out vec4 FragColor;

    uniform float uTime;
    uniform vec2  uRes;

    float sdSphere(vec3 p, float r) {
        return length(p) - r;
    }

    float map(vec3 p) {
        float t = uTime * 0.4;

        vec3 q = p;
        q.xz *= mat2(cos(t), -sin(t), sin(t), cos(t));
        q.yz *= mat2(cos(t * 0.7), -sin(t * 0.7), sin(t * 0.7), cos(t * 0.7));

        float scale = 1.0;
        float d = 1e9;
        for (int i = 0; i < 8; i++) {
            vec3 z = q;
            float r2 = dot(z, z);
            float k = 1.0;
            for (int j = 0; j < 3; j++) {
                z = abs(z) / clamp(dot(z, z), 0.25, 1.0) - vec3(0.9, 0.6, 1.1);
                z.xy *= mat2(0.8, -0.6, 0.6, 0.8);
            }
            float m = sdSphere(z, 1.0) / scale;
            d = min(d, m);
            scale *= 0.85;
        }
        return d;
    }

    vec3 palette(float t) {
        vec3 a = vec3(0.5, 0.5, 0.5);
        vec3 b = vec3(0.5, 0.5, 0.5);
        vec3 c = vec3(1.0, 1.0, 1.0);
        vec3 d = vec3(0.00, 0.33, 0.67);
        return a + b * cos(6.28318 * (c * t + d));
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
        vec2 uv = (gl_FragCoord.xy * 2.0 - uRes) / uRes.y;

        vec3 ro = vec3(0.0, 0.0, -3.5);
        vec3 rd = normalize(vec3(uv, 1.5));

        float t = 0.0;
        float hit = 0.0;
        vec3 p = ro;
        for (int i = 0; i < 96; i++) {
            p = ro + rd * t;
            float d = map(p);
            if (d < 0.0015) { hit = 1.0; break; }
            if (t > 12.0) break;
            t += d * 0.9;
        }

        vec3 col = vec3(0.02, 0.02, 0.05);

        if (hit > 0.5) {
            vec3 n = calcNormal(p);
            vec3 lightDir = normalize(vec3(0.6, 0.8, -0.4));
            float diff = clamp(dot(n, lightDir), 0.0, 1.0);
            float fres = pow(1.0 - clamp(dot(n, -rd), 0.0, 1.0), 3.0);
            float ao = clamp(1.0 - float(0) * 0.05, 0.4, 1.0);

            float iterT = length(p) * 0.35 + uTime * 0.15;
            vec3 base = palette(iterT);

            vec3 h = normalize(lightDir - rd);
            float spec = pow(clamp(dot(n, h), 0.0, 1.0), 48.0);

            col = base * (0.25 + 0.75 * diff) * ao;
            col += fres * vec3(0.6, 0.9, 1.0) * 0.8;
            col += spec * vec3(1.0);
            col += base * 0.15 * sin(uTime * 2.0 + p.y * 4.0);
        } else {
            float glow = exp(-t * 0.15);
            col += palette(uTime * 0.1 + uv.x * 0.5) * glow * 0.25;
        }

        col = pow(clamp(col, 0.0, 1.0), vec3(0.4545));
        FragColor = vec4(col, 1.0);
    }
)";

static unsigned int compileShader(unsigned int type, const char* source) noexcept
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

struct QuadVertex
{
    float x, y;
    QuadVertex() noexcept : x(0.0f), y(0.0f) {}
    QuadVertex(float px, float py) noexcept : x(px), y(py) {}
};

int main()
{
    constexpr std::size_t width = 960;
    constexpr std::size_t height = 720;

    AppGL3 app;
    if (!app.Init(width, height, "GL3 Mandelbulb Raymarch"))
    {
        return -1;
    }

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);

    const QuadVertex quad[6] = {
        QuadVertex(-1.0f, -1.0f),
        QuadVertex(1.0f, -1.0f),
        QuadVertex(1.0f,  1.0f),
        QuadVertex(-1.0f, -1.0f),
        QuadVertex(1.0f,  1.0f),
        QuadVertex(-1.0f,  1.0f)
    };

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    int uTimeLoc = glGetUniformLocation(prog, "uTime");
    int uResLoc = glGetUniformLocation(prog, "uRes");

    float elapsed = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float dt) noexcept {
        elapsed += dt;
        };

    app.OnRender = [&]() noexcept {
        glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
        glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prog);
        glUniform1f(uTimeLoc, elapsed);
        glUniform2f(uResLoc, static_cast<float>(width), static_cast<float>(height));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(prog);

    return 0;
}
