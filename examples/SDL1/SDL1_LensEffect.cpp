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
    constexpr std::size_t totalPixels = static_cast<std::size_t>(screenWidth) * static_cast<std::size_t>(screenHeight);

    SDL_WM_SetCaption("Daily C++ Modules - Demo 18: CPU Real-time Lens Effect", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint32_t> background(totalPixels, 0);

    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            float dx1 = static_cast<float>(x - screenWidth / 4);
            float dy1 = static_cast<float>(y - screenHeight / 4);
            float dist1 = std::sqrt(dx1 * dx1 + dy1 * dy1);

            float dx2 = static_cast<float>(x - 3 * screenWidth / 4);
            float dy2 = static_cast<float>(y - 3 * screenHeight / 4);
            float dist2 = std::sqrt(dx2 * dx2 + dy2 * dy2);

            std::uint8_t r = static_cast<std::uint8_t>(std::sin(dist1 * 0.1f) * 127.0f + 128.0f);
            std::uint8_t g = static_cast<std::uint8_t>(std::cos(dist2 * 0.08f) * 127.0f + 128.0f);
            std::uint8_t b = static_cast<std::uint8_t>((r ^ g) & 0xFF);

            background[static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x)] = SDL_MapRGB(screen->format, r, g, b);
        }
    }

    constexpr int lensRadius = 80;
    constexpr int lensDiameter = lensRadius * 2;
    constexpr float refractionIndex = 1.5f;

    std::vector<int> shiftTableX(static_cast<std::size_t>(lensDiameter) * static_cast<std::size_t>(lensDiameter), 0);
    std::vector<int> shiftTableY(static_cast<std::size_t>(lensDiameter) * static_cast<std::size_t>(lensDiameter), 0);

    for (int y = 0; y < lensDiameter; ++y)
    {
        for (int x = 0; x < lensDiameter; ++x)
        {
            int dx = x - lensRadius;
            int dy = y - lensRadius;
            float distance = std::sqrt(static_cast<float>(dx * dx + dy * dy));

            std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(lensDiameter) + static_cast<std::size_t>(x);

            if (distance < static_cast<float>(lensRadius))
            {
                float z = std::sqrt(static_cast<float>(lensRadius * lensRadius) - distance * distance);

                float angleX = std::asin(static_cast<float>(dx) / static_cast<float>(lensRadius));
                float angleY = std::asin(static_cast<float>(dy) / static_cast<float>(lensRadius));

                shiftTableX[idx] = static_cast<int>(std::sin(angleX * refractionIndex) * z - static_cast<float>(dx));
                shiftTableY[idx] = static_cast<int>(std::sin(angleY * refractionIndex) * z - static_cast<float>(dy));
            }
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

        int lensCenterX = static_cast<int>((screenWidth / 2) + std::sin(timeTicks * 0.8f) * (screenWidth / 3));
        int lensCenterY = static_cast<int>((screenHeight / 2) + std::cos(timeTicks * 1.1f) * (screenHeight / 4));

        int startX = lensCenterX - lensRadius;
        int startY = lensCenterY - lensRadius;

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        std::uint8_t* rawPixels = static_cast<std::uint8_t*>(screen->pixels);
        std::size_t pitch = static_cast<std::size_t>(screen->pitch);

        for (int y = 0; y < screenHeight; ++y)
        {
            for (int x = 0; x < screenWidth; ++x)
            {
                std::uint32_t color = background[static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x)];

                int lensX = x - startX;
                int lensY = y - startY;

                if (lensX >= 0 && lensX < lensDiameter && lensY >= 0 && lensY < lensDiameter)
                {
                    int dx = lensX - lensRadius;
                    int dy = lensY - lensRadius;

                    if (dx * dx + dy * dy < lensRadius * lensRadius)
                    {
                        std::size_t tableIdx = static_cast<std::size_t>(lensY) * static_cast<std::size_t>(lensDiameter) + static_cast<std::size_t>(lensX);

                        int targetX = std::clamp(x + shiftTableX[tableIdx], 0, screenWidth - 1);
                        int targetY = std::clamp(y + shiftTableY[tableIdx], 0, screenHeight - 1);

                        color = background[static_cast<std::size_t>(targetY) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(targetX)];
                    }
                }

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        timeTicks += 0.03f;
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
