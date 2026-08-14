// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <print>
#include <string>

import WinLite;
import Painter;
import BmpLoader;
import FpsCounter;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;
    constexpr std::size_t bytesPerPixel = 3;

    auto windowResult = SoftwareWindow::Create(static_cast<int>(width), static_cast<int>(height), "Daily C++ Modules: Starfield Simulation");

    if (!windowResult)
    {
        std::println("Error: {}", windowResult.error());
        return -1;
    }

    SoftwareWindow window = std::move(*windowResult);
    std::vector<std::uint8_t> frameBuffer(width * height * bytesPerPixel);
    Painter render(width, height, bytesPerPixel, std::span<std::uint8_t>(frameBuffer.data(), frameBuffer.size()));

    auto result = BmpLoader::Load("files/LDL_24_256.bmp");

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

        render.SetColor(Color{ 10, 10, 15 });
        render.Clear();

        if (result)
        {
            const BmpLoader::Image& img = result.value();

            render.Copy(0, 0, img.width, img.height, img.bpp, img.pixels);
        }

        window.Present(frameBuffer.data(), bytesPerPixel, width, height);

        if (counter.Update())
        {
            window.SetTitle(std::to_string(counter.GetFps()));
        }
    }

    return 0;
}
