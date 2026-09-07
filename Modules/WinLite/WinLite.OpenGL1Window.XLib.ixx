// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

export module WinLite.OpenGL1Window;

import std;
import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
	class OpenGL1Window
	{
	private:
		MainWindow _impl;

		OpenGL1Window(MainWindow&& impl) noexcept :
			_impl(std::move(impl))
		{
		}

		void ReleaseContexts() noexcept
		{
		}

	public:
		OpenGL1Window(OpenGL1Window&& other) noexcept :
			_impl(std::move(other._impl))
		{
		}

		OpenGL1Window& operator=(OpenGL1Window&& other) noexcept
		{
			if (this != &other)
			{
				ReleaseContexts();

				_impl = std::move(other._impl);
			}

			return *this;
		}

		OpenGL1Window(const OpenGL1Window&) = delete;
		OpenGL1Window& operator=(const OpenGL1Window&) = delete;

		static std::expected<OpenGL1Window, std::string> Create(std::size_t w, std::size_t h, const std::string& title)
		{
			auto result = MainWindow::Create(w, h, title);
			if (!result.has_value())
			{
				return std::unexpected(result.error());
			}

			MainWindow windowImpl = std::move(*result);

			return OpenGL1Window(std::move(windowImpl));
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
		}
	};
}
