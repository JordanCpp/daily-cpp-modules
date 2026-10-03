// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int NUM_AGENTS = 400;
const float VISUAL_RANGE = 40.0f;
const float PROTECTED_RANGE = 8.0f;
const float MATCHING_FACTOR = 0.05f;
const float COHESION_FACTOR = 0.005f;
const float SEPARATION_FACTOR = 0.05f;
const float MOUSE_EVADE_FACTOR = 0.2f;
const float MOUSE_RANGE = 80.0f;
const float MIN_SPEED = 150.0f;
const float MAX_SPEED = 300.0f;

struct Agent {
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
        "SDL2 Autonomous Agents (Boids) Demo",
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

    std::vector<Agent> agents;
    agents.reserve(static_cast<std::size_t>(NUM_AGENTS));

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist_x(50.0f, static_cast<float>(SCREEN_WIDTH) - 50.0f);
    std::uniform_real_distribution<float> dist_y(50.0f, static_cast<float>(SCREEN_HEIGHT) - 50.0f);
    std::uniform_real_distribution<float> dist_v(-100.0f, 100.0f);

    for (int i = 0; i < NUM_AGENTS; ++i)
    {
        agents.push_back(Agent{ dist_x(rng), dist_y(rng), dist_v(rng), dist_v(rng) });
    }

    bool isRunning = true;
    SDL_Event event;

    int current_mouse_x = 0;
    int current_mouse_y = 0;

    auto last_time = std::chrono::steady_clock::now();

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
                current_mouse_x = event.motion.x;
                current_mouse_y = event.motion.y;
            }
        }

        auto current_time = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(current_time - last_time).count();
        last_time = current_time;

        if (dt > 0.02f) dt = 0.02f;

        std::vector<Agent> next_agents = agents;

        for (std::size_t i = 0; i < agents.size(); ++i)
        {
            auto& a = next_agents[i];

            float close_dx = 0.0f;
            float close_dy = 0.0f;
            float xvel_avg = 0.0f;
            float yvel_avg = 0.0f;
            float xpos_avg = 0.0f;
            float ypos_avg = 0.0f;
            int neighboring_agents = 0;

            for (std::size_t j = 0; j < agents.size(); ++j)
            {
                if (i == j) continue;

                float dx = agents[i].x - agents[j].x;
                float dy = agents[i].y - agents[j].y;

                float sq_dist = dx * dx + dy * dy;

                if (sq_dist < PROTECTED_RANGE * PROTECTED_RANGE)
                {
                    close_dx += dx;
                    close_dy += dy;
                }
                else if (sq_dist < VISUAL_RANGE * VISUAL_RANGE)
                {
                    xvel_avg += agents[j].vx;
                    yvel_avg += agents[j].vy;
                    xpos_avg += agents[j].x;
                    ypos_avg += agents[j].y;
                    neighboring_agents++;
                }
            }

            if (neighboring_agents > 0)
            {
                float count_f = static_cast<float>(neighboring_agents);
                xvel_avg /= count_f;
                yvel_avg /= count_f;
                xpos_avg /= count_f;
                ypos_avg /= count_f;

                a.vx += (xvel_avg - agents[i].vx) * MATCHING_FACTOR;
                a.vy += (yvel_avg - agents[i].vy) * MATCHING_FACTOR;

                a.vx += (xpos_avg - agents[i].x) * COHESION_FACTOR;
                a.vy += (ypos_avg - agents[i].y) * COHESION_FACTOR;
            }

            a.vx += close_dx * SEPARATION_FACTOR;
            a.vy += close_dy * SEPARATION_FACTOR;

            float m_dx = agents[i].x - static_cast<float>(current_mouse_x);
            float m_dy = agents[i].y - static_cast<float>(current_mouse_y);
            float m_sq_dist = m_dx * m_dx + m_dy * m_dy;

            if (m_sq_dist < MOUSE_RANGE * MOUSE_RANGE)
            {
                float m_dist = std::sqrt(m_sq_dist);
                if (m_dist > 0.001f)
                {
                    a.vx += (m_dx / m_dist) * MOUSE_EVADE_FACTOR * (MOUSE_RANGE - m_dist);
                    a.vy += (m_dy / m_dist) * MOUSE_EVADE_FACTOR * (MOUSE_RANGE - m_dist);
                }
            }

            const float margin = 50.0f;
            const float turn_factor = 15.0f;
            if (a.x < margin) a.vx += turn_factor;
            if (a.x > static_cast<float>(SCREEN_WIDTH) - margin) a.vx -= turn_factor;
            if (a.y < margin) a.vy += turn_factor;
            if (a.y > static_cast<float>(SCREEN_HEIGHT) - margin) a.vy -= turn_factor;

            float speed = std::sqrt(a.vx * a.vx + a.vy * a.vy);
            if (speed < 0.001f) speed = 0.001f;

            if (speed < MIN_SPEED)
            {
                a.vx = (a.vx / speed) * MIN_SPEED;
                a.vy = (a.vy / speed) * MIN_SPEED;
            }
            else if (speed > MAX_SPEED)
            {
                a.vx = (a.vx / speed) * MAX_SPEED;
                a.vy = (a.vy / speed) * MAX_SPEED;
            }

            a.x += a.vx * dt;
            a.y += a.vy * dt;
        }

        agents = next_agents;

        SDL_SetRenderDrawColor(renderer, 10, 15, 25, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
        for (const auto& boid : agents)
        {
            float speed = std::sqrt(boid.vx * boid.vx + boid.vy * boid.vy);
            if (speed < 0.001f) speed = 0.001f;

            float dir_x = boid.vx / speed;
            float dir_y = boid.vy / speed;

            int x1 = static_cast<int>(boid.x + dir_x * 8.0f);
            int y1 = static_cast<int>(boid.y + dir_y * 8.0f);

            int x2 = static_cast<int>(boid.x - dir_x * 4.0f + dir_y * 3.0f);
            int y2 = static_cast<int>(boid.y - dir_y * 4.0f - dir_x * 3.0f);

            int x3 = static_cast<int>(boid.x - dir_x * 4.0f - dir_y * 3.0f);
            int y3 = static_cast<int>(boid.y - dir_y * 4.0f + dir_x * 3.0f);

            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
            SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
            SDL_RenderDrawLine(renderer, x3, y3, x1, y1);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
