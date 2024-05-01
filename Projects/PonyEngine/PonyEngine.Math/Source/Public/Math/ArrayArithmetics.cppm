/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:ArrayArithmetics;

import <cstddef>;
import <cmath>;
import <type_traits>;

import :Common;

export namespace PonyEngine::Math
{
	template<typename T>
	constexpr void AssignWithDestinationStep(T* destination, const T* source, std::size_t count, std::size_t destinationStep);
	template<typename T>
	constexpr void AssignWithSourceStep(T* destination, const T* source, std::size_t count, std::size_t sourceStep);

	template<Arithmetic T>
	constexpr void Add(T* result, const T* right, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Add(T* result, const T* left, const T* right, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Subtract(T* result, const T* right, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Subtract(T* result, const T* left, const T* right, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Multiply(T* result, const T* right, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Multiply(T* result, const T* left, const T* right, std::size_t count) noexcept;

	template<Arithmetic T, Arithmetic U>
	constexpr void Multiply(T* result, U multiplier, std::size_t count) noexcept;

	template<Arithmetic T, Arithmetic U>
	constexpr void Multiply(T* result, const T* left, U multiplier, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Divide(T* result, const T* right, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Divide(T* result, const T* left, const T* right, std::size_t count) noexcept;

	template<Arithmetic T, Arithmetic U>
	constexpr void Divide(T* result, U divisor, std::size_t count) noexcept;

	template<Arithmetic T, Arithmetic U>
	constexpr void Divide(T* result, const T* left, U divisor, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Negate(T* result, std::size_t count) noexcept;

	template<Arithmetic T>
	constexpr void Negate(T* result, const T* right, std::size_t count) noexcept;

	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const T* values, std::size_t count) noexcept;

	template<Arithmetic T> [[nodiscard("Pure function")]]
	constexpr T Dot(const T* left, const T* right, std::size_t count) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool IsFinite(const T* values, std::size_t count) noexcept;
}

namespace PonyEngine::Math
{
	template<typename T>
	constexpr void AssignWithDestinationStep(T* destination, const T* source, const std::size_t count, const std::size_t destinationStep)
	{
		if (std::is_constant_evaluated()) [[unlikely]]
		{
			for (const T* const end = source + count - 1; source != end; destination += destinationStep, ++source)
			{
				*destination = *source;
			}

			*destination = *source;
		}
		else [[likely]]
		{
			for (const T* const end = source + count; source != end; destination += destinationStep, ++source)
			{
				*destination = *source;
			}
		}
	}

	template<typename T>
	constexpr void AssignWithSourceStep(T* destination, const T* source, const std::size_t count, const std::size_t sourceStep)
	{
		if (std::is_constant_evaluated()) [[unlikely]]
		{
			for (const T* const end = destination + count - 1; destination != end; ++destination, source += sourceStep)
			{
				*destination = *source;
			}

			*destination = *source;
		}
		else [[likely]]
		{
			for (const T* const end = destination + count; destination != end; ++destination, source += sourceStep)
			{
				*destination = *source;
			}
		}
	}

	template<Arithmetic T>
	constexpr void Add(T* result, const T* right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result += *right;
		}
	}

	template<Arithmetic T>
	constexpr void Add(T* result, const T* left, const T* right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left, ++right)
		{
			*result = *left + *right;
		}
	}

	template<Arithmetic T>
	constexpr void Subtract(T* result, const T* right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result -= *right;
		}
	}

	template<Arithmetic T>
	constexpr void Subtract(T* result, const T* left, const T* right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left, ++right)
		{
			*result = *left - *right;
		}
	}

	template<Arithmetic T>
	constexpr void Multiply(T* result, const T* right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result *= *right;
		}
	}

	template<Arithmetic T>
	constexpr void Multiply(T* result, const T* left, const T* right, const std::size_t count) noexcept
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
	constexpr void Multiply(T* result, const T* left, U multiplier, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++left)
		{
			*result = *left * multiplier;
		}
	}

	template<Arithmetic T>
	constexpr void Divide(T* result, const T* right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result /= *right;
		}
	}

	template<Arithmetic T>
	constexpr void Divide(T* result, const T* left, const T* right, const std::size_t count) noexcept
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
	constexpr void Divide(T* result, const T* left, U divisor, const std::size_t count) noexcept
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
	constexpr void Negate(T* result, const T* right, const std::size_t count) noexcept
	{
		for (const T* const end = result + count; result != end; ++result, ++right)
		{
			*result = -*right;
		}
	}

	template<Arithmetic T>
	constexpr T Dot(const T* values, const std::size_t count) noexcept
	{
		T dot = T{0};

		for (const T* const end = values + count; values != end; ++values)
		{
			dot += *values * *values;
		}

		return dot;
	}

	template<Arithmetic T>
	constexpr T Dot(const T* left, const T* right, const std::size_t count) noexcept
	{
		T dot = T{0};

		for (const T* const end = left + count; left != end; ++left, ++right)
		{
			dot += *left * *right;
		}

		return dot;
	}

	template<std::floating_point T>
	constexpr bool IsFinite(const T* values, const std::size_t count) noexcept
	{
		bool isFinite = true;

		for (const T* const end = values + count; values != end && isFinite; ++values)
		{
			isFinite = std::isfinite(*values);
		}

		return isFinite;
	}
}
