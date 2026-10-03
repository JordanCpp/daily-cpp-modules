// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL1.API;
import SDL1.Loader;

struct Vector3D
{
    float x, y, z;
};

struct Point2D
{
    int x, y;
};

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color);
inline void drawLine(SDL_Surface* surface, int x1, int y1, int x2, int y2, std::uint32_t color);
inline Vector3D rotate(const Vector3D& p, float angleX, float angleY);

inline void putPixel32(SDL_Surface* surface, int x, int y, std::uint32_t color)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;

    std::uint8_t* pixelPtr = static_cast<std::uint8_t*>(surface->pixels)
        + static_cast<std::size_t>(y) * static_cast<std::size_t>(surface->pitch)
        + static_cast<std::size_t>(x) * sizeof(std::uint32_t);
    *reinterpret_cast<std::uint32_t*>(pixelPtr) = color;
}

inline void drawLine(SDL_Surface* surface, int x1, int y1, int x2, int y2, std::uint32_t color)
{
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        putPixel32(surface, x1, y1, color);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

inline Vector3D rotate(const Vector3D& p, float angleX, float angleY)
{
    float radX = angleX;
    float cosX = std::cos(radX);
    float sinX = std::sin(radX);
    float y1 = p.y * cosX - p.z * sinX;
    float z1 = p.y * sinX + p.z * cosX;

    float radY = angleY;
    float cosY = std::cos(radY);
    float sinY = std::sin(radY);
    float x2 = p.x * cosY + z1 * sinY;
    float z2 = -p.x * sinY + z1 * cosY;

    return { x2, y1, z2 };
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

    SDL_WM_SetCaption("Daily C++ Modules - Demo 5: Wireframe 3D Cube", nullptr);

    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (!screen)
    {
        std::println(std::cerr, "Video Mode Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    std::array<Vector3D, 8> vertices = { {
        {-1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, {-1.0f,  1.0f, -1.0f},
        {-1.0f, -1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f}
    } };

    std::array<std::pair<int, int>, 12> edges = { {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    } };

    bool isRunning = true;
    SDL_Event event{};

    float angleX = 0.0f;
    float angleY = 0.0f;

    constexpr float fov = 400.0f;
    constexpr float cameraDistance = 3.5f;
    constexpr int centerX = screenWidth / 2;
    constexpr int centerY = screenHeight / 2;

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

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 10, 15, 25));

        if (SDL_MUSTLOCK(screen))
        {
            if (SDL_LockSurface(screen) < 0) continue;
        }

        std::array<Point2D, 8> projectedVertices{};

        for (std::size_t i = 0; i < vertices.size(); ++i)
        {
            Vector3D rotated = rotate(vertices[i], angleX, angleY);

            float distanceZ = rotated.z + cameraDistance;

            projectedVertices[i].x = static_cast<int>((rotated.x * fov) / distanceZ) + centerX;
            projectedVertices[i].y = static_cast<int>((rotated.y * fov) / distanceZ) + centerY;
        }

        std::uint32_t lineColor = SDL_MapRGB(screen->format, 0, 255, 220);
        for (const auto& edge : edges)
        {
            const Point2D& p1 = projectedVertices[static_cast<std::size_t>(edge.first)];
            const Point2D& p2 = projectedVertices[static_cast<std::size_t>(edge.second)];
            drawLine(screen, p1.x, p1.y, p2.x, p2.y, lineColor);
        }

        if (SDL_MUSTLOCK(screen))
        {
            SDL_UnlockSurface(screen);
        }

        SDL_Flip(screen);

        angleX += 0.02f;
        angleY += 0.03f;

        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}
