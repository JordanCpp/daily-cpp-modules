// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

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

    constexpr int fireWidth = 640;
    constexpr int fireHeight = 480;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 7: Oldschool Fire Effect", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(fireWidth, fireHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint8_t> fireBuffer(static_cast<std::size_t>(fireWidth) * static_cast<std::size_t>(fireHeight), 0);

    std::array<std::uint32_t, 256> firePalette{};
    for (std::size_t i = 0; i < 256; ++i)
    {
        std::uint8_t r = 0, g = 0, b = 0;

        if (i < 85)
        {
            r = static_cast<std::uint8_t>(i * 3);
        }
        else if (i < 170)
        {
            r = 255;
            g = static_cast<std::uint8_t>((i - 85) * 3);
        }
        else
        {
            r = 255;
            g = 255;
            b = static_cast<std::uint8_t>((i - 170) * 3);
        }

        firePalette[i] = SDL_MapRGB(screen->format, r, g, b);
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distHeat(160, 255);

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

        int bottomRowOffset = (fireHeight - 1) * fireWidth;
        for (int x = 0; x < fireWidth; ++x)
        {
            fireBuffer[static_cast<std::size_t>(bottomRowOffset) + static_cast<std::size_t>(x)] = static_cast<std::uint8_t>(distHeat(rng));
        }

        for (int y = 0; y < fireHeight - 1; ++y)
        {
            for (int x = 0; x < fireWidth; ++x)
            {
                int belowIdx = ((y + 1) * fireWidth) + x;

                int belowLeftIdx = ((y + 1) * fireWidth) + ((x - 1 + fireWidth) % fireWidth);
                int belowRightIdx = ((y + 1) * fireWidth) + ((x + 1) % fireWidth);
                int doubleBelowIdx = ((y + 2) < fireHeight) ? (((y + 2) * fireWidth) + x) : belowIdx;

                int totalHeat = fireBuffer[static_cast<std::size_t>(belowIdx)] +
                    fireBuffer[static_cast<std::size_t>(belowLeftIdx)] +
                    fireBuffer[static_cast<std::size_t>(belowRightIdx)] +
                    fireBuffer[static_cast<std::size_t>(doubleBelowIdx)];
                int avgHeat = totalHeat / 4;

                if (avgHeat > 1)
                {
                    avgHeat -= 1;
                }
                else
                {
                    avgHeat = 0;
                }

                fireBuffer[static_cast<std::size_t>(y) * static_cast<std::size_t>(fireWidth) + static_cast<std::size_t>(x)] = static_cast<std::uint8_t>(avgHeat);
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        std::uint8_t* rawPixels = static_cast<std::uint8_t*>(screen->pixels);
        std::size_t pitch = static_cast<std::size_t>(screen->pitch);

        for (int y = 0; y < fireHeight; ++y)
        {
            for (int x = 0; x < fireWidth; ++x)
            {
                std::uint8_t heatValue = fireBuffer[static_cast<std::size_t>(y) * static_cast<std::size_t>(fireWidth) + static_cast<std::size_t>(x)];
                std::uint32_t color = firePalette[heatValue];

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
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
