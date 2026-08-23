// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import App;
import WinLite;
import PixelPainter;
import PixelCopier;
import FpsCounter;

using namespace WinLite;
using namespace Software;

enum class GridCell : std::uint8_t {
    Empty = 0,
    Sand = 1
};

struct CellColor {
    std::uint8_t r, g, b;
};

int main()
{
    constexpr std::size_t width = 800;
    constexpr std::size_t height = 800;

    App app;
    if (!app.Init(width, height, "Daily C++ Modules: Falling Sand Sandbox"))
    {
        return -1;
    }

    std::vector<GridCell> currentGrid(width * height, GridCell::Empty);
    std::vector<GridCell> nextGrid(width * height, GridCell::Empty);
    std::vector<CellColor> colorGrid(width * height, CellColor{ 0, 0, 0 });
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> colorDist(160, 240);

    bool isMousePressed = false;
    int mouseX = 0;
    int mouseY = 0;
    float elapsed = 0.0f;

    app.OnEvent = [&](const Event& event) noexcept {
        if (event.Type == EventType::MouseMove)
        {
            mouseX = event.Mouse.PosX;
            mouseY = event.Mouse.PosY;
        }

        if (event.IsMousePressed(MouseButton::Left))
        {
            isMousePressed = true;
        }
        if (event.IsMouseReleased(MouseButton::Left))
        {
            isMousePressed = false;
        }
        };

    app.OnUpdate = [&](float deltaTime) noexcept {
        elapsed += deltaTime;

        if (isMousePressed && mouseX >= 4 && mouseX < static_cast<int>(width) - 4 &&
            mouseY >= 4 && mouseY < static_cast<int>(height) - 4)
        {
            for (int dy = -3; dy <= 3; ++dy)
            {
                for (int dx = -3; dx <= 3; ++dx)
                {
                    if ((dx * dx + dy * dy) <= 9)
                    {
                        std::size_t spawnX = static_cast<std::size_t>(mouseX + dx);
                        std::size_t spawnY = static_cast<std::size_t>(mouseY + dy);
                        std::size_t idx = spawnY * width + spawnX;

                        if (currentGrid[idx] == GridCell::Empty)
                        {
                            currentGrid[idx] = GridCell::Sand;

                            std::uint8_t r = static_cast<std::uint8_t>(colorDist(gen));
                            std::uint8_t g = static_cast<std::uint8_t>(100.0f + 100.0f * std::sin(elapsed * 2.0f));
                            std::uint8_t b = static_cast<std::uint8_t>(80.0f + 50.0f * std::cos(elapsed * 1.5f));
                            colorGrid[idx] = CellColor{ r, g, b };
                        }
                    }
                }
            }
        }

        std::fill(nextGrid.begin(), nextGrid.end(), GridCell::Empty);

        for (int y = static_cast<int>(height) - 1; y >= 0; --y)
        {
            for (int x = 0; x < static_cast<int>(width); ++x)
            {
                std::size_t currentIdx = static_cast<std::size_t>(y * static_cast<int>(width) + x);

                if (currentGrid[currentIdx] == GridCell::Sand)
                {
                    int downY = y + 1;

                    if (downY < static_cast<int>(height))
                    {
                        std::size_t belowIdx = static_cast<std::size_t>(downY * static_cast<int>(width) + x);
                        std::size_t bottomLeftIdx = belowIdx - 1;
                        std::size_t bottomRightIdx = belowIdx + 1;

                        if (currentGrid[belowIdx] == GridCell::Empty && nextGrid[belowIdx] == GridCell::Empty)
                        {
                            nextGrid[belowIdx] = GridCell::Sand;
                            colorGrid[belowIdx] = colorGrid[currentIdx];
                        }
                        else if (x > 0 && currentGrid[bottomLeftIdx] == GridCell::Empty && nextGrid[bottomLeftIdx] == GridCell::Empty)
                        {
                            nextGrid[bottomLeftIdx] = GridCell::Sand;
                            colorGrid[bottomLeftIdx] = colorGrid[currentIdx];
                        }
                        else if (x < static_cast<int>(width) - 1 && currentGrid[bottomRightIdx] == GridCell::Empty && nextGrid[bottomRightIdx] == GridCell::Empty)
                        {
                            nextGrid[bottomRightIdx] = GridCell::Sand;
                            colorGrid[bottomRightIdx] = colorGrid[currentIdx];
                        }
                        else
                        {
                            nextGrid[currentIdx] = GridCell::Sand;
                            colorGrid[currentIdx] = colorGrid[currentIdx];
                        }
                    }
                    else
                    {
                        nextGrid[currentIdx] = GridCell::Sand;
                        colorGrid[currentIdx] = colorGrid[currentIdx];
                    }
                }
            }
        }
        currentGrid.swap(nextGrid);
        };

    app.OnRender = [&](PixelPainter& painter, PixelCopier&) noexcept {
        painter.SetColor(Color{ 18, 20, 26, 255 });
        painter.Clear();

        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                std::size_t idx = y * width + x;
                if (currentGrid[idx] == GridCell::Sand)
                {
                    const auto& col = colorGrid[idx];
                    painter.SetColor(Color{ col.r, col.g, col.b, 255 });
                    painter.Pixel(x, y);
                }
            }
        }
        };

    app.Run();

    return 0;
}
