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

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const DeviceStyle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::RawInput::DeviceStyle> final
{
	[[nodiscard("Pure operator")]]
	std::size_t operator ()(const PonyEngine::RawInput::DeviceStyle deviceStyleId) const noexcept
	{
		return std::hash<std::uint64_t>()(deviceStyleId.hash);
	}
};
