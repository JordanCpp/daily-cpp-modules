// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <print>
#include <string>

import App;
import WinLite;
import PixelPainter;
import PixelCopier;
import BmpLoader;
import FpsCounter;

using namespace WinLite;
using namespace Software;

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 600;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Starfield Simulation"))
    {
        return -1;
    }

    auto result = BmpLoader::Load("files/LDL_24_256.bmp");

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float) noexcept {};

    app.OnRender = [&](PixelPainter&, PixelCopier& copier) noexcept {
        if (result)
        {
            const BmpLoader::Image& img = result.value();
            copier.Copy(0, 0, img.width, img.height, img.bpp, img.pixels);
        }
        };

    app.Run();

    return 0;
}
