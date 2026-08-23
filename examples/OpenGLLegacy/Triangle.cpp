// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <print>
#include <string>

import AppGL1;
import WinLite;
import OpenGL;

using namespace WinLite;

const float vertices[] =
{
    0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

const float colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    AppGL1 app;
    if (!app.Init(width, height, "Daily C++ Modules: OpenGL 1.2 API"))
    {
        return -1;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float) noexcept {};

    app.OnRender = [&]() noexcept {
        glDrawArrays(GL_TRIANGLES, 0, 3);
        };

    app.Run();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    return 0;
}
