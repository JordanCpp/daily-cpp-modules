// GL3_VoronoiCrystal.cpp
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
    layout (location = 2) in float aSeed;

    out vec3  vWorldPos;
    out vec3  vNormal;
    out float vSeed;

    uniform mat4  uProj;
    uniform mat4  uView;
    uniform float uTime;

    void main() {
        float s = aSeed;
        float pulse = 1.0 + 0.05 * sin(uTime * 1.7 + s * 6.2831);
        vec3 n = normalize(aNormal);

        vec3 wobble = vec3(
            sin(uTime * 0.9 + s * 11.0),
            cos(uTime * 1.1 + s * 7.0),
            sin(uTime * 0.7 + s * 13.0)
        ) * 0.06;

        vec3 world = aPos * pulse + wobble;
        vWorldPos = world;
        vNormal   = n;
        vSeed     = s;

        gl_Position = uProj * uView * vec4(world, 1.0);
    }
)";

static const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3  vWorldPos;
    in vec3  vNormal;
    in float vSeed;

    out vec4 FragColor;

    uniform vec3  uCamPos;
    uniform float uTime;

    vec3 hash33(vec3 p) {
        p = vec3(
            dot(p, vec3(127.1, 311.7,  74.7)),
            dot(p, vec3(269.5, 183.3, 246.1)),
            dot(p, vec3(113.5, 271.9, 124.6))
        );
        return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
    }

    float voro(vec3 p, out vec3 cellColor) {
        vec3 g = floor(p);
        vec3 f = p - g;

        float d1 = 1e9;
        float d2 = 1e9;
        vec3  bestCell = vec3(0.0);

        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    vec3 offset = vec3(float(i), float(j), float(k));
                    vec3 cell   = g + offset;
                    vec3 pt     = offset + 0.5 + 0.5 * hash33(cell);

                    float d = length(f - pt);
                    if (d < d1) {
                        d2 = d1;
                        d1 = d;
                        bestCell = cell;
                    } else if (d < d2) {
                        d2 = d;
                    }
                }
            }
        }

        cellColor = 0.5 + 0.5 * hash33(bestCell);
        return d2 - d1;
    }

    vec3 palette(float t, vec3 base) {
        vec3 a = vec3(0.5, 0.5, 0.5);
        vec3 b = vec3(0.5, 0.5, 0.5);
        vec3 c = vec3(1.0, 1.0, 1.0);
        vec3 d = base;
        return a + b * cos(6.28318 * (c * t + d));
    }

    void main() {
        vec3 N = normalize(vNormal);
        vec3 V = normalize(uCamPos - vWorldPos);

        vec3 p = vWorldPos * 0.9 + vec3(0.0, uTime * 0.15, 0.0);

        vec3 cellColor;
        float edge = voro(p, cellColor);

        float cellEdge = smoothstep(0.02, 0.10, edge);
        float glow     = exp(-edge * 22.0);

        vec3 baseCol = palette(uTime * 0.05 + vSeed + dot(cellColor, vec3(0.33)), cellColor);

        vec3 lightDir = normalize(vec3(0.7, 0.9, -0.4));
        vec3 H = normalize(lightDir + V);
        float diff = clamp(dot(N, lightDir) * 0.5 + 0.5, 0.0, 1.0);
        float spec = pow(clamp(dot(N, H), 0.0, 1.0), 96.0);

        float fres = pow(1.0 - clamp(dot(N, V), 0.0, 1.0), 3.0);

        vec3 col = baseCol * (0.3 + 0.7 * diff);
        col = mix(vec3(0.02, 0.05, 0.10), col, cellEdge);
        col += baseCol * glow * 1.6;
        col += vec3(0.6, 0.9, 1.0) * spec * 1.2;
        col += vec3(0.3, 0.7, 1.0) * fres * 0.8;

        float veins = 0.5 + 0.5 * sin(edge * 60.0 - uTime * 3.0);
        col += baseCol * veins * glow * 0.6;

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
    float seed;
    Vertex() noexcept : x(0.0f), y(0.0f), z(0.0f),
        nx(0.0f), ny(1.0f), nz(0.0f), seed(0.0f) {
    }
    Vertex(float px, float py, float pz,
        float ax, float ay, float az,
        float s) noexcept
        : x(px), y(py), z(pz), nx(ax), ny(ay), nz(az), seed(s) {
    }
};

static void addTriangle(std::vector<Vertex>& out,
    const Vertex& a, const Vertex& b, const Vertex& c,
    float seed) noexcept
{
    out.push_back(Vertex(a.x, a.y, a.z, a.nx, a.ny, a.nz, seed));
    out.push_back(Vertex(b.x, b.y, b.z, b.nx, b.ny, b.nz, seed));
    out.push_back(Vertex(c.x, c.y, c.z, c.nx, c.ny, c.nz, seed));
}

static void addIcosphereFace(std::vector<Vertex>& out,
    const float* a, const float* b, const float* c,
    int depth, float seed) noexcept
{
    auto mid = [](const float* p, const float* q, float* m) noexcept {
        float x = (p[0] + q[0]) * 0.5f;
        float y = (p[1] + q[1]) * 0.5f;
        float z = (p[2] + q[2]) * 0.5f;
        float l = std::sqrt(x * x + y * y + z * z);
        m[0] = x / l; m[1] = y / l; m[2] = z / l;
        };

    if (depth == 0) {
        Vertex va(a[0], a[1], a[2], a[0], a[1], a[2], seed);
        Vertex vb(b[0], b[1], b[2], b[0], b[1], b[2], seed);
        Vertex vc(c[0], c[1], c[2], c[0], c[1], c[2], seed);
        addTriangle(out, va, vb, vc, seed);
        return;
    }

    float ab[3], bc[3], ca[3];
    mid(a, b, ab);
    mid(b, c, bc);
    mid(c, a, ca);

    addIcosphereFace(out, a, ab, ca, depth - 1, seed);
    addIcosphereFace(out, b, bc, ab, depth - 1, seed);
    addIcosphereFace(out, c, ca, bc, depth - 1, seed);
    addIcosphereFace(out, ab, bc, ca, depth - 1, seed);
}

static void buildIcosphere(std::vector<Vertex>& out, int depth) noexcept
{
    const float t = (1.0f + std::sqrt(5.0f)) * 0.5f;

    const float v0[3] = { -1.0f,  t, 0.0f };
    const float v1[3] = { 1.0f,  t, 0.0f };
    const float v2[3] = { -1.0f, -t, 0.0f };
    const float v3[3] = { 1.0f, -t, 0.0f };
    const float v4[3] = { 0.0f, -1.0f,  t };
    const float v5[3] = { 0.0f,  1.0f,  t };
    const float v6[3] = { 0.0f, -1.0f, -t };
    const float v7[3] = { 0.0f,  1.0f, -t };
    const float v8[3] = { t, 0.0f, -1.0f };
    const float v9[3] = { t, 0.0f,  1.0f };
    const float v10[3] = { -t, 0.0f, -1.0f };
    const float v11[3] = { -t, 0.0f,  1.0f };

    auto norm = [](const float* p, float* o) noexcept {
        float l = std::sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
        o[0] = p[0] / l; o[1] = p[1] / l; o[2] = p[2] / l;
        };

    float n0[3], n1[3], n2[3], n3[3], n4[3], n5[3];
    float n6[3], n7[3], n8[3], n9[3], n10[3], n11[3];
    norm(v0, n0); norm(v1, n1); norm(v2, n2); norm(v3, n3);
    norm(v4, n4); norm(v5, n5); norm(v6, n6); norm(v7, n7);
    norm(v8, n8); norm(v9, n9); norm(v10, n10); norm(v11, n11);

    const float* faces[20][3] = {
        { n0,  n11, n5  }, { n0,  n5,  n1  }, { n0,  n1,  n7  }, { n0,  n7,  n10 }, { n0,  n10, n11 },
        { n1,  n5,  n9  }, { n5,  n11, n4  }, { n11, n10, n2  }, { n10, n7,  n6  }, { n7,  n1,  n8  },
        { n3,  n9,  n4  }, { n3,  n4,  n2  }, { n3,  n2,  n6  }, { n3,  n6,  n8  }, { n3,  n8,  n9  },
        { n4,  n9,  n5  }, { n5,  n9,  n1  }, { n2,  n4,  n11 }, { n6,  n2,  n10 }, { n8,  n6,  n7  }
    };

    float seed = 0.0f;
    for (int f = 0; f < 20; f++) {
        addIcosphereFace(out, faces[f][0], faces[f][1], faces[f][2], depth, seed);
        seed += 0.05f;
    }
}

int main()
{
    constexpr std::size_t width = 960;
    constexpr std::size_t height = 720;

    AppGL3 app;
    if (!app.Init(width, height, "GL3 Voronoi Crystal"))
    {
        return -1;
    }

    unsigned int prog = linkProgram(vertexShaderSource, fragmentShaderSource);
    if (prog == 0) {
        return -1;
    }

    std::vector<Vertex> verts;
    buildIcosphere(verts, 5);

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(verts.size() * sizeof(Vertex)),
        verts.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    int uProjLoc = glGetUniformLocation(prog, "uProj");
    int uViewLoc = glGetUniformLocation(prog, "uView");
    int uTimeLoc = glGetUniformLocation(prog, "uTime");
    int uCamPosLoc = glGetUniformLocation(prog, "uCamPos");

    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    const float fov = 1.1f;
    const float nearP = 0.05f;
    const float farP = 100.0f;
    const float f = 1.0f / std::tan(fov * 0.5f);

    float proj[16] = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (farP + nearP) / (nearP - farP), -1.0f,
        0.0f, 0.0f, (2.0f * farP * nearP) / (nearP - farP), 0.0f
    };

    float elapsed = 0.0f;
    const std::size_t vertexCount = verts.size();

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
        glClearColor(0.01f, 0.01f, 0.03f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float camX = 2.8f * std::sin(elapsed * 0.25f);
        float camY = 1.5f + 0.9f * std::sin(elapsed * 0.4f);
        float camZ = 2.8f * std::cos(elapsed * 0.25f);

        float fx = 0.0f - camX;
        float fy = 0.0f - camY;
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
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
        };

    app.Run();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(prog);

    return 0;
}
