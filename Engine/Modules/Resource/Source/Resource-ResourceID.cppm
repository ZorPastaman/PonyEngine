/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource:ResourceID;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource ID.
	struct ResourceID final
	{
		std::uint64_t value = 0ull; ///< ID value.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ResourceID& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Resource::ResourceID> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::ResourceID& id) const noexcept
	{
		return std::hash<std::uint64_t>()(id.value);
	}
};
