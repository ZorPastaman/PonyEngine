/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Intersections;

import std;

import :Ball;
import :Box;
import :Common;
import :Flat;
import :Matrix;
import :OrientedBox;
import :Ray;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Ray bounds for intersection tests.
	/// @tparam T Value type.
	template<std::floating_point T>
	struct RayBounds final
	{
		T min = Tolerance<T>().relative; /// Minimum bound.
		T max = std::numeric_limits<T>::infinity(); ///< Maximum bound.
	};
	/// @brief Ray intersection mode.
	enum class RayIntersectionMode : std::uint8_t
	{
		Enter, ///< Check only for entering intersection.
		Exit, ///< Check only for exiting intersection.
		Any, ///< Check for any intersection.
		Both ///< Check for both entering and exiting intersections.
	};

	/// @brief Computes an intersection time of two rays.
	/// @tparam T Value type.
	/// @param lhs Left ray.
	/// @param rhs Right ray.
	/// @param lhsBounds Left ray bounds.
	/// @param rhsBounds Right ray bounds.
	/// @return Intersection time or nullopt if there is no intersection. The time is relative to the @p lhs ray.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds = RayBounds<T>(), const RayBounds<T>& rhsBounds = RayBounds<T>()) noexcept;
	/// @brief Computes an intersection time of the @p ray with the @p flat.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes intersection times of the @p ray with the @p ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes an intersection time of the @p ray with the @p ball.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes intersection times of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes an intersection time of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes intersection times of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes an intersection time of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);

	/// @brief Computes an intersection point of two rays.
	/// @tparam T Value type.
	/// @param lhs Left ray.
	/// @param rhs Right ray.
	/// @param lhsBounds Left ray bounds.
	/// @param rhsBounds Right ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::optional<Vector2<T>> IntersectionPoint(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds = RayBounds<T>(), const RayBounds<T>& rhsBounds = RayBounds<T>()) noexcept;
	/// @brief Computes an intersection point of the @p ray with the @p flat.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes intersection points of the @p ray with the @p ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes an intersection point of the @p ray with the @p ball.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes intersection points of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes an intersection point of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes intersection points of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Computes an intersection point of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);

	/// @brief Checks if the two rays are intersecting.
	/// @tparam T Value type.
	/// @param lhs Left ray.
	/// @param rhs Right ray.
	/// @param lhsBounds Left ray bounds.
	/// @param rhsBounds Right ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds = RayBounds<T>(), const RayBounds<T>& rhsBounds = RayBounds<T>()) noexcept;
	/// @brief Checks if the ray and the flat are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Checks if the ray and the ball are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Checks if the ray and the box are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
	/// @brief Checks if the ray and the box are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>()) noexcept requires (Size >= 2);
}

namespace PonyEngine::Math
{
	/// @brief Gets an intersection time if it is within the given bounds.
	/// @tparam T Value type.
	/// @param time Time.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if it is out of bounds.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::optional<T> GetIntersectionTimeInBounds(T time, const RayBounds<T>& rayBounds) noexcept;
	/// @brief Gets a pair of intersection times if they are within the given bounds.
	/// @tparam T Value type.
	/// @param enterTime Enter time.
	/// @param exitTime Exit time.
	/// @param rayBounds Ray bounds.
	/// @return Intersection times or nullopt if they are out of bounds.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> GetIntersectionTimesInBounds(T enterTime, T exitTime, const RayBounds<T>& rayBounds) noexcept;
	/// @brief Chooses a correct intersection time from the given pair.
	/// @tparam Exit Should it return the exit time or the enter time?
	/// @tparam T Value type.
	/// @param times Intersection times.
	/// @return Intersection time.
	template<bool Exit, std::floating_point T> [[nodiscard("Pure function")]]
	std::optional<T> ChooseIntersectionTime(const std::pair<std::optional<T>, std::optional<T>>& times) noexcept;
	/// @brief Finds an intersection point by thr ray and the intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param time Intersection time.
	/// @return Point or nullopt if the time is nullopt.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> FindIntersectionPoint(const Ray<T, Size>& ray, const std::optional<T>& time) noexcept;
	/// @brief Finds an intersection points by the ray and the intersection times.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param times Intersection times.
	/// @return Points or nullopt if the time is nullopt.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> FindIntersectionPoints(const Ray<T, Size>& ray, const std::pair<std::optional<T>, std::optional<T>>& times) noexcept;
	/// @brief Checks if an intersection exists by the mode and the intersection times.
	/// @tparam Mode Intersection mode.
	/// @tparam T Value type.
	/// @param times Intersection times.
	/// @return @a True if the intersection exists; @a false otherwise.
	template<RayIntersectionMode Mode, std::floating_point T> [[nodiscard("Pure function")]]
	bool IsIntersecting(const std::pair<std::optional<T>, std::optional<T>>& times) noexcept;

	template<std::floating_point T>
	std::optional<T> IntersectionTime(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds, const RayBounds<T>& rhsBounds) noexcept
	{
		const T det = CrossZ(rhs.Direction(), lhs.Direction());
		if (AreAlmostEqual(det, T{0})) [[unlikely]]
		{
			return std::nullopt;
		}

		const Vector2<T> leftToRight = rhs.Origin() - lhs.Origin();
		const T u = CrossZ(rhs.Direction(), leftToRight);
		const T v = CrossZ(lhs.Direction(), leftToRight);
		const T invDet = T{1} / det;
		const T tl = u * invDet;
		const T tr = v * invDet;

		return tl < lhsBounds.min || tl > lhsBounds.max || tr < rhsBounds.min || tr > rhsBounds.max
			? std::nullopt
			: tl;
	}

	template<std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		const T denom = Dot(ray.Direction(), flat.Normal());
		if (AreAlmostEqual(denom, T{0})) [[unlikely]]
		{
			return std::nullopt;
		}

		const T time = -flat.Distance(ray.Origin()) / denom;
		return GetIntersectionTimeInBounds(time, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		const Vector<T, Size> l = ray.Origin() - ball.Center();
		const T b = Dot(ray.Direction(), l);
		const T c = l.MagnitudeSquared() - ball.Radius() * ball.Radius();
		const T disc = b * b - c;
		if (disc < T{0})
		{
			return std::pair<std::optional<T>, std::optional<T>>(std::nullopt, std::nullopt);
		}

		const T discSqrt = std::sqrt(disc);
		const T enterTime = -b - discSqrt;
		const T exitTime = -b + discSqrt;

		return GetIntersectionTimesInBounds(enterTime, exitTime, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return ChooseIntersectionTime<Exit>(IntersectionTimes(ray, ball, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		T enterTime = -std::numeric_limits<T>::infinity();
		T exitTime = std::numeric_limits<T>::infinity();

		for (std::size_t i = 0; i < Size; ++i)
		{
			const T min = box.Min(i) - ray.Origin()[i];
			const T max = box.Max(i) - ray.Origin()[i];
			const T direction = ray.Direction()[i];
			if (AreAlmostEqual(direction, T{0})) [[unlikely]]
			{
				if (min > T{0} || max < T{0})
				{
					return std::pair<std::optional<T>, std::optional<T>>(std::nullopt, std::nullopt);
				}

				continue;
			}

			const T invDirection = T{1} / direction;
			const T invMin = min * invDirection;
			const T invMax = max * invDirection;
			const T t0 = std::min(invMin, invMax);
			const T t1 = std::max(invMin, invMax);

			enterTime = std::max(enterTime, t0);
			exitTime = std::min(exitTime, t1);
		}

		return enterTime <= exitTime
			? GetIntersectionTimesInBounds(enterTime, exitTime, rayBounds)
			: std::pair<std::optional<T>, std::optional<T>>(std::nullopt, std::nullopt);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return ChooseIntersectionTime<Exit>(IntersectionTimes(ray, box, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		const Vector<T, Size> rayOrigin = TransformInverse(box.Axes(), ray.Origin() - box.Center());
		const Vector<T, Size> rayDirection = TransformInverse(box.Axes(), ray.Direction());
		const auto newRay = Ray<T, Size>(rayOrigin, rayDirection);
		const auto newBox = Box<T, Size>(box.Extents());

		return IntersectionTimes(newRay, newBox, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return ChooseIntersectionTime<Exit>(IntersectionTimes(ray, box, rayBounds));
	}

	template<std::floating_point T>
	std::optional<Vector2<T>> IntersectionPoint(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds, const RayBounds<T>& rhsBounds) noexcept
	{
		return FindIntersectionPoint(lhs, IntersectionTime(lhs, rhs, lhsBounds, rhsBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return FindIntersectionPoint(ray,IntersectionTime(ray, flat, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return FindIntersectionPoints(ray, IntersectionTimes(ray, ball, rayBounds));
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return FindIntersectionPoint(ray, IntersectionTime<Exit>(ray, ball, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return FindIntersectionPoints(ray, IntersectionTimes(ray, box, rayBounds));
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return FindIntersectionPoint(ray, IntersectionTime<Exit>(ray, box, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return FindIntersectionPoints(ray, IntersectionTimes(ray, box, rayBounds));
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return FindIntersectionPoint(ray, IntersectionTime<Exit>(ray, box, rayBounds));
	}

	template<std::floating_point T>
	bool AreIntersecting(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds, const RayBounds<T>& rhsBounds) noexcept
	{
		return IntersectionTime(lhs, rhs, lhsBounds, rhsBounds).has_value();
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return IntersectionTime(ray, flat, rayBounds).has_value();
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return IsIntersecting<Mode>(IntersectionTimes(ray, ball, rayBounds));
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return IsIntersecting<Mode>(IntersectionTimes(ray, box, rayBounds));
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 2)
	{
		return IsIntersecting<Mode>(IntersectionTimes(ray, box, rayBounds));
	}

	template<std::floating_point T>
	std::optional<T> GetIntersectionTimeInBounds(const T time, const RayBounds<T>& rayBounds) noexcept
	{
		return time < rayBounds.min || time > rayBounds.max ? std::nullopt : time;
	}

	template<std::floating_point T>
	std::pair<std::optional<T>, std::optional<T>> GetIntersectionTimesInBounds(const T enterTime, const T exitTime, const RayBounds<T>& rayBounds) noexcept
	{
		return std::pair<std::optional<T>, std::optional<T>>(GetIntersectionTimeInBounds(enterTime, rayBounds), GetIntersectionTimeInBounds(exitTime, rayBounds));
	}

	template<bool Exit, std::floating_point T>
	std::optional<T> ChooseIntersectionTime(const std::pair<std::optional<T>, std::optional<T>>& times) noexcept
	{
		if constexpr (Exit)
		{
			return times.second;
		}
		else
		{
			return times.first;
		}
	}

	template<std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> FindIntersectionPoint(const Ray<T, Size>& ray, const std::optional<T>& time) noexcept
	{
		return time ? ray.Unnormalize(time.value()) : std::nullopt;
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> FindIntersectionPoints(const Ray<T, Size>& ray, const std::pair<std::optional<T>, std::optional<T>>& times) noexcept
	{
		return std::pair(FindIntersectionPoint(ray, times.first), FindIntersectionPoint(ray, times.second));
	}

	template<RayIntersectionMode Mode, std::floating_point T>
	bool IsIntersecting(const std::pair<std::optional<T>, std::optional<T>>& times) noexcept
	{
		if constexpr (Mode == RayIntersectionMode::Enter)
		{
			return times.first.has_value();
		}
		else if constexpr (Mode == RayIntersectionMode::Exit)
		{
			return times.second.has_value();
		}
		else if constexpr (Mode == RayIntersectionMode::Any)
		{
			return times.first.has_value() || times.second.has_value();
		}
		else
		{
			return times.first.has_value() && times.second.has_value();
		}
	}
}
