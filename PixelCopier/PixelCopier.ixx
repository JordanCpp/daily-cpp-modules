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

        /**
         * @brief OVERLOAD: Traditional plug-and-play direct copy method (1:1 scale matching native size)
         * @param screenX Destination coordinate on horizontal X-axis
         * @param screenY Destination coordinate on vertical Y-axis
         * @param bufferWidth Total width of the source asset buffer
         * @param bufferHeight Total height of the source asset buffer
         * @param bufferBytesPerPixel Byte density per pixel of the input source asset (3 or 4)
         * @param bufferSource Safe view handle over constant source image pixels array
         */
        constexpr void Copy(int screenX, int screenY, std::size_t bufferWidth, std::size_t bufferHeight, std::size_t bufferBytesPerPixel, std::span<const std::uint8_t> bufferSource) noexcept
        {
            // Simply forwards execution parameters straight into the advanced scaling pipeline
            Copy(screenX, screenY, static_cast<int>(bufferWidth), static_cast<int>(bufferHeight),
                bufferSource, bufferWidth, bufferHeight, bufferBytesPerPixel,
                0, 0, static_cast<int>(bufferWidth), static_cast<int>(bufferHeight));
        }

        /**
         * @brief ADVANCED: Software rendering upscale/downscale engine with source cropping and viewport clipping.
         * @param screenX Destination viewport location on horizontal X-axis (can be negative)
         * @param screenY Destination viewport location on vertical Y-axis (can be negative)
         * @param screenW Requested width bounding target viewport destination region
         * @param screenH Requested height bounding target viewport destination region
         * @param bufferSource Safe view handle over constant source image pixels array
         * @param bufferWidth Complete total width of the source asset buffer
         * @param bufferHeight Complete total height of the source asset buffer
         * @param bufferBytesPerPixel Byte density per pixel of the input source asset (3 or 4)
         * @param srcX Coordinate X of the sub-rectangle boundary crop start inside source asset
         * @param srcY Coordinate Y of the sub-rectangle boundary crop start inside source asset
         * @param srcSubW Width dimension of the sub-rectangle crop region from source asset
         * @param srcSubH Height dimension of the sub-rectangle crop region from source asset
         */
        constexpr void Copy(int screenX, int screenY, int screenW, int screenH,
            std::span<const std::uint8_t> bufferSource, std::size_t bufferWidth, std::size_t bufferHeight, std::size_t bufferBytesPerPixel,
            int srcX, int srcY, int srcSubW, int srcSubH) noexcept
        {
            // Fail-safe sanity parameters checks protecting against invalid memory access configurations
            if (screenW <= 0 || screenH <= 0 || srcSubW <= 0 || srcSubH <= 0 || bufferSource.empty() || bufferWidth == 0 || bufferHeight == 0) [[unlikely]]
            {
                return;
            }

            // High-speed analytical pre-calculations of scales mapping coordinates across spaces
            const float scaleX = static_cast<float>(srcSubW) / static_cast<float>(screenW);
            const float scaleY = static_cast<float>(srcSubH) / static_cast<float>(screenH);

            // Bounded nested viewport loops utilizing clipping against destination backbuffer resolution
            for (int dy = 0; dy < screenH; ++dy)
            {
                const int destY = screenY + dy;
                if (destY < 0 || destY >= static_cast<int>(_height)) [[likely]]
                {
                    if (destY < 0) continue;
                    else break; // Performance optimization: if we fly past the canvas bottom boundary, abort further rows loop evaluation
                }

                // Map row offset index to the nearest matching sampling source row geometry
                const int relativeSrcY = srcY + static_cast<int>(static_cast<float>(dy) * scaleY);
                if (relativeSrcY < 0 || relativeSrcY >= static_cast<int>(bufferHeight)) [[unlikely]]
                {
                    continue;
                }

                const std::size_t destRowOffset = static_cast<std::size_t>(destY) * _width;
                const std::size_t srcRowOffset = static_cast<std::size_t>(relativeSrcY) * bufferWidth;

                for (int dx = 0; dx < screenW; ++dx)
                {
                    const int destX = screenX + dx;
                    if (destX < 0 || destX >= static_cast<int>(_width)) [[likely]]
                    {
                        if (destX < 0) continue;
                        else break; // Performance optimization: if we fly past the canvas right margin, advance immediately to the next row sequence
                    }

                    // Map column offset index to the nearest matching sampling source column geometry
                    const int relativeSrcX = srcX + static_cast<int>(static_cast<float>(dx) * scaleX);
                    if (relativeSrcX < 0 || relativeSrcX >= static_cast<int>(bufferWidth)) [[unlikely]]
                    {
                        continue;
                    }

                    // Compute physical byte address mappings within memory blocks
                    const std::size_t dstPixelIdx = (destRowOffset + static_cast<std::size_t>(destX)) * _bytesPerPixel;
                    const std::size_t srcPixelIdx = (srcRowOffset + static_cast<std::size_t>(relativeSrcX)) * bufferBytesPerPixel;

                    // Direct pipeline channel assignments aligned to platform byte index mapping layouts
                    _pixels[dstPixelIdx + idxR] = bufferSource[srcPixelIdx + 0];
                    _pixels[dstPixelIdx + idxG] = bufferSource[srcPixelIdx + 1];
                    _pixels[dstPixelIdx + idxB] = bufferSource[srcPixelIdx + 2];

                    if (_bytesPerPixel == 4)
                    {
                        _pixels[dstPixelIdx + idxA] = (bufferBytesPerPixel == 4) ? bufferSource[srcPixelIdx + 3] : alphaByte;
                    }
                }
            }
        }
    };
}
