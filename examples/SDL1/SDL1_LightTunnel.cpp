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

    constexpr int screenWidth = 512;
    constexpr int screenHeight = 384;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 16: Ray-traced Tunnel with Attenuation", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    constexpr int texWidth = 256;
    constexpr int texHeight = 256;
    std::vector<std::uint32_t> texture(static_cast<std::size_t>(texWidth) * static_cast<std::size_t>(texHeight));

    for (int y = 0; y < texHeight; ++y)
    {
        for (int x = 0; x < texWidth; ++x)
        {
            std::uint8_t c1 = static_cast<std::uint8_t>(x ^ y);
            std::uint8_t c2 = static_cast<std::uint8_t>((x * 4) ^ (y * 4));
            texture[static_cast<std::size_t>(y) * static_cast<std::size_t>(texWidth) + static_cast<std::size_t>(x)] = SDL_MapRGB(screen->format, c1, static_cast<std::uint8_t>(c2 >> 1), static_cast<std::uint8_t>(c1 >> 1));
        }
    }

    std::vector<int> distanceTable(static_cast<std::size_t>(screenWidth) * static_cast<std::size_t>(screenHeight));
    std::vector<int> angleTable(static_cast<std::size_t>(screenWidth) * static_cast<std::size_t>(screenHeight));

    for (int y = 0; y < screenHeight; ++y)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            float dx = static_cast<float>(x - screenWidth / 2);
            float dy = static_cast<float>(y - screenHeight / 2);

            float radius = std::sqrt(dx * dx + dy * dy);
            if (radius == 0.0f) radius = 0.001f;

            int distance = static_cast<int>(32.0f * static_cast<float>(texHeight) / radius) % texHeight;

            float angleRad = std::atan2(dy, dx);
            int angle = static_cast<int>(static_cast<float>(texWidth) * (angleRad + static_cast<float>(std::numbers::pi)) / (2.0f * static_cast<float>(std::numbers::pi))) % texWidth;

            std::size_t tableOffset = static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x);
            distanceTable[tableOffset] = distance;
            angleTable[tableOffset] = angle;
        }
    }

    bool isRunning = true;
    SDL_Event event{};

    float animationTime = 0.0f;

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

        int shiftX = static_cast<int>(animationTime * 30.0f);
        int shiftY = static_cast<int>(animationTime * 50.0f);

        float lightZ = std::sin(animationTime * 2.0f) * 128.0f + 128.0f;

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
                std::size_t pixelOffset = static_cast<std::size_t>(y) * static_cast<std::size_t>(screenWidth) + static_cast<std::size_t>(x);

                int u = (angleTable[pixelOffset] + shiftX) & (texWidth - 1);
                int v = (distanceTable[pixelOffset] + shiftY) & (texHeight - 1);

                std::uint32_t baseColor = texture[static_cast<std::size_t>(v) * static_cast<std::size_t>(texWidth) + static_cast<std::size_t>(u)];

                std::uint8_t r, g, b;
                SDL_GetRGB(baseColor, screen->format, &r, &g, &b);

                float currentZ = static_cast<float>(distanceTable[pixelOffset]);
                float diffZ = std::abs(currentZ - lightZ);
                float lightIntensity = 2.0f - (diffZ * 0.015f) - (currentZ * 0.003f);
                lightIntensity = std::clamp(lightIntensity, 0.05f, 1.3f);

                r = static_cast<std::uint8_t>(std::clamp(static_cast<float>(r) * lightIntensity, 0.0f, 255.0f));
                g = static_cast<std::uint8_t>(std::clamp(static_cast<float>(g) * lightIntensity, 0.0f, 255.0f));
                b = static_cast<std::uint8_t>(std::clamp(static_cast<float>(b) * lightIntensity, 0.0f, 255.0f));

                std::uint32_t finalColor = SDL_MapRGB(screen->format, r, g, b);

                std::uint8_t* pixelPtr = rawPixels + static_cast<std::size_t>(y) * pitch + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
                *reinterpret_cast<std::uint32_t*>(pixelPtr) = finalColor;
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        animationTime += 0.02f;
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
