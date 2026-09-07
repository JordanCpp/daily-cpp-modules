// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module WinLite.SoftwareWindow;

import std;
import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
	class SoftwareWindow
	{
	private:
		MainWindow _impl;

		explicit SoftwareWindow(MainWindow&& impl) :
			_impl(std::move(impl))
		{
		}

	public:
		SoftwareWindow(SoftwareWindow&&) noexcept = default;
		SoftwareWindow& operator=(SoftwareWindow&&) noexcept = default;
		SoftwareWindow(const SoftwareWindow&) = delete;
		SoftwareWindow& operator=(const SoftwareWindow&) = delete;

		static std::expected<SoftwareWindow, std::string> Create(std::size_t w, std::size_t h, const std::string& title)
		{
			auto result = MainWindow::Create(w, h, title);

			if (!result.has_value())
			{
				return std::unexpected(result.error());
			}

			return SoftwareWindow(std::move(*result));
		}

		~SoftwareWindow() = default;

		bool IsRunning() const
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

		void SetTitle(const std::string& title)
		{
			_impl.SetTitle(title);
		}

		void Present(const std::uint8_t* pixels, std::uint8_t bytes, std::size_t w, std::size_t h)
		{
			if (pixels)
			{
			}

			if (bytes)
			{
			}

			if (w)
			{
			}

			if (h)
			{
			}
		}
	};
}
