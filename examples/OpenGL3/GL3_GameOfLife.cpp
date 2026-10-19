// GL3_GameOfLife.cpp
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

static const char* quadVertexSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    out vec2 vUV;
    void main() {
        vUV = aPos * 0.5 + 0.5;
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

static const char* seedFragmentSource = R"(
    #version 330 core
    in vec2 vUV;
    out vec4 FragColor;
    uniform float uTime;
    uniform vec2  uSeed;
    float hash(vec2 p) {
        p = fract(p * vec2(443.897, 441.423));
        p += dot(p, p + 19.19);
        return fract(p.x * p.y);
    }
    void main() {
        ivec2 cell = ivec2(vUV * uSeed);
        float r = hash(vec2(cell) + floor(uTime * 0.5) * 13.7);
        float alive = step(0.82, r);
        float age   = alive > 0.5 ? 1.0 : 0.0;
        FragColor = vec4(alive, age, 0.0, 1.0);
    }
)";

static const char* lifeStepSource = R"(
    #version 330 core
    in vec2 vUV;
    out vec4 FragColor;
    uniform sampler2D uState;
    uniform vec2 uTexel;
    void main() {
        float n = 0.0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;
                vec2 o = vec2(float(dx), float(dy)) * uTexel;
                n += texture(uState, vUV + o).r > 0.5 ? 1.0 : 0.0;
            }
        }
        float alive = texture(uState, vUV).r > 0.5 ? 1.0 : 0.0;
        float age   = texture(uState, vUV).g;

        float newAlive = 0.0;
        if (alive > 0.5) {
            if (n == 2.0 || n == 3.0) newAlive = 1.0;
        } else {
            if (n == 3.0) newAlive = 1.0;
        }

        float newAge = (newAlive > 0.5) ? (alive > 0.5 ? age + 0.02 : 0.02) : 0.0;
        FragColor = vec4(newAlive, newAge, 0.0, 1.0);
    }
)";

static const char* displayFragmentSource = R"(
    #version 330 core
    in vec2 vUV;
    out vec4 FragColor;
    uniform sampler2D uState;
    uniform vec2  uGrid;
    uniform float uTime;

    vec3 palette(float t) {
        vec3 a = vec3(0.5, 0.5, 0.5);
        vec3 b = vec3(0.5, 0.5, 0.5);
        vec3 c = vec3(1.0, 1.0, 1.0);
        vec3 d = vec3(0.00, 0.10, 0.20);
        return a + b * cos(6.28318 * (c * t + d));
    }

    void main() {
        vec2 uv = vUV;
        vec4 s = texture(uState, uv);
        float alive = s.r;
        float age   = s.g;

        vec2 cellUV = fract(uv * uGrid) - 0.5;
        float cellMask = smoothstep(0.5, 0.45, length(cellUV));
        float border   = smoothstep(0.42, 0.50, length(cellUV));

        vec3 col = vec3(0.03, 0.02, 0.06);

        if (alive > 0.5) {
            float t = age * 3.0 + uTime * 0.1;
            vec3 c = palette(t);
            c = mix(c, vec3(1.0, 0.9, 0.4), clamp(age * 0.6, 0.0, 1.0));
            col = c * cellMask;
            col += c * border * 0.4;
            col += vec3(0.2, 0.6, 1.0) * pow(age, 3.0) * 0.8 * cellMask;
        } else {
            col += vec3(0.05, 0.04, 0.08) * cellMask;
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

static unsigned int linkProgram(const char* vsSrc, const char* fsSrc) noexcept
{
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vsSrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fsSrc);
    unsigned int prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

struct QuadVertex
{
    float x, y;
    QuadVertex() noexcept : x(0.0f), y(0.0f) {}
    QuadVertex(float px, float py) noexcept : x(px), y(py) {}
};

static void makeTarget(unsigned int& fbo, unsigned int& tex, std::size_t w, std::size_t h) noexcept
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F,
        static_cast<int>(w), static_cast<int>(h), 0,
        GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int main()
{
    constexpr std::size_t width = 960;
    constexpr std::size_t height = 720;
    constexpr std::size_t simW = 256;
    constexpr std::size_t simH = 256;

    AppGL3 app;
    if (!app.Init(width, height, "GL3 Game of Life on GPU"))
    {
        return -1;
    }

    unsigned int seedProg = linkProgram(quadVertexSource, seedFragmentSource);
    unsigned int stepProg = linkProgram(quadVertexSource, lifeStepSource);
    unsigned int displayProg = linkProgram(quadVertexSource, displayFragmentSource);

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

    unsigned int fboA = 0;
    unsigned int texA = 0;
    unsigned int fboB = 0;
    unsigned int texB = 0;
    makeTarget(fboA, texA, simW, simH);
    makeTarget(fboB, texB, simW, simH);

    glBindFramebuffer(GL_FRAMEBUFFER, fboA);
    glViewport(0, 0, static_cast<int>(simW), static_cast<int>(simH));
    glUseProgram(seedProg);
    glUniform1f(glGetUniformLocation(seedProg, "uTime"), 0.0f);
    glUniform2f(glGetUniformLocation(seedProg, "uSeed"),
        static_cast<float>(simW), static_cast<float>(simH));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindFramebuffer(GL_FRAMEBUFFER, fboB);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    int uStateStepLoc = glGetUniformLocation(stepProg, "uState");
    int uTexelLoc = glGetUniformLocation(stepProg, "uTexel");
    int uStateDispLoc = glGetUniformLocation(displayProg, "uState");
    int uGridLoc = glGetUniformLocation(displayProg, "uGrid");
    int uTimeDispLoc = glGetUniformLocation(displayProg, "uTime");

    float elapsed = 0.0f;
    float accum = 0.0f;
    constexpr float stepInterval = 0.08f;
    bool pingpong = true;
    int generation = 0;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float dt) noexcept {
        elapsed += dt;
        accum += dt;
        };

    app.OnRender = [&]() noexcept {
        if (accum >= stepInterval) {
            accum -= stepInterval;
            generation++;
            if (generation % 400 == 0) {
                glBindFramebuffer(GL_FRAMEBUFFER, pingpong ? fboB : fboA);
                glViewport(0, 0, static_cast<int>(simW), static_cast<int>(simH));
                glUseProgram(seedProg);
                glUniform1f(glGetUniformLocation(seedProg, "uTime"), elapsed);
                glUniform2f(glGetUniformLocation(seedProg, "uSeed"),
                    static_cast<float>(simW), static_cast<float>(simH));
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }

            glViewport(0, 0, static_cast<int>(simW), static_cast<int>(simH));
            glUseProgram(stepProg);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, pingpong ? texA : texB);
            glUniform1i(uStateStepLoc, 0);
            glUniform2f(uTexelLoc, 1.0f / static_cast<float>(simW), 1.0f / static_cast<float>(simH));

            glBindFramebuffer(GL_FRAMEBUFFER, pingpong ? fboB : fboA);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            pingpong = !pingpong;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
        glClearColor(0.02f, 0.01f, 0.04f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(displayProg);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pingpong ? texA : texB);
        glUniform1i(uStateDispLoc, 0);
        glUniform2f(uGridLoc, static_cast<float>(simW), static_cast<float>(simH));
        glUniform1f(uTimeDispLoc, elapsed);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteFramebuffers(1, &fboA);
    glDeleteFramebuffers(1, &fboB);
    glDeleteTextures(1, &texA);
    glDeleteTextures(1, &texB);
    glDeleteProgram(seedProg);
    glDeleteProgram(stepProg);
    glDeleteProgram(displayProg);

    return 0;
}