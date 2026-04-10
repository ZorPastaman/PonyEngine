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

export module PonyEngine.RenderDevice:IWaiter;

import std;

import :IFence;

export namespace PonyEngine::RenderDevice
{
	/// @brief Waiter.
	class IWaiter
	{
		PONY_INTERFACE_BODY(IWaiter)

		/// @brief Puts a cpu thread the function is called on into a sleep till the fence reach its target values.
		/// @param fence Fence. Must be valid.
		/// @param value Fence target value.
		/// @param timeout Timeout.
		void Wait(const IFence& fence, std::uint64_t value, std::chrono::nanoseconds timeout);
		/// @brief Puts a cpu thread the function is called on into a sleep till all the fences reach their target values.
		/// @param fenceValues Pairs of fences and their target values. All the fences must be valid.
		/// @param timeout Timeout.
		virtual void Wait(std::span<const std::pair<const IFence*, std::uint64_t>> fenceValues, std::chrono::nanoseconds timeout) = 0;
		/// @brief Puts a cpu thread the function is called on into a sleep till the fence reach its target values.
		/// @tparam T Timeout type.
		/// @param fence Fence. Must be valid.
		/// @param value Fence target value.
		/// @param timeout Timeout in seconds.
		template<std::floating_point T>
		void WaitSeconds(const IFence& fence, std::uint64_t value, T timeout);
		/// @brief Puts a cpu thread the function is called on into a sleep till all the fences reach their target values.
		/// @tparam T Timeout type.
		/// @param fenceValues Pairs of fences and their target values.
		/// @param timeout Timeout in seconds.
		template<std::floating_point T>
		void WaitSeconds(std::span<const std::pair<const IFence*, std::uint64_t>> fenceValues, T timeout);

		/// @brief Gets the waiter name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the waiter name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void IWaiter::Wait(const IFence& fence, const std::uint64_t value, const std::chrono::nanoseconds timeout)
	{
		const auto pair = std::pair(&fence, value);
		Wait(std::span(&pair, 1uz), timeout);
	}

	template<std::floating_point T>
	void IWaiter::WaitSeconds(const IFence& fence, const std::uint64_t value, const T timeout)
	{
		Wait(fence, value, std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<T>(timeout)));
	}

	template<std::floating_point T>
	void IWaiter::WaitSeconds(const std::span<const std::pair<const IFence*, std::uint64_t>> fenceValues, const T timeout)
	{
		Wait(fenceValues, std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<T>(timeout)));
	}
}
