// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

import std;
import WinLite;
import OpenGL;
import OpenGL1Painter;

constexpr std::size_t width  = 1024;
constexpr std::size_t height = 768;

using namespace WinLite;
using namespace OpenGL1;

int main()
{
    auto windowResult = OpenGL1Window::Create(width, height, "OpenGL1Painter - Clear");
    if (!windowResult)
    {
        std::println("Error: {}", windowResult.error());
        return -1;
    }

    auto window = std::move(*windowResult);

    OpenGLLoader loader(1, 2);

    Painter painter(width, height);

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

        painter.SetColor(Color(255, 0, 0));
        painter.Clear();

        window.Present();
    }

    return 0;
}
