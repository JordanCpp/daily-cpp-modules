// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

import WinLite;

using namespace WinLite;

int main()
{
    if (auto result = Window::Create(100, 100, 800, 600, "WinLite::Window::Title"); !result)
    {
        std::cout << "Error: " << result.error() << std::endl;
        return -1;
    }
    else
    {
        Window window = std::move(*result);

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
        }
    }

    return 0;
}
