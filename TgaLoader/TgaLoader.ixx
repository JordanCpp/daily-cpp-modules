// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <cstdint>
#include <vector>
#include <expected>
#include <fstream>
#include <filesystem>
#include <limits>

export module TgaLoader;

export namespace TgaLoader
{
#pragma pack(push, 1)
    struct TGAHeader {
        std::uint8_t  id_length{ 0 };
        std::uint8_t  color_map_type{ 0 };
        std::uint8_t  data_type_code{ 0 };
        std::uint16_t color_map_origin{ 0 };
        std::uint16_t color_map_length{ 0 };
        std::uint8_t  color_map_depth{ 0 };
        std::uint16_t x_origin{ 0 };
        std::uint16_t y_origin{ 0 };
        std::uint16_t width{ 0 };
        std::uint16_t height{ 0 };
        std::uint8_t  bits_per_pixel{ 0 };
        std::uint8_t  image_descriptor{ 0 };
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

    std::expected<Image, Error> load_from_file(const std::filesystem::path& path) noexcept;

    std::expected<Image, Error> load_from_file(const std::filesystem::path& path) noexcept
    {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            return std::unexpected(Error::FileNotFound);
        }

        TGAHeader header{};
        constexpr std::streamsize header_size = static_cast<std::streamsize>(sizeof(TGAHeader));

        if (!file.read(reinterpret_cast<char*>(&header), header_size))
        {
            return std::unexpected(Error::CorruptedHeader);
        }

        if (header.id_length > 0U)
        {
            if (!file.seekg(static_cast<std::streamoff>(header.id_length), std::ios::cur))
            {
                return std::unexpected(Error::ReadError);
            }
        }

        if (header.data_type_code != 2U)
        {
            return std::unexpected(Error::InvalidFormat);
        }

        if (header.bits_per_pixel != 24U && header.bits_per_pixel != 32U)
        {
            return std::unexpected(Error::UnsupportedBpp);
        }

        const std::uint32_t width = static_cast<std::uint32_t>(header.width);
        const std::uint32_t height = static_cast<std::uint32_t>(header.height);

        if (width == 0U || height == 0U)
        {
            return std::unexpected(Error::InvalidFormat);
        }

        const bool is_top_down = (header.image_descriptor & 0x20U) != 0U;

        Image img{ .bpp = 4, .width = width, .height = height, .pixels = {} };

        const std::size_t total_pixels = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
        if (total_pixels > std::numeric_limits<std::size_t>::max() / 4U)
        {
            return std::unexpected(Error::InvalidFormat);
        }

        img.pixels.resize(total_pixels * 4U);

        const std::uint32_t bytes_per_pixel = static_cast<std::uint32_t>(header.bits_per_pixel / 8U);

        if (total_pixels > std::numeric_limits<std::size_t>::max() / static_cast<std::size_t>(bytes_per_pixel))
        {
            return std::unexpected(Error::InvalidFormat);
        }

        const std::size_t data_size = total_pixels * static_cast<std::size_t>(bytes_per_pixel);

        if (data_size > static_cast<std::size_t>(std::numeric_limits<std::streamsize>::max()))
        {
            return std::unexpected(Error::InvalidFormat);
        }
        const std::streamsize read_data_size = static_cast<std::streamsize>(data_size);

        std::vector<std::uint8_t> raw_data(data_size);
        if (!file.read(reinterpret_cast<char*>(raw_data.data()), read_data_size))
        {
            return std::unexpected(Error::ReadError);
        }

        for (std::uint32_t y = 0; y < height; ++y)
        {
            const std::uint32_t target_y = is_top_down ? y : (height - 1U - y);

            const std::size_t src_row_offset = static_cast<std::size_t>(y) * static_cast<std::size_t>(width) * static_cast<std::size_t>(bytes_per_pixel);
            const std::size_t dst_row_offset = static_cast<std::size_t>(target_y) * static_cast<std::size_t>(width) * 4U;

            for (std::uint32_t x = 0; x < width; ++x)
            {
                const std::size_t src_idx = src_row_offset + (static_cast<std::size_t>(x) * static_cast<std::size_t>(bytes_per_pixel));
                const std::size_t dst_idx = dst_row_offset + (static_cast<std::size_t>(x) * 4U);

                img.pixels[dst_idx + 0U] = raw_data[src_idx + 2U];
                img.pixels[dst_idx + 1U] = raw_data[src_idx + 1U];
                img.pixels[dst_idx + 2U] = raw_data[src_idx + 0U];

                if (bytes_per_pixel == 4U)
                {
                    img.pixels[dst_idx + 3U] = raw_data[src_idx + 3U];
                }
                else
                {
                    img.pixels[dst_idx + 3U] = 255U;
                }
            }
        }

        img.bpp = 4;

        return img;
    }
}
