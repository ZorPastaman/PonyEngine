/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display:DisplayHandle;

import std;

export namespace PonyEngine::Display
{
	using DisplayHandleID = std::uint32_t;
	using DisplayHandleVersion = std::uint32_t;

	/// @brief Display handle.
	struct alignas(std::uint64_t) DisplayHandle final
	{
		DisplayHandleID id = std::numeric_limits<DisplayHandleID>::max(); ///< ID.
		DisplayHandleVersion version = std::numeric_limits<DisplayHandleVersion>::min(); ///< Version.

		/// @brief Returns the display handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the display handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const DisplayHandle& other) const noexcept = default;
	};

	static_assert(sizeof(DisplayHandle) == sizeof(std::uint64_t) && alignof(DisplayHandle) == alignof(std::uint64_t), "DisplayHandle is invalid");

	/// @brief Returns the display handle as std::uint64_t.
	/// @param displayHandle Display handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(DisplayHandle& displayHandle) noexcept;
	/// @brief Returns the display handle as std::uint64_t.
	/// @param displayHandle Display handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const DisplayHandle& displayHandle) noexcept;

	/// @brief Returns the span of display handles as a span of std::uint64_t.
	/// @param displayHandles Display handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<DisplayHandle> displayHandles) noexcept;
	/// @brief Returns the span of display handles as a span of std::uint64_t.
	/// @param displayHandles Display handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const DisplayHandle> displayHandles) noexcept;
}

namespace PonyEngine::Display
{
	std::uint64_t& DisplayHandle::AsRawData() noexcept
	{
		return Display::AsRawData(*this);
	}

	const std::uint64_t& DisplayHandle::AsRawData() const noexcept
	{
		return Display::AsRawData(*this);
	}

	std::uint64_t& AsRawData(DisplayHandle& displayHandle) noexcept
	{
		return reinterpret_cast<std::uint64_t&>(displayHandle);
	}

	const std::uint64_t& AsRawData(const DisplayHandle& displayHandle) noexcept
	{
		return reinterpret_cast<const std::uint64_t&>(displayHandle);
	}

	std::span<std::uint64_t> AsRawData(const std::span<DisplayHandle> displayHandles) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(displayHandles.data()), displayHandles.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const DisplayHandle> displayHandles) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(displayHandles.data()), displayHandles.size());
	}
}

template<>
struct std::hash<PonyEngine::Display::DisplayHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Display::DisplayHandle& handle) const noexcept
	{
		return std::hash<std::uint64_t>()(handle.AsRawData());
	}
};
