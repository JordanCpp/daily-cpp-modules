// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

export module AppGL3;

import std;

import WinLite;
import OpenGL;
import FpsCounter;

using namespace WinLite;

export class AppGL3
{
public:
    std::move_only_function<void(const Event&) noexcept> OnEvent = nullptr;
    std::move_only_function<void(float deltaTime) noexcept> OnUpdate = nullptr;
    std::move_only_function<void() noexcept> OnRender = nullptr;

    AppGL3() noexcept
        : OnEvent(nullptr)
        , OnUpdate(nullptr)
        , OnRender(nullptr)
        , _width(0)
        , _height(0)
        , _window(std::nullopt)
        , _glLoader(std::nullopt)
    {
    }

    [[nodiscard]] std::size_t GetWidth() const noexcept { return _width; }
    [[nodiscard]] std::size_t GetHeight() const noexcept { return _height; }

    bool Init(std::size_t targetWidth = 800, std::size_t targetHeight = 600, const std::string& title = "")
    {
        _width  = targetWidth;
        _height = targetHeight;

        auto windowResult = OpenGL3Window::Create(_width, _height, title);
        if (!windowResult)
        {
            std::println("Error: {}", windowResult.error());
            return false;
        }

        _window.emplace(std::move(*windowResult));
        _glLoader.emplace(3, 0);

        glViewport(0, 0, static_cast<GLsizei>(_width), static_cast<GLsizei>(_height));

        return true;

    }

    void Run() noexcept
    {
        if (!_window || !_glLoader)
        {
            return;
        }
        FpsCounter counter;
        auto lastTime = std::chrono::steady_clock::now();

        while (_window->IsRunning())
        {
            const auto currentTime = std::chrono::steady_clock::now();
            const std::chrono::duration<float> elapsed = currentTime - lastTime;
            lastTime = currentTime;

            float deltaTime = elapsed.count();
            if (deltaTime > 0.1f)
            {
                deltaTime = 0.1f;
            }

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
                OnUpdate(deltaTime);
            }

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (OnRender)
            {
                OnRender();
            }

            _window->Present();

            if (counter.Update())
            {
                _window->SetTitle(std::to_string(counter.GetFps()));
            }
        }

    }

private:
    std::size_t _width = 0;
    std::size_t _height = 0;

    std::optional<OpenGL3Window> _window = std::nullopt;
    std::optional<OpenGLLoader> _glLoader = std::nullopt;
};