// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

#include <memory_resource>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <print>

import App;
import WinLite;
import PixelPainter;
import PixelCopier;

using namespace WinLite;
using namespace Software;

int main()
{
    App app;
    if (!app.Init(800, 600, "Daily C++ Modules: Demo Template"))
    {
        return -1;
    }

    app.OnEvent = [&](const Event&) noexcept {};

    app.OnUpdate = [&](float) noexcept {};

    app.OnRender = [&](PixelPainter&, PixelCopier&) noexcept {};

    app.Run();

    return 0;
}
