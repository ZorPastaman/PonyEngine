/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application:TickOrder;

import std;

export namespace PonyEngine::Application
{
	/// @brief Begin(), End() and Tick() orders of @p ITickable.
	struct TickableOrder final
	{
		std::optional<std::int32_t> beginOrder; ///< Begin order. End order is always reverse. If it's @p std::nullopt, @p Begin() and @p End() aren't called.
		std::optional<std::int32_t> tickOrder; ///< Tick order. If it's @p std::nullopt, @p Tick() isn't called.

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const TickableOrder& other) const noexcept = default;
	};
}
