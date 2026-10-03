// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

struct Star
{
    float x;
    float y;
    float z;
};

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
    constexpr int maxStars = 400;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 2: 3D Starfield", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distCoord(-300.0f, 300.0f);
    std::uniform_real_distribution<float> distDepth(1.0f, 1000.0f);

    std::vector<Star> stars(static_cast<std::size_t>(maxStars));
    for (auto& star : stars)
    {
        star.x = distCoord(rng);
        star.y = distCoord(rng);
        star.z = distDepth(rng);
    }

    bool isRunning = true;
    SDL_Event event{};

    constexpr float speed = 4.0f;
    constexpr float fov = 250.0f;
    constexpr int centerX = screenWidth / 2;
    constexpr int centerY = screenHeight / 2;

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

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        for (auto& star : stars)
        {
            star.z -= speed;

            if (star.z <= 0.0f)
            {
                star.x = distCoord(rng);
                star.y = distCoord(rng);
                star.z = 1000.0f;
            }

            int screenX = static_cast<int>((star.x * fov) / star.z) + centerX;
            int screenY = static_cast<int>((star.y * fov) / star.z) + centerY;

            if (screenX >= 0 && screenX < screenWidth && screenY >= 0 && screenY < screenHeight)
            {
                float colorIntensity = (1.0f - (star.z / 1000.0f));
                std::uint8_t brightness = static_cast<std::uint8_t>(colorIntensity * 255.0f);

                std::uint32_t color = SDL_MapRGB(screen->format, brightness, brightness, brightness);

                putPixel32(screen, screenX, screenY, color);
                if (star.z < 200.0f)
                {
                    putPixel32(screen, screenX + 1, screenY, color);
                    putPixel32(screen, screenX, screenY + 1, color);
                }
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
