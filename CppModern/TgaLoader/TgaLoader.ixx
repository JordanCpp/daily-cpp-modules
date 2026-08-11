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

export module TgaLoader;

export namespace TgaLoader 
{
#pragma pack(push, 1)
    struct TGAHeader {
        std::uint8_t  id_length;
        std::uint8_t  color_map_type;
        std::uint8_t  data_type_code;
        std::uint16_t color_map_origin;
        std::uint16_t color_map_length;
        std::uint8_t  color_map_depth;
        std::uint16_t x_origin;
        std::uint16_t y_origin;
        std::uint16_t width;
        std::uint16_t height;
        std::uint8_t  bits_per_pixel;
        std::uint8_t  image_descriptor;
    } header;
#pragma pack(pop)

    struct Image 
    {
        std::uint8_t  bpp   { 0 };
        std::uint32_t width { 0 };
        std::uint32_t height{ 0 };
        std::vector<std::uint8_t> pixels;
    };

    enum class Error 
    {
        FileNotFound,
        InvalidFormat,
        UnsupportedBpp,
        CorruptedHeader,
        ReadError
    };

    export std::expected<Image, Error> load_from_file(const std::filesystem::path& path) noexcept 
    {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) 
        {
            return std::unexpected(Error::FileNotFound);
        }

        if (!file.read(reinterpret_cast<char*>(&header), sizeof(header))) 
        {
            return std::unexpected(Error::CorruptedHeader);
        }

        if (header.id_length > 0) 
        {
            file.seekg(header.id_length, std::ios::cur);
        }

        if (header.data_type_code != 2) 
        {
            return std::unexpected(Error::InvalidFormat);
        }

        if (header.bits_per_pixel != 24 && header.bits_per_pixel != 32) 
        {
            return std::unexpected(Error::UnsupportedBpp);
        }

        const std::uint32_t width = header.width;
        const std::uint32_t height = header.height;

        if (width == 0 || height == 0) 
        {
            return std::unexpected(Error::InvalidFormat);
        }

        const bool is_top_down = (header.image_descriptor & 0x20) != 0;

        Image img{ .width = width, .height = height };
        img.pixels.resize(width * height * 4);

        const std::uint32_t bytes_per_pixel = header.bits_per_pixel / 8;
        const std::size_t data_size = static_cast<std::size_t>(width) * height * bytes_per_pixel;

        std::vector<std::uint8_t> raw_data(data_size);
        if (!file.read(reinterpret_cast<char*>(raw_data.data()), data_size))
        {
            return std::unexpected(Error::ReadError);
        }

        for (std::uint32_t y = 0; y < height; ++y) 
        {
            const std::uint32_t target_y = is_top_down ? y : (height - 1 - y);

            const std::size_t src_row_offset = static_cast<std::size_t>(y) * width * bytes_per_pixel;
            const std::size_t dst_row_offset = static_cast<std::size_t>(target_y) * width * 4;

            for (std::uint32_t x = 0; x < width; ++x) 
            {
                const std::size_t src_idx = src_row_offset + (x * bytes_per_pixel);
                const std::size_t dst_idx = dst_row_offset + (x * 4);

                img.pixels[dst_idx + 0] = raw_data[src_idx + 2];
                img.pixels[dst_idx + 1] = raw_data[src_idx + 1];
                img.pixels[dst_idx + 2] = raw_data[src_idx + 0];

                if (bytes_per_pixel == 4)
                {
                    img.pixels[dst_idx + 3] = raw_data[src_idx + 3];
                }
                else 
                {
                    img.pixels[dst_idx + 3] = 255;
                }
            }
        }

        img.bpp = 4;

        return img;
    }

}