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
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Converts the bounding box to a bounding ball.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param box Bounding box.
	/// @return Bounding ball.
	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const Box<T, Size>& box) noexcept requires (Size >= 1);

	/// @brief Converts the bounding ball to a bounding box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param ball Bounding ball.
	/// @return Bounding box.
	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> BoundingBox(const Ball<T, Size>& ball) noexcept requires (Size >= 1);
}

namespace PonyEngine::Math
{
	template<std::floating_point T, std::size_t Size>
	Ball<T, Size> BoundingBall(const Box<T, Size>& box) noexcept requires (Size >= 1)
	{
		return Ball<T, Size>(box.Center(), std::nextafter(box.Extents().Magnitude(), std::numeric_limits<T>::max()));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr Box<T, Size> BoundingBox(const Ball<T, Size>& ball) noexcept requires (Size >= 1)
	{
		return Box(ball.Center(), Vector<T, Size>(ball.Radius()));
	}
}
