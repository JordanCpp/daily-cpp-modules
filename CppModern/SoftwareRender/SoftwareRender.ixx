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

#if defined(_WIN32) || defined(__CYGWIN__)
    inline constexpr std::size_t idxR = 2;
    inline constexpr std::size_t idxG = 1;
    inline constexpr std::size_t idxB = 0;
#else
    inline constexpr std::size_t idxR = 0;
    inline constexpr std::size_t idxG = 1;
    inline constexpr std::size_t idxB = 2;
#endif
    inline constexpr std::size_t idxA = 3;

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
                    _pixels[i + idxR] = _color.r;
                    _pixels[i + idxG] = _color.g;
                    _pixels[i + idxB] = _color.b;
                    _pixels[i + idxA] = _color.a;
                }
            }
            else
            {
                for (std::size_t i = 0; i < _pixels.size(); i += 3)
                {
                    _pixels[i + idxR] = _color.r;
                    _pixels[i + idxG] = _color.g;
                    _pixels[i + idxB] = _color.b;
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

            _pixels[index + idxR] = _color.r;
            _pixels[index + idxG] = _color.g;
            _pixels[index + idxB] = _color.b;

            if (_bytesPerPixel == 4)
            {
                _pixels[index + idxA] = _color.a;
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
                    _pixels[index + idxR] = _color.r;
                    _pixels[index + idxG] = _color.g;
                    _pixels[index + idxB] = _color.b;

                    if (_bytesPerPixel == 4)
                    {
                        _pixels[index + idxA] = _color.a;
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
                        _pixels[rowStart + idxR] = _color.r;
                        _pixels[rowStart + idxG] = _color.g;
                        _pixels[rowStart + idxB] = _color.b;
                        _pixels[rowStart + idxA] = _color.a;
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
                        _pixels[rowStart + idxR] = _color.r;
                        _pixels[rowStart + idxG] = _color.g;
                        _pixels[rowStart + idxB] = _color.b;
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

        constexpr void Copy(int screenX, int screenY, std::size_t bufferWidth, std::size_t bufferHeight, std::size_t bufferBytesPerPixel, std::span<const std::uint8_t> bufferSource) noexcept
        {
            if (bufferWidth == 0 || bufferHeight == 0 || bufferSource.empty()) [[unlikely]]
            {
                return;
            }

            const int srcStartX  = std::max(0, -screenX);
            const int srcStartY  = std::max(0, -screenY);
            const int destStartX = std::max(0, screenX);
            const int destStartY = std::max(0, screenY);

            const int visibleWidth  = std::min(static_cast<int>(bufferWidth)  - srcStartX, static_cast<int>(_width)  - destStartX);
            const int visibleHeight = std::min(static_cast<int>(bufferHeight) - srcStartY, static_cast<int>(_height) - destStartY);

            if (visibleWidth <= 0 || visibleHeight <= 0) [[unlikely]]
            {
                return;
            }

            const std::size_t copyWidth  = static_cast<std::size_t>(visibleWidth);
            const std::size_t copyHeight = static_cast<std::size_t>(visibleHeight);

            for (std::size_t row = 0; row < copyHeight; ++row)
            {
                const std::size_t srcY  = static_cast<std::size_t>(srcStartY)  + row;
                const std::size_t destY = static_cast<std::size_t>(destStartY) + row;

                std::size_t srcRowOffset  = (srcY * bufferWidth + static_cast<std::size_t>(srcStartX)) * bufferBytesPerPixel;
                std::size_t destRowOffset = (destY * _width + static_cast<std::size_t>(destStartX)) * _bytesPerPixel;

                for (std::size_t col = 0; col < copyWidth; ++col)
                {
                    _pixels[destRowOffset + idxR] = bufferSource[srcRowOffset + 0];
                    _pixels[destRowOffset + idxG] = bufferSource[srcRowOffset + 1];
                    _pixels[destRowOffset + idxB] = bufferSource[srcRowOffset + 2];

                    if (_bytesPerPixel == 4)
                    {
                        _pixels[destRowOffset + 3] = (bufferBytesPerPixel == 4) ? bufferSource[srcRowOffset + 3] : alpha;
                    }

                    srcRowOffset  += bufferBytesPerPixel;
                    destRowOffset += _bytesPerPixel;
                }
            }
        }

    };
}
