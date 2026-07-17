/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:ThreadManager;

import std;

export namespace PonyEngine::Application
{
	/// @brief Thread manager.
	class ThreadManager final
	{
	public:
		/// @brief Creates a thread manager.
		/// @note Must be created on a main thread.
		[[nodiscard("Pure constructor")]]
		explicit ThreadManager() noexcept;
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
	ThreadManager::ThreadManager() noexcept :
		mainThreadId(std::this_thread::get_id())
	{
	}

	std::thread::id ThreadManager::MainThreadID() const noexcept
	{
		return mainThreadId;
	}
}
