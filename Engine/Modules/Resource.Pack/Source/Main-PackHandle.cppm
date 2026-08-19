/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack:PackHandle;

import std;

export namespace PonyEngine::Resource::Pack
{
	using PackID = std::uint32_t;
	using PackVersion = std::uint32_t;

	struct PackHandle final
	{
		PackID id = std::numeric_limits<PackID>::max();
		PackVersion version = std::numeric_limits<PackVersion>::min();

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const PackHandle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Resource::Pack::PackHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::Pack::PackHandle handle) const noexcept
	{
		using HashType = std::uint64_t;
		static_assert(sizeof(HashType) == sizeof(handle), "Invalid hash type.");

		HashType hash;
		std::memcpy(&hash, &handle, sizeof(HashType));
		return std::hash<HashType>()(hash);
	}
};
