/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Insides;

import std;

import PonyEngine.Type;

import :Ball;
import :Bounds;
import :Box;
import :Common;
import :Matrix;
import :OrientedBox;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Checks if the @p small ball is fully inside the @p large ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small ball.
	/// @param large Large ball.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Ball<T, Size>& small, const Ball<T, Size>& large) noexcept;
	/// @brief Checks if the @p small ball is fully inside the @p large box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small ball.
	/// @param large Large box.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Ball<T, Size>& small, const Box<T, Size>& large) noexcept;
	/// @brief Checks if the @p small ball is fully inside the @p large box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small ball.
	/// @param large Large box.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Ball<T, Size>& small, const OrientedBox<T, Size>& large) noexcept;

	/// @brief Checks if the @p small box is fully inside the @p large box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small box.
	/// @param large Large box.
	/// @return @a True if the @p small is fully inside the @p large.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Box<T, Size>& small, const Box<T, Size>& large) noexcept;
	/// @brief Checks if the @p small box is fully inside the @p large ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small box.
	/// @param large Large ball.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const Box<T, Size>& small, const Ball<T, Size>& large) noexcept;
	/// @brief Checks if the @p small box is fully inside the @p large box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small box.
	/// @param large Large box.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool IsInside(const Box<T, Size>& small, const OrientedBox<T, Size>& large) noexcept;

	/// @brief Checks if the @p small box is fully inside the @p large box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small box.
	/// @param large Large box.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool IsInside(const OrientedBox<T, Size>& small, const OrientedBox<T, Size>& large) noexcept;
	/// @brief Checks if the @p small box is fully inside the @p large ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small box.
	/// @param large Large ball.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const OrientedBox<T, Size>& small, const Ball<T, Size>& large) noexcept;
	/// @brief Checks if the @p small box is fully inside the @p large box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param small Small box.
	/// @param large Large box.
	/// @return @a True if the @p small is fully inside the @p large.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool IsInside(const OrientedBox<T, Size>& small, const Box<T, Size>& large) noexcept;
}

namespace PonyEngine::Math
{
	template<std::floating_point T, std::size_t Size>
	constexpr bool IsInside(const Ball<T, Size>& small, const Ball<T, Size>& large) noexcept
	{
		const T radiusDiff = large.Radius() - small.Radius();
		return radiusDiff >= T{0} && DistanceSquared(small.Center(), large.Center()) <= radiusDiff * radiusDiff;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool IsInside(const Ball<T, Size>& small, const Box<T, Size>& large) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (Abs(small.Center()[i] - large.Center()[i]) > large.Extent(i) - small.Radius())
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool IsInside(const Ball<T, Size>& small, const OrientedBox<T, Size>& large) noexcept
	{
		const Vector<T, Size> delta = small.Center() - large.Center();
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (const T distance = Dot(delta, large.Axis(i)); Abs(distance) > large.Extent(i) - small.Radius())
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr bool IsInside(const Box<T, Size>& small, const Box<T, Size>& large) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (Abs(small.Center()[i] - large.Center()[i]) > large.Extent(i) - small.Extent(i))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool IsInside(const Box<T, Size>& small, const Ball<T, Size>& large) noexcept
	{
		Vector<T, Size> furthestPoint;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			furthestPoint[i] = small.Center()[i] < large.Center()[i] ? small.Min(i) : small.Max(i);
		}

		return large.Contains(furthestPoint);
	}

	template<std::floating_point T, std::size_t Size>
	bool IsInside(const Box<T, Size>& small, const OrientedBox<T, Size>& large) noexcept
	{
		const Matrix<T, Size, Size> transpose = large.Axes().Transpose();
		const Vector<T, Size> center = transpose * (small.Center() - large.Center());

		return IsInside(OrientedBox<T, Size>(center, small.Extents(), transpose), Box<T, Size>(large.Extents()));
	}

	template<std::floating_point T, std::size_t Size>
	bool IsInside(const OrientedBox<T, Size>& small, const OrientedBox<T, Size>& large) noexcept
	{
		const Vector<T, Size> center = TransformTranspose(large.Axes(), small.Center() - large.Center());
		const Matrix<T, Size, Size> axes = MultiplyTranspose(large.Axes(), small.Axes());

		return IsInside(OrientedBox<T, Size>(center, small.Extents(), axes), Box<T, Size>(large.Extents()));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool IsInside(const OrientedBox<T, Size>& small, const Ball<T, Size>& large) noexcept
	{
		const Vector<T, Size> center = TransformTranspose(small.Axes(), large.Center() - small.Center());
		return IsInside(Box<T, Size>(small.Extents()), Ball<T, Size>(center, large.Radius()));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool IsInside(const OrientedBox<T, Size>& small, const Box<T, Size>& large) noexcept
	{
		return IsInside(AxisAlignedBoundingBox(small), large);
	}
}
