// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;
const std::int32_t POINTS_PER_FRAME = 30000;

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
        "SDL2 Clifford Attractor Demo",
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

    std::vector<Point2D> draw_buffer;
    draw_buffer.reserve(static_cast<std::size_t>(POINTS_PER_FRAME));

    bool isRunning = true;
    SDL_Event event;

    float current_time = 0.0f;
    float x = 0.1f;
    float y = 0.1f;

    const float center_x = static_cast<float>(SCREEN_WIDTH) / 2.0f;
    const float center_y = static_cast<float>(SCREEN_HEIGHT) / 2.0f;
    const float scale_factor = static_cast<float>(SCREEN_HEIGHT) * 0.22f;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        current_time += 0.002f;

        float a = -1.4f + 0.1f * std::sin(current_time);
        float b = 1.6f + 0.1f * std::cos(current_time * 0.7f);
        float c = 1.0f + 0.2f * std::sin(current_time * 0.5f);
        float d = 0.7f + 0.1f * std::cos(current_time * 1.3f);

        draw_buffer.clear();

        for (std::int32_t i = 0; i < POINTS_PER_FRAME; ++i)
        {
            float next_x = std::sin(a * y) + c * std::cos(a * x);
            float next_y = std::sin(b * x) + d * std::cos(b * y);

            x = next_x;
            y = next_y;

            std::int32_t screen_x = static_cast<std::int32_t>(center_x + x * scale_factor);
            std::int32_t screen_y = static_cast<std::int32_t>(center_y + y * scale_factor);

            if (screen_x >= 0 && screen_x < SCREEN_WIDTH && screen_y >= 0 && screen_y < SCREEN_HEIGHT)
            {
                draw_buffer.push_back(Point2D{ screen_x, screen_y });
            }
        }

        SDL_SetRenderDrawColor(renderer, 5, 5, 12, 255);
        SDL_RenderClear(renderer);

        for (std::size_t i = 0; i < draw_buffer.size(); ++i)
        {
            float ratio = static_cast<float>(i) / static_cast<float>(POINTS_PER_FRAME);

            auto r_color = static_cast<std::uint8_t>(130.0f + 125.0f * std::sin(ratio * 3.14f + current_time));
            auto g_color = static_cast<std::uint8_t>(60.0f + 100.0f * ratio);
            auto b_color = static_cast<std::uint8_t>(200.0f + 55.0f * std::cos(current_time));

            SDL_SetRenderDrawColor(renderer, r_color, g_color, b_color, 255);
            SDL_RenderDrawPoint(renderer, draw_buffer[i].x, draw_buffer[i].y);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
