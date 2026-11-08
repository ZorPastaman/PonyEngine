/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Application.Impl:IProcess;

import std;

import PonyEngine.Application;

export namespace PonyEngine::Application
{
	/// @brief Process.
	class IProcess
	{
		PONY_INTERFACE_BODY(IProcess)

		/// @brief Gets the process ID.
		/// @return Process ID.
		[[nodiscard("Pure function")]]
		virtual ProcessID ProcessID() const noexcept = 0;

		/// @brief Gets a current memory status.
		/// @return Memory status.
		[[nodiscard("Pure function")]]
		virtual MemoryStatus GetMemoryStatus() const = 0;

		/// @brief Creates a thread.
		/// @param func Thread function.
		/// @param params Thread parameters.
		/// @return Thread.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::thread CreateThread(std::move_only_function<void()> func, ThreadParams params) = 0;

		/// @brief Creates a sleeper.
		/// @return Sleeper.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ISleeper> CreateSleeper() = 0;
	};
}
