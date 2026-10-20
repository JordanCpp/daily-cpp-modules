// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module WinLite.Events;

import std;
import WinLite.KeyEnums;

export namespace WinLite
{
	enum class ButtonState : std::uint8_t
	{
		Released = 0,
		Pressed  = 1
	};

	enum class MouseButton : std::uint8_t
	{
		Left   = 1,
		Right  = 2,
		Middle = 3
	};

	enum class MouseScroll : std::uint8_t
	{
		Vertical   = 1,
		Horizontal = 2
	};

	enum class EventType : std::uint8_t
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
		Key         KeyCode;
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
			EventType Type = EventType::None;
			WinLite::Quit        Quit;
			WinLite::Mouse       Mouse;
			WinLite::Resize      Resize;
			WinLite::Keyboard    Keyboard;
			WinLite::GainedFocus GainedFocus;
			WinLite::LostFocus   LostFocus;
		};

		bool IsKeyPressed(Key key) const
		{
			return (Type == EventType::Keyboard && Keyboard.KeyCode == key && Keyboard.State == ButtonState::Pressed);
		}

		bool IsKeyReleased(Key key) const
		{
			return (Type == EventType::Keyboard && Keyboard.KeyCode == key && Keyboard.State == ButtonState::Released);
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