// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

const std::int32_t MAP_WIDTH = 16;
const std::int32_t MAP_HEIGHT = 16;

const std::array<std::array<std::int32_t, MAP_HEIGHT>, MAP_WIDTH> MAP = { {
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
    {{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1}},
    {{1,0,1,1,0,0,1,0,1,1,1,1,0,1,0,1}},
    {{1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1}},
    {{1,0,1,0,1,1,1,1,1,0,0,1,0,1,0,1}},
    {{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1}},
    {{1,0,1,0,1,0,0,0,1,0,1,1,1,1,0,1}},
    {{1,0,1,0,1,1,0,1,1,0,1,0,0,1,0,1}},
    {{1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1}},
    {{1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,1}},
    {{1,0,0,0,0,1,0,1,0,0,0,0,1,1,0,1}},
    {{1,1,1,0,0,1,0,1,0,1,1,0,1,1,0,1}},
    {{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1}},
    {{1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1}},
    {{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}},
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}
} };

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
        "SDL2 3D Raycaster Demo",
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

    float posX = 3.5f;
    float posY = 3.5f;
    float dirX = -1.0f;
    float dirY = 0.0f;
    float planeX = 0.0f;
    float planeY = 0.66f;

    bool isRunning = true;
    SDL_Event event;

    std::unordered_map<SDL_Keycode, bool> keys;
    keys[SDLK_w] = false;
    keys[SDLK_s] = false;
    keys[SDLK_a] = false;
    keys[SDLK_d] = false;

    auto last_time = std::chrono::steady_clock::now();

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (keys.contains(event.key.keysym.sym))
                {
                    keys[event.key.keysym.sym] = true;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                if (keys.contains(event.key.keysym.sym))
                {
                    keys[event.key.keysym.sym] = false;
                }
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                float rotSpeed = static_cast<float>(event.motion.xrel) * -0.003f;
                float oldDirX = dirX;
                dirX = dirX * std::cos(rotSpeed) - dirY * std::sin(rotSpeed);
                dirY = oldDirX * std::sin(rotSpeed) + dirY * std::cos(rotSpeed);
                float oldPlaneX = planeX;
                planeX = planeX * std::cos(rotSpeed) - planeY * std::sin(rotSpeed);
                planeY = oldPlaneX * std::sin(rotSpeed) + planeY * std::cos(rotSpeed);
            }
        }

        auto current_time = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(current_time - last_time).count();
        last_time = current_time;

        if (dt > 0.05f) dt = 0.05f;

        float moveSpeed = dt * 4.0f;

        if (keys[SDLK_w])
        {
            if (MAP[static_cast<std::size_t>(posX + dirX * moveSpeed)][static_cast<std::size_t>(posY)] == 0) posX += dirX * moveSpeed;
            if (MAP[static_cast<std::size_t>(posX)][static_cast<std::size_t>(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
        }
        if (keys[SDLK_s])
        {
            if (MAP[static_cast<std::size_t>(posX - dirX * moveSpeed)][static_cast<std::size_t>(posY)] == 0) posX -= dirX * moveSpeed;
            if (MAP[static_cast<std::size_t>(posX)][static_cast<std::size_t>(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
        }
        if (keys[SDLK_d])
        {
            if (MAP[static_cast<std::size_t>(posX + planeX * moveSpeed)][static_cast<std::size_t>(posY)] == 0) posX += planeX * moveSpeed;
            if (MAP[static_cast<std::size_t>(posX)][static_cast<std::size_t>(posY + planeY * moveSpeed)] == 0) posY += planeY * moveSpeed;
        }
        if (keys[SDLK_a])
        {
            if (MAP[static_cast<std::size_t>(posX - planeX * moveSpeed)][static_cast<std::size_t>(posY)] == 0) posX -= planeX * moveSpeed;
            if (MAP[static_cast<std::size_t>(posX)][static_cast<std::size_t>(posY - planeY * moveSpeed)] == 0) posY -= planeY * moveSpeed;
        }

        SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 40, 45, 60, 255);
        SDL_Rect ceiling_rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
        SDL_RenderFillRect(renderer, &ceiling_rect);

        SDL_SetRenderDrawColor(renderer, 30, 35, 40, 255);
        SDL_Rect floor_rect{ 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
        SDL_RenderFillRect(renderer, &floor_rect);

        for (std::int32_t x = 0; x < SCREEN_WIDTH; ++x)
        {
            float cameraX = 2.0f * static_cast<float>(x) / static_cast<float>(SCREEN_WIDTH) - 1.0f;
            float rayDirX = dirX + planeX * cameraX;
            float rayDirY = dirY + planeY * cameraX;

            auto mapX = static_cast<std::int32_t>(posX);
            auto mapY = static_cast<std::int32_t>(posY);

            float sideDistX = 0.0f;
            float sideDistY = 0.0f;

            float deltaDistX = (rayDirX == 0.0f) ? 1e30f : std::abs(1.0f / rayDirX);
            float deltaDistY = (rayDirY == 0.0f) ? 1e30f : std::abs(1.0f / rayDirY);
            float perpWallDist = 0.0f;

            std::int32_t stepX = 0;
            std::int32_t stepY = 0;

            std::int32_t hit = 0;
            std::int32_t side = 0;

            if (rayDirX < 0.0f)
            {
                stepX = -1;
                sideDistX = (posX - static_cast<float>(mapX)) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (static_cast<float>(mapX) + 1.0f - posX) * deltaDistX;
            }
            if (rayDirY < 0.0f)
            {
                stepY = -1;
                sideDistY = (posY - static_cast<float>(mapY)) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (static_cast<float>(mapY) + 1.0f - posY) * deltaDistY;
            }

            while (hit == 0)
            {
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (MAP[static_cast<std::size_t>(mapX)][static_cast<std::size_t>(mapY)] > 0) hit = 1;
            }

            if (side == 0) perpWallDist = (sideDistX - deltaDistX);
            else           perpWallDist = (sideDistY - deltaDistY);

            if (perpWallDist < 0.01f) perpWallDist = 0.01f;

            auto lineHeight = static_cast<std::int32_t>(static_cast<float>(SCREEN_HEIGHT) / perpWallDist);

            std::int32_t drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) drawStart = 0;
            std::int32_t drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

            std::uint8_t r = 0;
            std::uint8_t g = 140;
            std::uint8_t b = 180;

            if (side == 1)
            {
                g = 90;
                b = 130;
            }

            float shadow = 1.0f / (1.0f + perpWallDist * perpWallDist * 0.05f);
            r = static_cast<std::uint8_t>(static_cast<float>(r) * shadow);
            g = static_cast<std::uint8_t>(static_cast<float>(g) * shadow);
            b = static_cast<std::uint8_t>(static_cast<float>(b) * shadow);

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
