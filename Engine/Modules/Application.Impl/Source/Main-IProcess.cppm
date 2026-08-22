/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Application.Impl:IProcess;

import std;

import PonyEngine.Application;

export namespace PonyEngine::Application
{
	/// @brief Process.
	class IProcess
	{
		PONY_INTERFACE_BODY(IProcess)

		/// @brief Creates a thread.
		/// @param func Thread function.
		/// @param params Thread parameters.
		/// @return Thread.
		[[nodiscard("Pure function")]]
		virtual std::thread CreateThread(std::move_only_function<void()> func, const ThreadParams& params = ThreadParams{}) = 0;
	};
}
