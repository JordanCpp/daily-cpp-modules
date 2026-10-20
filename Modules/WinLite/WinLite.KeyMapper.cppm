// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

export module WinLite.KeyMapper;

import std;
import WinLite.KeyEnums;

export namespace WinLite
{
	struct KeyMap
	{
		Key           KeyCode{ Key::Unknown };
		std::uint32_t Code{ 0 };
	};

	class KeyMapper
	{
	public:
		constexpr KeyMapper() = default;

		constexpr void Add(std::uint32_t code, Key key) noexcept
		{
			if (Current < Table.size())
			{
				Table[Current] = KeyMap{ .KeyCode = key, .Code = code };
				Current++;
			}
		}

		[[nodiscard]] constexpr Key FindKey(std::uint32_t scanCode) const noexcept
		{
			for (std::size_t i = 0; i < Current; ++i)
			{
				if (Table[i].Code == scanCode)
				{
					return Table[i].KeyCode;
				}
			}

			return Key::Unknown;
		}

		constexpr void Clear() noexcept
		{
			Current = 0;
		}

	private:
		std::size_t             Current{ 0 };
		std::array<KeyMap, 256> Table{};
	};
}