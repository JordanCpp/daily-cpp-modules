// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <string>
#include <utility>
#include <expected>

export module WinLite.Window;

import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
	class Window
	{
	private:
		MainWindow _impl;

		explicit Window(MainWindow&& impl) : 
			_impl(std::move(impl)) 
		{
		}

	public:
		Window(Window&&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		static std::expected<Window, std::string> Create(int x, int y, int w, int h, const std::string& title)
		{
			auto result = MainWindow::Create(x, y, w, h, title);

			if (!result.has_value())
			{
				return std::unexpected(result.error());
			}

			return Window(std::move(*result));
		}

		~Window()
		{
		}

		bool IsRunning()
		{
			return _impl.IsRunning();
		}

		void StopEvent()
		{
			_impl.StopEvent();
		}

		bool GetEvent(Event& event)
		{
			return _impl.GetEvent(event);
		}
	};
}
