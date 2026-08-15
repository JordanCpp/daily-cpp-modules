// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <memory_resource>
#include <cstdint>
#include <string>
#include <utility>
#include <expected>
#include <Windows.h>

export module WinLite.SoftwareWindow;

import WinLite.Events;
import WinLite.MainWindow;

export namespace WinLite
{
	class SoftwareWindow
	{
	private:
		BITMAPINFO _bitmapInfo;
		MainWindow _impl;

		explicit SoftwareWindow(MainWindow&& impl) :
			_bitmapInfo{},
			_impl(std::move(impl))
		{
			_bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			_bitmapInfo.bmiHeader.biPlanes = 1;
			_bitmapInfo.bmiHeader.biCompression = BI_RGB;
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

		void Present(const uint8_t* pixels, uint8_t bytes, int w, int h)
		{
			_bitmapInfo.bmiHeader.biWidth    = static_cast<LONG>(w);
			_bitmapInfo.bmiHeader.biHeight   = static_cast<LONG>(-h);
			_bitmapInfo.bmiHeader.biBitCount = static_cast<WORD>(bytes * 8);

			SetDIBitsToDevice(_impl.GetHdc(), 0, 0, static_cast<DWORD>(w), static_cast<DWORD>(h), 0, 0, 0, static_cast<UINT>(h), pixels, &_bitmapInfo, DIB_RGB_COLORS);
		}
	};
}
