/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Memory:Utility;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Memory
{
	/// @brief Calculates a required buffer size according to a previous type.
	/// @tparam T Current type.
	/// @tparam Prev Previous type. If it's calculated for a first type, leave it as std::max_align_t or set a custom buffer alignment higher than std::max_align_t.
	/// @param count Object count.
	/// @return Required size to place this array.
	template<typename T, typename Prev = std::max_align_t> [[nodiscard("Pure function")]]
	constexpr std::size_t CalculateBufferSize(std::size_t count = 1uz) noexcept;
}

namespace PonyEngine::Memory
{
	template<typename T, typename Prev>
	constexpr std::size_t CalculateBufferSize(const std::size_t count) noexcept
	{
		const std::size_t alignmentShift = Math::DifferenceClamp(alignof(T), alignof(Prev)) & (static_cast<std::size_t>(count == 0uz) - 1uz);
		return count * sizeof(T) + alignmentShift;
	}
}
