// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int NUM_SEGMENTS = 30;
const float SEGMENT_LENGTH = 15.0f;

struct Segment {
    float x;
    float y;
    float angle;
    float length;
    float ex;
    float ey;
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
        "SDL2 Inverse Kinematics Demo",
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

    std::vector<Segment> segments;
    segments.reserve(static_cast<std::size_t>(NUM_SEGMENTS));

    for (int i = 0; i < NUM_SEGMENTS; ++i)
    {
        segments.push_back(Segment{ 0.0f, 0.0f, 0.0f, SEGMENT_LENGTH, 0.0f, 0.0f });
    }

    float base_x = static_cast<float>(SCREEN_WIDTH) / 2.0f;
    float base_y = static_cast<float>(SCREEN_HEIGHT) - 20.0f;

    bool isRunning = true;
    SDL_Event event;

    float target_x = base_x;
    float target_y = base_y - 200.0f;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                target_x = static_cast<float>(event.motion.x);
                target_y = static_cast<float>(event.motion.y);
            }
        }

        auto& head = segments[0];
        head.x = target_x;
        head.y = target_y;

        for (std::size_t i = 0; i < segments.size(); ++i)
        {
            float tx = (i == 0) ? target_x : segments[i - 1].x;
            float ty = (i == 0) ? target_y : segments[i - 1].y;

            auto& seg = segments[i];
            float dx = tx - seg.x;
            float dy = ty - seg.y;
            seg.angle = std::atan2(dy, dx);

            seg.x = tx - std::cos(seg.angle) * seg.length;
            seg.y = ty - std::sin(seg.angle) * seg.length;
        }

        if (!segments.empty())
        {
            std::size_t last_idx = segments.size() - 1;
            float diff_x = base_x - segments[last_idx].x;
            float diff_y = base_y - segments[last_idx].y;

            for (std::size_t i = segments.size(); i > 0; --i)
            {
                segments[i - 1].x += diff_x;
                segments[i - 1].y += diff_y;
            }
        }

        for (std::size_t i = 0; i < segments.size(); ++i)
        {
            auto& seg = segments[i];
            seg.ex = seg.x + std::cos(seg.angle) * seg.length;
            seg.ey = seg.y + std::sin(seg.angle) * seg.length;
            if (i > 0)
            {
                segments[i - 1].x = seg.ex;
                segments[i - 1].y = seg.ey;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 25, 255);
        SDL_RenderClear(renderer);

        for (std::size_t i = 0; i < segments.size(); ++i)
        {
            const auto& seg = segments[i];

            float ratio = static_cast<float>(i) / static_cast<float>(NUM_SEGMENTS);
            std::uint8_t r = static_cast<std::uint8_t>(50.0f + 205.0f * (1.0f - ratio));
            std::uint8_t g = static_cast<std::uint8_t>(200.0f * ratio);
            std::uint8_t b = static_cast<std::uint8_t>(255.0f);

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);

            float thickness = 12.0f * (1.0f - ratio * 0.7f);
            int t_int = static_cast<int>(thickness);
            if (t_int < 2) t_int = 2;

            for (int offset = -t_int / 2; offset <= t_int / 2; ++offset)
            {
                float nx = -std::sin(seg.angle) * static_cast<float>(offset);
                float ny = std::cos(seg.angle) * static_cast<float>(offset);

                SDL_RenderDrawLine(
                    renderer,
                    static_cast<int>(seg.x + nx),
                    static_cast<int>(seg.y + ny),
                    static_cast<int>(seg.ex + nx),
                    static_cast<int>(seg.ey + ny)
                );
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_Rect base_rect{ static_cast<int>(base_x) - 10, static_cast<int>(base_y) - 5, 20, 10 };
        SDL_RenderFillRect(renderer, &base_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
