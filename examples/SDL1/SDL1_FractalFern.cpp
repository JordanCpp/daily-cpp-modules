// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color);

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;

    std::uint8_t* pixelPtr = static_cast<std::uint8_t*>(surface->pixels)
        + static_cast<std::size_t>(y) * static_cast<std::size_t>(surface->pitch)
        + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
    *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
}

int main()
{
    SDL1Loader loader;
    if (!loader.load())
    {
        std::println(std::cerr, "Critical Error: Failed to map SDL1 runtime binaries.");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::println(std::cerr, "SDL_Init Error: {}", SDL_GetError());
        return 1;
    }

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 13: Interactive Fractal Fern", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    SDL_Event event{};

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distRoll(0.0f, 100.0f);

    float px = 0.0f;
    float py = 0.0f;
    float angle = 0.0f;

    constexpr int pointsPerFrame = 8000;

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
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
            }
        }

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 5, 10, 5));

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        float cosA = std::cos(angle);
        float sinA = std::sin(angle);

        for (int i = 0; i < pointsPerFrame; ++i)
        {
            float nextX = 0.0f;
            float nextY = 0.0f;
            float roll = distRoll(rng);

            if (roll < 1.0f)
            {
                nextX = 0.0f;
                nextY = 0.16f * py;
            }
            else if (roll < 86.0f)
            {
                nextX = 0.85f * px + 0.04f * py;
                nextY = -0.04f * px + 0.85f * py + 1.6f;
            }
            else if (roll < 93.0f)
            {
                nextX = 0.2f * px - 0.26f * py;
                nextY = 0.23f * px + 0.22f * py + 1.6f;
            }
            else
            {
                nextX = -0.15f * px + 0.28f * py;
                nextY = 0.26f * px + 0.24f * py + 0.44f;
            }

            px = nextX;
            py = nextY;

            float rotatedX = px * cosA - (py - 5.0f) * sinA;
            float rotatedY = px * sinA + (py - 5.0f) * cosA + 5.0f;

            int screenX = static_cast<int>(rotatedX * 65.0f) + (screenWidth / 2);
            int screenY = screenHeight - static_cast<int>(rotatedY * 52.0f) - 30;

            std::uint8_t g = static_cast<std::uint8_t>(std::clamp(py * 22.0f + 50.0f, 0.0f, 255.0f));
            std::uint8_t r = static_cast<std::uint8_t>(std::clamp(std::abs(px) * 40.0f, 0.0f, 255.0f));
            std::uint32_t color = SDL_MapRGB(screen->format, r, g, 30);

            putPixel32(screen, screenX, screenY, color);
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        angle += 0.015f;
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
