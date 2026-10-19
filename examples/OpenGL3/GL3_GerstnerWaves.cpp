// GL3_GerstnerWaves.cpp
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
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;

    out vec3 vWorldPos;
    out vec3 vNormal;
    out vec2 vUV;

    uniform mat4  uProj;
    uniform mat4  uView;
    uniform float uTime;

    const int   WAVE_COUNT = 4;
    const float AMP[4]   = float[4](0.22, 0.14, 0.09, 0.06);
    const vec2  DIRS[4]  = vec2[4](
        normalize(vec2( 1.0,  0.3)),
        normalize(vec2(-0.7,  0.8)),
        normalize(vec2( 0.4, -1.0)),
        normalize(vec2(-0.5, -0.6))
    );
    const float LEN[4]   = float[4](7.0, 5.5, 4.0, 3.0);
    const float SPEED[4] = float[4](1.1, 0.9, 1.4, 1.7);
    const float STEEP[4] = float[4](0.75, 0.65, 0.55, 0.5);

    vec3 gerstner(vec2 p, float t, out vec3 nrm) {
        vec3 disp = vec3(0.0);
        vec3 tangent  = vec3(1.0, 0.0, 0.0);
        vec3 binormal = vec3(0.0, 0.0, 1.0);

        for (int i = 0; i < WAVE_COUNT; i++) {
            float k = 6.28318 / LEN[i];
            float c = sqrt(9.81 / k);
            float f = k * (dot(DIRS[i], p) - c * SPEED[i] * t);
            float a = STEEP[i] / k;

            float s = sin(f);
            float co = cos(f);

            disp.x += DIRS[i].x * a * co;
            disp.z += DIRS[i].y * a * co;
            disp.y += a * s;

            tangent.x  -= DIRS[i].x * DIRS[i].x * STEEP[i] * s;
            tangent.y  += DIRS[i].x * STEEP[i] * co;
            tangent.z  -= DIRS[i].x * DIRS[i].y * STEEP[i] * s;

            binormal.x -= DIRS[i].x * DIRS[i].y * STEEP[i] * s;
            binormal.y += DIRS[i].y * STEEP[i] * co;
            binormal.z -= DIRS[i].y * DIRS[i].y * STEEP[i] * s;
        }

        nrm = normalize(cross(binormal, tangent));
        return disp;
    }

    void main() {
        vec3 nrm;
        vec3 disp = gerstner(aPos.xz, uTime, nrm);

        vec3 world = aPos + disp;
        vWorldPos = world;
        vNormal   = nrm;
        vUV = aPos.xz * 0.08 + uTime * 0.02;

        gl_Position = uProj * uView * vec4(world, 1.0);
    }
)";

static const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 vWorldPos;
    in vec3 vNormal;
    in vec2 vUV;

    out vec4 FragColor;

    uniform vec3  uCamPos;
    uniform float uTime;

    vec3 sky(vec3 d) {
        float t = clamp(d.y * 0.5 + 0.5, 0.0, 1.0);
        vec3 top = vec3(0.10, 0.16, 0.35);
        vec3 hor = vec3(0.85, 0.55, 0.35);
        vec3 col = mix(hor, top, pow(t, 0.8));
        float sun = pow(clamp(dot(d, normalize(vec3(0.6, 0.4, -0.7))), 0.0, 1.0), 220.0);
        col += vec3(1.0, 0.9, 0.7) * sun * 3.0;
        return col;
    }

    vec3 palette(float t) {
        vec3 a = vec3(0.05, 0.15, 0.25);
        vec3 b = vec3(0.35, 0.45, 0.55);
        vec3 c = vec3(0.7,  0.6,  0.5);
        return mix(a, mix(b, c, t), t);
    }

    void main() {
        vec3 N = normalize(vNormal);
        vec3 V = normalize(uCamPos - vWorldPos);

        float fres = pow(1.0 - clamp(dot(N, V), 0.0, 1.0), 3.5);

        vec3 R = reflect(-V, N);
        R.y = abs(R.y);
        vec3 skyRefl = sky(R);

        vec3 deep = vec3(0.02, 0.14, 0.22);
        vec3 shallow = vec3(0.10, 0.42, 0.50);

        float h = clamp(vWorldPos.y * 0.8 + 0.5, 0.0, 1.0);
        vec3 waterBase = mix(deep, shallow, h);

        vec3 lightDir = normalize(vec3(0.6, 0.7, -0.5));
        vec3 H = normalize(lightDir + V);
        float spec = pow(clamp(dot(N, H), 0.0, 1.0), 180.0);

        float foam = smoothstep(0.75, 1.0, vWorldPos.y + 0.15 * sin(vUV.x * 40.0 + uTime * 3.0) * sin(vUV.y * 37.0 - uTime * 2.0));
        vec3 foamCol = vec3(0.92, 0.96, 1.0) * foam;

        float ca = fres * 0.03;
        vec3 skyReflR = sky(normalize(R + vec3( ca, 0.0, 0.0)));
        vec3 skyReflG = sky(R);
        vec3 skyReflB = sky(normalize(R - vec3( ca, 0.0, 0.0)));
        vec3 chroma = vec3(skyReflR.r, skyReflG.g, skyReflB.b);

        vec3 col = mix(waterBase, chroma, fres * 0.9);
        col += spec * vec3(1.0, 0.95, 0.85) * 1.4;
        col += foamCol * 0.6;

        col = mix(col, palette(fres), 0.05);

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

struct Vertex
{
    float x, y, z;
    float nx, ny, nz;
    Vertex() noexcept : x(0.0f), y(0.0f), z(0.0f), nx(0.0f), ny(1.0f), nz(0.0f) {}
    Vertex(float px, float py, float pz, float ax, float ay, float az) noexcept
        : x(px), y(py), z(pz), nx(ax), ny(ay), nz(az) {
    }
};

static constexpr std::size_t gridN = 256;
static constexpr std::size_t gridVerts = (gridN + 1) * (gridN + 1);
static constexpr std::size_t gridIndices = gridN * gridN * 6;

static void buildGrid(std::vector<Vertex>& verts, std::vector<unsigned int>& indices) noexcept
{
    verts.resize(gridVerts);
    indices.resize(gridIndices);

    const float half = 12.0f;
    const float step = (half * 2.0f) / static_cast<float>(gridN);

    for (std::size_t z = 0; z <= gridN; ++z) {
        for (std::size_t x = 0; x <= gridN; ++x) {
            const std::size_t idx = z * (gridN + 1) + x;
            const float px = -half + static_cast<float>(x) * step;
            const float pz = -half + static_cast<float>(z) * step;
            verts[idx] = Vertex(px, 0.0f, pz, 0.0f, 1.0f, 0.0f);
        }
    }

    std::size_t k = 0;
    for (std::size_t z = 0; z < gridN; ++z) {
        for (std::size_t x = 0; x < gridN; ++x) {
            const unsigned int a = static_cast<unsigned int>(z * (gridN + 1) + x);
            const unsigned int b = static_cast<unsigned int>(z * (gridN + 1) + x + 1);
            const unsigned int c = static_cast<unsigned int>((z + 1) * (gridN + 1) + x);
            const unsigned int d = static_cast<unsigned int>((z + 1) * (gridN + 1) + x + 1);

            indices[k++] = a; indices[k++] = c; indices[k++] = b;
            indices[k++] = b; indices[k++] = c; indices[k++] = d;
        }
    }
}

int main()
{
    constexpr std::size_t width = 960;
    constexpr std::size_t height = 720;

    AppGL3 app;
    if (!app.Init(width, height, "GL3 Gerstner Waves"))
    {
        return -1;
    }

    unsigned int prog = linkProgram(vertexShaderSource, fragmentShaderSource);
    if (prog == 0) {
        return -1;
    }

    std::vector<Vertex> verts;
    std::vector<unsigned int> indices;
    buildGrid(verts, indices);

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(verts.size() * sizeof(Vertex)),
        verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)),
        indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    int uProjLoc = glGetUniformLocation(prog, "uProj");
    int uViewLoc = glGetUniformLocation(prog, "uView");
    int uTimeLoc = glGetUniformLocation(prog, "uTime");
    int uCamPosLoc = glGetUniformLocation(prog, "uCamPos");

    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    const float fov = 1.15f;
    const float nearP = 0.05f;
    const float farP = 200.0f;
    const float f = 1.0f / std::tan(fov * 0.5f);

    float proj[16] = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (farP + nearP) / (nearP - farP), -1.0f,
        0.0f, 0.0f, (2.0f * farP * nearP) / (nearP - farP), 0.0f
    };

    float elapsed = 0.0f;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float dt) noexcept {
        elapsed += dt;
        };

    app.OnRender = [&]() noexcept {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
        glClearColor(0.05f, 0.07f, 0.14f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float camX = 5.5f * std::cos(elapsed * 0.15f);
        float camZ = 5.5f * std::sin(elapsed * 0.15f);
        float camY = 3.2f + 0.6f * std::sin(elapsed * 0.25f);

        float fx = 0.0f - camX;
        float fy = 0.6f - camY;
        float fz = 0.0f - camZ;
        float fl = std::sqrt(fx * fx + fy * fy + fz * fz);
        fx /= fl; fy /= fl; fz /= fl;

        float upx = 0.0f, upy = 1.0f, upz = 0.0f;
        float sx = fy * upz - fz * upy;
        float sy = fz * upx - fx * upz;
        float sz = fx * upy - fy * upx;
        float sl = std::sqrt(sx * sx + sy * sy + sz * sz);
        sx /= sl; sy /= sl; sz /= sl;

        float ux = sy * fz - sz * fy;
        float uy = sz * fx - sx * fz;
        float uz = sx * fy - sy * fx;

        float view[16] = {
            sx, ux, -fx, 0.0f,
            sy, uy, -fy, 0.0f,
            sz, uz, -fz, 0.0f,
            -(sx * camX + sy * camY + sz * camZ),
            -(ux * camX + uy * camY + uz * camZ),
             (fx * camX + fy * camY + fz * camZ),
             1.0f
        };

        glUseProgram(prog);
        glUniformMatrix4fv(uProjLoc, 1, GL_FALSE, proj);
        glUniformMatrix4fv(uViewLoc, 1, GL_FALSE, view);
        glUniform1f(uTimeLoc, elapsed);
        glUniform3f(uCamPosLoc, camX, camY, camZ);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
            GL_UNSIGNED_INT, nullptr);
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(prog);

    return 0;
}
