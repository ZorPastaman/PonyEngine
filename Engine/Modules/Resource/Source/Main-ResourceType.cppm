/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource:ResourceType;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource type.
	struct ResourceType final
	{
		std::uint64_t value = 0ull; ///< Type value.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ResourceType& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Resource::ResourceType> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::ResourceType& type) const noexcept
	{
		return std::hash<std::uint64_t>()(type.value);
	}
};
