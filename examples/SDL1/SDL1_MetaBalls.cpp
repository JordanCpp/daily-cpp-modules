// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

struct Ball
{
    float x, y;
    float vx, vy;
    float radius;
};

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

    SDL_WM_SetCaption("Daily C++ Modules - Demo 9: Organic Metaballs", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::array<Ball, 3> balls = { {
        { 100.0f, 100.0f, 2.5f, 2.0f, 40.0f },
        { 200.0f, 150.0f, -2.0f, 3.0f, 55.0f },
        { 150.0f, 80.0f,  1.8f, -2.2f, 35.0f }
    } };

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

        for (auto& ball : balls)
        {
            ball.x += ball.vx;
            ball.y += ball.vy;

            if (ball.x - ball.radius < 0.0f || ball.x + ball.radius >= static_cast<float>(screenWidth))  ball.vx *= -1.0f;
            if (ball.y - ball.radius < 0.0f || ball.y + ball.radius >= static_cast<float>(screenHeight)) ball.vy *= -1.0f;
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
                float totalEnergy = 0.0f;

                for (const auto& ball : balls)
                {
                    float dx = static_cast<float>(x) - ball.x;
                    float dy = static_cast<float>(y) - ball.y;
                    float distSq = dx * dx + dy * dy;

                    if (distSq == 0.0f) distSq = 0.001f;

                    totalEnergy += (ball.radius * ball.radius) / distSq;
                }

                std::uint8_t r = static_cast<std::uint8_t>(std::clamp(totalEnergy * 130.0f, 0.0f, 255.0f));
                std::uint8_t g = static_cast<std::uint8_t>(std::clamp(totalEnergy * 60.0f, 0.0f, 255.0f));
                std::uint8_t b = static_cast<std::uint8_t>(std::clamp(totalEnergy * 200.0f, 0.0f, 255.0f));

                if (r < 40 && b < 60)
                {
                    r = g = b = 0;
                }

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
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
