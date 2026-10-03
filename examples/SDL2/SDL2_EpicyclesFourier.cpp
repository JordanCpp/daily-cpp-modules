// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

import std;
import SDL2.API;
import SDL2.Loader;

const std::int32_t SCREEN_WIDTH = 800;
const std::int32_t SCREEN_HEIGHT = 600;

struct Complex {
    float re;
    float im;
};

struct FourierCoefficient {
    float freq;
    float amplitude;
    float phase;
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
        "SDL2 Epicycles Fourier Demo",
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

    const std::int32_t num_samples = 200;
    std::vector<Complex> signal;
    signal.reserve(static_cast<std::size_t>(num_samples));

    for (std::int32_t i = 0; i < num_samples; ++i)
    {
        float t = (2.0f * 3.14159265f * static_cast<float>(i)) / static_cast<float>(num_samples);

        float x = 16.0f * std::sin(t) * std::sin(t) * std::sin(t);
        float y = 13.0f * std::cos(t) - 5.0f * std::cos(2.0f * t) - 2.0f * std::cos(3.0f * t) - std::cos(4.0f * t);

        signal.push_back(Complex{ x * 12.0f, -y * 12.0f });
    }

    std::vector<FourierCoefficient> fourier;
    fourier.reserve(static_cast<std::size_t>(num_samples));

    for (std::int32_t k = 0; k < num_samples; ++k)
    {
        float sum_re = 0.0f;
        float sum_im = 0.0f;
        float k_f = static_cast<float>(k);

        for (std::int32_t n = 0; n < num_samples; ++n)
        {
            float n_f = static_cast<float>(n);
            float angle = (2.0f * 3.14159265f * k_f * n_f) / static_cast<float>(num_samples);

            sum_re += signal[static_cast<std::size_t>(n)].re * std::cos(angle) + signal[static_cast<std::size_t>(n)].im * std::sin(angle);
            sum_im += -signal[static_cast<std::size_t>(n)].re * std::sin(angle) + signal[static_cast<std::size_t>(n)].im * std::cos(angle);
        }

        sum_re /= static_cast<float>(num_samples);
        sum_im /= static_cast<float>(num_samples);

        float amplitude = std::sqrt(sum_re * sum_re + sum_im * sum_im);
        float phase = std::atan2(sum_im, sum_re);

        fourier.push_back(FourierCoefficient{ k_f, amplitude, phase });
    }

    std::sort(fourier.begin(), fourier.end(), [](const FourierCoefficient& a, const FourierCoefficient& b) noexcept {
        return a.amplitude > b.amplitude;
        });

    std::vector<SDL_Point> path;
    path.reserve(static_cast<std::size_t>(num_samples));

    bool isRunning = true;
    SDL_Event event;
    float time_step = 0.0f;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 15, 16, 22, 255);
        SDL_RenderClear(renderer);

        float current_x = static_cast<float>(SCREEN_WIDTH) / 2.0f;
        float current_y = static_cast<float>(SCREEN_HEIGHT) / 2.0f;

        SDL_SetRenderDrawColor(renderer, 60, 70, 90, 255);
        for (const auto& coeff : fourier)
        {
            float prev_x = current_x;
            float prev_y = current_y;

            float angle = coeff.freq * time_step + coeff.phase;
            current_x += coeff.amplitude * std::cos(angle);
            current_y += coeff.amplitude * std::sin(angle);

            if (coeff.amplitude > 0.5f)
            {
                SDL_RenderDrawLine(
                    renderer,
                    static_cast<std::int32_t>(prev_x),
                    static_cast<std::int32_t>(prev_y),
                    static_cast<std::int32_t>(current_x),
                    static_cast<std::int32_t>(current_y)
                );
            }
        }

        SDL_Point current_pt{ static_cast<std::int32_t>(current_x), static_cast<std::int32_t>(current_y) };

        if (path.size() < static_cast<std::size_t>(num_samples))
        {
            path.push_back(current_pt);
        }
        else
        {
            std::rotate(path.begin(), path.begin() + 1, path.end());
            path.back() = current_pt;
        }

        SDL_SetRenderDrawColor(renderer, 255, 60, 100, 255);
        if (path.size() > 1)
        {
            SDL_RenderDrawLines(renderer, path.data(), static_cast<std::int32_t>(path.size()));
        }

        SDL_RenderPresent(renderer);

        time_step += (2.0f * 3.14159265f) / static_cast<float>(num_samples);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
