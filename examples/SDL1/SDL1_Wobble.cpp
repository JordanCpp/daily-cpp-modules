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

    constexpr int screenWidth = 640;
    constexpr int screenHeight = 480;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 10: Raster Screen Wobble", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* background = SDL_CreateRGBSurface(SDL_SWSURFACE, screenWidth, screenHeight, 32,
        screen->format->Rmask, screen->format->Gmask,
        screen->format->Bmask, screen->format->Amask);
    if (!background)
    {
        std::println(std::cerr, "Failed to create background surface.");
        SDL_Quit();
        return 1;
    }

    if (SDL_MUSTLOCK(background)) SDL_LockSurface(background);

    std::uint8_t* bgPixels = static_cast<std::uint8_t*>(background->pixels);
    std::size_t bgPitch = static_cast<std::size_t>(background->pitch);

    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            float dx1 = static_cast<float>(x - screenWidth / 3);
            float dy1 = static_cast<float>(y - screenHeight / 3);
            float dist1 = std::sqrt(dx1 * dx1 + dy1 * dy1);

            float dx2 = static_cast<float>(x - 2 * screenWidth / 3);
            float dy2 = static_cast<float>(y - 2 * screenHeight / 3);
            float dist2 = std::sqrt(dx2 * dx2 + dy2 * dy2);

            std::uint8_t r = static_cast<std::uint8_t>(std::sin(dist1 * 0.1f) * 127.0f + 128.0f);
            std::uint8_t g = static_cast<std::uint8_t>(std::cos(dist2 * 0.15f) * 127.0f + 128.0f);
            std::uint8_t b = static_cast<std::uint8_t>((r ^ g));

            std::uint32_t color = SDL_MapRGB(background->format, r, g, b);
            std::uint8_t* pixelPtr = bgPixels + static_cast<std::size_t>(y) * bgPitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
            *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
        }
    }
    if (SDL_MUSTLOCK(background)) SDL_UnlockSurface(background);

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

        if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
        if (SDL_MUSTLOCK(background)) SDL_LockSurface(background);

        std::uint8_t* srcPixels = static_cast<std::uint8_t*>(background->pixels);
        std::uint8_t* dstPixels = static_cast<std::uint8_t*>(screen->pixels);
        std::size_t srcPitch = static_cast<std::size_t>(background->pitch);
        std::size_t dstPitch = static_cast<std::size_t>(screen->pitch);

        for (int y = 0; y < screenHeight; ++y)
        {
            int waveX = static_cast<int>(std::sin(static_cast<float>(y) * 0.03f + timeTicks) * 15.0f);

            for (int x = 0; x < screenWidth; ++x)
            {
                int srcX = (x + waveX + screenWidth) % screenWidth;

                std::uint8_t* srcPtr = srcPixels + static_cast<std::size_t>(y) * srcPitch + static_cast<std::size_t>(srcX) * sizeof(std::uint32_t);
                std::uint32_t color = *reinterpret_cast<std::uint32_t*>(srcPtr);

                std::uint8_t* dstPtr = dstPixels + static_cast<std::size_t>(y) * dstPitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(dstPtr) = color;
            }
        }

        if (SDL_MUSTLOCK(background)) SDL_UnlockSurface(background);
        if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

        SDL_Flip(screen);

        timeTicks += 0.07f;
        SDL_Delay(16);
    }

    SDL_FreeSurface(background);
    SDL_Quit();
    return 0;
}
