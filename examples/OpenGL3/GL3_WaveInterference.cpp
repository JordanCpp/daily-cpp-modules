// GL3_WaveInterference.cpp
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

    float wave(vec2 p, vec2 src, float t, float k, float speed) {
        float d = distance(p, src);
        float phase = k * d - speed * t;
        float atten = 1.0 / (1.0 + d * 3.5);
        return sin(phase) * atten;
    }

    vec3 palette(float t) {
        vec3 a = vec3(0.5, 0.5, 0.5);
        vec3 b = vec3(0.5, 0.5, 0.5);
        vec3 c = vec3(1.0, 1.0, 1.0);
        vec3 d = vec3(0.00, 0.33, 0.67);
        return a + b * cos(6.28318 * (c * t + d));
    }

    void main() {
        vec2 uv = (gl_FragCoord.xy * 2.0 - uRes) / uRes.y;
        float t = uTime;

        vec2 s1 = vec2(0.85 * cos(t * 0.55),        0.85 * sin(t * 0.55));
        vec2 s2 = vec2(0.85 * cos(t * 0.55 + 2.09), 0.85 * sin(t * 0.55 + 2.09));
        vec2 s3 = vec2(0.85 * cos(t * 0.55 + 4.19), 0.85 * sin(t * 0.55 + 4.19));
        vec2 s4 = vec2(0.45 * cos(-t * 0.9 + 1.1),  0.45 * sin(-t * 0.9 + 1.1));

        float kR = 42.0;
        float kG = 48.0;
        float kB = 56.0;

        float wR = 0.0;
        wR += wave(uv, s1, t, kR, 4.5);
        wR += wave(uv, s2, t, kR, 4.5);
        wR += wave(uv, s3, t, kR, 4.5);
        wR += wave(uv, s4, t, kR, 5.2);

        float wG = 0.0;
        wG += wave(uv, s1, t, kG, 5.0);
        wG += wave(uv, s2, t, kG, 5.0);
        wG += wave(uv, s3, t, kG, 5.0);
        wG += wave(uv, s4, t, kG, 5.6);

        float wB = 0.0;
        wB += wave(uv, s1, t, kB, 5.5);
        wB += wave(uv, s2, t, kB, 5.5);
        wB += wave(uv, s3, t, kB, 5.5);
        wB += wave(uv, s4, t, kB, 6.0);

        vec3 inter = vec3(wR, wG, wB);

        float amps = length(vec3(wR, wG, wB)) * 0.35;
        float energy = amps;

        vec3 base = palette(0.15 * t + energy * 0.4);
        vec3 col = base * (0.25 + 0.75 * (inter * 0.5 + 0.5));

        col += vec3(1.0, 0.4, 0.2) * pow(max(wR, 0.0), 3.0) * 0.6;
        col += vec3(0.2, 1.0, 0.4) * pow(max(wG, 0.0), 3.0) * 0.6;
        col += vec3(0.3, 0.5, 1.0) * pow(max(wB, 0.0), 3.0) * 0.6;

        float nodes = 1.0 - smoothstep(0.0, 0.4, amps);
        col = mix(col, vec3(0.01, 0.01, 0.03), nodes * 0.35);

        float v = length(vec2(dFdx(energy), dFdy(energy)));
        col += vec3(0.6, 0.9, 1.0) * clamp(v * 0.35, 0.0, 1.0) * 0.5;

        vec2 sp;
        sp = uv - s1; col += vec3(1.0, 0.6, 0.4) * 0.045 / (0.02 + dot(sp, sp) * 40.0);
        sp = uv - s2; col += vec3(0.4, 1.0, 0.6) * 0.045 / (0.02 + dot(sp, sp) * 40.0);
        sp = uv - s3; col += vec3(0.5, 0.7, 1.0) * 0.045 / (0.02 + dot(sp, sp) * 40.0);
        sp = uv - s4; col += vec3(1.0, 0.9, 0.4) * 0.045 / (0.02 + dot(sp, sp) * 40.0);

        col = pow(clamp(col, 0.0, 1.0), vec3(0.4545));
        FragColor = vec4(col, 1.0);
    }
)";

static void printLog(const char* log) noexcept
{
    if (log != nullptr && log[0] != '\0') {
        std::cerr << log << '\n';
    }
}

static unsigned int compileShader(unsigned int type, const char* source) noexcept
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int status = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int logLen = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            std::vector<char> log(static_cast<std::size_t>(logLen), '\0');
            glGetShaderInfoLog(id, logLen, nullptr, log.data());
            printLog(log.data());
        }
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int linkProgram(const char* vsSrc, const char* fsSrc) noexcept
{
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vsSrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fsSrc);
    if (vs == 0 || fs == 0) {
        if (vs != 0) glDeleteShader(vs);
        if (fs != 0) glDeleteShader(fs);
        return 0;
    }

    unsigned int prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);

    int status = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int logLen = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            std::vector<char> log(static_cast<std::size_t>(logLen), '\0');
            glGetProgramInfoLog(prog, logLen, nullptr, log.data());
            printLog(log.data());
        }
        glDeleteProgram(prog);
        return 0;
    }
    return prog;
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
    if (!app.Init(width, height, "GL3 Wave Interference"))
    {
        return -1;
    }

    unsigned int prog = linkProgram(vertexShaderSource, fragmentShaderSource);
    if (prog == 0) {
        return -1;
    }

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
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
        glClearColor(0.01f, 0.01f, 0.03f, 1.0f);
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
