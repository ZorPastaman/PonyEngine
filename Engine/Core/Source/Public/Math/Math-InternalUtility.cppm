/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:InternalUtility;

import PonyEngine.Type;

export namespace PonyEngine::Math
{
	/// @brief Converts the @p value to the type @p T.
	/// @note This function allows to convert between arithmetic types without any checks, but it doesn't suppress warnings.
	/// @tparam T Target type.
	/// @tparam U Source type.
	/// @param value Value to convert.
	/// @return Converted value.
	template<Type::Arithmetic T, Type::Arithmetic U>
	constexpr T ConvertTo(U value) noexcept;
}

namespace PonyEngine::Math
{
	template<Type::Arithmetic T, Type::Arithmetic U>
	constexpr T ConvertTo(const U value) noexcept
	{
		return value;
	}
}
