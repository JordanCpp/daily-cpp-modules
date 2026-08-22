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

export module PixelCopier;

export namespace Software
{
    inline constexpr std::uint8_t alphaByte = 255;

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

    class PixelCopier
    {
    private:
        std::size_t _width;
        std::size_t _height;
        std::size_t _bytesPerPixel;
        std::span<std::uint8_t> _pixels;

    public:
        constexpr PixelCopier(std::size_t w, std::size_t h, std::size_t bytesPerPixel, std::span<std::uint8_t> pixels) :
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
                        _pixels[destRowOffset + 3] = (bufferBytesPerPixel == 4) ? bufferSource[srcRowOffset + 3] : alphaByte;
                    }

                    srcRowOffset  += bufferBytesPerPixel;
                    destRowOffset += _bytesPerPixel;
                }
            }
        }
    };
}
