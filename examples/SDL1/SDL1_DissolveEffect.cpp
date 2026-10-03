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

    SDL_WM_SetCaption("Daily C++ Modules - Demo 20: 2D Dissolve Fade Effect", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint32_t> sourceTexture(totalPixels);
    std::vector<std::uint32_t> targetTexture(totalPixels);

    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x);

            std::uint8_t r1 = static_cast<std::uint8_t>((x ^ y) & 0xFF);
            std::uint8_t g1 = static_cast<std::uint8_t>(x * 255 / screenWidth);
            std::uint8_t b1 = static_cast<std::uint8_t>(y * 255 / screenHeight);
            sourceTexture[idx] = SDL_MapRGB(screen->format, r1, g1, b1);

            float fx = static_cast<float>(x - screenWidth / 2);
            float fy = static_cast<float>(y - screenHeight / 2);
            float dist = std::sqrt(fx * fx + fy * fy);
            std::uint8_t c2 = static_cast<std::uint8_t>(std::clamp(255.0f - dist * 0.8f, 0.0f, 255.0f));
            targetTexture[idx] = SDL_MapRGB(screen->format, c2, static_cast<std::uint8_t>(c2 >> 1), static_cast<std::uint8_t>(255 - c2));
        }
    }

    std::vector<std::size_t> pixelIndices(totalPixels);
    for (std::size_t i = 0; i < totalPixels; ++i)
    {
        pixelIndices[i] = i;
    }

    std::mt19937 rng(std::random_device{}());
    std::shuffle(pixelIndices.begin(), pixelIndices.end(), rng);

    if (SDL_MUSTLOCK(screen))
    {
        if (SDL_LockSurface(screen) < 0) return 1;
    }
    std::uint8_t* rawPixels = static_cast<std::uint8_t*>(screen->pixels);
    std::size_t pitch = static_cast<std::size_t>(screen->pitch);
    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x);
            std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
            *reinterpret_cast<std::uint32_t*>(pixelPtr) = sourceTexture[idx];
        }
    }
    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
    SDL_Flip(screen);

    bool isRunning = true;
    SDL_Event event{};
    std::size_t dissolveProgress = 0;
    constexpr std::size_t pixelsPerFrame = totalPixels / 120;

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
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    dissolveProgress = 0;
                    std::shuffle(pixelIndices.begin(), pixelIndices.end(), rng);

                    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
                    for (int y = 0; y < screenHeight; ++y)
                    {
                        for (int x = 0; x < screenWidth; ++x)
                        {
                            std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x);
                            std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                            *reinterpret_cast<std::uint32_t*>(pixelPtr) = sourceTexture[idx];
                        }
                    }
                    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
                    SDL_Flip(screen);
                }
            }
        }

        if (dissolveProgress < totalPixels)
        {
            if (SDL_MUSTLOCK(screen))
            {
                if (SDL_LockSurface(screen) < 0) continue;
            }

            std::size_t endStep = std::min(dissolveProgress + pixelsPerFrame, totalPixels);
            for (std::size_t i = dissolveProgress; i < endStep; ++i)
            {
                std::size_t linearIdx = pixelIndices[i];
                int px = static_cast<int>(linearIdx % static_cast<std::size_t>(screenWidth));
                int py = static_cast<int>(linearIdx / static_cast<std::size_t>(screenWidth));

                std::uint32_t targetColor = targetTexture[linearIdx];

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(py) * pitch + static_cast<std::size_t>(px) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(pixelPtr) = targetColor;
            }

            dissolveProgress = endStep;

            if (SDL_MUSTLOCK(screen))
            {
                SDL_UnlockSurface(screen);
            }

            SDL_Flip(screen);
        }

        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
