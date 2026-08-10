// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <span>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <stdexcept>

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

    class SoftwareRender
    {
    private:
        Color       _color;
        std::size_t _width;
        std::size_t _height;
        std::size_t _bytesPerPixel;
        std::span<std::uint8_t> _pixels;

    public:
        constexpr SoftwareRender(std::size_t w, std::size_t h, std::size_t bytesPerPixel, std::span<std::uint8_t> pixels) :
            _width(w),
            _height(h),
            _bytesPerPixel(bytesPerPixel),
            _pixels(pixels)
        {
            if (_bytesPerPixel != 3 && _bytesPerPixel != 4)
            {
                throw std::invalid_argument("Only 3 or 4 bytes per pixel are supported.");
            }
        }

        constexpr void SetColor(Color color) noexcept
        {
            _color = color;
        }

        constexpr void Clear() noexcept
        {
            if (_color.r == _color.g && _color.g == _color.b && (_bytesPerPixel == 3 || _color.g == _color.a))
            {
                std::fill(_pixels.begin(), _pixels.end(), _color.r);
                return;
            }

            if (_bytesPerPixel == 4)
            {
                for (std::size_t i = 0; i < _pixels.size(); i += 4)
                {
                    _pixels[i + 0] = _color.r;
                    _pixels[i + 1] = _color.g;
                    _pixels[i + 2] = _color.b;
                    _pixels[i + 3] = _color.a;
                }
            }
            else
            {
                for (std::size_t i = 0; i < _pixels.size(); i += 3)
                {
                    _pixels[i + 0] = _color.r;
                    _pixels[i + 1] = _color.g;
                    _pixels[i + 2] = _color.b;
                }
            }
        }

        constexpr void Pixel(std::size_t x, std::size_t y) noexcept
        {
            if (x >= _width || y >= _height) [[unlikely]]
            {
                return;
            }

            const std::size_t index = (y * _width + x) * _bytesPerPixel;

            _pixels[index + 0] = _color.r;
            _pixels[index + 1] = _color.g;
            _pixels[index + 2] = _color.b;

            if (_bytesPerPixel == 4)
            {
                _pixels[index + 3] = _color.a;
            }
        }

        constexpr void Line(int x0, int y0, int x1, int y1) noexcept
        {
            const int dx = std::abs(x1 - x0);
            const int dy = std::abs(y1 - y0);
            const int sx = (x0 < x1) ? 1 : -1;
            const int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                if (x0 >= 0 && static_cast<std::size_t>(x0) < _width &&
                    y0 >= 0 && static_cast<std::size_t>(y0) < _height) [[likely]]
                {
                    const std::size_t index = (static_cast<std::size_t>(y0) * _width + static_cast<std::size_t>(x0)) * _bytesPerPixel;
                    _pixels[index + 0] = _color.r;
                    _pixels[index + 1] = _color.g;
                    _pixels[index + 2] = _color.b;

                    if (_bytesPerPixel == 4)
                    {
                        _pixels[index + 3] = _color.a;
                    }
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

        constexpr void Fill(int x, int y, int width, int height) noexcept
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

            if (_bytesPerPixel == 4)
            {
                for (std::size_t currY = y0; currY < y1; ++currY)
                {
                    std::size_t rowStart = (currY * _width + x0) * 4;
                    for (std::size_t currX = x0; currX < x1; ++currX)
                    {
                        _pixels[rowStart + 0] = _color.r;
                        _pixels[rowStart + 1] = _color.g;
                        _pixels[rowStart + 2] = _color.b;
                        _pixels[rowStart + 3] = _color.a;
                        rowStart += 4;
                    }
                }
            }
            else
            {
                for (std::size_t currY = y0; currY < y1; ++currY)
                {
                    std::size_t rowStart = (currY * _width + x0) * 3;
                    for (std::size_t currX = x0; currX < x1; ++currX)
                    {
                        _pixels[rowStart + 0] = _color.r;
                        _pixels[rowStart + 1] = _color.g;
                        _pixels[rowStart + 2] = _color.b;
                        rowStart += 3;
                    }
                }
            }
        }

        [[nodiscard]] constexpr Color GetColor() const noexcept
        {
            return _color;
        }

        [[nodiscard]] constexpr std::size_t GetWidth() const noexcept
        {
            return _width;
        }

        [[nodiscard]] constexpr std::size_t GetHeight() const noexcept
        {
            return _height;
        }

        [[nodiscard]] constexpr std::size_t GetBytesPerPixel() const noexcept
        {
            return _bytesPerPixel;
        }
    };
}
