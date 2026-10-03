// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

const std::int32_t BUFFER_WIDTH = 400;
const std::int32_t BUFFER_HEIGHT = 300;

const float DAMPING = 0.99f;

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
        "SDL2 Interactive Wave Equation Demo",
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

    std::size_t total_cells = static_cast<std::size_t>(BUFFER_WIDTH * BUFFER_HEIGHT);
    std::vector<float> current_wave(total_cells, 0.0f);
    std::vector<float> previous_wave(total_cells, 0.0f);
    std::vector<std::uint32_t> pixel_buffer(total_cells, 0);

    bool isRunning = true;
    SDL_Event event;
    bool is_mouse_pressed = false;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_mouse_pressed = true;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_mouse_pressed = false;
                }
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                if (is_mouse_pressed)
                {
                    std::int32_t m_x = (event.motion.x * BUFFER_WIDTH) / SCREEN_WIDTH;
                    std::int32_t m_y = (event.motion.y * BUFFER_HEIGHT) / SCREEN_HEIGHT;

                    if (m_x > 2 && m_x < BUFFER_WIDTH - 2 && m_y > 2 && m_y < BUFFER_HEIGHT - 2)
                    {
                        for (std::int32_t dy = -1; dy <= 1; ++dy)
                        {
                            for (std::int32_t dx = -1; dx <= 1; ++dx)
                            {
                                std::size_t idx = static_cast<std::size_t>((m_y + dy) * BUFFER_WIDTH + (m_x + dx));
                                current_wave[idx] = 512.0f;
                            }
                        }
                    }
                }
            }
        }

        for (std::int32_t y = 1; y < BUFFER_HEIGHT - 1; ++y)
        {
            for (std::int32_t x = 1; x < BUFFER_WIDTH - 1; ++x)
            {
                std::size_t idx = static_cast<std::size_t>(y * BUFFER_WIDTH + x);

                float neighbors_sum =
                    current_wave[static_cast<std::size_t>(y * BUFFER_WIDTH + (x - 1))] +
                    current_wave[static_cast<std::size_t>(y * BUFFER_WIDTH + (x + 1))] +
                    current_wave[static_cast<std::size_t>((y - 1) * BUFFER_WIDTH + x)] +
                    current_wave[static_cast<std::size_t>((y + 1) * BUFFER_WIDTH + x)];

                float next_val = (neighbors_sum * 0.5f) - previous_wave[idx];

                next_val *= DAMPING;
                previous_wave[idx] = next_val;
            }
        }

        std::swap(current_wave, previous_wave);

        for (std::int32_t y = 1; y < BUFFER_HEIGHT - 1; ++y)
        {
            for (std::int32_t x = 1; x < BUFFER_WIDTH - 1; ++x)
            {
                std::size_t idx = static_cast<std::size_t>(y * BUFFER_WIDTH + x);

                float diff_x = current_wave[static_cast<std::size_t>(y * BUFFER_WIDTH + (x + 1))] - current_wave[idx];
                float diff_y = current_wave[static_cast<std::size_t>((y + 1) * BUFFER_WIDTH + x)] - current_wave[idx];

                float light_offset = diff_x - diff_y;

                std::int32_t base_r = 10;
                std::int32_t base_g = 70;
                std::int32_t base_b = 150;

                auto r = static_cast<std::uint8_t>(std::clamp(base_r + static_cast<std::int32_t>(light_offset), 0, 255));
                auto g = static_cast<std::uint8_t>(std::clamp(base_g + static_cast<std::int32_t>(light_offset * 1.5f), 0, 255));
                auto b = static_cast<std::uint8_t>(std::clamp(base_b + static_cast<std::int32_t>(light_offset * 2.0f), 0, 255));

                pixel_buffer[idx] = static_cast<std::uint32_t>((r << 24) | (g << 16) | (b << 8) | 0xFF);
            }
        }

        SDL_UpdateTexture(
            wave_texture,
            nullptr,
            pixel_buffer.data(),
            BUFFER_WIDTH * static_cast<std::int32_t>(sizeof(std::uint32_t))
        );

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
