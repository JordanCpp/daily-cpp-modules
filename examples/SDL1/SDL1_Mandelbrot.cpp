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

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    constexpr int maxIterations = 80;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 4: Mandelbrot Fractal", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    SDL_Event event{};

    double minRe = -2.0, maxRe = 1.0;
    double minIm = -1.2, maxIm = 1.2;

    double reFactor = (maxRe - minRe) / (screenWidth - 1);
    double imFactor = (maxIm - minIm) / (screenHeight - 1);

    std::vector<std::uint32_t> colorPalette(static_cast<std::size_t>(maxIterations) + 1);
    for (int i = 0; i <= maxIterations; ++i)
    {
        if (i == maxIterations)
        {
            colorPalette[static_cast<std::size_t>(i)] = SDL_MapRGB(screen->format, 0, 0, 0);
        }
        else
        {
            float t = static_cast<float>(i) / maxIterations;
            std::uint8_t r = static_cast<std::uint8_t>(9.0f * (1.0f - t) * t * t * t * 255.0f);
            std::uint8_t g = static_cast<std::uint8_t>(15.0f * (1.0f - t) * (1.0f - t) * t * t * 255.0f);
            std::uint8_t b = static_cast<std::uint8_t>(8.5f * (1.0f - t) * (1.0f - t) * (1.0f - t) * t * 255.0f);

            colorPalette[static_cast<std::size_t>(i)] = SDL_MapRGB(screen->format, r, g, b);
        }
    }

    if (SDL_MUSTLOCK(screen))
    {
        if (SDL_LockSurface(screen) < 0) return 1;
    }

    for (int y = 0; y < screenHeight; ++y)
    {
        double c_im = maxIm - y * imFactor;
        for (int x = 0; x < screenWidth; ++x)
        {
            double c_re = minRe + x * reFactor;

            double z_re = c_re, z_im = c_im;
            int isInside = maxIterations;

            for (int n = 0; n < maxIterations; ++n)
            {
                double z_re2 = z_re * z_re;
                double z_im2 = z_im * z_im;

                if (z_re2 + z_im2 > 4.0)
                {
                    isInside = n;
                    break;
                }

                z_im = 2.0 * z_re * z_im + c_im;
                z_re = z_re2 - z_im2 + c_re;
            }

            putPixel32(screen, x, y, colorPalette[static_cast<std::size_t>(isInside)]);
        }
    }

    if (SDL_MUSTLOCK(screen))
    {
        SDL_UnlockSurface(screen);
    }

    SDL_Flip(screen);

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

        SDL_Delay(32);
    }

    SDL_Quit();
    return 0;
}
