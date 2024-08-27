/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time:FrameTimeFrameRateConversion;

import <concepts>;

export namespace PonyEngine::Time
{
	/// @brief Converts frame time to frame rate or frame rate to frame time.
	/// @tparam T Value type.
	/// @param value Value to convert.
	/// @return 1/value if the @p value is greater than 0; 0 otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	T ConvertFrameRateFrameTime(T value) noexcept;
}

namespace PonyEngine::Time
{
	template<std::floating_point T>
	T ConvertFrameRateFrameTime(const T value) noexcept
	{
		return value > T{0} ? T{1} / value : T{0};
	}
}
