/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:AxisID;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Axis ID.
	struct AxisID final
	{
		std::uint32_t hash = 0u; ///< Axis hash.
		std::uint32_t index = 0u; ///< Axis hash index. It's used when different axes have the same hash.

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const AxisID& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::RawInput::AxisID> final
{
	[[nodiscard("Pure function")]]
	std::size_t operator ()(const PonyEngine::RawInput::AxisID axisId) const noexcept
	{
		return std::hash<std::uint64_t>()(*reinterpret_cast<const std::uint64_t*>(&axisId));
	}
};
