// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

import std;

export module BmpSaver;

export namespace BmpSaver
{
    enum class Error : std::uint8_t
    {
        InvalidArguments,
        EmptyData,
        CannotOpenFile,
        WriteError
    };

    [[nodiscard]] std::expected<void, Error> Save(
        const std::filesystem::path& path,
        std::uint32_t width,
        std::uint32_t height,
        std::uint8_t bpp,
        std::span<const std::uint8_t> pixels,
        bool save_as_32bit = false) noexcept;
}

namespace BmpSaver
{
    std::expected<void, Error> Save(
        const std::filesystem::path& path,
        const std::uint32_t width,
        const std::uint32_t height,
        const std::uint8_t bpp,
        const std::span<const std::uint8_t> pixels,
        const bool save_as_32bit) noexcept
    {
        if (width == 0U || height == 0U || (bpp != 3U && bpp != 4U))
        {
            return std::unexpected(Error::InvalidArguments);
        }

        const std::size_t total_pixels = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
        if (pixels.size() < total_pixels * static_cast<std::size_t>(bpp))
        {
            return std::unexpected(Error::EmptyData);
        }

        std::ofstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            return std::unexpected(Error::CannotOpenFile);
        }

        constexpr std::size_t file_hdr_size = 14U;
        constexpr std::size_t info_hdr_size = 40U;
        constexpr std::size_t total_hdr_size = file_hdr_size + info_hdr_size;

        const std::uint16_t out_bit_count = save_as_32bit ? 32U : 24U;
        const std::uint32_t out_bytes_per_pixel = save_as_32bit ? 4U : 3U;

        const std::uint32_t row_stride = (width * out_bytes_per_pixel + 3U) & ~3U;

        const std::size_t total_image_size = static_cast<std::size_t>(row_stride) * static_cast<std::size_t>(height);
        const std::size_t total_file_size = total_hdr_size + total_image_size;

        if (total_file_size > std::numeric_limits<std::uint32_t>::max())
        {
            return std::unexpected(Error::InvalidArguments);
        }

        std::array<std::uint8_t, total_hdr_size> header_buffer{};

        const std::uint16_t file_type = 0x4D42U; // 'BM'
        const std::uint32_t file_size = static_cast<std::uint32_t>(total_file_size);
        const std::uint32_t offset_data = static_cast<std::uint32_t>(total_hdr_size);

        std::memcpy(&header_buffer[0U], &file_type, sizeof(file_type));
        std::memcpy(&header_buffer[2U], &file_size, sizeof(file_size));
        std::memcpy(&header_buffer[10U], &offset_data, sizeof(offset_data));

        const std::uint32_t bi_size = static_cast<std::uint32_t>(info_hdr_size);
        const std::int32_t  bi_width = static_cast<std::int32_t>(width);
        const std::int32_t  bi_height = static_cast<std::int32_t>(height);
        const std::uint16_t bi_planes = 1U;
        const std::uint32_t bi_compression = 0U; // BI_RGB
        const std::uint32_t bi_size_image = static_cast<std::uint32_t>(total_image_size);

        std::memcpy(&header_buffer[file_hdr_size + 0U], &bi_size, sizeof(bi_size));
        std::memcpy(&header_buffer[file_hdr_size + 4U], &bi_width, sizeof(bi_width));
        std::memcpy(&header_buffer[file_hdr_size + 8U], &bi_height, sizeof(bi_height));
        std::memcpy(&header_buffer[file_hdr_size + 12U], &bi_planes, sizeof(bi_planes));
        std::memcpy(&header_buffer[file_hdr_size + 14U], &out_bit_count, sizeof(out_bit_count));
        std::memcpy(&header_buffer[file_hdr_size + 16U], &bi_compression, sizeof(bi_compression));
        std::memcpy(&header_buffer[file_hdr_size + 20U], &bi_size_image, sizeof(bi_size_image));

        if (!file.write(reinterpret_cast<const char*>(header_buffer.data()), static_cast<std::streamsize>(total_hdr_size)))
        {
            return std::unexpected(Error::WriteError);
        }

        std::vector<std::uint8_t> row_buffer(row_stride, 0U);

        const std::uint32_t src_bytes_per_pixel = static_cast<std::uint32_t>(bpp);

        for (std::uint32_t y = 0; y < height; ++y)
        {
            const std::uint32_t src_y = height - 1U - y;
            const std::uint32_t src_row_offset = src_y * width * src_bytes_per_pixel;

            for (std::uint32_t x = 0; x < width; ++x)
            {
                const std::uint32_t src_idx = src_row_offset + (x * src_bytes_per_pixel);
                const std::uint32_t dst_idx = x * out_bytes_per_pixel;

                row_buffer[dst_idx + 0U] = pixels[src_idx + 0U]; // B
                row_buffer[dst_idx + 1U] = pixels[src_idx + 1U]; // G
                row_buffer[dst_idx + 2U] = pixels[src_idx + 2U]; // R

                if (save_as_32bit)
                {
                    row_buffer[dst_idx + 3U] = (src_bytes_per_pixel == 4U) ? pixels[src_idx + 3U] : 255U;
                }
            }

            if (!file.write(reinterpret_cast<const char*>(row_buffer.data()), static_cast<std::streamsize>(row_stride)))
            {
                return std::unexpected(Error::WriteError);
            }
        }

        return {};
    }
}
