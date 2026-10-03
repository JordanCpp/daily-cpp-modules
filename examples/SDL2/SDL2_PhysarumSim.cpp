// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

const std::int32_t MAP_WIDTH = 400;
const std::int32_t MAP_HEIGHT = 300;
const std::int32_t NUM_AGENTS = 8000;

const float SENSOR_ANGLE = 45.0f * 3.14159265f / 180.0f;
const float SENSOR_DIST = 9.0f;
const float TURN_SPEED = 0.4f;
const float EVAPORATE_SPEED = 0.96f;

struct SlimeAgent {
    float x;
    float y;
    float angle;
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
        "SDL2 Physarum Slime Simulation Demo",
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

    SDL_Texture* map_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        MAP_WIDTH,
        MAP_HEIGHT
    );

    if (map_texture == nullptr)
    {
        std::println(std::cerr, "Failed to create texture! Error: {}", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<float> trail_map(static_cast<std::size_t>(MAP_WIDTH * MAP_HEIGHT), 0.0f);
    std::vector<std::uint32_t> pixel_buffer(static_cast<std::size_t>(MAP_WIDTH * MAP_HEIGHT), 0);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist_x(10.0f, static_cast<float>(MAP_WIDTH) - 10.0f);
    std::uniform_real_distribution<float> dist_y(10.0f, static_cast<float>(MAP_HEIGHT) - 10.0f);
    std::uniform_real_distribution<float> dist_angle(0.0f, 2.0f * 3.14159265f);

    std::vector<SlimeAgent> agents;
    agents.reserve(static_cast<std::size_t>(NUM_AGENTS));
    for (std::int32_t i = 0; i < NUM_AGENTS; ++i)
    {
        agents.push_back(SlimeAgent{ dist_x(rng), dist_y(rng), dist_angle(rng) });
    }

    auto sense = [&trail_map](const SlimeAgent& agent, float angle_offset) -> float {
        float sense_angle = agent.angle + angle_offset;
        auto sx = static_cast<std::int32_t>(agent.x + std::cos(sense_angle) * SENSOR_DIST);
        auto sy = static_cast<std::int32_t>(agent.y + std::sin(sense_angle) * SENSOR_DIST);

        if (sx >= 0 && sx < MAP_WIDTH && sy >= 0 && sy < MAP_HEIGHT)
        {
            return trail_map[static_cast<std::size_t>(sy * MAP_WIDTH + sx)];
        }
        return 0.0f;
        };

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

        for (auto& a : agents)
        {
            float weight_fwd = sense(a, 0.0f);
            float weight_left = sense(a, -SENSOR_ANGLE);
            float weight_right = sense(a, SENSOR_ANGLE);

            if (weight_fwd > weight_left && weight_fwd > weight_right)
            {
            }
            else if (weight_fwd < weight_left && weight_fwd < weight_right)
            {
                a.angle += (rng() % 2 == 0 ? 1.0f : -1.0f) * TURN_SPEED;
            }
            else if (weight_left > weight_right)
            {
                a.angle -= TURN_SPEED;
            }
            else if (weight_right > weight_left)
            {
                a.angle += TURN_SPEED;
            }

            a.x += std::cos(a.angle) * 1.0f;
            a.y += std::sin(a.angle) * 1.0f;

            if (a.x < 0.0f || a.x >= static_cast<float>(MAP_WIDTH) || a.y < 0.0f || a.y >= static_cast<float>(MAP_HEIGHT))
            {
                a.x = std::clamp(a.x, 0.0f, static_cast<float>(MAP_WIDTH) - 1.0f);
                a.y = std::clamp(a.y, 0.0f, static_cast<float>(MAP_HEIGHT) - 1.0f);
                a.angle = dist_angle(rng);
            }

            std::size_t idx = static_cast<std::size_t>(static_cast<std::int32_t>(a.y) * MAP_WIDTH + static_cast<std::int32_t>(a.x));
            trail_map[idx] = 1.0f;
        }

        std::vector<float> next_trail = trail_map;
        for (std::int32_t y = 1; y < MAP_HEIGHT - 1; ++y)
        {
            for (std::int32_t x = 1; x < MAP_WIDTH - 1; ++x)
            {
                float sum = 0.0f;
                for (std::int32_t ny = -1; ny <= 1; ++ny)
                {
                    for (std::int32_t nx = -1; nx <= 1; ++nx)
                    {
                        sum += trail_map[static_cast<std::size_t>((y + ny) * MAP_WIDTH + (x + nx))];
                    }
                }

                std::size_t idx = static_cast<std::size_t>(y * MAP_WIDTH + x);
                float blurred = sum / 9.0f;
                next_trail[idx] = blurred * EVAPORATE_SPEED;

                auto intensity = static_cast<std::uint8_t>(next_trail[idx] * 255.0f);

                auto r = static_cast<std::uint8_t>(std::min(255, static_cast<std::int32_t>(intensity) * 2));
                auto g = static_cast<std::uint8_t>(static_cast<std::int32_t>(intensity));
                std::uint8_t b = 0;

                pixel_buffer[idx] = static_cast<std::uint32_t>((r << 24) | (g << 16) | (b << 8) | 0xFF);
            }
        }
        trail_map = next_trail;

        SDL_UpdateTexture(
            map_texture,
            nullptr,
            pixel_buffer.data(),
            MAP_WIDTH * static_cast<std::int32_t>(sizeof(std::uint32_t))
        );

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, map_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(map_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
