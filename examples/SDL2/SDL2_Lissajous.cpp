// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;
const std::int32_t MAX_POINTS = 5000;

struct Point2D {
    std::int32_t x;
    std::int32_t y;
};

int main(int, char* [])
{
    SDL2Loader loader;

    if (!loader.load())
    {
        std::println(std::cerr, "Critical Error: Failed to map SDL2 runtime binaries.");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::println(std::cerr, "Failed to initialize SDL! Error: {}", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Lissajous Curves Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::println(std::cerr, "Failed to create window! Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::println(std::cerr, "Failed to create renderer! Error: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<Point2D> trajectory;
    trajectory.reserve(static_cast<std::size_t>(MAX_POINTS));

    bool isRunning = true;
    SDL_Event event;

    float phase = 0.0f;
    const float freqX = 3.0f;
    const float freqY = 4.0f;

    const float centerX = static_cast<float>(SCREEN_WIDTH) / 2.0f;
    const float centerY = static_cast<float>(SCREEN_HEIGHT) / 2.0f;
    const float radiusX = static_cast<float>(SCREEN_WIDTH) * 0.4f;
    const float radiusY = static_cast<float>(SCREEN_HEIGHT) * 0.4f;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        phase += 0.02f;

        trajectory.clear();
        for (std::int32_t i = 0; i < MAX_POINTS; ++i)
        {
            float t = static_cast<float>(i) * 0.005f;

            float x_f = centerX + radiusX * std::sin(freqX * t + phase);
            float y_f = centerY + radiusY * std::sin(freqY * t);

            trajectory.push_back(Point2D{
                static_cast<std::int32_t>(x_f),
                static_cast<std::int32_t>(y_f)
                });
        }

        SDL_SetRenderDrawColor(renderer, 10, 10, 15, 255);
        SDL_RenderClear(renderer);

        for (std::size_t i = 0; i < trajectory.size(); ++i)
        {
            float ratio = static_cast<float>(i) / static_cast<float>(MAX_POINTS);

            auto r = static_cast<std::uint8_t>(100.0f + 155.0f * std::sin(phase + ratio * 2.0f));
            auto g = static_cast<std::uint8_t>(150.0f + 105.0f * std::cos(phase));
            auto b = static_cast<std::uint8_t>(200.0f * ratio + 55.0f);

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderDrawPoint(renderer, trajectory[i].x, trajectory[i].y);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
