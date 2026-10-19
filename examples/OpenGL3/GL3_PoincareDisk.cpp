// GL3_PoincareDisk.cpp
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

    uniform vec2  uRes;
    uniform float uTime;

    vec2 cmul(vec2 a, vec2 b) {
        return vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }

    vec2 cdiv(vec2 a, vec2 b) {
        float d = dot(b, b);
        return vec2(a.x * b.x + a.y * b.y, a.y * b.x - a.x * b.y) / d;
    }

    vec2 conj(vec2 z) {
        return vec2(z.x, -z.y);
    }

    vec2 mobius(vec2 z, vec2 a) {
        return cdiv(z - a, vec2(1.0) - cmul(conj(a), z));
    }

    vec3 palette(float t) {
        vec3 a = vec3(0.5, 0.5, 0.5);
        vec3 b = vec3(0.5, 0.5, 0.5);
        vec3 c = vec3(1.0, 1.0, 1.0);
        vec3 d = vec3(0.00, 0.33, 0.67);
        return a + b * cos(6.28318 * (c * t + d));
    }

    float hashf(vec2 p) {
        return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
    }

    float circleSDF(vec2 p, float r) {
        return length(p) - r;
    }

    float apollonianStep(vec2 p, float r) {
        return circleSDF(p, r);
    }

    void main() {
        vec2 uv = (gl_FragCoord.xy * 2.0 - uRes) / uRes.y;
        vec2 z = uv;

        float t = uTime * 0.3;

        if (length(z) > 0.999) {
            vec3 edge = palette(0.3 + 0.2 * sin(uTime));
            float glow = smoothstep(1.05, 0.98, length(z));
            vec3 col = mix(vec3(0.0), edge, glow);
            col = pow(clamp(col, 0.0, 1.0), vec3(0.4545));
            FragColor = vec4(col, 1.0);
            return;
        }

        vec2 a1 = 0.55 * vec2(cos(t), sin(t));
        vec2 a2 = 0.45 * vec2(cos(-t * 1.3 + 1.7), sin(-t * 1.3 + 1.7));
        vec2 a3 = 0.35 * vec2(cos(t * 0.7 + 3.1), sin(t * 0.7 + 3.1));

        z = mobius(z, a1);
        z = mobius(z, a2);
        z = mobius(z, a3);

        vec2 kz = z;

        for (int i = 0; i < 4; i++) {
            float fx = floor(kz.x);
            kz.x = kz.x - fx;
        }

        vec2 tz = z;
        float scale = 1.0;
        float dTotal = 0.0;
        vec3 cellColor = vec3(0.0);

        for (int i = 0; i < 6; i++) {
            vec2 cell = floor(tz * scale) / scale;
            float h = hashf(cell);
            cellColor += palette(h + uTime * 0.05) * (1.0 / scale);
            dTotal += 1.0 / scale;
            tz = tz * 1.618 - floor(tz * 1.618 * 0.5) * 2.0;
            scale *= 1.618;
        }

        float band = 0.0;
        for (int i = 0; i < 8; i++) {
            float fi = float(i);
            float r = 0.06 + 0.045 * fi;
            vec2 c = vec2(
                0.35 * cos(t * 0.8 + fi * 1.9),
                0.35 * sin(t * 0.7 + fi * 1.3)
            );
            float d = abs(circleSDF(z, r) - length(c) * 0.0);
            float ring = smoothstep(0.012, 0.0, abs(length(z - c) - r));
            float ring2 = smoothstep(0.008, 0.0, abs(length(z + c) - r));
            band += ring + ring2;
        }

        float edge = smoothstep(0.02, 0.12, dTotal);

        vec3 col = cellColor * 0.4;
        col = mix(col, palette(dTotal * 0.8 + uTime * 0.1), edge);

        float vein = 0.5 + 0.5 * sin(dTotal * 30.0 - uTime * 2.5);
        col += palette(uTime * 0.2 + dTotal) * vein * 0.35;

        float rings = band;
        col += vec3(1.0, 0.85, 0.55) * rings * 1.2;

        float radial = 1.0 - clamp(length(z), 0.0, 1.0);
        col *= mix(0.5, 1.2, radial);

        float vignette = smoothstep(1.0, 0.15, length(uv));
        col *= vignette;

        float boundary = smoothstep(1.0, 0.97, length(uv));
        col += vec3(0.3, 0.7, 1.0) * (1.0 - boundary) * 0.6;

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
    if (!app.Init(width, height, "GL3 Poincare Disk"))
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

    int uResLoc = glGetUniformLocation(prog, "uRes");
    int uTimeLoc = glGetUniformLocation(prog, "uTime");

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
        glUniform2f(uResLoc, static_cast<float>(width), static_cast<float>(height));
        glUniform1f(uTimeLoc, elapsed);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(prog);

    return 0;
}
