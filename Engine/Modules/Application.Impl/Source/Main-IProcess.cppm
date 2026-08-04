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

		/// @brief Creates a thread control.
		/// @param thread Target thread.
		/// @return Thread control.
		/// @note The function is thread-safe.
		/// @note Only one thread control per thread may be created.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IThreadControl> CreateThreadControl(std::thread& thread) = 0;
		/// @brief Gets a current role of a main thread.
		/// @return Role.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::string_view MainThreadRole() const noexcept = 0;
		/// @brief Sets the role to a main thread.
		/// @param role Role to set. Empty role means a default role.
		/// @note In case of an exception, a default role will be applied.
		/// @note The function must be called on a main thread.
		virtual void MainThreadRole(std::string_view role) = 0;
	};
}
