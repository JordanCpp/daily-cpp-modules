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

    constexpr int screenWidth = 640;
    constexpr int screenHeight = 480;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 1: Retro Plasma", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    SDL_Event event{};
    float timeTicks = 0.0f;

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

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        for (int y = 0; y < screenHeight; ++y)
        {
            for (int x = 0; x < screenWidth; ++x)
            {
                float u = static_cast<float>(x) / static_cast<float>(screenWidth);
                float v = static_cast<float>(y) / static_cast<float>(screenHeight);

                float wave1 = std::sin(u * 6.0f + timeTicks);
                float wave2 = std::sin(1.0f * (v * 4.0f + timeTicks * 1.5f));
                float wave3 = std::sin(4.0f * (u + v) + timeTicks * 0.8f);

                float result = (wave1 + wave2 + wave3 + 3.0f) / 6.0f;

                std::uint8_t r = static_cast<std::uint8_t>(result * 255.0f);
                std::uint8_t g = static_cast<std::uint8_t>(std::sin(result * std::numbers::pi) * 255.0f);
                std::uint8_t b = static_cast<std::uint8_t>((1.0f - result) * 255.0f);

                std::uint32_t color = SDL_MapRGB(screen->format, r, g, b);
                putPixel32(screen, x, y, color);
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        timeTicks += 0.04f;
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
