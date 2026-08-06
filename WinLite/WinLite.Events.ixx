// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <cstdint>

export module WinLite.Events;

export namespace WinLite
{
	enum class ButtonState : uint8_t
	{
		Released = 0,
		Pressed  = 1
	};

	enum class MouseButton : uint8_t
	{
		Left   = 1,
		Right  = 2,
		Middle = 3
	};

	enum class MouseScroll : uint8_t
	{
		Vertical   = 1,
		Horizontal = 2
	};

	enum class EventType : uint8_t
	{
		None = 0,
		Quit = 1,
		MouseMove,
		MouseClick,
		Resize,
		Keyboard,
		GainedFocus,
		LostFocus,
		MouseScroll
	};

	class GainedFocus
	{
	public:
		EventType Type;
	};

	class LostFocus
	{
	public:
		EventType Type;
	};

	class Quit
	{
	public:
		EventType Type;
	};

	class Keyboard
	{
	public:
		EventType   Type;
		ButtonState State;
		uint8_t     Key;
	};

	class Resize
	{
	public:
		EventType Type;
		int       Width;
		int       Height;
	};

	class Mouse
	{
	public:
		EventType Type;
		ButtonState State;
		MouseButton Button;
		MouseScroll Scroll;
		int PosX;
		int PosY;
		int PosRelX;
		int PosRelY;
		int Delta;
	};

	class Event
	{
	public:
		union
		{
			EventType   Type = EventType::None;
			Quit        Quit;
			Mouse       Mouse;
			Resize      Resize;
			Keyboard    Keyboard;
			GainedFocus GainedFocus;
			LostFocus   LostFocus;
		};

		bool IsKeyPressed(uint8_t key) const
		{
			return (Type == EventType::Keyboard && Keyboard.Key == key && Keyboard.State == ButtonState::Pressed);
		}

		bool IsKeyReleased(uint8_t key) const
		{
			return (Type == EventType::Keyboard && Keyboard.Key == key && Keyboard.State == ButtonState::Released);
		}

		bool IsMousePressed(MouseButton button) const
		{
			return (Type == EventType::MouseClick && Mouse.Button == button && Mouse.State == ButtonState::Pressed);
		}

		bool IsMouseReleased(MouseButton button) const
		{
			return (Type == EventType::MouseClick && Mouse.Button == button && Mouse.State == ButtonState::Released);
		}
	};
}