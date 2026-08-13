// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <print>
#include <string>

import WinLite;
import OpenGL;
import FpsCounter;

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
    constexpr int width  = 800;
    constexpr int height = 600;

    auto windowResult = OpenGL1Window::Create(width, height, "Daily C++ Modules: OpenGL 1.2");

    if (!windowResult)
    {
        std::println("Error: {}", windowResult.error());
        return -1;
    }

    OpenGL1Window window = std::move(*windowResult);

    OpenGLLoader loader(1, 2);

    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    FpsCounter counter;

    while (window.IsRunning())
    {
        Event event;
        while (window.GetEvent(event))
        {
            if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
            {
                window.StopEvent();
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.Present();

        if (counter.Update())
        {
            window.SetTitle(std::to_string(counter.GetFps()));
        }
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    return 0;
}