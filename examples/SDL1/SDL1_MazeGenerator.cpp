// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

struct Cell
{
    bool visited = false;
    bool walls[4] = { true, true, true, true };
};

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color);
inline void drawGridCell(SDL_Surface* surface, int cx, int cy, int size, const Cell& cell, std::uint32_t color, std::uint32_t wallColor);

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;

    std::uint8_t* pixelPtr = static_cast<std::uint8_t*>(surface->pixels)
        + static_cast<std::size_t>(y) * static_cast<std::size_t>(surface->pitch)
        + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
    *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
}

inline void drawGridCell(SDL_Surface* surface, int cx, int cy, int size, const Cell& cell, std::uint32_t color, std::uint32_t wallColor)
{
    int startX = cx * size;
    int startY = cy * size;

    for (int y = 1; y < size - 1; ++y)
    {
        for (int x = 1; x < size - 1; ++x)
        {
            putPixel32(surface, startX + x, startY + y, color);
        }
    }

    for (int i = 0; i < size; ++i)
    {
        if (cell.walls[0]) putPixel32(surface, startX + i, startY, wallColor);
        else if (i > 0 && i < size - 1) putPixel32(surface, startX + i, startY, color);

        if (cell.walls[1]) putPixel32(surface, startX + size - 1, startY + i, wallColor);
        else if (i > 0 && i < size - 1) putPixel32(surface, startX + size - 1, startY + i, color);

        if (cell.walls[2]) putPixel32(surface, startX + i, startY + size - 1, wallColor);
        else if (i > 0 && i < size - 1) putPixel32(surface, startX + i, startY + size - 1, color);

        if (cell.walls[3]) putPixel32(surface, startX, startY + i, wallColor);
        else if (i > 0 && i < size - 1) putPixel32(surface, startX, startY + i, color);
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

    constexpr int screenWidth = 640;
    constexpr int screenHeight = 480;
    constexpr int cellSize = 16;
    constexpr int gridWidth = screenWidth / cellSize;
    constexpr int gridHeight = screenHeight / cellSize;

    SDL_WM_SetCaption("Daily C++ Modules - Demo 19: Procedural Maze DFS Visualizer", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::vector<Cell> grid(static_cast<std::size_t>(gridWidth) * static_cast<std::size_t>(gridHeight));
    std::vector<std::size_t> stack;
    std::vector<std::uint8_t> cellColorIntensity(grid.size(), 0);

    std::mt19937 rng(std::random_device{}());

    auto resetMaze = [&]() {
        std::fill(grid.begin(), grid.end(), Cell{});
        std::fill(cellColorIntensity.begin(), cellColorIntensity.end(), 0);
        stack.clear();

        grid[0].visited = true;
        stack.push_back(0);
        };

    resetMaze();

    bool isRunning = true;
    SDL_Event event{};

    std::uint32_t wallColor = SDL_MapRGB(screen->format, 40, 45, 55);
    std::uint32_t unvisitedColor = SDL_MapRGB(screen->format, 15, 20, 25);

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
                    resetMaze();
                }
            }
        }

        if (!stack.empty())
        {
            std::size_t currentIdx = stack.back();
            int cx = static_cast<int>(currentIdx % static_cast<std::size_t>(gridWidth));
            int cy = static_cast<int>(currentIdx / static_cast<std::size_t>(gridWidth));

            std::vector<std::size_t> neighbors;
            std::vector<int> directions;

            int dx[4] = { 0, 1, 0, -1 };
            int dy[4] = { -1, 0, 1, 0 };

            for (int i = 0; i < 4; ++i)
            {
                int nx = cx + dx[i];
                int ny = cy + dy[i];

                if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight)
                {
                    std::size_t nIdx = static_cast<std::size_t>(ny) * static_cast<std::size_t>(gridWidth) + static_cast<std::size_t>(nx);
                    if (!grid[nIdx].visited)
                    {
                        neighbors.push_back(nIdx);
                        directions.push_back(i);
                    }
                }
            }

            if (!neighbors.empty())
            {
                std::uniform_int_distribution<std::size_t> dist(0, neighbors.size() - 1);
                std::size_t pick = dist(rng);

                std::size_t nextIdx = neighbors[pick];
                int dir = directions[pick];

                grid[currentIdx].walls[dir] = false;
                grid[nextIdx].walls[(dir + 2) % 4] = false;

                grid[nextIdx].visited = true;
                cellColorIntensity[nextIdx] = 255;
                stack.push_back(nextIdx);
            }
            else
            {
                if (cellColorIntensity[currentIdx] > 100)
                {
                    cellColorIntensity[currentIdx] = 100;
                }
                stack.pop_back();
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 10, 12, 15));

        for (int y = 0; y < gridHeight; ++y)
        {
            for (int x = 0; x < gridWidth; ++x)
            {
                std::size_t idx = static_cast<std::size_t>(y) * static_cast<std::size_t>(gridWidth) + static_cast<std::size_t>(x);
                std::uint32_t renderColor = unvisitedColor;

                if (grid[idx].visited)
                {
                    std::uint8_t intensity = cellColorIntensity[idx];

                    if (intensity > 100)
                    {
                        renderColor = SDL_MapRGB(screen->format, intensity, static_cast<std::uint8_t>(255 - intensity), 40);
                    }
                    else
                    {
                        if (cellColorIntensity[idx] > 0) cellColorIntensity[idx]--;
                        std::uint8_t bG = static_cast<std::uint8_t>(30 + (y * 3));
                        std::uint8_t bB = static_cast<std::uint8_t>(50 + (x * 2));
                        renderColor = SDL_MapRGB(screen->format, cellColorIntensity[idx], bG, bB);
                    }
                }

                if (!stack.empty() && idx == stack.back())
                {
                    renderColor = SDL_MapRGB(screen->format, 255, 255, 255);
                }

                drawGridCell(screen, x, y, cellSize, grid[idx], renderColor, wallColor);
            }
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);
        SDL_Delay(8);
    }

    SDL_Quit();
    return 0;
}
