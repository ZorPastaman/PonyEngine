/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource:ContextKey;

import std;

export namespace PonyEngine::Resource
{
	struct ContextKey final
	{
		std::uint64_t value = 0ull;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ContextKey& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Resource::ContextKey> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::ContextKey& key) const noexcept
	{
		return std::hash<std::uint64_t>()(key.value);
	}
};
