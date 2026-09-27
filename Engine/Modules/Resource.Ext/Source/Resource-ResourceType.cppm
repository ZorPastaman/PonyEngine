/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceType;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource type.
	struct ResourceType final
	{
		std::uint64_t value = 0ull; ///< Type value.

		/// @brief Returns the type as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the type as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ResourceType& other) const noexcept = default;
	};

	static_assert(sizeof(ResourceType) == sizeof(std::uint64_t) && alignof(ResourceType) == alignof(std::uint64_t), "ResourceType is invalid");

	/// @brief Returns the resource type as std::uint64_t.
	/// @param type Resource type.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(ResourceType& type) noexcept;
	/// @brief Returns the resource type as std::uint64_t.
	/// @param type Resource type.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const ResourceType& type) noexcept;

	/// @brief Returns the span of resource types as a span of std::uint64_t.
	/// @param types Resource types.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<ResourceType> types) noexcept;
	/// @brief Returns the span of resource types as a span of std::uint64_t.
	/// @param types Resource types.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const ResourceType> types) noexcept;
}

namespace PonyEngine::Resource
{
	std::uint64_t& ResourceType::AsRawData() noexcept
	{
		return value;
	}

	const std::uint64_t& ResourceType::AsRawData() const noexcept
	{
		return value;
	}

	std::uint64_t& AsRawData(ResourceType& type) noexcept
	{
		return type.value;
	}

	const std::uint64_t& AsRawData(const ResourceType& type) noexcept
	{
		return type.value;
	}

	std::span<std::uint64_t> AsRawData(const std::span<ResourceType> types) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(types.data()), types.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const ResourceType> types) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(types.data()), types.size());
	}
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
