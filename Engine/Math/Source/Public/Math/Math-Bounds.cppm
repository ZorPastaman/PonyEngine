/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Bounds;

import std;

import PonyEngine.Type;

import :Ball;
import :Box;
import :Common;
import :Matrix;
import :OrientedBox;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Creates a bounding ball.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param points Points to bound.
	/// @return Bounding ball.
	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(std::span<const Vector<T, Size>> points) noexcept requires (Size >= 1);
	/// @brief Converts the axis-aligned bounding box to a bounding ball.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Axis-aligned bounding box.
	/// @return Bounding ball.
	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const Box<T, Size>& box) noexcept requires (Size >= 1);
	/// @brief Converts the oriented bounding box to a bounding ball.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Oriented bounding box.
	/// @return Bounding ball.
	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const OrientedBox<T, Size>& box) noexcept requires (Size >= 1);

	/// @brief Creates an axis-aligned bounding box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param points Points to bound.
	/// @return Axis-aligned bounding box.
	template<Type::Arithmetic T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(std::span<const Vector<T, Size>> points) noexcept requires (Size >= 1);
	/// @brief Converts the bounding ball to an axis-aligned bounding box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param ball Bounding ball.
	/// @return Axis-aligned bounding box.
	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(const Ball<T, Size>& ball) noexcept requires (Size >= 1);
	/// @brief Converts the oriented bounding box to an axis-aligned bounding box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Oriented bounding box.
	/// @return Axis-aligned bounding box.
	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(const OrientedBox<T, Size>& box) noexcept requires (Size >= 1);

	/// @brief Converts the bounding ball to an oriented bounding box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param ball Bounding ball.
	/// @return Oriented bounding box.
	template<std::floating_point T, std::size_t Size>
	constexpr OrientedBox<T, Size> OrientedBoundingBox(const Ball<T, Size>& ball) noexcept requires (Size >= 1);
	/// @brief Converts the axis-aligned bounding box to an oriented bounding box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Axis-aligned bounding box.
	/// @return Oriented bounding box.
	template<std::floating_point T, std::size_t Size>
	constexpr OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box) noexcept requires (Size >= 1);
	/// @brief Converts the axis-aligned bounding box to an oriented bounding box with the transformation.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Axis-aligned bounding box.
	/// @param rs Rotation-scaling matrix.
	/// @return Oriented bounding box.
	template<std::floating_point T, std::size_t Size>
	OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box, const Matrix<T, Size, Size>& rs) noexcept requires (Size >= 1);
	/// @brief Converts the axis-aligned bounding box to an oriented bounding box with the transformation.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Axis-aligned bounding box.
	/// @param trs Translation-rotation-scaling matrix.
	/// @return Oriented bounding box.
	template<std::floating_point T, std::size_t Size>
	OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box, const Matrix<T, Size, Size + 1>& trs) noexcept requires (Size >= 1);
	/// @brief Converts the axis-aligned bounding box to an oriented bounding box with the transformation.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Axis-aligned bounding box.
	/// @param trs Translation-rotation-scaling matrix. Must be pure trs matrix.
	/// @return Oriented bounding box.
	template<std::floating_point T, std::size_t Size>
	OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box, const Matrix<T, Size + 1, Size + 1>& trs) noexcept requires (Size >= 1);
}

namespace PonyEngine::Math
{
	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const std::span<const Vector<T, Size>> points) noexcept requires (Size >= 1)
	{
		if (points.size() == 0uz) [[unlikely]]
		{
			return Ball<T, Size>();
		}
		if (points.size() == 1uz) [[unlikely]]
		{
			return Ball(points[0], T{0});
		}

		auto bestPair = std::pair<const Vector<T, Size>*, const Vector<T, Size>*>(&points[0], &points[1]);
		T distance = (points[0] - points[1]).MagnitudeSquared();
		for (std::size_t i = 0uz; i < points.size(); ++i)
		{
			for (std::size_t j = i + 1uz; j < points.size(); ++j)
			{
				if (const T dist = (points[i] - points[j]).MagnitudeSquared(); dist > distance)
				{
					bestPair.first = &points[i];
					bestPair.second = &points[j];
					distance = dist;
				}
			}
		}

		const Vector<T, Size> center = Lerp(*bestPair.first, *bestPair.second, T{0.5});
		T radius = T{0};
		for (const Vector<T, Size>& point : points)
		{
			radius = std::max(radius, (point - center).MagnitudeSquared());
		}

		return Ball(center, std::nextafter(std::sqrt(radius), std::numeric_limits<T>::max()));
	}

	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const Box<T, Size>& box) noexcept requires (Size >= 1)
	{
		return Ball<T, Size>(box.Center(), std::nextafter(box.Extents().Magnitude(), std::numeric_limits<T>::max()));
	}

	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const OrientedBox<T, Size>& box) noexcept requires (Size >= 1)
	{
		return Ball<T, Size>(box.Center(), std::nextafter(box.Extents().Magnitude(), std::numeric_limits<T>::max()));
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(const std::span<const Vector<T, Size>> points) noexcept requires (Size >= 1)
	{
		if (points.size() == 0uz) [[unlikely]]
		{
			return Box<T, Size>();
		}

		Vector<T, Size> min = points[0];
		Vector<T, Size> max = points[0];
		for (std::size_t i = 1uz; i < points.size(); ++i)
		{
			min = Min(min, points[i]);
			max = Max(max, points[i]);
		}

		using TimeType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
		const Vector<T, Size> center = Lerp(min, max, TimeType{0.5});
		Vector<T, Size> extents;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			extents[i] = std::max(max[i] - center[i], center[i] - min[i]);
		}

		return Box(center, extents);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(const Ball<T, Size>& ball) noexcept requires (Size >= 1)
	{
		return Box<T, Size>(ball.Center(), Vector<T, Size>(ball.Radius()));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(const OrientedBox<T, Size>& box) noexcept requires (Size >= 1)
	{
		return Box<T, Size>(box.Center(), Abs(box.Axes()) * box.Extents());
	}

	template<std::floating_point T, std::size_t Size>
	constexpr OrientedBox<T, Size> OrientedBoundingBox(const Ball<T, Size>& ball) noexcept requires (Size >= 1)
	{
		return OrientedBox<T, Size>(ball.Center(), Vector<T, Size>(ball.Radius()));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box) noexcept requires (Size >= 1)
	{
		return OrientedBox<T, Size>(box.Center(), box.Extents());
	}

	template<std::floating_point T, std::size_t Size>
	OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box, const Matrix<T, Size, Size>& rs) noexcept requires (Size >= 1)
	{
		return OrientedBox<T, Size>(rs * box.Center(), box.Extents(), rs);
	}

	template<std::floating_point T, std::size_t Size>
	OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box, const Matrix<T, Size, Size + 1>& trs) noexcept requires (Size >= 1)
	{
		return OrientedBox<T, Size>(TransformPoint(trs, box.Center()), box.Extents(), ExtractRsMatrixFromTrs(trs));
	}

	template<std::floating_point T, std::size_t Size>
	OrientedBox<T, Size> OrientedBoundingBox(const Box<T, Size>& box, const Matrix<T, Size + 1, Size + 1>& trs) noexcept requires (Size >= 1)
	{
		return OrientedBox<T, Size>(TransformPoint(trs, box.Center()), box.Extents(), ExtractRsMatrixFromTrs(trs));
	}
}
