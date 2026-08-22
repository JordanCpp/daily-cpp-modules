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
        std::size_t            _width;
        std::size_t            _height;
        std::size_t            _bytesPerPixel;
        std::span<std::uint8_t>_pixels;
        constexpr void ValidateBounds(std::size_t w, std::size_t h, std::size_t bpp, std::size_t spanSize) const
        {
            if (w > 0 && h > 0 && spanSize < (w * h * bpp))
            {
                throw std::out_of_range("Pixel buffer size is smaller than width * height * bytesPerPixel.");
            }
        }

    public:
        constexpr PixelCopier(
            std::size_t             w,
            std::size_t             h,
            std::size_t             bytesPerPixel,
            std::span<std::uint8_t> pixels
        ) :
            _width{ w },
            _height{ h },
            _bytesPerPixel{ bytesPerPixel },
            _pixels{ pixels }
        {
            if (_bytesPerPixel != 3 && _bytesPerPixel != 4)
            {
                throw std::invalid_argument("Only 3 or 4 bytes per pixel are supported.");
            }
            ValidateBounds(_width, _height, _bytesPerPixel, _pixels.size());
        }
        [[nodiscard]] constexpr std::size_t GetWidth() const noexcept { return _width; }
        [[nodiscard]] constexpr std::size_t GetHeight() const noexcept { return _height; }
        [[nodiscard]] constexpr std::size_t GetBytesPerPixel() const noexcept { return _bytesPerPixel; }

        constexpr void Copy(
            int                          screenX,
            int                          screenY,
            std::size_t                  bufferWidth,
            std::size_t                  bufferHeight,
            std::size_t                  bufferBytesPerPixel,
            std::span<const std::uint8_t> bufferSource
        ) noexcept
        {
            Copy(
                screenX, screenY,
                static_cast<int>(bufferWidth), static_cast<int>(bufferHeight),
                bufferSource,
                bufferWidth, bufferHeight, bufferBytesPerPixel,
                0, 0,
                static_cast<int>(bufferWidth), static_cast<int>(bufferHeight)
            );
        }

        constexpr void Copy(
            int                          screenX,
            int                          screenY,
            int                          screenW,
            int                          screenH,
            std::span<const std::uint8_t> bufferSource,
            std::size_t                  bufferWidth,
            std::size_t                  bufferHeight,
            std::size_t                  bufferBytesPerPixel,
            int                          srcX,
            int                          srcY,
            int                          srcSubW,
            int                          srcSubH
        ) noexcept
        {
            if (screenW <= 0 || screenH <= 0 || srcSubW <= 0 || srcSubH <= 0 ||
                bufferWidth == 0 || bufferHeight == 0 ||
                bufferSource.size() < (bufferWidth * bufferHeight * bufferBytesPerPixel))
            {
                return;
            }

            const int64_t scaleX_fp = (static_cast<int64_t>(srcSubW) << 16) / screenW;
            const int64_t scaleY_fp = (static_cast<int64_t>(srcSubH) << 16) / screenH;

            const bool dstHasAlpha = (_bytesPerPixel == 4);
            const bool srcHasAlpha = (bufferBytesPerPixel == 4);

            for (int dy = 0; dy < screenH; ++dy)
            {
                const int destY = screenY + dy;
                if (destY < 0) continue;
                if (destY >= static_cast<int>(_height)) break;

                const int relativeSrcY = srcY + static_cast<int>((static_cast<int64_t>(dy) * scaleY_fp) >> 16);
                if (relativeSrcY < 0 || relativeSrcY >= static_cast<int>(bufferHeight))
                {
                    continue;
                }

                const std::size_t destRowOffset = static_cast<std::size_t>(destY) * _width;
                const std::size_t srcRowOffset = static_cast<std::size_t>(relativeSrcY) * bufferWidth;

                for (int dx = 0; dx < screenW; ++dx)
                {
                    const int destX = screenX + dx;
                    if (destX < 0) continue;
                    if (destX >= static_cast<int>(_width)) break;

                    const int relativeSrcX = srcX + static_cast<int>((static_cast<int64_t>(dx) * scaleX_fp) >> 16);
                    if (relativeSrcX < 0 || relativeSrcX >= static_cast<int>(bufferWidth))
                    {
                        continue;
                    }

                    const std::size_t dstPixelIdx = (destRowOffset + static_cast<std::size_t>(destX)) * _bytesPerPixel;
                    const std::size_t srcPixelIdx = (srcRowOffset + static_cast<std::size_t>(relativeSrcX)) * bufferBytesPerPixel;

                    _pixels[dstPixelIdx + idxR] = bufferSource[srcPixelIdx + 0];
                    _pixels[dstPixelIdx + idxG] = bufferSource[srcPixelIdx + 1];
                    _pixels[dstPixelIdx + idxB] = bufferSource[srcPixelIdx + 2];

                    if (dstHasAlpha)
                    {
                        _pixels[dstPixelIdx + idxA] = srcHasAlpha ? bufferSource[srcPixelIdx + 3] : alphaByte;
                    }
                }
            }
        }

    };
}
