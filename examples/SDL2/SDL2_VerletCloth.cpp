// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float GRAVITY = 400.0f;

struct PointMass {
    float x;
    float y;
    float px;
    float py;
    bool is_pinned;
};

struct Link {
    std::size_t p1;
    std::size_t p2;
    float rest_length;
    bool is_broken;
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
        "SDL2 Verlet Cloth Demo",
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

    const int cloth_width = 25;
    const int cloth_height = 20;
    const float spacing = 18.0f;
    const float start_x = static_cast<float>(SCREEN_WIDTH - (cloth_width - 1) * static_cast<int>(spacing)) / 2.0f;
    const float start_y = 50.0f;

    std::vector<PointMass> points;
    points.reserve(static_cast<std::size_t>(cloth_width * cloth_height));

    for (int y = 0; y < cloth_height; ++y)
    {
        for (int x = 0; x < cloth_width; ++x)
        {
            float px = start_x + static_cast<float>(x) * spacing;
            float py = start_y + static_cast<float>(y) * spacing;
            bool pinned = (y == 0 && (x % 2 == 0));
            points.push_back(PointMass{ px, py, px, py, pinned });
        }
    }

    std::vector<Link> links;
    links.reserve(static_cast<std::size_t>(cloth_width * cloth_height * 2));

    auto get_idx = [](int x, int y) -> std::size_t {
        return static_cast<std::size_t>(y * cloth_width + x);
        };

    for (int y = 0; y < cloth_height; ++y)
    {
        for (int x = 0; x < cloth_width; ++x)
        {
            if (x < cloth_width - 1)
            {
                links.push_back(Link{ get_idx(x, y), get_idx(x + 1, y), spacing, false });
            }
            if (y < cloth_height - 1)
            {
                links.push_back(Link{ get_idx(x, y), get_idx(x, y + 1), spacing, false });
            }
        }
    }

    bool isRunning = true;
    SDL_Event event;

    int mouse_x = 0;
    int mouse_y = 0;
    int prev_mouse_x = 0;
    int prev_mouse_y = 0;
    bool is_left_pressed = false;
    bool is_right_pressed = false;
    std::size_t grabbed_node = 0;
    bool node_found = false;

    auto last_time = std::chrono::steady_clock::now();

    while (isRunning)
    {
        prev_mouse_x = mouse_x;
        prev_mouse_y = mouse_y;

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
                    is_left_pressed = true;
                    float min_dist = 400.0f;
                    node_found = false;
                    for (std::size_t i = 0; i < points.size(); ++i)
                    {
                        float dx = points[i].x - static_cast<float>(event.button.x);
                        float dy = points[i].y - static_cast<float>(event.button.y);
                        float dist = dx * dx + dy * dy;
                        if (dist < min_dist)
                        {
                            min_dist = dist;
                            grabbed_node = i;
                            node_found = true;
                        }
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    is_right_pressed = true;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_left_pressed = false;
                    node_found = false;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    is_right_pressed = false;
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

        if (is_right_pressed)
        {
            float mx1 = static_cast<float>(prev_mouse_x);
            float my1 = static_cast<float>(prev_mouse_y);
            float mx2 = static_cast<float>(mouse_x);
            float my2 = static_cast<float>(mouse_y);

            for (auto& link : links)
            {
                if (link.is_broken) continue;

                float cx1 = points[link.p1].x;
                float cy1 = points[link.p1].y;
                float cx2 = points[link.p2].x;
                float cy2 = points[link.p2].y;

                float den = (mx1 - mx2) * (cy1 - cy2) - (my1 - my2) * (cx1 - cx2);
                if (std::abs(den) > 0.001f)
                {
                    float t = ((mx1 - cx1) * (cy1 - cy2) - (my1 - cy1) * (cx1 - cx2)) / den;
                    float u = -((mx1 - mx2) * (my1 - cy1) - (my1 - my2) * (mx1 - cx1)) / den;

                    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f)
                    {
                        link.is_broken = true;
                    }
                }
            }
        }

        if (is_left_pressed && node_found && grabbed_node < points.size())
        {
            points[grabbed_node].x = static_cast<float>(mouse_x);
            points[grabbed_node].y = static_cast<float>(mouse_y);
            points[grabbed_node].px = static_cast<float>(mouse_x);
            points[grabbed_node].py = static_cast<float>(mouse_y);
        }

        for (auto& p : points)
        {
            if (p.is_pinned) continue;

            float vx = (p.x - p.px) * 0.99f;
            float vy = (p.y - p.py) * 0.99f;

            p.px = p.x;
            p.py = p.y;

            p.x += vx;
            p.y += vy + GRAVITY * dt * dt;
        }

        for (int step = 0; step < 5; ++step)
        {
            for (const auto& link : links)
            {
                if (link.is_broken) continue;

                auto& p1 = points[link.p1];
                auto& p2 = points[link.p2];

                float dx = p2.x - p1.x;
                float dy = p2.y - p1.y;
                float dist = std::sqrt(dx * dx + dy * dy);
                if (dist < 0.001f) dist = 0.001f;

                float diff = (link.rest_length - dist) / dist * 0.5f;
                float offsetX = dx * diff;
                float offsetY = dy * diff;

                if (!p1.is_pinned)
                {
                    p1.x -= offsetX;
                    p1.y -= offsetY;
                }
                if (!p2.is_pinned)
                {
                    p2.x += offsetX;
                    p2.y += offsetY;
                }
            }

            for (auto& p : points)
            {
                if (p.x < 0.0f) p.x = 0.0f;
                if (p.x > static_cast<float>(SCREEN_WIDTH)) p.x = static_cast<float>(SCREEN_WIDTH);
                if (p.y < 0.0f) p.y = 0.0f;
                if (p.y > static_cast<float>(SCREEN_HEIGHT)) p.y = static_cast<float>(SCREEN_HEIGHT);
            }
        }

        SDL_SetRenderDrawColor(renderer, 15, 15, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 200, 220, 255);
        for (const auto& link : links)
        {
            if (link.is_broken) continue;
            SDL_RenderDrawLine(
                renderer,
                static_cast<int>(points[link.p1].x),
                static_cast<int>(points[link.p1].y),
                static_cast<int>(points[link.p2].x),
                static_cast<int>(points[link.p2].y)
            );
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
