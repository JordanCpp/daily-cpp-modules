// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float GRAVITY = 500.0f;
const float DAMPING = 0.98f;

struct PointMass {
    float x;
    float y;
    float px;
    float py;
    float vx;
    float vy;
    float mass;
};

struct Spring {
    std::size_t i;
    std::size_t j;
    float rest_length;
    float stiffness;
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
        "SDL2 Soft Body Physics Demo",
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

    std::vector<PointMass> points;
    std::vector<Spring> springs;

    const int rows = 6;
    const int cols = 6;
    const float spacing = 40.0f;
    const float start_x = 300.0f;
    const float start_y = 100.0f;

    points.reserve(static_cast<std::size_t>(rows * cols));
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            float x = start_x + static_cast<float>(c) * spacing;
            float y = start_y + static_cast<float>(r) * spacing;
            points.push_back(PointMass{ x, y, x, y, 0.0f, 0.0f, 1.0f });
        }
    }

    auto get_index = [](int r, int c) -> std::size_t {
        return static_cast<std::size_t>(r * cols + c);
        };

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            std::size_t current = get_index(r, c);
            if (c < cols - 1)
                springs.push_back(Spring{ current, get_index(r, c + 1), spacing, 400.0f });
            if (r < rows - 1)
                springs.push_back(Spring{ current, get_index(r + 1, c), spacing, 400.0f });
            if (c < cols - 1 && r < rows - 1)
            {
                float diag = std::sqrt(spacing * spacing + spacing * spacing);
                springs.push_back(Spring{ current, get_index(r + 1, c + 1), diag, 400.0f });
                springs.push_back(Spring{ get_index(r, c + 1), get_index(r + 1, c), diag, 400.0f });
            }
        }
    }

    bool isRunning = true;
    SDL_Event event;
    auto last_time = std::chrono::steady_clock::now();

    int mouse_x = 0;
    int mouse_y = 0;
    bool is_grabbing = false;
    std::size_t grabbed_node = 0;

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
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    float min_dist = 999999.0f;
                    for (std::size_t i = 0; i < points.size(); ++i)
                    {
                        float dx = points[i].x - static_cast<float>(mouse_x);
                        float dy = points[i].y - static_cast<float>(mouse_y);
                        float dist = dx * dx + dy * dy;
                        if (dist < min_dist)
                        {
                            min_dist = dist;
                            grabbed_node = i;
                        }
                    }
                    if (min_dist < 2500.0f)
                    {
                        is_grabbing = true;
                    }
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_grabbing = false;
                }
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
            }
        }

        auto current_time = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(current_time - last_time).count();
        last_time = current_time;

        if (dt > 0.02f) dt = 0.02f;

        if (is_grabbing && grabbed_node < points.size())
        {
            points[grabbed_node].x = static_cast<float>(mouse_x);
            points[grabbed_node].y = static_cast<float>(mouse_y);
            points[grabbed_node].vx = 0.0f;
            points[grabbed_node].vy = 0.0f;
        }

        for (auto& p : points)
        {
            p.vy += GRAVITY * dt;
            p.x += p.vx * dt;
            p.y += p.vy * dt;
        }

        for (int step = 0; step < 8; ++step)
        {
            float sub_dt = dt / 8.0f;
            for (const auto& spring : springs)
            {
                auto& p1 = points[spring.i];
                auto& p2 = points[spring.j];

                float dx = p2.x - p1.x;
                float dy = p2.y - p1.y;
                float dist = std::sqrt(dx * dx + dy * dy);
                if (dist < 0.001f) dist = 0.001f;

                float delta = dist - spring.rest_length;
                float forceX = (dx / dist) * delta * spring.stiffness;
                float forceY = (dy / dist) * delta * spring.stiffness;

                if (!is_grabbing || spring.i != grabbed_node)
                {
                    p1.vx += (forceX / p1.mass) * sub_dt;
                    p1.vy += (forceY / p1.mass) * sub_dt;
                }
                if (!is_grabbing || spring.j != grabbed_node)
                {
                    p2.vx -= (forceX / p2.mass) * sub_dt;
                    p2.vy -= (forceY / p2.mass) * sub_dt;
                }
            }
        }

        const float radius = 10.0f;
        for (std::size_t i = 0; i < points.size(); ++i)
        {
            if (is_grabbing && i == grabbed_node) continue;

            auto& p = points[i];
            p.vx *= DAMPING;
            p.vy *= DAMPING;

            if (p.y > static_cast<float>(SCREEN_HEIGHT) - radius)
            {
                p.y = static_cast<float>(SCREEN_HEIGHT) - radius;
                p.vy = -p.vy * 0.3f;
            }
            if (p.x < radius)
            {
                p.x = radius;
                p.vx = -p.vx * 0.3f;
            }
            if (p.x > static_cast<float>(SCREEN_WIDTH) - radius)
            {
                p.x = static_cast<float>(SCREEN_WIDTH) - radius;
                p.vx = -p.vx * 0.3f;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
        for (const auto& spring : springs)
        {
            SDL_RenderDrawLine(
                renderer,
                static_cast<int>(points[spring.i].x),
                static_cast<int>(points[spring.i].y),
                static_cast<int>(points[spring.j].x),
                static_cast<int>(points[spring.j].y)
            );
        }

        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        for (const auto& p : points)
        {
            SDL_Rect r{ static_cast<int>(p.x) - 4, static_cast<int>(p.y) - 4, 8, 8 };
            SDL_RenderFillRect(renderer, &r);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
