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
    inline constexpr std::uint8_t alpha = 255;

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

    template <std::size_t BytesPerPixel>
    class SoftwareRender
    {
        static_assert(BytesPerPixel == 3 || BytesPerPixel == 4, "Only 3 or 4 bytes per pixel are supported.");

    private:
        std::size_t _width;
        std::size_t _height;
        std::span<std::uint8_t> _pixels;

    public:
        constexpr SoftwareRender(std::size_t w, std::size_t h, std::span<std::uint8_t> pixels) noexcept :
            _width(w),
            _height(h),
            _pixels(pixels)
        {
        }

        constexpr void Clear(Color color) noexcept
        {
            if (color.r == color.g && color.g == color.b && (BytesPerPixel == 3 || color.g == color.a))
            {
                std::fill(_pixels.begin(), _pixels.end(), color.r);
                return;
            }

            if constexpr (BytesPerPixel == 4)
            {
                for (std::size_t i = 0; i < _pixels.size(); i += 4)
                {
                    _pixels[i + 0] = color.r;
                    _pixels[i + 1] = color.g;
                    _pixels[i + 2] = color.b;
                    _pixels[i + 3] = color.a;
                }
            }
            else if constexpr (BytesPerPixel == 3)
            {
                for (std::size_t i = 0; i < _pixels.size(); i += 3)
                {
                    _pixels[i + 0] = color.r;
                    _pixels[i + 1] = color.g;
                    _pixels[i + 2] = color.b;
                }
            }
        }

        constexpr void Pixel(std::size_t x, std::size_t y, Color color) noexcept
        {
            if (x >= _width || y >= _height) [[unlikely]]
            {
                return;
            }

            const std::size_t index = (y * _width + x) * BytesPerPixel;

            if (index + BytesPerPixel <= _pixels.size()) [[likely]]
            {
                _pixels[index + 0] = color.r;
                _pixels[index + 1] = color.g;
                _pixels[index + 2] = color.b;

                if constexpr (BytesPerPixel == 4)
                {
                    _pixels[index + 3] = color.a;
                }
            }
        }

        constexpr void Line(int x0, int y0, int x1, int y1, Color color) noexcept
        {
            const int dx = std::abs(x1 - x0);
            const int dy = std::abs(y1 - y0);
            const int sx = (x0 < x1) ? 1 : -1;
            const int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                if (x0 >= 0 && static_cast<std::size_t>(x0) < _width &&
                    y0 >= 0 && static_cast<std::size_t>(y0) < _height)
                {
                    Pixel(static_cast<std::size_t>(x0), static_cast<std::size_t>(y0), color);
                }

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

        constexpr void Fill(int x, int y, int width, int height, Color color) noexcept
        {
            if (width <= 0 || height <= 0) [[unlikely]]
            {
                return;
            }

            const std::size_t x0 = static_cast<std::size_t>(std::max(0, x));
            const std::size_t y0 = static_cast<std::size_t>(std::max(0, y));
            const std::size_t x1 = std::min(_width, static_cast<std::size_t>(x + width));
            const std::size_t y1 = std::min(_height, static_cast<std::size_t>(y + height));

            if (x0 >= x1 || y0 >= y1) [[unlikely]]
            {
                return;
            }

            for (std::size_t currY = y0; currY < y1; ++currY)
            {
                std::size_t rowStart = (currY * _width + x0) * BytesPerPixel;

                for (std::size_t currX = x0; currX < x1; ++currX)
                {
                    if (rowStart + BytesPerPixel <= _pixels.size()) [[likely]]
                    {
                        _pixels[rowStart + 0] = color.r;
                        _pixels[rowStart + 1] = color.g;
                        _pixels[rowStart + 2] = color.b;

                        if constexpr (BytesPerPixel == 4)
                        {
                            _pixels[rowStart + 3] = color.a;
                        }
                    }
                    rowStart += BytesPerPixel;
                }
            }
        }

        [[nodiscard]] constexpr std::size_t GetWidth() const noexcept
        {
            return _width; 
        }

        [[nodiscard]] constexpr std::size_t GetHeight() const noexcept 
        { 
            return _height;
        }

        [[nodiscard]] static constexpr std::size_t GetBytesPerPixel() noexcept 
        { 
            return BytesPerPixel; 
        }
    };
}
