/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:DeviceHandle;

import std;

export namespace PonyEngine::RawInput
{
	using DeviceHandleID = std::uint32_t;
	using DeviceHandleVersion = std::uint32_t;

	/// @brief Device handle.
	struct alignas(std::uint64_t) DeviceHandle final
	{
		DeviceHandleID id = std::numeric_limits<DeviceHandleID>::max(); ///< ID.
		DeviceHandleVersion version = std::numeric_limits<DeviceHandleVersion>::min(); ///< Version.

		/// @brief Returns the device handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the device handle as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const DeviceHandle& other) const noexcept = default;
	};

	static_assert(sizeof(DeviceHandle) == sizeof(std::uint64_t) && alignof(DeviceHandle) == alignof(std::uint64_t), "DeviceHandle is invalid");

	/// @brief Returns the device handle as std::uint64_t.
	/// @param deviceHandle Device handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(DeviceHandle& deviceHandle) noexcept;
	/// @brief Returns the device handle as std::uint64_t.
	/// @param deviceHandle Device handle.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const DeviceHandle& deviceHandle) noexcept;

	/// @brief Returns the span of device handles as a span of std::uint64_t.
	/// @param deviceHandles Device handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<DeviceHandle> deviceHandles) noexcept;
	/// @brief Returns the span of device handles as a span of std::uint64_t.
	/// @param deviceHandles Device handles.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const DeviceHandle> deviceHandles) noexcept;
}

namespace PonyEngine::RawInput
{
	std::uint64_t& DeviceHandle::AsRawData() noexcept
	{
		return RawInput::AsRawData(*this);
	}

	const std::uint64_t& DeviceHandle::AsRawData() const noexcept
	{
		return RawInput::AsRawData(*this);
	}

	std::uint64_t& AsRawData(DeviceHandle& deviceHandle) noexcept
	{
		return reinterpret_cast<std::uint64_t&>(deviceHandle);
	}

	const std::uint64_t& AsRawData(const DeviceHandle& deviceHandle) noexcept
	{
		return reinterpret_cast<const std::uint64_t&>(deviceHandle);
	}

	std::span<std::uint64_t> AsRawData(const std::span<DeviceHandle> deviceHandles) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(deviceHandles.data()), deviceHandles.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const DeviceHandle> deviceHandles) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(deviceHandles.data()), deviceHandles.size());
	}
}

export template<>
struct std::hash<PonyEngine::RawInput::DeviceHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::RawInput::DeviceHandle& handle) const noexcept
	{
		return std::hash<std::uint64_t>()(handle.AsRawData());
	}
};
