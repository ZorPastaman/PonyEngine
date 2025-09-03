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

import PonyEngine.Type;

import :Ball;
import :Bounds;
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
	std::optional<T> IntersectionTime(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds = RayBounds<T>::Intersection(), const RayBounds<T>& rhsBounds = RayBounds<T>::Intersection()) noexcept;
	/// @brief Computes an intersection time of the @p ray with the @p flat.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes intersection times of the @p ray with the @p ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection time of the @p ray with the @p ball.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes intersection times of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection time of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes intersection times of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection time of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes an intersection time of the @p ray with the @p flat.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Flat<T, Size>& flat, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes intersection times of the @p ray with the @p ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection time of the @p ray with the @p ball.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes intersection times of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection time of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes intersection times of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection times or nullopt if there is no intersection. The order is enter time, exit time.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection time of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection time is returned; otherwise the enter intersection time.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection time or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<T> IntersectionTime(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes an intersection point of two rays.
	/// @tparam T Value type.
	/// @param lhs Left ray.
	/// @param rhs Right ray.
	/// @param lhsBounds Left ray bounds.
	/// @param rhsBounds Right ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::optional<Vector2<T>> IntersectionPoint(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds = RayBounds<T>::Intersection(), const RayBounds<T>& rhsBounds = RayBounds<T>::Intersection()) noexcept;
	/// @brief Computes an intersection point of the @p ray with the @p flat.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes intersection points of the @p ray with the @p ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection point of the @p ray with the @p ball.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes intersection points of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection point of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes intersection points of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection point of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes an intersection point of the two lines.
	/// @tparam T Value type.
	/// @param lhs Left line.
	/// @param rhs Right line.
	/// @return Intersection point or nullopt if there is no intersection.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::optional<Vector2<T>> IntersectionPoint(const Line<T>& lhs, const Line<T>& rhs) noexcept;
	/// @brief Computes an intersection point of the @p ray with the @p flat.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Flat<T, Size>& flat, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes intersection points of the @p ray with the @p ball.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection point of the @p ray with the @p ball.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes intersection points of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection point of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes intersection points of the @p ray with the @p box.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Pair of intersection points or nullopt if there is no intersection. The order is enter point, exit point.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Computes an intersection point of the @p ray with the @p box.
	/// @tparam Exit If @a true, the exit intersection point is returned; otherwise the enter intersection point.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return Intersection point or nullopt if there is no intersection.
	template<bool Exit = false, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::optional<Vector<T, Size>> IntersectionPoint(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Computes an intersection ray of the two planes.
	/// @tparam T Value type.
	/// @param lhs Left plane.
	/// @param rhs Right plane.
	/// @return Intersection ray or nullopt if there is no intersection.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	std::optional<Ray3D<T>> IntersectionRay(const Plane<T>& lhs, const Plane<T>& rhs) noexcept;

	/// @brief Checks if the two rays are intersecting.
	/// @tparam T Value type.
	/// @param lhs Left ray.
	/// @param rhs Right ray.
	/// @param lhsBounds Left ray bounds.
	/// @param rhsBounds Right ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds = RayBounds<T>::Intersection(), const RayBounds<T>& rhsBounds = RayBounds<T>::Intersection()) noexcept;
	/// @brief Checks if the ray and the flat are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Checks if the ray and the ball are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Checks if the ray and the box are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Checks if the ray and the box are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);

	/// @brief Checks if the two flats are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param lhs Left flat.
	/// @param rhs Right flat.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Flat<T, Size>& lhs, const Flat<T, Size>& rhs) noexcept requires (Size >= 1);
	/// @brief Checks if the ray and the flat are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param flat Flat.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Flat<T, Size>& flat, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the ball are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param flat Flat.
	/// @param ball Ball.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Flat<T, Size>& flat, const Ball<T, Size>& ball) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param flat Flat.
	/// @param box Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Flat<T, Size>& flat, const Box<T, Size>& box) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param flat Flat.
	/// @param box Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Flat<T, Size>& flat, const OrientedBox<T, Size>& box) noexcept requires (Size >= 1);

	/// @brief Checks if the two balls are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param lhs Left ball.
	/// @param rhs Right ball.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ball<T, Size>& lhs, const Ball<T, Size>& rhs) noexcept requires (Size >= 1);
	/// @brief Checks if the ray and the ball are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param ball Ball.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the ball are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param flat Flat.
	/// @param ball Ball.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ball<T, Size>& ball, const Flat<T, Size>& flat) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param box Flat.
	/// @param ball Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ball<T, Size>& ball, const Box<T, Size>& box) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param box Flat.
	/// @param ball Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ball<T, Size>& ball, const OrientedBox<T, Size>& box) noexcept requires (Size >= 1);

	/// @brief Checks if the two boxes are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param lhs Left box.
	/// @param rhs Right box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<Type::Arithmetic T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T, Size>& lhs, const Box<T, Size>& rhs) noexcept requires (Size >= 1);
	/// @brief Checks if the ray and the box are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param flat Flat.
	/// @param box Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Box<T, Size>& box, const Flat<T, Size>& flat) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param box Flat.
	/// @param ball Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T, Size>& box, const Ball<T, Size>& ball) noexcept requires (Size >= 1);
	/// @brief Checks if the two boxes are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param lhs Left box.
	/// @param rhs Right box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Box<T, Size>& lhs, const OrientedBox<T, Size>& rhs) noexcept requires (Size >= 1 && Size <= 3);

	/// @brief Checks if the two boxes are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param lhs Left box.
	/// @param rhs Right box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OrientedBox<T, Size>& lhs, const OrientedBox<T, Size>& rhs) noexcept requires (Size >= 1 && Size <= 3);
	/// @brief Checks if the ray and the box are intersecting.
	/// @tparam Mode Ray intersection mode.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param ray Ray.
	/// @param box Box.
	/// @param rayBounds Ray bounds.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<RayIntersectionMode Mode = RayIntersectionMode::Enter, std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds = RayBounds<T>::Intersection()) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param flat Flat.
	/// @param box Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OrientedBox<T, Size>& box, const Flat<T, Size>& flat) noexcept requires (Size >= 1);
	/// @brief Checks if the flat and the box are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param box Flat.
	/// @param ball Box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OrientedBox<T, Size>& box, const Ball<T, Size>& ball) noexcept requires (Size >= 1);
	/// @brief Checks if the two boxes are intersecting.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param lhs Left box.
	/// @param rhs Right box.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OrientedBox<T, Size>& lhs, const Box<T, Size>& rhs) noexcept requires (Size >= 1 && Size <= 3);
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

	/// @brief Checks if a vector component is almost zero.
	/// @tparam T Value type.
	/// @tparam Size Dimension.
	/// @param vector Vector.
	/// @return @a True if a component is almost zero; @a false otherwise. Component-wise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	std::array<bool, Size> IsAlmostZero(const Vector<T, Size>& vector) noexcept;

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
			? std::optional<T>(std::nullopt)
			: tl;
	}

	template<std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
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
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
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
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return ChooseIntersectionTime<Exit>(IntersectionTimes(ray, ball, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		const Vector<T, Size> min = box.Min() - ray.Origin();
		const Vector<T, Size> max = box.Max() - ray.Origin();
		const std::array<bool, Size> isZero = IsAlmostZero(ray.Direction());

		for (std::size_t i = 0; i < Size; ++i)
		{
			if (isZero[i] && (min[i] > T{0} || max[i] < T{0})) [[unlikely]]
			{
				return std::pair<std::optional<T>, std::optional<T>>(std::nullopt, std::nullopt);
			}
		}

		const Vector<T, Size> invDirection = T{1} / ray.Direction();
		const Vector<T, Size> invMin = Multiply(min, invDirection);
		const Vector<T, Size> invMax = Multiply(max, invDirection);
		const Vector<T, Size> enterTimes = Min(invMin, invMax);
		const Vector<T, Size> exitTimes = Max(invMin, invMax);

		T enterTime = -std::numeric_limits<T>::infinity();
		T exitTime = std::numeric_limits<T>::infinity();
		for (std::size_t i = 0; i < Size; ++i)
		{
			enterTime = isZero[i] ? enterTime : std::max(enterTime, enterTimes[i]);
			exitTime = isZero[i] ? exitTime : std::min(exitTime, exitTimes[i]);
		}

		return enterTime <= exitTime
			? GetIntersectionTimesInBounds(enterTime, exitTime, rayBounds)
			: std::pair<std::optional<T>, std::optional<T>>(std::nullopt, std::nullopt);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return ChooseIntersectionTime<Exit>(IntersectionTimes(ray, box, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		const Vector<T, Size> rayOrigin = TransformInverse(box.Axes(), ray.Origin() - box.Center());
		const Vector<T, Size> rayDirection = TransformInverse(box.Axes(), ray.Direction());
		const auto newRay = Ray<T, Size>(rayOrigin, rayDirection);
		const auto newBox = Box<T, Size>(box.Extents());

		return IntersectionTimes(newRay, newBox, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return ChooseIntersectionTime<Exit>(IntersectionTimes(ray, box, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Flat<T, Size>& flat, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTime(ray, flat, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTimes(ray, ball, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTime<Exit>(ray, ball, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTimes(ray, box, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTime<Exit>(ray, box, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<T>, std::optional<T>> IntersectionTimes(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTimes(ray, box, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<T> IntersectionTime(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTime<Exit>(ray, box, rayBounds);
	}

	template<std::floating_point T>
	std::optional<Vector2<T>> IntersectionPoint(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds, const RayBounds<T>& rhsBounds) noexcept
	{
		return FindIntersectionPoint(lhs, IntersectionTime(lhs, rhs, lhsBounds, rhsBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return FindIntersectionPoint(ray,IntersectionTime(ray, flat, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return FindIntersectionPoints(ray, IntersectionTimes(ray, ball, rayBounds));
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return FindIntersectionPoint(ray, IntersectionTime<Exit>(ray, ball, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return FindIntersectionPoints(ray, IntersectionTimes(ray, box, rayBounds));
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return FindIntersectionPoint(ray, IntersectionTime<Exit>(ray, box, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return FindIntersectionPoints(ray, IntersectionTimes(ray, box, rayBounds));
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return FindIntersectionPoint(ray, IntersectionTime<Exit>(ray, box, rayBounds));
	}

	template<std::floating_point T>
	std::optional<Vector2<T>> IntersectionPoint(const Line<T>& lhs, const Line<T>& rhs) noexcept
	{
		const T det = CrossZ(lhs.Normal(), rhs.Normal());
		if (AreAlmostEqual(det, T{0})) [[unlikely]]
		{
			return std::nullopt;
		}

		const T invDet = T{1} / det;

		Vector2<T> point;
		point.X() = (rhs.Distance() * lhs.Normal().Y() - lhs.Distance() * rhs.Normal().Y()) * invDet;
		point.Y() = (lhs.Distance() * rhs.Normal().X() - rhs.Distance() * lhs.Normal().X()) * invDet;

		return point;
	}

	template<std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Flat<T, Size>& flat, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionPoint(ray, flat, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionPoints(ray, ball, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionPoint<Exit>(ray, ball, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionPoints(ray, box, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionPoint<Exit>(ray, box, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	std::pair<std::optional<Vector<T, Size>>, std::optional<Vector<T, Size>>> IntersectionPoints(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionPoints(ray, box, rayBounds);
	}

	template<bool Exit, std::floating_point T, std::size_t Size>
	std::optional<Vector<T, Size>> IntersectionPoint(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionPoint<Exit>(ray, box, rayBounds);
	}

	template<std::floating_point T>
	std::optional<Ray3D<T>> IntersectionRay(const Plane<T>& lhs, const Plane<T>& rhs) noexcept
	{
		const Vector3<T> direction = Cross(lhs.Normal(), rhs.Normal());
		if (direction.IsAlmostZero()) [[unlikely]]
		{
			return std::nullopt;
		}

		const Vector3<T> origin = Cross(lhs.Normal() * rhs.Distance() - rhs.Normal() * lhs.Distance(), direction) * (T{1} / direction.MagnitudeSquared());
		return Ray3D<T>(origin, direction);
	}

	template<std::floating_point T>
	bool AreIntersecting(const Ray2D<T>& lhs, const Ray2D<T>& rhs, const RayBounds<T>& lhsBounds, const RayBounds<T>& rhsBounds) noexcept
	{
		return IntersectionTime(lhs, rhs, lhsBounds, rhsBounds).has_value();
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const Flat<T, Size>& flat, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IntersectionTime(ray, flat, rayBounds).has_value();
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const Ball<T, Size>& ball, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IsIntersecting<Mode>(IntersectionTimes(ray, ball, rayBounds));
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const Box<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IsIntersecting<Mode>(IntersectionTimes(ray, box, rayBounds));
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ray<T, Size>& ray, const OrientedBox<T, Size>& box, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return IsIntersecting<Mode>(IntersectionTimes(ray, box, rayBounds));
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Flat<T, Size>& lhs, const Flat<T, Size>& rhs) noexcept requires (Size >= 1)
	{
		if constexpr (Size == 1)
		{
			return false;
		}
		else if constexpr (Size == 2)
		{
			return !AreAlmostEqual(CrossZ(lhs.Normal(), rhs.Normal()), T{0});
		}
		else if constexpr (Size == 3)
		{
			return !Cross(lhs.Normal(), rhs.Normal()).IsAlmostZero();
		}
		else
		{
			return !AreAlmostEqual(std::min(std::abs(Dot(lhs.Normal(), rhs.Normal())), T{1}), T{1});
		}
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Flat<T, Size>& flat, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return AreIntersecting(ray, flat, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Flat<T, Size>& flat, const Ball<T, Size>& ball) noexcept requires (Size >= 1)
	{
		return std::abs(flat.Distance(ball.Center())) <= ball.Radius();
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Flat<T, Size>& flat, const Box<T, Size>& box) noexcept requires (Size >= 1)
	{
		return std::abs(flat.Distance(box.Center())) <= Dot(box.Extents(), Abs(flat.Normal()));
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Flat<T, Size>& flat, const OrientedBox<T, Size>& box) noexcept requires (Size >= 1)
	{
		return std::abs(flat.Distance(box.Center())) <= Dot(box.Extents(), Abs(TransformInverse(box.Axes(), flat.Normal())));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const Ball<T, Size>& lhs, const Ball<T, Size>& rhs) noexcept requires (Size >= 1)
	{
		const T radius = lhs.Radius() + rhs.Radius();
		return DistanceSquared(lhs.Center(), rhs.Center()) <= radius * radius;
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ball<T, Size>& ball, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return AreIntersecting<Mode>(ray, ball, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Ball<T, Size>& ball, const Flat<T, Size>& flat) noexcept requires (Size >= 1)
	{
		return AreIntersecting(flat, ball);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const Ball<T, Size>& ball, const Box<T, Size>& box) noexcept requires (Size >= 1)
	{
		return DistanceSquared(box.ClosestPoint(ball.Center()), ball.Center()) <= ball.Radius() * ball.Radius();
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const Ball<T, Size>& ball, const OrientedBox<T, Size>& box) noexcept requires (Size >= 1)
	{
		const Vector<T, Size> delta = TransformInverse(box.Axes(), ball.Center() - box.Center());
		const Vector<T, Size> point = Clamp(delta, -box.Extents(), box.Extents());
		return (delta - point).MagnitudeSquared() <= ball.Radius() * ball.Radius();
	}

	template<Type::Arithmetic T, std::size_t Size>
	constexpr bool AreIntersecting(const Box<T, Size>& lhs, const Box<T, Size>& rhs) noexcept requires (Size >= 1)
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (Abs(lhs.Center()[i] - rhs.Center()[i]) > lhs.Extent(i) + rhs.Extent(i))
			{
				return false;
			}
		}

		return true;
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Box<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return AreIntersecting<Mode>(ray, box, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const Box<T, Size>& box, const Flat<T, Size>& flat) noexcept requires (Size >= 1)
	{
		return AreIntersecting(flat, box);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const Box<T, Size>& box, const Ball<T, Size>& ball) noexcept requires (Size >= 1)
	{
		return AreIntersecting(ball, box);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const Box<T, Size>& lhs, const OrientedBox<T, Size>& rhs) noexcept requires (Size >= 1 && Size <= 3)
	{
		const Vector<T, Size> delta = rhs.Center() - lhs.Center();
		const Matrix<T, Size, Size> absAxes = Abs(rhs.Axes());

		const Vector<T, Size> rightProjections = absAxes * rhs.Extents();
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (Abs(delta[i]) > lhs.Extent(i) + rightProjections[i])
			{
				return false;
			}
		}

		for (std::size_t i = 0uz; i < Size; ++i)
		{
			const T leftProjection = Dot(absAxes.Column(i), lhs.Extents());
			const T projection = Dot(rhs.Axis(i), delta);

			if (Abs(projection) > leftProjection + rhs.Extent(i))
			{
				return false;
			}
		}

		if constexpr (Size == 3)
		{
			for (std::size_t i = 0uz; i < Size; ++i)
			{
				for (std::size_t j = 0uz; j < Size; ++j)
				{
					const T leftProjection = lhs.Extent((i + 1) % 3) * absAxes[(i + 2) % 3, j] + lhs.Extent((i + 2) % 3) * absAxes[(i + 1) % 3, j];
					const T rightProjection = rhs.Extent((j + 1) % 3) * absAxes[i, (j + 2) % 3] + rhs.Extent((j + 2) % 3) * absAxes[i, (j + 1) % 3];
					const T projection = delta[(i + 2) % 3] * rhs.Axes()[(i + 1) % 3, j] - delta[(i + 1) % 3] * rhs.Axes()[(i + 2) % 3, j];

					if (Abs(projection) > leftProjection + rightProjection)
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const OrientedBox<T, Size>& lhs, const OrientedBox<T, Size>& rhs) noexcept requires (Size >= 1 && Size <= 3)
	{
		const Matrix<T, Size, Size> rotation = MultiplyTranspose(lhs.Axes(), rhs.Axes());
		const Matrix<T, Size, Size> rotationAbs = Abs(rotation);
		const Vector<T, Size> delta = rhs.Center() - lhs.Center();
		const Vector<T, Size> rotatedDelta = TransformInverse(lhs.Axes(), delta);

		const Vector<T, Size> rightProjections = rotationAbs * rhs.Extents();
		for (std::size_t i = 0; i < Size; ++i)
		{
			if (Abs(rotatedDelta[i]) > lhs.Extent(i) + rightProjections[i])
			{
				return false;
			}
		}

		for (std::size_t i = 0; i < Size; ++i)
		{
			const T leftProjection = Dot(lhs.Extents(), rotationAbs.Column(i));
			const T projection = Dot(rotation.Column(i), rotatedDelta);

			if (Abs(projection) > leftProjection + rhs.Extent(i))
			{
				return false;
			}
		}

		if constexpr (Size == 3)
		{
			for (std::size_t i = 0; i < Size; ++i)
			{
				for (std::size_t j = 0; j < Size; ++j)
				{
					const T leftProjection = lhs.Extent((i + 1) % 3) * rotationAbs[(i + 2) % 3, j] + lhs.Extent((i + 2) % 3) * rotationAbs[(i + 1) % 3, j];
					const T rightProjection = rhs.Extent((j + 1) % 3) * rotationAbs[i, (j + 2) % 3] + rhs.Extent((j + 2) % 3) * rotationAbs[i, (j + 1) % 3];
					const T projection = rotatedDelta[(i + 2) % 3] * rotation[(i + 1) % 3, j] - rotatedDelta[(i + 1) % 3] * rotation[(i + 2) % 3, j];

					if (Abs(projection) > leftProjection + rightProjection)
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	template<RayIntersectionMode Mode, std::floating_point T, std::size_t Size>
	bool AreIntersecting(const OrientedBox<T, Size>& box, const Ray<T, Size>& ray, const RayBounds<T>& rayBounds) noexcept requires (Size >= 1)
	{
		return AreIntersecting<Mode>(ray, box, rayBounds);
	}

	template<std::floating_point T, std::size_t Size>
	bool AreIntersecting(const OrientedBox<T, Size>& box, const Flat<T, Size>& flat) noexcept requires (Size >= 1)
	{
		return AreIntersecting(flat, box);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const OrientedBox<T, Size>& box, const Ball<T, Size>& ball) noexcept requires (Size >= 1)
	{
		return AreIntersecting(ball, box);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreIntersecting(const OrientedBox<T, Size>& lhs, const Box<T, Size>& rhs) noexcept requires (Size >= 1 && Size <= 3)
	{
		return AreIntersecting(rhs, lhs);
	}

	template<std::floating_point T>
	std::optional<T> GetIntersectionTimeInBounds(const T time, const RayBounds<T>& rayBounds) noexcept
	{
		return time < rayBounds.min || time > rayBounds.max ? std::optional<T>(std::nullopt) : time;
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
		return time ? ray.Unnormalize(time.value()) : std::optional<Vector<T, Size>>(std::nullopt);
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

	template<std::floating_point T, std::size_t Size>
	std::array<bool, Size> IsAlmostZero(const Vector<T, Size>& vector) noexcept
	{
		std::array<bool, Size> answer;
		for (std::size_t i = 0; i < Size; ++i)
		{
			answer[i] = AreAlmostEqual(vector[i], T{0});
		}

		return answer;
	}
}
