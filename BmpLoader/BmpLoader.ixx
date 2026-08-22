// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <memory_resource>
#include <cstdint>
#include <vector>
#include <expected>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <limits>

export module BmpLoader;

export namespace BmpLoader
{
#pragma pack(push, 1)
    struct BmpFileHeader
    {
        std::uint16_t type{ 0 };
        std::uint32_t size{ 0 };
        std::uint16_t reserved1{ 0 };
        std::uint16_t reserved2{ 0 };
        std::uint32_t offset_data{ 0 };
    };

    struct BmpInfoHeader
    {
        std::uint32_t size{ 0 };
        std::int32_t  width{ 0 };
        std::int32_t  height{ 0 };
        std::uint16_t planes{ 0 };
        std::uint16_t bit_count{ 0 };
        std::uint32_t compression{ 0 };
        std::uint32_t size_image{ 0 };
        std::int32_t  x_pixels_per_meter{ 0 };
        std::int32_t  y_pixels_per_meter{ 0 };
        std::uint32_t colors_used{ 0 };
        std::uint32_t colors_important{ 0 };
    };
#pragma pack(pop)

    struct Image
    {
        std::uint8_t  bpp{ 0 };
        std::uint32_t width{ 0 };
        std::uint32_t height{ 0 };
        std::vector<std::uint8_t> pixels{};
    };

    enum class Error
    {
        FileNotFound,
        InvalidFormat,
        UnsupportedBpp,
        CorruptedHeader,
        ReadError
    };

    std::expected<Image, Error> Load(const std::filesystem::path& path) noexcept;

    std::expected<Image, Error> Load(const std::filesystem::path& path) noexcept
    {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            return std::unexpected(Error::FileNotFound);
        }

        BmpFileHeader file_header{};
        BmpInfoHeader info_header{};

        constexpr std::streamsize file_hdr_size = static_cast<std::streamsize>(sizeof(BmpFileHeader));
        constexpr std::streamsize info_hdr_size = static_cast<std::streamsize>(sizeof(BmpInfoHeader));

        if (!file.read(reinterpret_cast<char*>(&file_header), file_hdr_size) ||
            !file.read(reinterpret_cast<char*>(&info_header), info_hdr_size))
        {
            return std::unexpected(Error::CorruptedHeader);
        }

        if (file_header.type != 0x4D42)
        {
            return std::unexpected(Error::InvalidFormat);
        }

        if (info_header.compression != 0 || (info_header.bit_count != 24 && info_header.bit_count != 32))
        {
            return std::unexpected(Error::UnsupportedBpp);
        }

        if (info_header.width == std::numeric_limits<std::int32_t>::min() ||
            info_header.height == std::numeric_limits<std::int32_t>::min())
        {
            return std::unexpected(Error::InvalidFormat);
        }

        const std::uint32_t width = static_cast<std::uint32_t>(std::abs(info_header.width));
        const std::uint32_t height = static_cast<std::uint32_t>(std::abs(info_header.height));
        const bool is_top_down = info_header.height < 0;

        Image img{ .bpp = 4, .width = width, .height = height, .pixels = {} };

        const std::size_t total_pixels = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
        if (total_pixels > std::numeric_limits<std::size_t>::max() / 4U)
        {
            return std::unexpected(Error::InvalidFormat);
        }

        img.pixels.resize(total_pixels * 4U);

        if (!file.seekg(static_cast<std::streamoff>(file_header.offset_data), std::ios::beg))
        {
            return std::unexpected(Error::ReadError);
        }

        const std::uint32_t bytes_per_pixel = static_cast<std::uint32_t>(info_header.bit_count / 8U);

        const std::uint32_t row_stride = (width * bytes_per_pixel + 3U) & ~3U;

        if (row_stride > static_cast<std::uint32_t>(std::numeric_limits<std::streamsize>::max()))
        {
            return std::unexpected(Error::InvalidFormat);
        }
        const std::streamsize read_stride = static_cast<std::streamsize>(row_stride);

        std::vector<std::uint8_t> row_buffer(row_stride);

        for (std::uint32_t y = 0; y < height; ++y)
        {
            if (!file.read(reinterpret_cast<char*>(row_buffer.data()), read_stride))
            {
                return std::unexpected(Error::ReadError);
            }

            const std::uint32_t target_y = is_top_down ? y : (height - 1U - y);
            const std::uint32_t target_row_offset = target_y * width * 4U;

            for (std::uint32_t x = 0; x < width; ++x)
            {
                const std::uint32_t src_idx = x * bytes_per_pixel;
                const std::uint32_t dst_idx = target_row_offset + (x * 4U);

                img.pixels[dst_idx + 0U] = row_buffer[src_idx + 2U];
                img.pixels[dst_idx + 1U] = row_buffer[src_idx + 1U];
                img.pixels[dst_idx + 2U] = row_buffer[src_idx + 0U];

                if (bytes_per_pixel == 4U)
                {
                    img.pixels[dst_idx + 3U] = row_buffer[src_idx + 3U];
                }
                else
                {
                    img.pixels[dst_idx + 3U] = 255U;
                }
            }
        }

        return img;
    }
}
