// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int TEXTURE_WIDTH = 200;
const int TEXTURE_HEIGHT = 150;

struct NoiseGenerator {
    std::array<int, 256> p{};

    explicit NoiseGenerator() {
        std::iota(p.begin(), p.end(), 0);
        std::mt19937 rng(1337);
        std::shuffle(p.begin(), p.end(), rng);
    }

    [[nodiscard]] float fade(float t) const noexcept {
        return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
    }

    [[nodiscard]] float lerp(float t, float a, float b) const noexcept {
        return a + t * (b - a);
    }

    [[nodiscard]] float noise2d(float x, float y) const noexcept {
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;

        float x_frac = x - std::floor(x);
        float y_frac = y - std::floor(y);

        float u = fade(x_frac);
        float v = fade(y_frac);

        int aa = p[static_cast<std::size_t>(p[static_cast<std::size_t>(X)] + Y) & 255];
        int ab = p[static_cast<std::size_t>(p[static_cast<std::size_t>(X)] + ((Y + 1) & 255)) & 255];
        int ba = p[static_cast<std::size_t>(p[static_cast<std::size_t>((X + 1) & 255)] + Y) & 255];
        int bb = p[static_cast<std::size_t>(p[static_cast<std::size_t>((X + 1) & 255)] + ((Y + 1) & 255)) & 255];

        float res_a = lerp(u, static_cast<float>(aa) / 255.0f, static_cast<float>(ba) / 255.0f);
        float res_b = lerp(u, static_cast<float>(ab) / 255.0f, static_cast<float>(bb) / 255.0f);

        return lerp(v, res_a, res_b);
    }

    [[nodiscard]] float fbm(float x, float y) const noexcept {
        float value = 0.0f;
        float amplitude = 0.5f;
        float frequency = 1.0f;
        for (int i = 0; i < 4; ++i) {
            value += amplitude * noise2d(x * frequency, y * frequency);
            int idx = i;
            frequency *= (2.0f + static_cast<float>(idx) * 0.01f);
            amplitude *= 0.5f;
        }
        return value;
    }
};

int main(int, char* [])
{
    SDL2Loader loader;

    if (!loader.load())
    {
        std::println(std::cerr, "Critical Error: Failed to map SDL2 runtime binaries.");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::println(std::cerr, "Failed to initialize SDL! Error: {}", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Raymarched Clouds Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::println(std::cerr, "Failed to create window! Error: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::println(std::cerr, "Failed to create renderer! Error: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* cloud_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        TEXTURE_WIDTH,
        TEXTURE_HEIGHT
    );

    if (cloud_texture == nullptr)
    {
        std::println(std::cerr, "Failed to create texture! Error: {}", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    NoiseGenerator noise;
    std::vector<std::uint32_t> pixel_buffer(static_cast<std::size_t>(TEXTURE_WIDTH * TEXTURE_HEIGHT), 0);

    bool isRunning = true;
    SDL_Event event;
    float time_offset = 0.0f;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                time_offset = static_cast<float>(event.motion.x) * 0.01f;
            }
        }

        for (int y = 0; y < TEXTURE_HEIGHT; ++y)
        {
            float v = static_cast<float>(y) / static_cast<float>(TEXTURE_HEIGHT);

            for (int x = 0; x < TEXTURE_WIDTH; ++x)
            {
                float u = static_cast<float>(x) / static_cast<float>(TEXTURE_WIDTH);

                float density = 0.0f;
                float light_energy = 1.0f;

                for (int step = 0; step < 6; ++step)
                {
                    float step_f = static_cast<float>(step);
                    float sample_x = u * 4.0f + time_offset + step_f * 0.05f;
                    float sample_y = v * 3.0f + step_f * 0.05f;

                    float n = noise.fbm(sample_x, sample_y);

                    float d = std::max(0.0f, n - 0.4f);
                    if (d > 0.0f)
                    {
                        density += d * 0.4f;
                        light_energy *= std::max(0.0f, 1.0f - d * 0.5f);
                    }
                    if (density >= 1.0f)
                    {
                        density = 1.0f;
                        break;
                    }
                }

                float sky_r = 30.0f + (1.0f - v) * 50.0f;
                float sky_g = 100.0f + (1.0f - v) * 80.0f;
                float sky_b = 200.0f + (1.0f - v) * 55.0f;

                float cloud_color = 255.0f * (light_energy + 0.2f);

                float final_r = std::lerp(sky_r, cloud_color, density);
                float final_g = std::lerp(sky_g, cloud_color, density);
                float final_b = std::lerp(sky_b, cloud_color, density);

                auto r_u8 = static_cast<std::uint8_t>(std::clamp(final_r, 0.0f, 255.0f));
                auto g_u8 = static_cast<std::uint8_t>(std::clamp(final_g, 0.0f, 255.0f));
                auto b_u8 = static_cast<std::uint8_t>(std::clamp(final_b, 0.0f, 255.0f));

                std::size_t buffer_idx = static_cast<std::size_t>(y * TEXTURE_WIDTH + x);
                pixel_buffer[buffer_idx] = static_cast<std::uint32_t>((r_u8 << 24) | (g_u8 << 16) | (b_u8 << 8) | 0xFF);
            }
        }

        SDL_UpdateTexture(
            cloud_texture,
            nullptr,
            pixel_buffer.data(),
            TEXTURE_WIDTH * static_cast<int>(sizeof(std::uint32_t))
        );

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, cloud_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(cloud_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
