// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

const std::int32_t FIELD_WIDTH = 400;
const std::int32_t FIELD_HEIGHT = 300;
const std::int32_t NUM_PARTICLES = 3000;

struct Walker {
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
        "SDL2 Crystal Growth (DLA Fractal) Demo",
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

    SDL_Texture* field_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        FIELD_WIDTH,
        FIELD_HEIGHT
    );

    if (field_texture == nullptr)
    {
        std::println(std::cerr, "Failed to create texture! Error: {}", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint32_t> pixels(static_cast<std::size_t>(FIELD_WIDTH * FIELD_HEIGHT), 0x000000FF);
    std::vector<std::uint8_t> grid(static_cast<std::size_t>(FIELD_WIDTH * FIELD_HEIGHT), 0);

    std::int32_t center_x = FIELD_WIDTH / 2;
    std::int32_t center_y = FIELD_HEIGHT / 2;
    grid[static_cast<std::size_t>(center_y * FIELD_WIDTH + center_x)] = 1;
    pixels[static_cast<std::size_t>(center_y * FIELD_WIDTH + center_x)] = 0xFFFFFFFF;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::int32_t> dist_x(1, FIELD_WIDTH - 2);
    std::uniform_int_distribution<std::int32_t> dist_y(1, FIELD_HEIGHT - 2);
    std::uniform_int_distribution<std::int32_t> dist_dir(-1, 1);

    std::vector<Walker> walkers;
    walkers.reserve(static_cast<std::size_t>(NUM_PARTICLES));
    for (std::int32_t i = 0; i < NUM_PARTICLES; ++i)
    {
        walkers.push_back(Walker{ dist_x(rng), dist_y(rng) });
    }

    auto has_frozen_neighbor = [&grid](std::int32_t x, std::int32_t y) -> bool {
        for (std::int32_t ny = -1; ny <= 1; ++ny)
        {
            for (std::int32_t nx = -1; nx <= 1; ++nx)
            {
                if (grid[static_cast<std::size_t>((y + ny) * FIELD_WIDTH + (x + nx))] == 1)
                {
                    return true;
                }
            }
        }
        return false;
        };

    bool isRunning = true;
    SDL_Event event;
    std::uint32_t crystal_color_counter = 0;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        // Делаем несколько шагов симуляции за кадр для ускорения роста
        for (std::int32_t step = 0; step < 10; ++step)
        {
            for (auto& w : walkers)
            {
                w.x += dist_dir(rng);
                w.y += dist_dir(rng);

                if (w.x < 1 || w.x >= FIELD_WIDTH - 1 || w.y < 1 || w.y >= FIELD_HEIGHT - 1)
                {
                    w.x = dist_x(rng);
                    w.y = dist_y(rng);
                    continue;
                }

                if (has_frozen_neighbor(w.x, w.y))
                {
                    std::size_t idx = static_cast<std::size_t>(w.y * FIELD_WIDTH + w.x);
                    grid[idx] = 1;

                    // Плавный градиент цвета по мере роста кристалла
                    crystal_color_counter++;
                    auto r = static_cast<std::uint8_t>(100 + (crystal_color_counter / 50) % 155);
                    auto g = static_cast<std::uint8_t>(150 + (crystal_color_counter / 100) % 105);
                    auto b = static_cast<std::uint8_t>(255);

                    pixels[idx] = static_cast<std::uint32_t>((r << 24) | (g << 16) | (b << 8) | 0xFF);

                    // Респавним частицу на случайном краю
                    w.x = dist_x(rng);
                    w.y = dist_y(rng);
                }
            }
        }

        // Отрисовка блуждающих частиц (временный слой)
        std::vector<std::uint32_t> temp_pixels = pixels;
        for (const auto& w : walkers)
        {
            std::size_t idx = static_cast<std::size_t>(w.y * FIELD_WIDTH + w.x);
            temp_pixels[idx] = 0x00FF00FF; // Зеленые точки — активный газ/раствор
        }

        SDL_UpdateTexture(
            field_texture,
            nullptr,
            temp_pixels.data(),
            FIELD_WIDTH * static_cast<std::int32_t>(sizeof(std::uint32_t))
        );

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, field_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(field_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
