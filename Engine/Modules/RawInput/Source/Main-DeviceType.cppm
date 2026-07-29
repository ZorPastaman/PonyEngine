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

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const DeviceType& other) const noexcept = default;
	};
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
