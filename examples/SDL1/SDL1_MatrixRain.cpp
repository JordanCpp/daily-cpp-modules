// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

struct RainDrop
{
    int x;
    float y;
    float speed;
    int length;
};

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color);
inline void fadeScreen(SDL_Surface* surface);

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;

    std::uint8_t* pixelPtr = static_cast<std::uint8_t*>(surface->pixels)
        + static_cast<std::size_t>(y) * static_cast<std::size_t>(surface->pitch)
        + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
    *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
}

inline void fadeScreen(SDL_Surface* surface)
{
    if (SDL_MUSTLOCK(surface))
    {
        if (SDL_LockSurface(surface) < 0) return;
    }

    std::uint32_t* pixels = static_cast<std::uint32_t*>(surface->pixels);
    int totalPixels = (surface->pitch / static_cast<int>(sizeof(std::uint32_t))) * surface->h;

    for (int i = 0; i < totalPixels; ++i)
    {
        std::uint32_t color = pixels[static_cast<std::size_t>(i)];
        if (color == 0) continue;

        std::uint8_t r, g, b;
        SDL_GetRGB(color, surface->format, &r, &g, &b);

        r = (r > 4) ? static_cast<std::uint8_t>(r - 4) : static_cast<std::uint8_t>(0);
        g = (g > 3) ? static_cast<std::uint8_t>(g - 3) : static_cast<std::uint8_t>(0);
        b = (b > 4) ? static_cast<std::uint8_t>(b - 4) : static_cast<std::uint8_t>(0);

        pixels[static_cast<std::size_t>(i)] = SDL_MapRGB(surface->format, r, g, b);
    }

    if (SDL_MUSTLOCK(surface))
    {
        surface->flags &= static_cast<std::uint32_t>(~SDL_LOGPAL);
        SDL_UnlockSurface(surface);
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

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    constexpr int columnSize = 12;
    constexpr int maxDrops = screenWidth / columnSize;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 3: Digital Matrix Rain", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distSpeed(2.0f, 7.0f);
    std::uniform_int_distribution<int> distLength(50, 200);
    std::uniform_real_distribution<float> distStartSlot(-300.0f, 0.0f);

    std::vector<RainDrop> drops(static_cast<std::size_t>(maxDrops));
    for (int i = 0; i < maxDrops; ++i)
    {
        drops[static_cast<std::size_t>(i)].x = i * columnSize + 4;
        drops[static_cast<std::size_t>(i)].y = distStartSlot(rng);
        drops[static_cast<std::size_t>(i)].speed = distSpeed(rng);
        drops[static_cast<std::size_t>(i)].length = distLength(rng);
    }

    bool isRunning = true;
    SDL_Event event{};

    SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));

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

        fadeScreen(screen);

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        for (auto& drop : drops)
        {
            drop.y += drop.speed;

            if (drop.y > screenHeight)
            {
                drop.y = distStartSlot(rng);
                drop.speed = distSpeed(rng);
                drop.length = distLength(rng);
            }

            int headY = static_cast<int>(drop.y);

            if (headY >= 0 && headY < screenHeight)
            {
                std::uint32_t headColor = SDL_MapRGB(screen->format, 180, 255, 180);
                putPixel32(screen, drop.x, headY, headColor);
                putPixel32(screen, drop.x + 1, headY, headColor);

                for (int j = 1; j < 6; ++j)
                {
                    if (headY - j >= 0)
                    {
                        std::uint32_t bodyColor = SDL_MapRGB(screen->format, 0, static_cast<std::uint8_t>(255 - (j * 20)), 0);
                        putPixel32(screen, drop.x, headY - j, bodyColor);
                        putPixel32(screen, drop.x + 1, headY - j, bodyColor);
                    }
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
