// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

struct Particle
{
    float x, y;
    float vx, vy;
    float r, g, b;
    float lifetime;
    float decay;
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

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    constexpr int maxParticles = 15'000;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 6: Dense Particle Fountain (15k)", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distSpeedX(-3.5f, 3.5f);
    std::uniform_real_distribution<float> distSpeedY(-9.5f, -3.5f);
    std::uniform_real_distribution<float> distColor(80.0f, 255.0f);
    std::uniform_real_distribution<float> distDecay(0.003f, 0.012f);

    auto resetParticle = [&](Particle& p) {
        p.x = screenWidth / 2.0f;
        p.y = screenHeight - 30.0f;
        p.vx = distSpeedX(rng);
        p.vy = distSpeedY(rng);
        p.r = distColor(rng);
        p.g = distColor(rng);
        p.b = distColor(rng);
        p.lifetime = 1.0f;
        p.decay = distDecay(rng);
        };

    std::vector<Particle> particles(static_cast<std::size_t>(maxParticles));
    for (auto& p : particles)
    {
        resetParticle(p);
        std::uniform_real_distribution<float> distLife(0.0f, 1.0f);
        p.lifetime = distLife(rng);
    }

    bool isRunning = true;
    SDL_Event event{};

    constexpr float gravity = 0.16f;
    constexpr float bounce = -0.5f;

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

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 3, 3, 10));

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        std::uint8_t* rawPixels = static_cast<std::uint8_t*>(screen->pixels);
        std::size_t pitch = static_cast<std::size_t>(screen->pitch);

        for (auto& p : particles)
        {
            p.lifetime -= p.decay;

            if (p.lifetime <= 0.0f)
            {
                resetParticle(p);
                continue;
            }

            p.vy += gravity;
            p.x += p.vx;
            p.y += p.vy;

            if (p.y >= static_cast<float>(screenHeight - 15))
            {
                p.y = static_cast<float>(screenHeight - 15);
                p.vy *= bounce;
            }

            if (p.x <= 0.0f || p.x >= static_cast<float>(screenWidth))
            {
                p.vx *= -0.8f;
            }

            int px = static_cast<int>(p.x);
            int py = static_cast<int>(p.y);

            if (px >= 0 && px < screenWidth && py >= 0 && py < screenHeight)
            {
                std::uint8_t finalR = static_cast<std::uint8_t>(p.r * p.lifetime);
                std::uint8_t finalG = static_cast<std::uint8_t>(p.g * p.lifetime);
                std::uint8_t finalB = static_cast<std::uint8_t>(p.b * p.lifetime);

                std::uint32_t color = SDL_MapRGB(screen->format, finalR, finalG, finalB);

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(py) * pitch + static_cast<std::size_t>(px) * sizeof(std::uint32_t);
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
