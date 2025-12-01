/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:AxisId;

import std;

export namespace PonyEngine::Input
{
	/// @brief Axis ID.
	struct AxisId final
	{
		std::uint32_t hash; ///< Axis hash.
		std::uint32_t index; ///< Axis hash index. It's used when different axes have the same hash.

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const AxisId& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Input::AxisId> final
{
	[[nodiscard("Pure function")]]
	std::size_t operator ()(const PonyEngine::Input::AxisId axisId) const noexcept
	{
		return std::hash<std::uint64_t>()(*reinterpret_cast<const std::uint64_t*>(&axisId));
	}
};
