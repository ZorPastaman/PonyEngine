/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:DeviceTypeID;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Device type ID.
	struct DeviceTypeID final
	{
		std::uint64_t hash = 0u; ///< Device type hash.

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const DeviceTypeID& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::RawInput::DeviceTypeID> final
{
	[[nodiscard("Pure operator")]]
	std::size_t operator ()(const PonyEngine::RawInput::DeviceTypeID deviceTypeId) const noexcept
	{
		return std::hash<std::uint64_t>()(deviceTypeId.hash);
	}
};
