/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceCollection;

import std;

export namespace PonyEngine::Resource
{
	using ResourceCollectionID = std::uint32_t; ///< Resource collection ID type.
	using ResourceCollectionVersion = std::uint32_t; ///< Resource collection version type.

	/// @brief Resource collection.
	struct ResourceCollection final
	{
		ResourceCollectionID id = std::numeric_limits<ResourceCollectionID>::max(); ///< Resource collection ID.
		ResourceCollectionVersion version = std::numeric_limits<ResourceCollectionVersion>::min(); ///< Resource collection version.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ResourceCollection& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Resource::ResourceCollection> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::ResourceCollection collection) const noexcept
	{
		using HashType = std::uint64_t;
		static_assert(sizeof(HashType) == sizeof(collection), "Invalid hash type.");

		HashType hash;
		std::memcpy(&hash, &collection, sizeof(HashType));
		return std::hash<HashType>()(hash);
	}
};
