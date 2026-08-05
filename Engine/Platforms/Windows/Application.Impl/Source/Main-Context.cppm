/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:Context;

import std;

import PonyEngine.Application.Impl;

export namespace PonyEngine::Application
{
	class Context final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Context(const App& application) noexcept;
		Context(const Context&) = delete;
		Context(Context&&) = delete;

		~Context() noexcept = default;

		[[nodiscard("Pure function")]]
		const App& Application() const noexcept;

		void IncrementThreadControlCount() const noexcept;
		void DecrementThreadControlCount() const noexcept;

		/// @brief Ensures that counts are zero. Must be called on process destruction.
		void EnsureZeroCounts() const noexcept;

		Context& operator =(const Context&) = delete;
		Context& operator =(Context&&) = delete;

	private:
		const App* application;

#ifndef NDEBUG
		mutable std::atomic_size_t threadControlCount;
#endif

		static_assert(std::atomic_size_t::is_always_lock_free, "std::atomic_size_t is not lock free.");
	};
}

namespace PonyEngine::Application
{
	Context::Context(const App& application) noexcept :
#ifndef NDEBUG
		threadControlCount(0uz),
#endif
		application{&application}
	{
	}

	const App& Context::Application() const noexcept
	{
		return *application;
	}

	void Context::IncrementThreadControlCount() const noexcept
	{
#ifndef NDEBUG
		threadControlCount.fetch_add(1uz, std::memory_order::relaxed);
#endif
	}

	void Context::DecrementThreadControlCount() const noexcept
	{
#ifndef NDEBUG
		const std::size_t prev = threadControlCount.fetch_sub(1uz, std::memory_order::relaxed);
		assert(prev > 0uz && "Invalid thread control count decrement.");
#endif
	}

	void Context::EnsureZeroCounts() const noexcept
	{
#ifndef NDEBUG
		assert(threadControlCount.load(std::memory_order::relaxed) == 0uz && "Thread control count isn't zero.");
#endif
	}
}
