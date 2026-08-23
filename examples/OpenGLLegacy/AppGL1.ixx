// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

#include <string>
#include <utility>
#include <print>
#include <optional>
#include <functional>

export module AppGL1;

import WinLite;
import OpenGL;
import FpsCounter;

using namespace WinLite;

export class AppGL1
{
public:
    AppGL1() noexcept
        : OnEvent(nullptr)
        , OnUpdate(nullptr)
        , OnRender(nullptr)
        , _width(0)
        , _height(0)
        , _window(std::nullopt)
        , _glLoader(std::nullopt)
    {
    }

    bool Init(std::size_t width = 800, std::size_t height = 600, const std::string& title = "")
    {
        _width = width;
        _height = height;

        auto windowResult = OpenGL1Window::Create(_width, _height, title);
        if (!windowResult)
        {
            std::println("Error: {}", windowResult.error());
            return false;
        }

        _window.emplace(std::move(*windowResult));
        _glLoader.emplace(1, 2);

        glViewport(0, 0, static_cast<GLsizei>(_width), static_cast<GLsizei>(_height));

        return true;
    }

    std::move_only_function<void(const Event&) noexcept> OnEvent = nullptr;
    std::move_only_function<void(float deltaTime) noexcept> OnUpdate = nullptr;
    std::move_only_function<void() noexcept> OnRender = nullptr;

    void Run() noexcept
    {
        if (!_window || !_glLoader) return;

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

    std::optional<OpenGL1Window> _window = std::nullopt;
    std::optional<OpenGLLoader> _glLoader = std::nullopt;
};
