// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color);
inline void generateDiamondSquare(std::vector<float>& map, int size, float roughness, std::mt19937& rng);

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;

    std::uint8_t* pixelPtr = static_cast<std::uint8_t*>(surface->pixels)
        + static_cast<std::size_t>(y) * static_cast<std::size_t>(surface->pitch)
        + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
    *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
}

inline void generateDiamondSquare(std::vector<float>& map, int size, float roughness, std::mt19937& rng)
{
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    map[0] = dist(rng);
    map[static_cast<std::size_t>(size - 1)] = dist(rng);
    map[static_cast<std::size_t>(size - 1) * static_cast<std::size_t>(size)] = dist(rng);
    map[static_cast<std::size_t>(size * size - 1)] = dist(rng);

    float changeRange = 1.0f;

    for (int step = size - 1; step > 1; step /= 2)
    {
        int half = step / 2;

        for (int y = 0; y < size - 1; y += step)
        {
            for (int x = 0; x < size - 1; x += step)
            {
                float cornerTotal = map[static_cast<std::size_t>(y) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x)] +
                    map[static_cast<std::size_t>(y) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x + step)] +
                    map[static_cast<std::size_t>(y + step) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x)] +
                    map[static_cast<std::size_t>(y + step) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x + step)];

                float avg = cornerTotal / 4.0f;
                map[static_cast<std::size_t>(y + half) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x + half)] = avg + (dist(rng) * changeRange);
            }
        }

        for (int y = 0; y < size; y += half)
        {
            for (int x = (y % step == 0) ? half : 0; x < size; x += step)
            {
                float sum = 0.0f;
                int count = 0;

                if (x >= half) { sum += map[static_cast<std::size_t>(y) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x - half)]; count++; }
                if (x + half < size) { sum += map[static_cast<std::size_t>(y) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x + half)]; count++; }
                if (y >= half) { sum += map[static_cast<std::size_t>(y - half) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x)]; count++; }
                if (y + half < size) { sum += map[static_cast<std::size_t>(y + half) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x)]; count++; }

                map[static_cast<std::size_t>(y) * static_cast<std::size_t>(size) + static_cast<std::size_t>(x)] = (sum / static_cast<float>(count)) + (dist(rng) * changeRange);
            }
        }

        changeRange *= roughness;
    }
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

    constexpr int screenWidth = 512;
    constexpr int screenHeight = 512;
    constexpr int mapSize = 513;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 15: Diamond-Square Fractal Plasma", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::vector<float> plasmaMap(static_cast<std::size_t>(mapSize) * static_cast<std::size_t>(mapSize), 0.0f);
    std::mt19937 rng(std::random_device{}());

    generateDiamondSquare(plasmaMap, mapSize, 0.55f, rng);

    float minVal = plasmaMap[0];
    float maxVal = plasmaMap[0];
    for (float val : plasmaMap)
    {
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
    }

    std::vector<std::uint8_t> normalizedMap(plasmaMap.size());
    for (std::size_t i = 0; i < plasmaMap.size(); ++i)
    {
        normalizedMap[i] = static_cast<std::uint8_t>(((plasmaMap[i] - minVal) / (maxVal - minVal)) * 255.0f);
    }

    bool isRunning = true;
    SDL_Event event{};
    int scrollOffset = 0;

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
            for (int x = 0; x < screenWidth; ++x)
            {
                int targetX = (x + scrollOffset) % (mapSize - 1);
                std::size_t mapIdx = static_cast<std::size_t>(y) * static_cast<std::size_t>(mapSize) + static_cast<std::size_t>(targetX);

                std::uint8_t intensity = normalizedMap[mapIdx];

                std::uint8_t r = static_cast<std::uint8_t>(intensity);
                std::uint8_t g = static_cast<std::uint8_t>(std::abs(std::sin(static_cast<float>(intensity) * 0.02f)) * 255.0f);
                std::uint8_t b = static_cast<std::uint8_t>(255 - intensity);

                std::uint32_t color = SDL_MapRGB(screen->format, r, g, b);

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        scrollOffset = (scrollOffset + 1) % (mapSize - 1);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
