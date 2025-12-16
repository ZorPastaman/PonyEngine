/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:DeviceTypeId;

import std;

export namespace PonyEngine::Input
{
	/// @brief Device type ID.
	struct DeviceTypeId final
	{
		std::uint64_t hash = 0u; ///< Device type hash.

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const DeviceTypeId& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Input::DeviceTypeId> final
{
	[[nodiscard("Pure operator")]]
	std::size_t operator ()(const PonyEngine::Input::DeviceTypeId deviceTypeId) const noexcept
	{
		return std::hash<std::uint64_t>()(deviceTypeId.hash);
	}
};
