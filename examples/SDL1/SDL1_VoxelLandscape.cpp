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

    SDL_WM_SetCaption("Daily C++ Modules - Demo 12: Voxel Landscape", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    constexpr int mapSize = 1024;
    std::vector<std::uint8_t> heightMap(static_cast<std::size_t>(mapSize) * static_cast<std::size_t>(mapSize), 0);
    std::vector<std::uint32_t> colorMap(static_cast<std::size_t>(mapSize) * static_cast<std::size_t>(mapSize), 0);

    for (int y = 0; y < mapSize; ++y)
    {
        for (int x = 0; x < mapSize; ++x)
        {
            float fx = static_cast<float>(x) * 0.005f;
            float fy = static_cast<float>(y) * 0.005f;

            float n = std::sin(fx * 4.0f) * std::cos(fy * 4.0f)
                + std::sin(fx * 8.0f) * 0.5f
                + std::cos(fy * 16.0f) * 0.25f;

            n = (n + 1.75f) / 3.5f;
            n = std::clamp(n, 0.0f, 1.0f);

            std::uint8_t h = static_cast<std::uint8_t>(n * 240.0f);
            std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(mapSize) + static_cast<std::size_t>(x);
            heightMap[idx] = h;

            std::uint8_t r = static_cast<std::uint8_t>(h * 0.4f + 20);
            std::uint8_t g = static_cast<std::uint8_t>(h * 0.8f + 30);
            std::uint8_t b = static_cast<std::uint8_t>(h * 0.3f + 15);

            if (h < 60)
            {
                r = 20; g = 40; b = static_cast<std::uint8_t>(120 + h);
            }
            else if (h > 200)
            {
                r = g = b = static_cast<std::uint8_t>(h);
            }

            colorMap[idx] = SDL_MapRGB(screen->format, r, g, b);
        }
    }

    bool isRunning = true;
    SDL_Event event{};

    float cameraX = 512.0f;
    float cameraY = 512.0f;
    float cameraAngle = 0.0f;
    float cameraHeight = 160.0f;
    float horizon = 120.0f;

    constexpr float distanceMax = 400.0f;

    std::vector<int> yBuffer(static_cast<std::size_t>(screenWidth));

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

        cameraX += std::cos(cameraAngle) * 2.0f;
        cameraY += std::sin(cameraAngle) * 2.0f;
        cameraAngle += 0.005f;

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 135, 206, 235));

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        std::fill(yBuffer.begin(), yBuffer.end(), screenHeight);

        float sinAngle = std::sin(cameraAngle);
        float cosAngle = std::cos(cameraAngle);

        for (float z = 1.0f; z < distanceMax; z += 1.5f)
        {
            float pleftX = -cosAngle * z - sinAngle * z;
            float pleftY = -sinAngle * z + cosAngle * z;
            float prightX = cosAngle * z - sinAngle * z;
            float prightY = sinAngle * z + cosAngle * z;

            float dx = (prightX - pleftX) / screenWidth;
            float dy = (prightY - pleftY) / screenWidth;

            float rx = cameraX + pleftX;
            float ry = cameraY + pleftY;

            float invZ = 1.0f / z * 240.0f;

            for (int i = 0; i < screenWidth; ++i)
            {
                int mapX = static_cast<int>(rx) & (mapSize - 1);
                int mapY = static_cast<int>(ry) & (mapSize - 1);
                std::size_t mapIdx = static_cast<std::size_t>(mapY) * static_cast<std::size_t>(mapSize) + static_cast<std::size_t>(mapX);

                float hMap = static_cast<float>(heightMap[mapIdx]);
                int heightOnScreen = static_cast<int>((cameraHeight - hMap) * invZ + horizon);

                if (heightOnScreen < 0) heightOnScreen = 0;

                std::size_t bufIdx = static_cast<std::size_t>(i);
                if (heightOnScreen < yBuffer[bufIdx])
                {
                    std::uint32_t color = colorMap[mapIdx];
                    for (int y = heightOnScreen; y < yBuffer[bufIdx]; ++y)
                    {
                        putPixel32(screen, i, y, color);
                    }
                    yBuffer[bufIdx] = heightOnScreen;
                }

                rx += dx;
                ry += dy;
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
