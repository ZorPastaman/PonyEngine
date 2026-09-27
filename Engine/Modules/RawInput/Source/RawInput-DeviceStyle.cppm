/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:DeviceStyle;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Device style.
	struct DeviceStyle final
	{
		std::uint64_t hash = 0u; ///< Device style hash.

		/// @brief Returns the device style as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the device style as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const DeviceStyle& other) const noexcept = default;
	};

	static_assert(sizeof(DeviceStyle) == sizeof(std::uint64_t) && alignof(DeviceStyle) == alignof(std::uint64_t), "DeviceStyle is invalid");

	/// @brief Returns the device style as std::uint64_t.
	/// @param deviceStyle Device style.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(DeviceStyle& deviceStyle) noexcept;
	/// @brief Returns the device style as std::uint64_t.
	/// @param deviceStyle Device style.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const DeviceStyle& deviceStyle) noexcept;

	/// @brief Returns the span of device styles as a span of std::uint64_t.
	/// @param deviceStyles Device styles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<DeviceStyle> deviceStyles) noexcept;
	/// @brief Returns the span of device styles as a span of std::uint64_t.
	/// @param deviceStyles Device styles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const DeviceStyle> deviceStyles) noexcept;
}

namespace PonyEngine::RawInput
{
	std::uint64_t& DeviceStyle::AsRawData() noexcept
	{
		return hash;
	}

	const std::uint64_t& DeviceStyle::AsRawData() const noexcept
	{
		return hash;
	}

	std::uint64_t& AsRawData(DeviceStyle& deviceStyle) noexcept
	{
		return deviceStyle.hash;
	}

	const std::uint64_t& AsRawData(const DeviceStyle& deviceStyle) noexcept
	{
		return deviceStyle.hash;
	}

	std::span<std::uint64_t> AsRawData(const std::span<DeviceStyle> deviceStyles) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(deviceStyles.data()), deviceStyles.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const DeviceStyle> deviceStyles) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(deviceStyles.data()), deviceStyles.size());
	}
}

export template<>
struct std::hash<PonyEngine::RawInput::DeviceStyle> final
{
	[[nodiscard("Pure operator")]]
	std::size_t operator ()(const PonyEngine::RawInput::DeviceStyle& deviceStyleId) const noexcept
	{
		return std::hash<std::uint64_t>()(deviceStyleId.hash);
	}
};
