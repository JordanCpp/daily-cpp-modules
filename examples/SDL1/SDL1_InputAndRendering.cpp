// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

void clearScreen(SDL_Surface* surface, std::uint8_t r, std::uint8_t g, std::uint8_t b);

void clearScreen(SDL_Surface* surface, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    if (!surface) return;

    std::uint32_t color = SDL_MapRGB(surface->format, r, g, b);

    if (SDL_MUSTLOCK(surface))
    {
        if (SDL_LockSurface(surface) < 0)
        {
            std::println(std::cerr, "Surface Lock Error: {}", SDL_GetError());
            return;
        }
    }

    SDL_FillRect(surface, nullptr, color);

    if (SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }

    SDL_Flip(surface);
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

    SDL_WM_SetCaption("Daily C++ Modules - Input & Rendering", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    SDL_Event event{};

    std::uint8_t red = 128;
    std::uint8_t green = 128;
    std::uint8_t blue = 128;

    std::println("Controls: Press R, G, or B to change background color. ESC to quit.");

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_r:
                    red = (red == 255) ? 0 : 255;
                    std::println("Red toggled: {}", red);
                    break;
                case SDLK_g:
                    green = (green == 255) ? 0 : 255;
                    std::println("Green toggled: {}", green);
                    break;
                case SDLK_b:
                    blue = (blue == 255) ? 0 : 255;
                    std::println("Blue toggled: {}", blue);
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        clearScreen(screen, red, green, blue);

        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}
