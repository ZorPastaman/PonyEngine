/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:Axis;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Axis.
	struct Axis final
	{
		std::uint32_t hash = 0u; ///< Axis hash.
		std::uint32_t index = 0u; ///< Axis hash index. It's used when different axes have the same hash.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const Axis& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::RawInput::Axis> final
{
	[[nodiscard("Pure function")]]
	std::size_t operator ()(const PonyEngine::RawInput::Axis axisId) const noexcept
	{
		const std::uint64_t hash = static_cast<std::uint64_t>(axisId.hash) << 32 | axisId.index;
		return std::hash<std::uint64_t>()(hash);
	}
};
