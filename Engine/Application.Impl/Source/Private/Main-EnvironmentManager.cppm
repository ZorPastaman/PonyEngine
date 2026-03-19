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

export module PonyEngine.Application.Impl:EnvironmentManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Environment manager.
	class EnvironmentManager final
	{
	public:
		/// @brief Creates an environment manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit EnvironmentManager(IApplicationContext& application) noexcept;
		EnvironmentManager(const EnvironmentManager&) = delete;
		EnvironmentManager(EnvironmentManager&&) = delete;

		~EnvironmentManager() noexcept = default;

		/// @brief Gets the main thread ID. It's the thread on which the manager was created.
		/// @return Main thread ID.
		[[nodiscard("Pure function")]]
		std::thread::id MainThreadId() const noexcept;

		EnvironmentManager& operator =(const EnvironmentManager&) = delete;
		EnvironmentManager& operator =(EnvironmentManager&&) = delete;

	private:
		std::thread::id mainThreadId; ///< Main thread ID.
	};
}

namespace PonyEngine::Application
{
	EnvironmentManager::EnvironmentManager(IApplicationContext& application) noexcept :
		mainThreadId(std::this_thread::get_id())
	{
		PONY_LOG(application.Logger(), Log::LogType::Info, "Main thread id: '{}'.", mainThreadId);
	}

	std::thread::id EnvironmentManager::MainThreadId() const noexcept
	{
		return mainThreadId;
	}
}
