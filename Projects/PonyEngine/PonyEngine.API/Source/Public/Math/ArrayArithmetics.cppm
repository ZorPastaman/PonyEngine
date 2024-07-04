/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Core/Optimization.h"

export module PonyEngine.Math:ArrayArithmetics;

import <algorithm>;
import <cstddef>;
import <cmath>;
import <type_traits>;

import :Common;

export namespace PonyEngine::Math
{
	/// @brief Copies the @p source array to the @p destination array.
	/// @tparam T Value type.
	/// @param destination Destination array. Its length must be at least @p count.
	/// @param source Source array. Its length must be at least @p count.
	/// @param count Element count.
	template<typename T>
	constexpr void Copy(T* PONY_RESTRICT destination, const T* PONY_RESTRICT source, std::size_t count) noexcept;

	/// @brief Casts every element in the @p source array to @p U and puts the result to the @p destination array.
	/// @tparam T Source type.
	/// @tparam U Target type.
	/// @param destination Destination array.Its length must be at least @p count.
	/// @param source Source array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T, Arithmetic U>
	constexpr void Cast(U* PONY_RESTRICT destination, const T* PONY_RESTRICT source, std::size_t count) noexcept;

	/// @brief Computes result += right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Add(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, std::size_t count) noexcept;
	/// @brief Computes result = left + right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param left Left operand array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Add(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, std::size_t count) noexcept;

	/// @brief Computes result -= right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Subtract(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, std::size_t count) noexcept;
	/// @brief Computes result = left - right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param left Left operand array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Subtract(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, std::size_t count) noexcept;

	/// @brief Computes result *= right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Multiply(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, std::size_t count) noexcept;
	/// @brief Computes result = left * right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param left Left operand array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Multiply(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, std::size_t count) noexcept;
	/// @brief Computes result *= multiplier on every element in the sequential order.
	/// @tparam T Value type.
	/// @tparam U Multiplier type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param multiplier Multiplier.
	/// @param count Element count.
	template<Arithmetic T, Arithmetic U>
	constexpr void Multiply(T* result, U multiplier, std::size_t count) noexcept;
	/// @brief Computes result = left * multiplier on every element in the sequential order.
	/// @tparam T Value type.
	/// @tparam U Multiplier type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param left Left operand array. Its length must be at least @p count.
	/// @param multiplier Multiplier.
	/// @param count Element count.
	template<Arithmetic T, Arithmetic U>
	constexpr void Multiply(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, U multiplier, std::size_t count) noexcept;

	/// @brief Computes result /= right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Divide(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, std::size_t count) noexcept;
	/// @brief Computes result = left / right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param left Left operand array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Divide(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, std::size_t count) noexcept;
	/// @brief Computes result /= divisor on every element in the sequential order.
	/// @tparam T Value type.
	/// @tparam U Divisor type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param divisor Divisor.
	/// @param count Element count.
	template<Arithmetic T, Arithmetic U>
	constexpr void Divide(T* result, U divisor, std::size_t count) noexcept;
	/// @brief Computes result = left / divisor on every element in the sequential order.
	/// @tparam T Value type.
	/// @tparam U Divisor type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param left Left operand array. Its length must be at least @p count.
	/// @param divisor Divisor.
	/// @param count Element count.
	template<Arithmetic T, Arithmetic U>
	constexpr void Divide(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, U divisor, std::size_t count) noexcept;

	/// @brief Computes result = -result on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Negate(T* result, std::size_t count) noexcept;
	/// @brief Computes result = -right on every element in the sequential order.
	/// @tparam T Value type.
	/// @param result Result array. Its length must be at least @p count.
	/// @param right Right operand array. Its length must be at least @p count.
	/// @param count Element count.
	template<Arithmetic T>
	constexpr void Negate(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, std::size_t count) noexcept;

	/// @brief Checks if all the values in the array are finite.
	/// @tparam T Value type.
	/// @param values Value array. Its length must be at least @p count.
	/// @param count Element count.
	/// @return @a True if all the values are finite; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsFinite(const T* values, std::size_t count) noexcept;
}

namespace PonyEngine::Math
{
	template<typename T>
	constexpr void Copy(T* const PONY_RESTRICT destination, const T* const PONY_RESTRICT source, const std::size_t count) noexcept
	{
		std::copy(source, source + count, destination);
	}

	template<Arithmetic T, Arithmetic U>
	constexpr void Cast(U* PONY_RESTRICT destination, const T* PONY_RESTRICT source, const std::size_t count) noexcept
	{
		for (const U* const end = destination + count; destination != end; ++destination, ++source)
		{
			*destination = static_cast<U>(*source);
		}
	}

	template<Arithmetic T>
	constexpr void Add(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result += *right;
		}
	}

	template<Arithmetic T>
	constexpr void Add(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left, ++right)
		{
			*result = *left + *right;
		}
	}

	template<Arithmetic T>
	constexpr void Subtract(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result -= *right;
		}
	}

	template<Arithmetic T>
	constexpr void Subtract(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left, ++right)
		{
			*result = *left - *right;
		}
	}

	template<Arithmetic T>
	constexpr void Multiply(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result *= *right;
		}
	}

	template<Arithmetic T>
	constexpr void Multiply(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left, ++right)
		{
			*result = *left * *right;
		}
	}

	template<Arithmetic T, Arithmetic U>
	constexpr void Multiply(T* result, const U multiplier, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result)
		{
			*result *= multiplier;
		}
	}

	template<Arithmetic T, Arithmetic U>
	constexpr void Multiply(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const U multiplier, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left)
		{
			*result = *left * multiplier;
		}
	}

	template<Arithmetic T>
	constexpr void Divide(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result /= *right;
		}
	}

	template<Arithmetic T>
	constexpr void Divide(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left, ++right)
		{
			*result = *left / *right;
		}
	}

	template<Arithmetic T, Arithmetic U>
	constexpr void Divide(T* result, const U divisor, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result)
		{
			*result /= divisor;
		}
	}

	template<Arithmetic T, Arithmetic U>
	constexpr void Divide(T* PONY_RESTRICT result, const T* PONY_RESTRICT left, const U divisor, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left)
		{
			*result = *left / divisor;
		}
	}

	template<Arithmetic T>
	constexpr void Negate(T* result, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result)
		{
			*result = -*result;
		}
	}

	template<Arithmetic T>
	constexpr void Negate(T* PONY_RESTRICT result, const T* PONY_RESTRICT right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result = -*right;
		}
	}

	template<std::floating_point T>
	bool IsFinite(const T* values, const std::size_t count) noexcept
	{
		for (const T* const end = values + count; values != end; ++values)
		{
			if (!std::isfinite(*values))
			{
				return false;
			}
		}

		return true;
	}
}
