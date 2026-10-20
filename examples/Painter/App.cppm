// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

export module App;

import std;
import WinLite;
import PixelPainter;
import PixelCopier;
import FpsCounter;
import BmpSaver;

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

    bool Init(std::size_t width, std::size_t height, const std::string& title)
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

    bool Init(const std::string& title)
    {
        return Init(800U, 600U, title);
    }

    [[nodiscard]] std::size_t GetWidth() const noexcept { return _width; }
    [[nodiscard]] std::size_t GetHeight() const noexcept { return _height; }

    std::move_only_function<void(const Event&) noexcept> OnEvent = nullptr;
    std::move_only_function<void(float deltaTime) noexcept> OnUpdate = nullptr;
    std::move_only_function<void(PixelPainter&, PixelCopier&) noexcept> OnRender = nullptr;

    [[nodiscard]] static std::filesystem::path MakeScreenshotName(const std::source_location location = std::source_location::current())
    {
        try
        {
            const std::string_view fullPath{ location.file_name() };

            const std::size_t lastSlash = fullPath.find_last_of("/\\");
            std::string_view fileStem = (lastSlash == std::string_view::npos) ? fullPath : fullPath.substr(lastSlash + 1U);

            const std::size_t dotPos = fileStem.find_last_of('.');
            if (dotPos != std::string_view::npos)
            {
                fileStem = fileStem.substr(0U, dotPos);
            }

            if (fileStem.empty())
            {
                fileStem = "UnknownExample";
            }

            const auto now = std::chrono::system_clock::now();

            const auto localTime = std::chrono::current_zone()->to_local(now);

            std::string fileName = std::format("Screenshot_{}_{:%Y-%m-%d_%H-%M-%S}.bmp", fileStem, localTime);

            return std::filesystem::path(std::move(fileName));
        }
        catch (const std::format_error&)
        {
            return std::filesystem::path("Screenshot_FormatError_Fallback.bmp");
        }
        catch (const std::bad_alloc&)
        {
            return std::filesystem::path("Screenshot_AllocError_Fallback.bmp");
        }
    }

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

                if (event.IsKeyPressed(Key::F5))
                {
                    try
                    {
                        const std::filesystem::path screenshotPath = MakeScreenshotName();

                        std::span<const std::uint8_t> pixelSpan(_frameBuffer.data(), _frameBuffer.size());

                        auto saveResult = BmpSaver::Save(screenshotPath, static_cast<std::uint32_t>(_width), static_cast<std::uint32_t>(_height), _bytesPerPixel, pixelSpan);

                        if (!saveResult.has_value())
                        {
                            _window->SetTitle(std::format("ERROR: Save failed! Code: {}", static_cast<std::uint32_t>(saveResult.error())));
                        }
                        else
                        {
                            _window->SetTitle(std::format("Saved: {}", screenshotPath.string()));
                        }
                    }
                    catch (const std::exception& e)
                    {
                        _window->SetTitle(std::format("CRITICAL ERROR: {}", e.what()));
                    }

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
