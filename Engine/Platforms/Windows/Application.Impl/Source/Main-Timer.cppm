/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:Timer;

import std;

import PonyEngine.Application.Impl;
import PonyEngine.Chrono;
import PonyEngine.Log;

export namespace PonyEngine::Application::Windows
{
	/// @brief Creates a timer.
	/// @param application Application.
	/// @return Timer.
	[[nodiscard("Pure function")]]
	HANDLE CreateTimer(const App& application) noexcept;
	/// @brief Destroys the timer.
	/// @param timer Timer to destroy. May be nullptr.
	/// @param application Application.
	void DestroyTimer(HANDLE& timer, const App& application) noexcept;

	/// @brief Waits for the next frame.
	/// @param timer Timer to use.
	/// @param application Application.
	void WaitForNextFrame(HANDLE timer, const App& application) noexcept;
}

namespace PonyEngine::Application::Windows
{
	HANDLE CreateTimer(const App& application) noexcept
	{
		const HANDLE timer = CreateWaitableTimerExA(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_MODIFY_STATE | SYNCHRONIZE);
		if (!timer) [[unlikely]]
		{
			PONY_LOG(application.LogService(), Log::LogType::Error, "Failed to create a high resolution waitable timer. Error code: '0x{:X}'.", GetLastError());
		}

		return timer;
	}

	void DestroyTimer(HANDLE& timer, const App& application) noexcept
	{
		if (timer) [[likely]]
		{
			if (!CloseHandle(timer)) [[unlikely]]
			{
				PONY_LOG(application.LogService(), Log::LogType::Error, "Failed to destroy a high resolution waitable timer. Error code: '0x{:X}'.", GetLastError());
			}

			timer = nullptr;
		}
	}

	void WaitForNextFrame(const HANDLE timer, const App& application) noexcept
	{
		if (!timer) [[unlikely]]
		{
			return;
		}

		constexpr std::chrono::nanoseconds busySpinLength = Chrono::ToDuration<std::chrono::nanoseconds>(double{PONY_ENGINE_APPLICATION_NEXT_FRAME_BUSY_SPIN_LENGTH});
		const std::chrono::time_point<std::chrono::steady_clock> nextFrameTimePoint = application.NextFrameTimePoint();
		const std::chrono::time_point<std::chrono::steady_clock> waitTill = nextFrameTimePoint - busySpinLength;
		const std::chrono::nanoseconds waitLength = std::chrono::duration_cast<std::chrono::nanoseconds>(waitTill - std::chrono::steady_clock::now());
		const auto waitTime = LARGE_INTEGER{.QuadPart = -waitLength.count() / 100ll};
		if (waitTime.QuadPart >= 0ll)
		{
			return;
		}

		if (!SetWaitableTimer(timer, &waitTime, 0, nullptr, nullptr, FALSE)) [[unlikely]]
		{
			PONY_LOG(application.LogService(), Log::LogType::Error, "Failed to set a high resolution waitable timer. Error code: '0x{:X}'.", GetLastError());
		}
		if (const DWORD result =  WaitForSingleObject(timer, INFINITE); result != WAIT_OBJECT_0) [[unlikely]]
		{
			if (result == WAIT_FAILED)
			{
				PONY_LOG(application.LogService(), Log::LogType::Error, "Failed to wait for a high resolution waitable timer. Error code: '0x{:X}'.", GetLastError());
			}
			else
			{
				PONY_LOG(application.LogService(), Log::LogType::Error, "Failed to wait for a high resolution waitable timer. Result: '0x{:X}'.", result);
			}
		}
	}
}
