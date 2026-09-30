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
	struct alignas(std::uint64_t) ResourceCollection final
	{
		ResourceCollectionID id = std::numeric_limits<ResourceCollectionID>::max(); ///< Resource collection ID.
		ResourceCollectionVersion version = std::numeric_limits<ResourceCollectionVersion>::min(); ///< Resource collection version.

		/// @brief Returns the collection as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the collection as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ResourceCollection& other) const noexcept = default;
	};

	static_assert(sizeof(ResourceCollection) == sizeof(std::uint64_t) && alignof(ResourceCollection) == alignof(std::uint64_t), "ResourceCollection is invalid");

	/// @brief Returns the resource collection as std::uint64_t.
	/// @param collection Resource collection.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(ResourceCollection& collection) noexcept;
	/// @brief Returns the resource collection as std::uint64_t.
	/// @param collection Resource collection.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const ResourceCollection& collection) noexcept;

	/// @brief Returns the span of resource collections as a span of std::uint64_t.
	/// @param collections Resource collections.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<ResourceCollection> collections) noexcept;
	/// @brief Returns the span of resource collections as a span of std::uint64_t.
	/// @param collections Resource collections.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const ResourceCollection> collections) noexcept;
}

namespace PonyEngine::Resource
{
	std::uint64_t& ResourceCollection::AsRawData() noexcept
	{
		return Resource::AsRawData(*this);
	}

	const std::uint64_t& ResourceCollection::AsRawData() const noexcept
	{
		return Resource::AsRawData(*this);
	}

	std::uint64_t& AsRawData(ResourceCollection& collection) noexcept
	{
		return reinterpret_cast<std::uint64_t&>(collection);
	}

	const std::uint64_t& AsRawData(const ResourceCollection& collection) noexcept
	{
		return reinterpret_cast<const std::uint64_t&>(collection);
	}

	std::span<std::uint64_t> AsRawData(const std::span<ResourceCollection> collections) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(collections.data()), collections.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const ResourceCollection> collections) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(collections.data()), collections.size());
	}
}

export template<>
struct std::hash<PonyEngine::Resource::ResourceCollection> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::ResourceCollection& collection) const noexcept
	{
		return std::hash<std::uint64_t>()(collection.AsRawData());
	}
};
