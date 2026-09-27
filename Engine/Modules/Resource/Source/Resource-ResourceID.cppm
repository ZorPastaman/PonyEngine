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

		/// @brief Returns the ID as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the ID as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ResourceID& other) const noexcept = default;
	};

	static_assert(sizeof(ResourceID) == sizeof(std::uint64_t) && alignof(ResourceID) == alignof(std::uint64_t), "ResourceID is invalid");

	/// @brief Returns the resource ID as std::uint64_t.
	/// @param id Resource ID.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(ResourceID& id) noexcept;
	/// @brief Returns the resource ID as std::uint64_t.
	/// @param id Resource ID.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const ResourceID& id) noexcept;

	/// @brief Returns the span of resource IDs as a span of std::uint64_t.
	/// @param ids Resource IDs.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<ResourceID> ids) noexcept;
	/// @brief Returns the span of resource IDs as a span of std::uint64_t.
	/// @param ids Resource IDs.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const ResourceID> ids) noexcept;
}

namespace PonyEngine::Resource
{
	std::uint64_t& ResourceID::AsRawData() noexcept
	{
		return value;
	}

	const std::uint64_t& ResourceID::AsRawData() const noexcept
	{
		return value;
	}

	std::uint64_t& AsRawData(ResourceID& id) noexcept
	{
		return id.value;
	}

	const std::uint64_t& AsRawData(const ResourceID& id) noexcept
	{
		return id.value;
	}

	std::span<std::uint64_t> AsRawData(const std::span<ResourceID> ids) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(ids.data()), ids.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const ResourceID> ids) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(ids.data()), ids.size());
	}
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
