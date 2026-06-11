/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource:ContextValue;

import std;

export namespace PonyEngine::Resource
{
	struct ContextValue final
	{
		std::uint64_t value = 0ull;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ContextValue& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Resource::ContextValue> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::ContextValue& value) const noexcept
	{
		return std::hash<std::uint64_t>()(value.value);
	}
};
