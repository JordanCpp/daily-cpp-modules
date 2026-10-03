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

    constexpr int screenWidth = 640;
    constexpr int screenHeight = 480;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 11: Distortion Portal", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    constexpr int texWidth = 256;
    constexpr int texHeight = 256;
    std::vector<std::uint32_t> texture(static_cast<std::size_t>(texWidth) * static_cast<std::size_t>(texHeight));

    for (int y = 0; y < texHeight; ++y)
    {
        for (int x = 0; x < texWidth; ++x)
        {
            float fx = static_cast<float>(x) / static_cast<float>(texWidth);
            float fy = static_cast<float>(y) / static_cast<float>(texHeight);

            std::uint8_t r = static_cast<std::uint8_t>((std::sin(fx * static_cast<float>(std::numbers::pi) * 4.0f) * 0.5f + 0.5f) * 255.0f);
            std::uint8_t g = static_cast<std::uint8_t>((std::cos(fy * static_cast<float>(std::numbers::pi) * 4.0f) * 0.5f + 0.5f) * 255.0f);

            std::uint8_t b = static_cast<std::uint8_t>((x ^ y) & 0xFF);

            texture[static_cast<std::size_t>(y) * static_cast<std::size_t>(texWidth) + static_cast<std::size_t>(x)] = SDL_MapRGB(screen->format, r, g, b);
        }
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

        std::uint8_t* rawPixels = static_cast<std::uint8_t*>(screen->pixels);
        std::size_t pitch = static_cast<std::size_t>(screen->pitch);

        for (int y = 0; y < screenHeight; ++y)
        {
            float targetY = static_cast<float>(y - screenHeight / 2);

            for (int x = 0; x < screenWidth; ++x)
            {
                float targetX = static_cast<float>(x - screenWidth / 2);

                float distance = std::sqrt(targetX * targetX + targetY * targetY);
                if (distance == 0.0f) distance = 0.001f;

                float angle = std::atan2(targetY, targetX);

                int u = static_cast<int>(static_cast<float>(texWidth) * (angle + static_cast<float>(std::numbers::pi)) / (2.0f * static_cast<float>(std::numbers::pi)) + std::sin(distance * 0.05f + timeTicks) * 20.0f);
                int v = static_cast<int>(static_cast<float>(texHeight) * 40.0f / distance + timeTicks * 30.0f);

                std::size_t texU = static_cast<std::size_t>(u) & static_cast<std::size_t>(texWidth - 1);
                std::size_t texV = static_cast<std::size_t>(v) & static_cast<std::size_t>(texHeight - 1);

                std::uint32_t color = texture[texV * static_cast<std::size_t>(texWidth) + texU];

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        timeTicks += 0.05f;
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
