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

import :Ball;
import :Box;
import :Common;
import :Matrix;
import :OrientedBox;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
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
	Ball<T, Size> BoundingBall(const Box<T, Size>& box) noexcept requires (Size >= 1)
	{
		return Ball<T, Size>(box.Center(), std::nextafter(box.Extents().Magnitude(), std::numeric_limits<T>::max()));
	}

	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const OrientedBox<T, Size>& box) noexcept requires (Size >= 1)
	{
		return Ball<T, Size>(box.Center(), std::nextafter(box.Extents().Magnitude(), std::numeric_limits<T>::max()));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(const Ball<T, Size>& ball) noexcept requires (Size >= 1)
	{
		return Box<T, Size>(ball.Center(), Vector<T, Size>(ball.Radius()));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> AxisAlignedBoundingBox(const OrientedBox<T, Size>& box) noexcept requires (Size >= 1)
	{
		Vector<T, Size> extents = Vector<T, Size>::Zero();
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			extents += Abs(box.Axis(i)) * box.Extent(i);
		}

		return Box<T, Size>(box.Center(), extents);
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
