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
    constexpr int cellSize = 4;
    constexpr int gridWidth = screenWidth / cellSize;
    constexpr int gridHeight = screenHeight / cellSize;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 14: Thermal Game of Life", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint8_t> currentGrid(static_cast<std::size_t>(gridWidth) * static_cast<std::size_t>(gridHeight), 0);
    std::vector<std::uint8_t> nextGrid(static_cast<std::size_t>(gridWidth) * static_cast<std::size_t>(gridHeight), 0);
    std::vector<std::uint8_t> cellAge(static_cast<std::size_t>(gridWidth) * static_cast<std::size_t>(gridHeight), 0);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 100);

    for (int y = 0; y < gridHeight; ++y)
    {
        for (int x = 0; x < gridWidth; ++x)
        {
            std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(gridWidth) + static_cast<std::size_t>(x);
            if (dist(rng) < 20)
            {
                currentGrid[idx] = 1;
                cellAge[idx] = 255;
            }
        }
    }

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
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    std::fill(currentGrid.begin(), currentGrid.end(), 0);
                    std::fill(cellAge.begin(), cellAge.end(), 0);
                    for (std::size_t i = 0; i < currentGrid.size(); ++i)
                    {
                        if (dist(rng) < 20)
                        {
                            currentGrid[i] = 1;
                            cellAge[i] = 255;
                        }
                    }
                }
            }
        }

        for (int y = 0; y < gridHeight; ++y)
        {
            for (int x = 0; x < gridWidth; ++x)
            {
                int neighbors = 0;
                for (int dy = -1; dy <= 1; ++dy)
                {
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        if (dx == 0 && dy == 0) continue;
                        int nx = (x + dx + gridWidth) % gridWidth;
                        int ny = (y + dy + gridHeight) % gridHeight;
                        neighbors += currentGrid[static_cast<std::size_t>(ny) * static_cast<std::size_t>(gridWidth) + static_cast<std::size_t>(nx)];
                    }
                }

                std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(gridWidth) + static_cast<std::size_t>(x);
                if (currentGrid[idx] == 1)
                {
                    if (neighbors < 2 || neighbors > 3)
                    {
                        nextGrid[idx] = 0;
                    }
                    else
                    {
                        nextGrid[idx] = 1;
                    }
                }
                else
                {
                    if (neighbors == 3)
                    {
                        nextGrid[idx] = 1;
                    }
                    else
                    {
                        nextGrid[idx] = 0;
                    }
                }
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        for (int y = 0; y < gridHeight; ++y)
        {
            for (int x = 0; x < gridWidth; ++x)
            {
                std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(gridWidth) + static_cast<std::size_t>(x);

                if (nextGrid[idx] == 1)
                {
                    if (cellAge[idx] < 245) cellAge[idx] += 10;
                    else cellAge[idx] = 255;
                }
                else
                {
                    if (cellAge[idx] > 3) cellAge[idx] -= 4;
                    else cellAge[idx] = 0;
                }

                std::uint8_t age = cellAge[idx];
                std::uint8_t r = 0, g = 0, b = 0;

                if (nextGrid[idx] == 1)
                {
                    r = static_cast<std::uint8_t>(age);
                    g = 255;
                    b = static_cast<std::uint8_t>(255 - age);
                }
                else if (age > 0)
                {
                    r = static_cast<std::uint8_t>(age >> 1);
                    g = 0;
                    b = age;
                }

                std::uint32_t color = SDL_MapRGB(screen->format, r, g, b);

                int screenX = x * cellSize;
                int screenY = y * cellSize;

                for (int h = 0; h < cellSize; ++h)
                {
                    for (int w = 0; w < cellSize; ++w)
                    {
                        putPixel32(screen, screenX + w, screenY + h, color);
                    }
                }
            }
        }

        currentGrid = nextGrid;

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
