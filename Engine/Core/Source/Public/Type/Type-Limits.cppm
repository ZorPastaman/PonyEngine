/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Type:Limits;

import std;

export namespace PonyEngine::Type
{
	/// @brief Calculates how many 10-base digits the @p value has.
	/// @tparam T Value type.
	/// @param value Value.
	/// @return Digit count.
	/// @remark It doesn't include sign.
	template<std::integral T> [[nodiscard("Pure function")]]
	constexpr std::int32_t Digits10(T value) noexcept;
}

namespace PonyEngine::Type
{
	template<std::integral T>
	constexpr std::int32_t Digits10(T value) noexcept
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			return 1;
		}
		else
		{
			std::int32_t digits = 0;
			for (; value != T{0}; value = static_cast<T>(value / 10), ++digits);
			return std::max(digits, 1);
		}
	}
}
