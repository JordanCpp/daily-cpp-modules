// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

#include <memory_resource>
#include <string>
#include <utility>
#include <expected>
#include <Windows.h>

export module WinLite.OpenGL1Window;

import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
	class OpenGL1Window
	{
	private:
		MainWindow _impl;
		HDC        _hdc = nullptr;
		HGLRC      _hglrc = nullptr;

		OpenGL1Window(MainWindow&& impl, HDC hdc, HGLRC hglrc) noexcept :
			_impl(std::move(impl)),
			_hdc(hdc),
			_hglrc(hglrc)
		{
		}

		void ReleaseContexts() noexcept
		{
			if (_hglrc)
			{
				if (wglGetCurrentContext() == _hglrc)
				{
					wglMakeCurrent(nullptr, nullptr);
				}

				wglDeleteContext(_hglrc);
				_hglrc = nullptr;
			}

			if (_hdc)
			{
				ReleaseDC(_impl.GetHwnd(), _hdc);
				_hdc = nullptr;
			}
		}

	public:
		OpenGL1Window(OpenGL1Window&& other) noexcept :
			_impl(std::move(other._impl)),
			_hdc(std::exchange(other._hdc, nullptr)),
			_hglrc(std::exchange(other._hglrc, nullptr))
		{
		}

		OpenGL1Window& operator=(OpenGL1Window&& other) noexcept
		{
			if (this != &other)
			{
				ReleaseContexts();

				_impl = std::move(other._impl);
				_hdc = std::exchange(other._hdc, nullptr);
				_hglrc = std::exchange(other._hglrc, nullptr);
			}

			return *this;
		}

		OpenGL1Window(const OpenGL1Window&) = delete;
		OpenGL1Window& operator=(const OpenGL1Window&) = delete;

		static std::expected<OpenGL1Window, std::string> Create(int w, int h, const std::string& title)
		{
			auto result = MainWindow::Create(w, h, title);
			if (!result.has_value())
			{
				return std::unexpected(result.error());
			}

			MainWindow windowImpl = std::move(*result);
			HWND hwnd = windowImpl.GetHwnd();

			HDC hdc = windowImpl.GetHdc();
			if (!hdc)
			{
				return std::unexpected("Failed to get device context (HDC) from MainWindow");
			}

			PIXELFORMATDESCRIPTOR pfd{};
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 24;
			pfd.cDepthBits = 16;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int format = ChoosePixelFormat(hdc, &pfd);
			if (format == 0)
			{
				return std::unexpected("Failed to choose pixel format");
			}

			if (!SetPixelFormat(hdc, format, &pfd))
			{
				return std::unexpected("Failed to set pixel format");
			}

			HGLRC hglrc = wglCreateContext(hdc);
			if (!hglrc)
			{
				return std::unexpected("Failed to create OpenGL context");
			}

			if (!wglMakeCurrent(hdc, hglrc))
			{
				wglDeleteContext(hglrc);
				return std::unexpected("Failed to make OpenGL context current");
			}

			return OpenGL1Window(std::move(windowImpl), hdc, hglrc);
		}

		~OpenGL1Window()
		{
			ReleaseContexts();
		}

		[[nodiscard]] bool IsRunning() const noexcept
		{
			return _impl.IsRunning();
		}

		void StopEvent() noexcept
		{
			_impl.StopEvent();
		}

		bool GetEvent(Event& event) noexcept
		{
			return _impl.GetEvent(event);
		}

		void SetTitle(const std::string& title)
		{
			_impl.SetTitle(title);
		}

		void Present() noexcept
		{
			if (_hdc)
			{
				SwapBuffers(_hdc);
			}
		}
	};
}
