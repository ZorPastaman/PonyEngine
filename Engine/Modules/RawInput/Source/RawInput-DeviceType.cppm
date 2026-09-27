/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:DeviceType;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Device type.
	struct DeviceType final
	{
		std::uint64_t hash = 0u; ///< Device type hash.

		/// @brief Returns the device type as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the device type as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const DeviceType& other) const noexcept = default;
	};

	static_assert(sizeof(DeviceType) == sizeof(std::uint64_t) && alignof(DeviceType) == alignof(std::uint64_t), "DeviceType is invalid");

	/// @brief Returns the device type as std::uint64_t.
	/// @param deviceType Device type.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(DeviceType& deviceType) noexcept;
	/// @brief Returns the device type as std::uint64_t.
	/// @param deviceType Device type.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const DeviceType& deviceType) noexcept;

	/// @brief Returns the span of device types as a span of std::uint64_t.
	/// @param deviceTypes Device types.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<DeviceType> deviceTypes) noexcept;
	/// @brief Returns the span of device types as a span of std::uint64_t.
	/// @param deviceTypes Device types.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const DeviceType> deviceTypes) noexcept;
}

namespace PonyEngine::RawInput
{
	std::uint64_t& DeviceType::AsRawData() noexcept
	{
		return hash;
	}

	const std::uint64_t& DeviceType::AsRawData() const noexcept
	{
		return hash;
	}

	std::uint64_t& AsRawData(DeviceType& deviceType) noexcept
	{
		return deviceType.hash;
	}

	const std::uint64_t& AsRawData(const DeviceType& deviceType) noexcept
	{
		return deviceType.hash;
	}

	std::span<std::uint64_t> AsRawData(const std::span<DeviceType> deviceTypes) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(deviceTypes.data()), deviceTypes.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const DeviceType> deviceTypes) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(deviceTypes.data()), deviceTypes.size());
	}
}

export template<>
struct std::hash<PonyEngine::RawInput::DeviceType> final
{
	[[nodiscard("Pure operator")]]
	std::size_t operator ()(const PonyEngine::RawInput::DeviceType deviceTypeId) const noexcept
	{
		return std::hash<std::uint64_t>()(deviceTypeId.hash);
	}
};
