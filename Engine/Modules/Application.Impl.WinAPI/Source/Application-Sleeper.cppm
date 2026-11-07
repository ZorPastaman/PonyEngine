/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.Application.Impl.WinAPI:Sleeper;

import std;

import PonyEngine.Application;

export namespace PonyEngine::Application
{
	/// @brief Sleeper.
	class Sleeper final : public ISleeper
	{
	public:
		/// @brief Creates a sleeper.
		[[nodiscard("Pure constructor")]]
		Sleeper();
		Sleeper(const Sleeper&) = delete;
		Sleeper(Sleeper&&) = delete;

		~Sleeper() noexcept;

		virtual void SleepUntil(std::chrono::time_point<std::chrono::steady_clock> target) override;
		virtual void SleepFor(std::chrono::nanoseconds duration) override;

		Sleeper& operator =(const Sleeper&) = delete;
		Sleeper& operator =(Sleeper&&) = delete;

	private:
		HANDLE timer; ///< Timer handle.
	};
}

namespace PonyEngine::Application
{
	Sleeper::Sleeper()
	{
		timer = CreateWaitableTimerExA(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_MODIFY_STATE | SYNCHRONIZE);
		if (!timer) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create timer. Error code: '0x{:X}'.", GetLastError()));
		}
	}

	Sleeper::~Sleeper() noexcept
	{
		CloseHandle(timer);
	}

	void Sleeper::SleepUntil(const std::chrono::time_point<std::chrono::steady_clock> target)
	{
		return SleepFor(target - std::chrono::steady_clock::now());
	}

	void Sleeper::SleepFor(const std::chrono::nanoseconds duration)
	{
		const std::chrono::nanoseconds::rep durationCount = duration.count();
		if (durationCount <= 0ll)
		{
			return;
		}

		const LONGLONG intervals = durationCount / 100ll + (durationCount % 100ll > 0ll);
		const auto waitTime = LARGE_INTEGER{.QuadPart = -intervals};
		if (!SetWaitableTimer(timer, &waitTime, 0, nullptr, nullptr, false)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set timer: Error code = '0x{:X}'", GetLastError()));
		}

		switch (const DWORD result = WaitForSingleObject(timer, INFINITE))
		{
		case WAIT_OBJECT_0: [[likely]]
			return;
		case WAIT_FAILED: [[unlikely]]
			throw std::runtime_error(std::format("Failed to wait for timer: Error code = '0x{:X}'", GetLastError()));
		default: [[unlikely]]
			throw std::runtime_error(std::format("Failed to wait for timer: Result = '0x{:X}'", result));
		}
	}
}
