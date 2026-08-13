// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <memory_resource>
#include <queue>

export module WinLite.Queue;

import WinLite.Events;

export namespace WinLite
{
	class Queue
	{
	private:
		bool              _running;
		std::queue<Event> _events;

	public:
		Queue() :
			_running(true),
			_events{}
		{
		}

		bool Empty() const
		{
			return _events.empty();
		}

		void Push(const Event& event)
		{
			_events.push(event);
		}

		bool Pop(Event& event)
		{
			if (!_events.empty())
			{
				event = _events.front();
				_events.pop();

				return true;
			}

			return false;
		}

		bool IsRunning() const
		{
			return _running;
		}

		void Stop()
		{
			_running = false;
		}
	};
}