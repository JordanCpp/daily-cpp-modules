// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

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
        "SDL2 Barnsley Fern Fractal Demo",
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

    SDL_Texture* fern_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    if (fern_texture == nullptr)
    {
        std::println(std::cerr, "Failed to create texture! Error: {}", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint32_t> pixel_buffer(static_cast<std::size_t>(SCREEN_WIDTH * SCREEN_HEIGHT), 0x05050AFF);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);

    float x = 0.0f;
    float y = 0.0f;

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

        for (std::int32_t i = 0; i < 4000; ++i)
        {
            float next_x = 0.0f;
            float next_y = 0.0f;
            float r = dist(rng);

            if (r < 1.0f)
            {
                next_x = 0.0f;
                next_y = 0.16f * y;
            }
            else if (r < 86.0f)
            {
                next_x = 0.85f * x + 0.04f * y;
                next_y = -0.04f * x + 0.85f * y + 1.6f;
            }
            else if (r < 93.0f)
            {
                next_x = 0.2f * x - 0.26f * y;
                next_y = 0.23f * x + 0.22f * y + 1.6f;
            }
            else
            {
                next_x = -0.15f * x + 0.28f * y;
                next_y = 0.26f * x + 0.24f * y + 0.44f;
            }

            x = next_x;
            y = next_y;

            auto px = static_cast<std::int32_t>(static_cast<float>(SCREEN_WIDTH) / 2.0f + x * static_cast<float>(SCREEN_WIDTH) * 0.11f);
            auto py = static_cast<std::int32_t>(static_cast<float>(SCREEN_HEIGHT) - y * static_cast<float>(SCREEN_HEIGHT) * 0.09f);

            if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT)
            {
                std::size_t idx = static_cast<std::size_t>(py * SCREEN_WIDTH + px);

                auto green_shade = static_cast<std::uint8_t>(50.0f + y * 18.0f);
                pixel_buffer[idx] = static_cast<std::uint32_t>((30 << 24) | (green_shade << 16) | (40 << 8) | 0xFF);
            }
        }

        SDL_UpdateTexture(
            fern_texture,
            nullptr,
            pixel_buffer.data(),
            SCREEN_WIDTH * static_cast<std::int32_t>(sizeof(std::uint32_t))
        );

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fern_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(fern_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
