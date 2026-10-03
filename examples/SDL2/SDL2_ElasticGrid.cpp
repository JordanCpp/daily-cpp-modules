// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

const std::int32_t CELL_SIZE = 25;
const std::int32_t COLS = SCREEN_WIDTH / CELL_SIZE + 1;
const std::int32_t ROWS = SCREEN_HEIGHT / CELL_SIZE + 1;

const float FORCE_RADIUS = 120.0f;
const float ELASTICITY = 0.1f;
const float DAMPING = 0.85f;

struct GridPoint {
    float base_x;
    float base_y;
    float x;
    float y;
    float vx;
    float vy;
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
        "SDL2 Elastic Grid Demo",
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

    std::vector<GridPoint> grid;
    grid.reserve(static_cast<std::size_t>(COLS * ROWS));

    for (std::int32_t r = 0; r < ROWS; ++r)
    {
        for (std::int32_t c = 0; c < COLS; ++c)
        {
            float bx = static_cast<float>(c * CELL_SIZE);
            float by = static_cast<float>(r * CELL_SIZE);
            grid.push_back(GridPoint{ bx, by, bx, by, 0.0f, 0.0f });
        }
    }

    auto get_node_idx = [](std::int32_t c, std::int32_t r) -> std::size_t {
        return static_cast<std::size_t>(r * COLS + c);
        };

    bool isRunning = true;
    SDL_Event event;

    float mouse_x = -1000.0f;
    float mouse_y = -1000.0f;

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
                mouse_x = static_cast<float>(event.motion.x);
                mouse_y = static_cast<float>(event.motion.y);
            }
        }

        for (auto& node : grid)
        {
            float dx = node.x - mouse_x;
            float dy = node.y - mouse_y;
            float sq_dist = dx * dx + dy * dy;

            if (sq_dist < FORCE_RADIUS * FORCE_RADIUS)
            {
                float dist = std::sqrt(sq_dist);
                if (dist > 0.001f)
                {
                    float force = (FORCE_RADIUS - dist) / FORCE_RADIUS;
                    node.vx += (dx / dist) * force * 8.0f;
                    node.vy += (dy / dist) * force * 8.0f;
                }
            }

            float home_dx = node.base_x - node.x;
            float home_dy = node.base_y - node.y;

            node.vx += home_dx * ELASTICITY;
            node.vy += home_dy * ELASTICITY;

            node.vx *= DAMPING;
            node.vy *= DAMPING;

            node.x += node.vx;
            node.y += node.vy;
        }

        SDL_SetRenderDrawColor(renderer, 20, 22, 28, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 65, 105, 225, 255);
        for (std::int32_t r = 0; r < ROWS; ++r)
        {
            for (std::int32_t c = 0; c < COLS; ++c)
            {
                if (c < COLS - 1)
                {
                    const auto& n1 = grid[get_node_idx(c, r)];
                    const auto& n2 = grid[get_node_idx(c + 1, r)];
                    SDL_RenderDrawLine(
                        renderer,
                        static_cast<std::int32_t>(n1.x),
                        static_cast<std::int32_t>(n1.y),
                        static_cast<std::int32_t>(n2.x),
                        static_cast<std::int32_t>(n2.y)
                    );
                }
                if (r < ROWS - 1)
                {
                    const auto& n1 = grid[get_node_idx(c, r)];
                    const auto& n2 = grid[get_node_idx(c, r + 1)];
                    SDL_RenderDrawLine(
                        renderer,
                        static_cast<std::int32_t>(n1.x),
                        static_cast<std::int32_t>(n1.y),
                        static_cast<std::int32_t>(n2.x),
                        static_cast<std::int32_t>(n2.y)
                    );
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
