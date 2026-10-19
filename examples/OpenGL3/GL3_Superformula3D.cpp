// GL3_Superformula3D.cpp
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
    layout (location = 2) in vec2 aUV;

    out vec3 vWorldPos;
    out vec3 vNormal;
    out vec2 vUV;

    uniform mat4 uProj;
    uniform mat4 uView;

    void main() {
        vWorldPos = aPos;
        vNormal   = aNormal;
        vUV       = aUV;
        gl_Position = uProj * uView * vec4(aPos, 1.0);
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

    vec3 pal(float t) {
        vec3 a = vec3(0.5, 0.5, 0.5);
        vec3 b = vec3(0.5, 0.5, 0.5);
        vec3 c = vec3(1.0, 1.0, 1.0);
        vec3 d = vec3(0.00, 0.33, 0.67);
        return a + b * cos(6.28318 * (c * t + d));
    }

    float hashf(vec3 p) {
        float n = dot(p, vec3(127.1, 311.7, 74.7));
        return fract(sin(n) * 43758.5453123);
    }

    float valueNoise(vec3 p) {
        vec3 i = floor(p);
        vec3 f = fract(p);
        f = f * f * (3.0 - 2.0 * f);

        float n000 = hashf(i + vec3(0.0, 0.0, 0.0));
        float n100 = hashf(i + vec3(1.0, 0.0, 0.0));
        float n010 = hashf(i + vec3(0.0, 1.0, 0.0));
        float n110 = hashf(i + vec3(1.0, 1.0, 0.0));
        float n001 = hashf(i + vec3(0.0, 0.0, 1.0));
        float n101 = hashf(i + vec3(1.0, 0.0, 1.0));
        float n011 = hashf(i + vec3(0.0, 1.0, 1.0));
        float n111 = hashf(i + vec3(1.0, 1.0, 1.0));

        float x00 = mix(n000, n100, f.x);
        float x10 = mix(n010, n110, f.x);
        float x01 = mix(n001, n101, f.x);
        float x11 = mix(n011, n111, f.x);

        float y0 = mix(x00, x10, f.y);
        float y1 = mix(x01, x11, f.y);

        return mix(y0, y1, f.z);
    }

    float fbm(vec3 p) {
        float v = 0.0;
        float a = 0.5;
        for (int i = 0; i < 5; i++) {
            v += a * valueNoise(p);
            p *= 2.03;
            a *= 0.5;
        }
        return v;
    }

    void main() {
        vec3 N = normalize(vNormal);
        vec3 V = normalize(uCamPos - vWorldPos);

        vec3 warped = vWorldPos * 2.5 + vec3(0.0, uTime * 0.15, 0.0);
        float n = fbm(warped);

        float band  = sin(vUV.x * 40.0 + n * 12.0 + uTime * 2.0) * 0.5 + 0.5;
        float band2 = sin(vUV.y * 55.0 - n * 15.0 - uTime * 1.6) * 0.5 + 0.5;
        float veins = band * band2;

        vec3 base = pal(vUV.x * 1.5 + vUV.y * 0.5 + n * 0.6 + uTime * 0.05);
        base = mix(base, base * vec3(1.6, 0.6, 0.3), veins * 0.6);

        vec3 lightDir = normalize(vec3(0.6, 0.9, -0.5));
        vec3 H = normalize(lightDir + V);
        float diff = clamp(dot(N, lightDir) * 0.5 + 0.5, 0.0, 1.0);
        float spec = pow(clamp(dot(N, H), 0.0, 1.0), 64.0);
        float fres = pow(1.0 - clamp(dot(N, V), 0.0, 1.0), 3.0);

        vec3 col = base * (0.25 + 0.85 * diff);
        col += vec3(1.0, 0.9, 0.7) * spec * 1.4;
        col += vec3(0.4, 0.8, 1.0) * fres * 1.0;
        col += base * veins * 0.35;

        float rim = pow(1.0 - clamp(dot(N, V), 0.0, 1.0), 6.0);
        col += pal(uTime * 0.1 + 0.5) * rim * 0.9;

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
    float u, v;
    Vertex() noexcept : x(0.0f), y(0.0f), z(0.0f),
        nx(0.0f), ny(1.0f), nz(0.0f), u(0.0f), v(0.0f) {
    }
    Vertex(float px, float py, float pz,
        float ax, float ay, float az,
        float tu, float tv) noexcept
        : x(px), y(py), z(pz), nx(ax), ny(ay), nz(az), u(tu), v(tv) {
    }
};

struct SuperformulaParams
{
    float m1, n1_1, n1_2, n1_3;
    float m2, n2_1, n2_2, n2_3;
    SuperformulaParams() noexcept
        : m1(0.0f), n1_1(0.0f), n1_2(0.0f), n1_3(0.0f),
        m2(0.0f), n2_1(0.0f), n2_2(0.0f), n2_3(0.0f) {
    }
};

static float superformulaR(float angle, float m, float n1, float n2, float n3) noexcept
{
    float t1 = std::fabs(std::cos(m * angle / 4.0f));
    float t2 = std::fabs(std::sin(m * angle / 4.0f));
    float r = std::pow(std::pow(t1, n2) + std::pow(t2, n3), -1.0f / n1);
    return r;
}

static float morphLerp(float a, float b, float t) noexcept
{
    float s = t * t * (3.0f - 2.0f * t);
    return a + (b - a) * s;
}

static void buildSuperformula(std::vector<Vertex>& out,
    std::size_t uSegs, std::size_t vSegs,
    const SuperformulaParams& p) noexcept
{
    auto eval = [&](float u, float v, float& x, float& y, float& z) noexcept {
        float a1 = u * 2.0f * 3.14159265f;
        float a2 = v * 3.14159265f - 3.14159265f * 0.5f;

        float r1 = superformulaR(a1, p.m1, p.n1_1, p.n1_2, p.n1_3);
        float r2 = superformulaR(a2, p.m2, p.n2_1, p.n2_2, p.n2_3);

        r1 = std::clamp(r1, 0.0f, 3.0f);
        r2 = std::clamp(r2, 0.0f, 3.0f);

        float c2 = std::cos(a2);
        x = r1 * r2 * c2 * std::cos(a1);
        y = r1 * r2 * c2 * std::sin(a1);
        z = r2 * std::sin(a2);
        };

    out.clear();
    out.reserve(uSegs * vSegs * 6);

    const float du = 1.0f / static_cast<float>(uSegs);
    const float dv = 1.0f / static_cast<float>(vSegs);
    const float eps = 1e-3f;

    for (std::size_t i = 0; i < uSegs; ++i) {
        for (std::size_t j = 0; j < vSegs; ++j) {
            float u0 = static_cast<float>(i) * du;
            float v0 = static_cast<float>(j) * dv;
            float u1 = u0 + du;
            float v1 = v0 + dv;

            float x00, y00, z00, x10, y10, z10, x01, y01, z01, x11, y11, z11;
            eval(u0, v0, x00, y00, z00);
            eval(u1, v0, x10, y10, z10);
            eval(u0, v1, x01, y01, z01);
            eval(u1, v1, x11, y11, z11);

            float xdu, ydu, zdu, xdv, ydv, zdv;
            eval(u0 + eps, v0, xdu, ydu, zdu);
            eval(u0, v0 + eps, xdv, ydv, zdv);

            float tx = xdu - x00, ty = ydu - y00, tz = zdu - z00;
            float bx = xdv - x00, by = ydv - y00, bz = zdv - z00;

            float nx = ty * bz - tz * by;
            float ny = tz * bx - tx * bz;
            float nz = tx * by - ty * bx;
            float nl = std::sqrt(nx * nx + ny * ny + nz * nz);
            if (nl > 1e-9f) { nx /= nl; ny /= nl; nz /= nl; }

            Vertex a(x00, y00, z00, nx, ny, nz, u0, v0);
            Vertex b(x10, y10, z10, nx, ny, nz, u1, v0);
            Vertex c(x11, y11, z11, nx, ny, nz, u1, v1);
            Vertex d(x01, y01, z01, nx, ny, nz, u0, v1);

            out.push_back(a); out.push_back(b); out.push_back(c);
            out.push_back(a); out.push_back(c); out.push_back(d);
        }
    }
}

int main()
{
    constexpr std::size_t width = 960;
    constexpr std::size_t height = 720;
    constexpr std::size_t uSegs = 220;
    constexpr std::size_t vSegs = 160;

    AppGL3 app;
    if (!app.Init(width, height, "GL3 Superformula 3D"))
    {
        return -1;
    }

    unsigned int prog = linkProgram(vertexShaderSource, fragmentShaderSource);
    if (prog == 0) {
        return -1;
    }

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
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

    SuperformulaParams shapeA;
    shapeA.m1 = 6.0f;  shapeA.n1_1 = 1.0f; shapeA.n1_2 = 1.0f; shapeA.n1_3 = 1.0f;
    shapeA.m2 = 6.0f;  shapeA.n2_1 = 1.0f; shapeA.n2_2 = 1.0f; shapeA.n2_3 = 1.0f;

    SuperformulaParams shapeB;
    shapeB.m1 = 14.0f; shapeB.n1_1 = 0.3f; shapeB.n1_2 = 1.7f; shapeB.n1_3 = 1.7f;
    shapeB.m2 = 8.0f;  shapeB.n2_1 = 0.3f; shapeB.n2_2 = 1.7f; shapeB.n2_3 = 1.7f;

    SuperformulaParams shapeC;
    shapeC.m1 = 3.0f;  shapeC.n1_1 = 0.5f; shapeC.n1_2 = 1.0f; shapeC.n1_3 = 6.0f;
    shapeC.m2 = 4.0f;  shapeC.n2_1 = 0.5f; shapeC.n2_2 = 1.0f; shapeC.n2_3 = 6.0f;

    std::vector<Vertex> verts;
    std::size_t vertexCount = 0;

    float elapsed = 0.0f;
    float morphPhase = 0.0f;
    int lastBuildStep = -1;

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float dt) noexcept {
        elapsed += dt;
        morphPhase += dt * 0.15f;
        };

    app.OnRender = [&]() noexcept {
        float cycle = std::fmod(morphPhase, 3.0f);
        int step = static_cast<int>(cycle * 6.0f);

        if (step != lastBuildStep) {
            lastBuildStep = step;

            float t01 = std::fmod(cycle, 1.0f);
            SuperformulaParams from, to;
            if (cycle < 1.0f) { from = shapeA; to = shapeB; }
            else if (cycle < 2.0f) { from = shapeB; to = shapeC; }
            else { from = shapeC; to = shapeA; }

            SuperformulaParams blended;
            blended.m1 = morphLerp(from.m1, to.m1, t01);
            blended.n1_1 = morphLerp(from.n1_1, to.n1_1, t01);
            blended.n1_2 = morphLerp(from.n1_2, to.n1_2, t01);
            blended.n1_3 = morphLerp(from.n1_3, to.n1_3, t01);
            blended.m2 = morphLerp(from.m2, to.m2, t01);
            blended.n2_1 = morphLerp(from.n2_1, to.n2_1, t01);
            blended.n2_2 = morphLerp(from.n2_2, to.n2_2, t01);
            blended.n2_3 = morphLerp(from.n2_3, to.n2_3, t01);

            buildSuperformula(verts, uSegs, vSegs, blended);
            vertexCount = verts.size();

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(verts.size() * sizeof(Vertex)),
                verts.data(), GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
        glClearColor(0.01f, 0.01f, 0.03f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float camX = 3.6f * std::sin(elapsed * 0.22f);
        float camY = 1.0f + 1.3f * std::sin(elapsed * 0.37f);
        float camZ = 3.6f * std::cos(elapsed * 0.22f);

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