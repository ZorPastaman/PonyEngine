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

export module PonyEngine.Application.Impl:ThreadManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Thread manager.
	class ThreadManager final
	{
	public:
		/// @brief Creates a thread manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit ThreadManager(IApplicationContext& application) noexcept;
		ThreadManager(const ThreadManager&) = delete;
		ThreadManager(ThreadManager&&) = delete;

		~ThreadManager() noexcept = default;

		/// @brief Gets the main thread ID. It's the thread on which the manager was created.
		/// @return Main thread ID.
		[[nodiscard("Pure function")]]
		std::thread::id MainThreadID() const noexcept;

		ThreadManager& operator =(const ThreadManager&) = delete;
		ThreadManager& operator =(ThreadManager&&) = delete;

	private:
		std::thread::id mainThreadId; ///< Main thread ID.
	};
}

namespace PonyEngine::Application
{
	ThreadManager::ThreadManager(IApplicationContext& application) noexcept :
		mainThreadId(std::this_thread::get_id())
	{
		PONY_LOG(application.Logger(), Log::LogType::Info, "Main thread id: '{}'.", mainThreadId);
	}

	std::thread::id ThreadManager::MainThreadID() const noexcept
	{
		return mainThreadId;
	}
}
