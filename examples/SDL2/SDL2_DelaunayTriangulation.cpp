// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

struct Point2D {
    float x;
    float y;
};

struct Triangle {
    std::size_t p1;
    std::size_t p2;
    std::size_t p3;
    bool is_bad;
};

struct Edge {
    std::size_t p1;
    std::size_t p2;
};

[[nodiscard]] bool is_point_in_circumcircle(const Point2D& p, const Point2D& p1, const Point2D& p2, const Point2D& p3) noexcept;

[[nodiscard]] bool is_point_in_circumcircle(const Point2D& p, const Point2D& p1, const Point2D& p2, const Point2D& p3) noexcept
{
    float ab = p1.x * p1.x + p1.y * p1.y;
    float cd = p2.x * p2.x + p2.y * p2.y;
    float ef = p3.x * p3.x + p3.y * p3.y;

    float den = p1.x * (p3.y - p2.y) + p2.x * (p1.y - p3.y) + p3.x * (p2.y - p1.y);
    if (std::abs(den) < 0.0001f) return false;

    float circum_x = (ab * (p3.y - p2.y) + cd * (p1.y - p3.y) + ef * (p2.y - p1.y)) / den * 0.5f;
    float circum_y = (ab * (p3.x - p2.x) + cd * (p1.x - p3.x) + ef * (p2.x - p1.x)) /
        (p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) + p3.y * (p2.x - p1.x)) * 0.5f;

    float dx = p1.x - circum_x;
    float dy = p1.y - circum_y;
    float r_sq = dx * dx + dy * dy;

    float p_dx = p.x - circum_x;
    float p_dy = p.y - circum_y;
    float p_dist_sq = p_dx * p_dx + p_dy * p_dy;

    return p_dist_sq <= r_sq;
}

[[nodiscard]] std::vector<Triangle> triangulate(const std::vector<Point2D>& points);

[[nodiscard]] std::vector<Triangle> triangulate(const std::vector<Point2D>& points)
{
    std::vector<Triangle> triangles;
    if (points.size() < 3) return triangles;

    std::vector<Point2D> pts = points;

    std::size_t st_idx1 = pts.size();
    pts.push_back(Point2D{ -2000.0f, -2000.0f });
    std::size_t st_idx2 = pts.size();
    pts.push_back(Point2D{ 4000.0f, -2000.0f });
    std::size_t st_idx3 = pts.size();
    pts.push_back(Point2D{ 800.0f, 4000.0f });

    triangles.push_back(Triangle{ st_idx1, st_idx2, st_idx3, false });

    for (std::size_t i = 0; i < points.size(); ++i)
    {
        std::vector<Edge> polygon;

        for (auto& t : triangles)
        {
            if (is_point_in_circumcircle(pts[i], pts[t.p1], pts[t.p2], pts[t.p3]))
            {
                t.is_bad = true;
                polygon.push_back(Edge{ t.p1, t.p2 });
                polygon.push_back(Edge{ t.p2, t.p3 });
                polygon.push_back(Edge{ t.p3, t.p1 });
            }
        }

        auto it = std::remove_if(triangles.begin(), triangles.end(), [](const Triangle& t) noexcept {
            return t.is_bad;
            });
        triangles.erase(it, triangles.end());

        std::vector<Edge> unique_polygon;
        unique_polygon.reserve(polygon.size());

        for (std::size_t e1 = 0; e1 < polygon.size(); ++e1)
        {
            bool is_shared = false;
            for (std::size_t e2 = 0; e2 < polygon.size(); ++e2)
            {
                if (e1 == e2) continue;
                if ((polygon[e1].p1 == polygon[e2].p2 && polygon[e1].p2 == polygon[e2].p1) ||
                    (polygon[e1].p1 == polygon[e2].p1 && polygon[e1].p2 == polygon[e2].p2))
                {
                    is_shared = true;
                    break;
                }
            }
            if (!is_shared)
            {
                unique_polygon.push_back(polygon[e1]);
            }
        }

        for (const auto& edge : unique_polygon)
        {
            triangles.push_back(Triangle{ edge.p1, edge.p2, i, false });
        }
    }

    auto it_cleanup = std::remove_if(triangles.begin(), triangles.end(), [st_idx1, st_idx2, st_idx3](const Triangle& t) noexcept {
        return t.p1 == st_idx1 || t.p2 == st_idx1 || t.p3 == st_idx1 ||
            t.p1 == st_idx2 || t.p2 == st_idx2 || t.p3 == st_idx2 ||
            t.p1 == st_idx3 || t.p2 == st_idx3 || t.p3 == st_idx3;
        });
    triangles.erase(it_cleanup, triangles.end());

    return triangles;
}

int main(int, char* [])
{
    SDL2Loader loader;

    if (!loader.load())
    {
        std::println(std::cerr, "Critical Error: Failed to map SDL2 runtime binaries.");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::println(std::cerr, "Failed to initialize SDL! Error: {}", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Delaunay Triangulation Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::println(std::cerr, "Failed to create window! Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::println(std::cerr, "Failed to create renderer! Error: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<Point2D> points;
    points.reserve(500);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist_x(50.0f, static_cast<float>(SCREEN_WIDTH) - 50.0f);
    std::uniform_real_distribution<float> dist_y(50.0f, static_cast<float>(SCREEN_HEIGHT) - 50.0f);
    for (std::int32_t i = 0; i < 10; ++i)
    {
        points.push_back(Point2D{ dist_x(rng), dist_y(rng) });
    }

    std::vector<Triangle> mesh = triangulate(points);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    points.push_back(Point2D{ static_cast<float>(event.button.x), static_cast<float>(event.button.y) });
                    mesh = triangulate(points);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 22, 24, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 160, 220, 255);
        for (const auto& t : mesh)
        {
            SDL_RenderDrawLine(renderer, static_cast<std::int32_t>(points[t.p1].x), static_cast<std::int32_t>(points[t.p1].y), static_cast<std::int32_t>(points[t.p2].x), static_cast<std::int32_t>(points[t.p2].y));
            SDL_RenderDrawLine(renderer, static_cast<std::int32_t>(points[t.p2].x), static_cast<std::int32_t>(points[t.p2].y), static_cast<std::int32_t>(points[t.p3].x), static_cast<std::int32_t>(points[t.p3].y));
            SDL_RenderDrawLine(renderer, static_cast<std::int32_t>(points[t.p3].x), static_cast<std::int32_t>(points[t.p3].y), static_cast<std::int32_t>(points[t.p1].x), static_cast<std::int32_t>(points[t.p1].y));
        }

        SDL_SetRenderDrawColor(renderer, 255, 90, 120, 255);
        for (const auto& pt : points)
        {
            SDL_Rect r{ static_cast<std::int32_t>(pt.x) - 3, static_cast<std::int32_t>(pt.y) - 3, 6, 6 };
            SDL_RenderFillRect(renderer, &r);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
