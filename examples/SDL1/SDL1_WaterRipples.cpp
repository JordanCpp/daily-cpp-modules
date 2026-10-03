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

    SDL_WM_SetCaption("Daily C++ Modules - Demo 17: CPU Water Ripple Effect", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::vector<int> buffer1(totalPixels, 0);
    std::vector<int> buffer2(totalPixels, 0);
    std::vector<std::uint32_t> texture(totalPixels, 0);

    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            std::uint8_t c = (((x / 40) + (y / 40)) % 2 == 0) ? 220 : 60;
            texture[static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x)] = SDL_MapRGB(screen->format, c, static_cast<std::uint8_t>(c + 20), 255);
        }
    }

    int* bufferCurrent = buffer1.data();
    int* bufferNext = buffer2.data();

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distDrop(0, 100);
    std::uniform_int_distribution<int> distRangeX(5, screenWidth - 6);
    std::uniform_int_distribution<int> distRangeY(5, screenHeight - 6);

    bool isRunning = true;
    SDL_Event event{};

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

        if (distDrop(rng) < 4)
        {
            int dropX = distRangeX(rng);
            int dropY = distRangeY(rng);
            std::size_t idx = static_cast<std::size_t>(dropY) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(dropX);
            bufferCurrent[idx] = 512;
        }

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        std::uint8_t* rawPixels = static_cast<std::uint8_t*>(screen->pixels);
        std::size_t pitch = static_cast<std::size_t>(screen->pitch);

        for (int y = 1; y < screenHeight - 1; ++y)
        {
            std::size_t offset = static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth);
            for (int x = 1; x < screenWidth - 1; ++x)
            {
                std::size_t idx = offset + static_cast<std::size_t>(x);

                int data = (bufferCurrent[idx - 1] +
                    bufferCurrent[idx + 1] +
                    bufferCurrent[idx - static_cast<std::size_t>(screenWidth)] +
                    bufferCurrent[idx + static_cast<std::size_t>(screenWidth)]) >> 1;

                data -= bufferNext[idx];
                data -= data >> 5;

                bufferNext[idx] = data;

                int xBias = bufferCurrent[idx - 1] - bufferCurrent[idx + 1];
                int yBias = bufferCurrent[idx - static_cast<std::size_t>(screenWidth)] - bufferCurrent[idx + static_cast<std::size_t>(screenWidth)];

                int texX = std::clamp(x + (xBias >> 3), 0, screenWidth - 1);
                int texY = std::clamp(y + (yBias >> 3), 0, screenHeight - 1);

                std::uint32_t color = texture[static_cast<std::size_t>(texY) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(texX)];

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        std::swap(bufferCurrent, bufferNext);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
