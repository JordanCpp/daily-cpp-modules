// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://boost.org)

module;

#include <X11/Xlib.h>
#include <X11/Xutil.h>

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
		Pixmap _backBuffer{0};
		GC _gc{nullptr};
		std::vector<std::uint8_t> _conversionBuffer;
		explicit SoftwareWindow(MainWindow &&impl) : _impl(std::move(impl))
		{
		}

	public:
		SoftwareWindow(SoftwareWindow &&other) noexcept : _impl(std::move(other._impl)),
														  _backBuffer(other._backBuffer),
														  _gc(other._gc)
		{
			other._backBuffer = 0;
			other._gc = nullptr;
		}

		SoftwareWindow &operator=(SoftwareWindow &&other) noexcept
		{
			if (this != &other)
			{
				Destroy();
				_impl = std::move(other._impl);
				_backBuffer = other._backBuffer;
				_gc = other._gc;

				other._backBuffer = 0;
				other._gc = nullptr;
			}
			return *this;
		}

		SoftwareWindow(const SoftwareWindow &) = delete;
		SoftwareWindow &operator=(const SoftwareWindow &) = delete;

		static std::expected<SoftwareWindow, std::string> Create(std::size_t w, std::size_t h, const std::string &title)
		{
			auto result = MainWindow::Create(w, h, title);

			if (!result.has_value())
			{
				return std::unexpected(result.error());
			}

			return SoftwareWindow(std::move(*result));
		}

		~SoftwareWindow()
		{
			Destroy();
		}

		bool IsRunning() const { return _impl.IsRunning(); }
		void StopEvent() { _impl.StopEvent(); }
		bool GetEvent(Event &event) { return _impl.GetEvent(event); }
		void SetTitle(const std::string &title) { _impl.SetTitle(title); }

		void Present(const std::uint8_t *pixels, std::uint8_t bytes, std::size_t w, std::size_t h)
		{
			Display *display = _impl.GetDisplay();
			Window window = _impl.GetWindow();

			if (!display || !window || !pixels || w == 0 || h == 0)
			{
				return;
			}

			int screen = DefaultScreen(display);
			Visual *visual = DefaultVisual(display, screen);
			int systemDepth = DefaultDepth(display, screen);

			if (!_backBuffer)
			{
				_backBuffer = XCreatePixmap(display, window, static_cast<unsigned int>(w), static_cast<unsigned int>(h), static_cast<unsigned int>(systemDepth));
				_gc = XCreateGC(display, window, 0, nullptr);
			}

			const std::uint8_t *finalPixels = pixels;
			int bitsPerPixel = bytes * 8;
			int bytesPerLine = static_cast<int>(w * bytes);

			if (bytes == 3)
			{
				_conversionBuffer.resize(w * h * 4);

				for (std::size_t i = 0; i < w * h; ++i)
				{
					std::size_t srcIdx = i * 3;
					std::size_t dstIdx = i * 4;

					_conversionBuffer[dstIdx + 0] = pixels[srcIdx + 0]; // R
					_conversionBuffer[dstIdx + 1] = pixels[srcIdx + 1]; // G
					_conversionBuffer[dstIdx + 2] = pixels[srcIdx + 2]; // B
					_conversionBuffer[dstIdx + 3] = 255;				// А (X11 требует этот байт для выравнивания)
				}
				
				finalPixels = _conversionBuffer.data();
				bitsPerPixel = 32;
				bytesPerLine = static_cast<int>(w * 4);
			}

			XImage *image = XCreateImage(
				display,
				visual,
				static_cast<unsigned int>(systemDepth),
				ZPixmap,
				0,
				const_cast<char *>(reinterpret_cast<const char *>(finalPixels)),
				static_cast<unsigned int>(w),
				static_cast<unsigned int>(h),
				32,
				bytesPerLine);

			if (image)
			{
				image->bits_per_pixel = 32;

				XPutImage(display, _backBuffer, _gc, image, 0, 0, 0, 0,
						  static_cast<unsigned int>(w), static_cast<unsigned int>(h));

				XCopyArea(display, _backBuffer, window, _gc, 0, 0,
						  static_cast<unsigned int>(w), static_cast<unsigned int>(h), 0, 0);

				image->data = nullptr;
				XDestroyImage(image);
				XFlush(display);
			}
		}

	private:
		void Destroy()
		{
			Display *display = _impl.GetDisplay();

			if (display)
			{
				if (_gc)
				{
					XFreeGC(display, _gc);
					_gc = nullptr;
				}

				if (_backBuffer)
				{
					XFreePixmap(display, _backBuffer);
					_backBuffer = 0;
				}
			}
		}
	};
}
