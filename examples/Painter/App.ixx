// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

#include <string>
#include <vector>
#include <span>
#include <cstdint>
#include <utility>
#include <print>
#include <optional>
#include <functional>
#include <memory>

export module App;

import WinLite;
import PixelPainter;
import PixelCopier;
import FpsCounter;

using namespace WinLite;
using namespace Software;

export class App
{
public:
    App() noexcept
        : OnEvent(nullptr)
        , OnUpdate(nullptr)
        , OnRender(nullptr)
        , _width(0)
        , _height(0)
        , _window(std::nullopt)
        , _frameBuffer{}
        , _painter(std::nullopt)
        , _copier(std::nullopt)
    {
    }

    bool Init(std::size_t width = 800, std::size_t height = 600, const std::string& title = "")
    {
        _width = width;
        _height = height;

        auto windowResult = SoftwareWindow::Create(_width, _height, title);
        if (!windowResult)
        {
            std::println("Error: {}", windowResult.error());
            return false;
        }

        _window = std::move(*windowResult);

        _frameBuffer.resize(_width * _height * _bytesPerPixel);

        _painter.emplace(_width, _height, _bytesPerPixel, std::span<std::uint8_t>(_frameBuffer.data(), _frameBuffer.size()));
        _copier.emplace(_width, _height, _bytesPerPixel, std::span<std::uint8_t>(_frameBuffer.data(), _frameBuffer.size()));

        return true;
    }

    std::move_only_function<void(const Event&) noexcept> OnEvent = nullptr;
    std::move_only_function<void(float deltaTime) noexcept> OnUpdate = nullptr;
    std::move_only_function<void(PixelPainter&, PixelCopier&) noexcept> OnRender = nullptr;

    void Run() noexcept
    {
        if (!_window || !_painter || !_copier) return;

        FpsCounter counter;

        while (_window->IsRunning())
        {
            Event event;
            while (_window->GetEvent(event))
            {
                if ((event.Type == EventType::Quit) || event.IsKeyPressed(Key::Escape))
                {
                    _window->StopEvent();
                }

                if (OnEvent)
                {
                    OnEvent(event);
                }
            }

            if (OnUpdate)
            {
                OnUpdate(0.016f);
            }

            _painter->SetColor(Color{ 10, 10, 15 });
            _painter->Clear();

            if (OnRender)
            {
                OnRender(*_painter, *_copier);
            }

            _window->Present(_frameBuffer.data(), _bytesPerPixel, _width, _height);

            if (counter.Update())
            {
                _window->SetTitle(std::to_string(counter.GetFps()));
            }
        }
    }

private:
    std::size_t _width = 0;
    std::size_t _height = 0;
    inline static constexpr std::size_t _bytesPerPixel = 3;
    std::optional<SoftwareWindow> _window = std::nullopt;
    std::vector<std::uint8_t>     _frameBuffer{};
    std::optional<PixelPainter>   _painter = std::nullopt;
    std::optional<PixelCopier>    _copier = std::nullopt;
};
