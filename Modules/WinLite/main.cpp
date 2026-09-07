// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include <memory_resource>
#include <cstdint>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

import WinLite;

using namespace WinLite;

int main()
{
    auto result = SoftwareWindow::Create(800, 600, "Random color pixels");

    if (!result)
    {
        std::cout << "Error: " << result.error() << std::endl;
        return -1;
    }

    SoftwareWindow window = std::move(*result);
    std::vector<uint8_t> screen(800 * 600 * 3);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> dist(0, 255);

    while (window.IsRunning())
    {
        Event event;

        while (window.GetEvent(event))
        {
            if (event.Type == EventType::Quit)
            {
                window.StopEvent();
            }
        }

        std::ranges::generate(screen, [&]() {
            return static_cast<uint8_t>(dist(gen));
            });

        window.Present(screen.data(), 3, 800, 600);
    }

    return 0;
}
