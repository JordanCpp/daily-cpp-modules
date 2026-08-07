// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <span>
#include <cmath>
#include <cstdint>
#include <algorithm>

export module SoftwareRender;

export namespace Software
{
    const int alpha = 255;

    struct Color
    {
        std::uint8_t r{ 0 };
        std::uint8_t g{ 0 };
        std::uint8_t b{ 0 };
        std::uint8_t a{ alpha };

        constexpr Color() noexcept = default;
        constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = alpha) noexcept :
            r(red), 
            g(green), 
            b(blue),
            a(alpha) 
        {
        }
    };

    class SoftwareRender
    {
    private:
        int _width;
        int _height;
        int _bytes;
        std::span<std::uint8_t> _pixels;
    public:
        SoftwareRender(int w, int h, int bytes, std::span<std::uint8_t> pixels) noexcept :
            _width(w),
            _height(h),
            _bytes(bytes),
            _pixels(pixels)
        {
        }

        void Clear(Color color) noexcept
        {
            if (_bytes == 4)
            {
                for (std::size_t i = 0; i < _pixels.size(); i += 4)
                {
                    _pixels[i + 0] = color.r;
                    _pixels[i + 1] = color.g;
                    _pixels[i + 2] = color.b;
                    _pixels[i + 3] = color.a;
                }
            }
            else
            {
                for (std::size_t i = 0; i < _pixels.size(); i += 3)
                {
                    _pixels[i + 0] = color.r;
                    _pixels[i + 1] = color.g;
                    _pixels[i + 2] = color.b;
                }
            }
        }

        void Pixel(int x, int y, Color color) noexcept
        {
            if (x >= 0 && x < _width && y >= 0 && y < _height)
            {
                std::size_t index = static_cast<std::size_t>(y * _width + x) * _bytes;
                _pixels[index + 0] = color.r;
                _pixels[index + 1] = color.g;
                _pixels[index + 2] = color.b;

                if (_bytes == 4)
                {
                    _pixels[index + 3] = color.a;
                }
            }
        }

        void Line(int x0, int y0, int x1, int y1, Color color) noexcept
        {
            const int dx = std::abs(x1 - x0);
            const int dy = std::abs(y1 - y0);
            const int sx = (x0 < x1) ? 1 : -1;
            const int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                Pixel(x0, y0, color);

                if (x0 == x1 && y0 == y1)
                {
                    break;
                }

                int e2 = 2 * err;
                if (e2 > -dy)
                {
                    err -= dy;
                    x0 += sx;
                }
                if (e2 < dx)
                {
                    err += dx;
                    y0 += sy;
                }
            }
        }

        void Fill(int x, int y, int width, int height, Color color) noexcept
        {
            int x0 = std::max(0, x);
            int y0 = std::max(0, y);
            int x1 = std::min(_width,  x + width);
            int y1 = std::min(_height, y + height);

            if (x0 >= x1 || y0 >= y1) [[unlikely]]
            {
                return;
            }

            for (int currY = y0; currY < y1; ++currY)
            {
                std::size_t rowStart = static_cast<std::size_t>(currY * _width + x0) * _bytes;

                if (_bytes == 4)
                {
                    for (int currX = x0; currX < x1; ++currX)
                    {
                        _pixels[rowStart + 0] = color.r;
                        _pixels[rowStart + 1] = color.g;
                        _pixels[rowStart + 2] = color.b;
                        _pixels[rowStart + 3] = color.a;
                        rowStart += 4;
                    }
                }
                else
                {
                    for (int currX = x0; currX < x1; ++currX)
                    {
                        _pixels[rowStart + 0] = color.r;
                        _pixels[rowStart + 1] = color.g;
                        _pixels[rowStart + 2] = color.b;
                        rowStart += 3;
                    }
                }
            }
        }
    };
}
