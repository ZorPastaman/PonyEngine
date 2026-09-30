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
	using PackID = std::uint32_t; ///< Pack handle ID type.
	using PackVersion = std::uint32_t; ///< Pack handle version type.

	/// @brief Pack handle.
	struct alignas(std::uint64_t) PackHandle final
	{
		PackID id = std::numeric_limits<PackID>::max(); ///< Pack handle ID.
		PackVersion version = std::numeric_limits<PackVersion>::min(); ///< Pack handle version.

		/// @brief Returns the handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const PackHandle& other) const noexcept = default;
	};

	static_assert(sizeof(PackHandle) == sizeof(std::uint64_t) && alignof(PackHandle) == alignof(std::uint64_t), "PackHandle is invalid");

	/// @brief Returns the handle as std::uint64_t.
	/// @param handle Pack handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(PackHandle& handle) noexcept;
	/// @brief Returns the handle as std::uint64_t.
	/// @param handle Pack handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const PackHandle& handle) noexcept;

	/// @brief Returns the span of handles as a span of std::uint64_t.
	/// @param handles Pack handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<PackHandle> handles) noexcept;
	/// @brief Returns the span of handles as a span of std::uint64_t.
	/// @param handles Pack handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const PackHandle> handles) noexcept;
}

namespace PonyEngine::Resource::Pack
{
	std::uint64_t& PackHandle::AsRawData() noexcept
	{
		return Pack::AsRawData(*this);
	}

	const std::uint64_t& PackHandle::AsRawData() const noexcept
	{
		return Pack::AsRawData(*this);
	}

	std::uint64_t& AsRawData(PackHandle& handle) noexcept
	{
		return reinterpret_cast<std::uint64_t&>(handle);
	}

	const std::uint64_t& AsRawData(const PackHandle& handle) noexcept
	{
		return reinterpret_cast<const std::uint64_t&>(handle);
	}

	std::span<std::uint64_t> AsRawData(const std::span<PackHandle> handles) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(handles.data()), handles.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const PackHandle> handles) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(handles.data()), handles.size());
	}
}

export template<>
struct std::hash<PonyEngine::Resource::Pack::PackHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::Pack::PackHandle& handle) const noexcept
	{
		return std::hash<std::uint64_t>()(handle.AsRawData());
	}
};
