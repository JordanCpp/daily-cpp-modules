// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

const std::int32_t BUFFER_WIDTH = 320;
const std::int32_t BUFFER_HEIGHT = 240;

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
        "SDL2 Color Wave Demo",
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

    SDL_Texture* wave_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        BUFFER_WIDTH,
        BUFFER_HEIGHT
    );

    if (wave_texture == nullptr)
    {
        std::println(std::cerr, "Failed to create texture! Error: {}", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint32_t> pixel_buffer(static_cast<std::size_t>(BUFFER_WIDTH * BUFFER_HEIGHT), 0);

    bool isRunning = true;
    SDL_Event event;
    float time_counter = 0.0f;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        time_counter += 0.05f;

        for (std::int32_t y = 0; y < BUFFER_HEIGHT; ++y)
        {
            float fy = static_cast<float>(y) * 0.04f;

            for (std::int32_t x = 0; x < BUFFER_WIDTH; ++x)
            {
                float fx = static_cast<float>(x) * 0.04f;

                float wave1 = std::sin(fx + time_counter);
                float wave2 = std::cos(fy - time_counter);
                float wave3 = std::sin(std::sqrt(fx * fx + fy * fy) + time_counter);

                float total_wave = (wave1 + wave2 + wave3) / 3.0f;

                float color_factor = (total_wave + 1.0f) * 127.5f;

                auto r = static_cast<std::uint8_t>(color_factor);
                auto g = static_cast<std::uint8_t>(128.0f + 127.0f * std::sin(time_counter * 0.5f));
                auto b = static_cast<std::uint8_t>(255.0f - color_factor);

                std::size_t buffer_idx = static_cast<std::size_t>(y * BUFFER_WIDTH + x);
                pixel_buffer[buffer_idx] = static_cast<std::uint32_t>((r << 24) | (g << 16) | (b << 8) | 0xFF);
            }
        }

        SDL_UpdateTexture(
            wave_texture,
            nullptr,
            pixel_buffer.data(),
            BUFFER_WIDTH * static_cast<std::int32_t>(sizeof(std::uint32_t))
        );

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, wave_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(wave_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
