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

export module BmpLoader;

export namespace BmpLoader
{
#pragma pack(push, 1)
    struct BmpFileHeader 
    {
        std::uint16_t type;
        std::uint32_t size;
        std::uint16_t reserved1;
        std::uint16_t reserved2;
        std::uint32_t offset_data;
    } file_header;

    struct BmpInfoHeader 
    {
        std::uint32_t size;
        std::int32_t  width;
        std::int32_t  height;
        std::uint16_t planes;
        std::uint16_t bit_count;
        std::uint32_t compression;
        std::uint32_t size_image;
        std::int32_t  x_pixels_per_meter;
        std::int32_t  y_pixels_per_meter;
        std::uint32_t colors_used;
        std::uint32_t colors_important;
    } info_header;
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

    export std::expected<Image, Error> Load(const std::filesystem::path& path) noexcept 
    {
        std::ifstream file(path, std::ios::binary);

        if (!file.is_open()) 
        {
            return std::unexpected(Error::FileNotFound);
        }

        if (!file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header)) ||
            !file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header))) 
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

        const std::uint32_t width  = std::abs(info_header.width);
        const std::uint32_t height = std::abs(info_header.height);
        const bool is_top_down     = info_header.height < 0;

        Image img{ .width = width, .height = height };
        img.pixels.resize(width * height * 4);

        file.seekg(file_header.offset_data, std::ios::beg);

        const std::uint32_t bytes_per_pixel = info_header.bit_count / 8;
        const std::uint32_t row_stride = (width * bytes_per_pixel + 3) & ~3;

        std::vector<std::uint8_t> row_buffer(row_stride);

        for (std::uint32_t y = 0; y < height; ++y) 
        {
            if (!file.read(reinterpret_cast<char*>(row_buffer.data()), row_stride)) 
            {
                return std::unexpected(Error::ReadError);
            }

            const std::uint32_t target_y = is_top_down ? y : (height - 1 - y);
            const std::uint32_t target_row_offset = target_y * width * 4;

            for (std::uint32_t x = 0; x < width; ++x)
            {
                const std::uint32_t src_idx = x * bytes_per_pixel;
                const std::uint32_t dst_idx = target_row_offset + (x * 4);

                img.pixels[dst_idx + 0] = row_buffer[src_idx + 2];
                img.pixels[dst_idx + 1] = row_buffer[src_idx + 1];
                img.pixels[dst_idx + 2] = row_buffer[src_idx + 0];

                if (bytes_per_pixel == 4)
                {
                    img.pixels[dst_idx + 3] = row_buffer[src_idx + 3];
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