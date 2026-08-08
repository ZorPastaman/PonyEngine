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
	struct DeviceHandle final
	{
		DeviceHandleID id = std::numeric_limits<DeviceHandleID>::max(); ///< ID.
		DeviceHandleVersion version = std::numeric_limits<DeviceHandleVersion>::min(); ///< Version.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const DeviceHandle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::RawInput::DeviceHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::RawInput::DeviceHandle& handle) const noexcept
	{
		using Hash = std::uint64_t;
		static_assert(sizeof(Hash) == sizeof(handle), "Invalid hash type.");

		Hash hash;
		std::memcpy(&hash, &handle, sizeof(Hash));
		return std::hash<Hash>()(hash);
	}
};
