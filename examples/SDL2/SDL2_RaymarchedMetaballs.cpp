// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

const std::int32_t BUFFER_WIDTH = 200;
const std::int32_t BUFFER_HEIGHT = 150;
const std::size_t NUM_METABALLS = 5;

struct Ball {
    float x;
    float y;
    float vx;
    float vy;
    float radius;
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
        "SDL2 Raymarched Metaballs Demo",
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

    SDL_Texture* render_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        BUFFER_WIDTH,
        BUFFER_HEIGHT
    );

    if (render_texture == nullptr)
    {
        std::println(std::cerr, "Failed to create texture! Error: {}", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<Ball> balls;
    balls.reserve(NUM_METABALLS);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist_x(20.0f, static_cast<float>(BUFFER_WIDTH) - 20.0f);
    std::uniform_real_distribution<float> dist_y(20.0f, static_cast<float>(BUFFER_HEIGHT) - 20.0f);
    std::uniform_real_distribution<float> dist_v(-2.0f, 2.0f);
    std::uniform_real_distribution<float> dist_r(15.0f, 30.0f);

    for (std::size_t i = 0; i < NUM_METABALLS; ++i)
    {
        balls.push_back(Ball{ dist_x(rng), dist_y(rng), dist_v(rng), dist_v(rng), dist_r(rng) });
    }

    std::vector<std::uint32_t> pixel_buffer(static_cast<std::size_t>(BUFFER_WIDTH * BUFFER_HEIGHT), 0);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        for (auto& b : balls)
        {
            b.x += b.vx;
            b.y += b.vy;

            if (b.x < 0.0f || b.x >= static_cast<float>(BUFFER_WIDTH))  b.vx = -b.vx;
            if (b.y < 0.0f || b.y >= static_cast<float>(BUFFER_HEIGHT)) b.vy = -b.vy;

            b.x = std::clamp(b.x, 0.0f, static_cast<float>(BUFFER_WIDTH) - 1.0f);
            b.y = std::clamp(b.y, 0.0f, static_cast<float>(BUFFER_HEIGHT) - 1.0f);
        }

        for (std::int32_t y = 0; y < BUFFER_HEIGHT; ++y)
        {
            float y_f = static_cast<float>(y);

            for (std::int32_t x = 0; x < BUFFER_WIDTH; ++x)
            {
                float x_f = static_cast<float>(x);
                float total_sum = 0.0f;

                for (const auto& b : balls)
                {
                    float dx = x_f - b.x;
                    float dy = y_f - b.y;
                    float sq_dist = dx * dx + dy * dy;

                    if (sq_dist > 0.001f)
                    {
                        total_sum += (b.radius * b.radius) / sq_dist;
                    }
                }

                std::size_t pixel_idx = static_cast<std::size_t>(y * BUFFER_WIDTH + x);

                if (total_sum > 1.0f)
                {
                    auto edge_shading = static_cast<std::uint8_t>(std::min(255.0f, (total_sum - 1.0f) * 150.0f));

                    auto r_color = static_cast<std::uint8_t>(30 + edge_shading / 3);
                    auto g_color = static_cast<std::uint8_t>(180 + edge_shading / 4);
                    auto b_color = static_cast<std::uint8_t>(220 + std::min(35, static_cast<std::int32_t>(edge_shading)));

                    pixel_buffer[pixel_idx] = static_cast<std::uint32_t>((r_color << 24) | (g_color << 16) | (b_color << 8) | 0xFF);
                }
                else
                {
                    auto bg_fade = static_cast<std::uint8_t>(y * 40 / BUFFER_HEIGHT);
                    pixel_buffer[pixel_idx] = static_cast<std::uint32_t>((10 << 24) | (12 << 16) | ((20 + bg_fade) << 8) | 0xFF);
                }
            }
        }

        SDL_UpdateTexture(
            render_texture,
            nullptr,
            pixel_buffer.data(),
            BUFFER_WIDTH * static_cast<std::int32_t>(sizeof(std::uint32_t))
        );

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, render_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(render_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
