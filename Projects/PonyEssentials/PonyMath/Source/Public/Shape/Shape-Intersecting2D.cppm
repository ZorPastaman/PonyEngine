/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Intersecting2D;

import <algorithm>;
import <array>;
import <cmath>;
import <concepts>;
import <cstddef>;
import <cstdint>;
import <limits>;
import <span>;

import PonyMath.Core;

import :AABR;
import :Circle;
import :Line;
import :OBR;
import :Ray2D;

export namespace PonyMath::Shape
{
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left ray.
	/// @param right Right ray.
	/// @param leftMaxDistance Left ray max distance.
	/// @param rightMaxDistance Right ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray2D<T>& left, const Ray2D<T>& right, T leftMaxDistance = std::numeric_limits<T>::infinity(), T rightMaxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param ray Ray.
	/// @param line Line.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray2D<T>& ray, const Line<T>& line, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param ray Ray.
	/// @param circle Circle.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray2D<T>& ray, const Circle<T>& circle, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param ray Ray.
	/// @param aabr Axis-aligned bounding rect.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray2D<T>& ray, const AABR<T>& aabr, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param ray Ray.
	/// @param obr Oriented bounding rect.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Ray2D<T>& ray, const OBR<T>& obr, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;

	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left line.
	/// @param right Right line.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Line<T>& left, const Line<T>& right) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param line Line.
	/// @param ray Ray.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Line<T>& line, const Ray2D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param line Line.
	/// @param circle Circle.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Line<T>& line, const Circle<T>& circle) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param line Line.
	/// @param aabr Axis-aligned bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Line<T>& line, const AABR<T>& aabr) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param line Line.
	/// @param obr Oriented bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Line<T>& line, const OBR<T>& obr) noexcept;

	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left circle.
	/// @param right Right circle.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Circle<T>& left, const Circle<T>& right) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param circle Circle.
	/// @param ray Ray.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Circle<T>& circle, const Ray2D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param circle Circle.
	/// @param line Line.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Circle<T>& circle, const Line<T>& line) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param circle Circle.
	/// @param aabr Axis-aligned bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Circle<T>& circle, const AABR<T>& aabr) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param circle Circle.
	/// @param obr Oriented bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Circle<T>& circle, const OBR<T>& obr) noexcept;

	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left axis-aligned bounding rect.
	/// @param right Right axis-aligned bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABR<T>& left, const AABR<T>& right) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param aabr Axis-aligned bounding rect.
	/// @param ray Ray.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABR<T>& aabr, const Ray2D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param aabr Axis-aligned bounding rect.
	/// @param line Line.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABR<T>& aabr, const Line<T>& line) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param aabr Axis-aligned bounding rect.
	/// @param circle Circle.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABR<T>& aabr, const Circle<T>& circle) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param aabr Axis-aligned bounding rect.
	/// @param obr Oriented bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const AABR<T>& aabr, const OBR<T>& obr) noexcept;

	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param left Left oriented bounding rect.
	/// @param right Right oriented bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBR<T>& left, const OBR<T>& right) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param obr Oriented bounding rect.
	/// @param ray Ray.
	/// @param maxDistance Ray max distance.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBR<T>& obr, const Ray2D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param obr Oriented bounding rect.
	/// @param line Line.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBR<T>& obr, const Line<T>& line) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param obr Oriented bounding rect.
	/// @param circle Circle.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBR<T>& obr, const Circle<T>& circle) noexcept;
	/// @brief Checks if two shapes are intersecting.
	/// @tparam T Component type.
	/// @param obr Oriented bounding rect.
	/// @param aabr Axis-aligned bounding rect.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const OBR<T>& obr, const AABR<T>& aabr) noexcept;
}

namespace PonyMath::Shape
{
	/// @brief Checks if the @p line intersects a shape described with the @p corners.
	/// @tparam T Component type.
	/// @param line Line.
	/// @param corners Shape corners.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreIntersecting(const Line<T>& line, std::span<const Core::Vector2<T>> corners) noexcept;

	/// @brief Checks if a rect intersects a convex shape described with the @p corners using separating axis theorem.
	/// @note It's one step of the theorem. The calling function must call other steps.
	/// @tparam T Component type.
	/// @tparam CornerCount Corner count.
	/// @param center Rect center.
	/// @param extents Rect extents.
	/// @param axes Rect axes.
	/// @param corners Convex shape corners.
	/// @return @a True if they are intersecting; @a false otherwise.
	template<std::floating_point T, std::size_t CornerCount> [[nodiscard("Pure function")]]
	bool CheckSat(const Core::Vector2<T>& center, const Core::Vector2<T>& extents, std::span<const Core::Vector2<T>, 2> axes, std::span<const Core::Vector2<T>, CornerCount> corners);

	template<std::floating_point T>
	bool AreIntersecting(const Ray2D<T>& left, const Ray2D<T>& right, const T leftMaxDistance, const T rightMaxDistance) noexcept
	{
		const Core::Vector2<T> leftToRight = right.Origin() - left.Origin();

		const T u = Core::CrossZ(right.Direction(), leftToRight);
		const T v = Core::CrossZ(left.Direction(), leftToRight);
		const T det = Core::CrossZ(right.Direction(), left.Direction());

		return std::signbit(u) == std::signbit(v) && std::signbit(u) == std::signbit(det) &&
			std::abs(u) > T{0} && std::abs(v) > T{0} && std::abs(det) > T{0.0001} &&
			std::abs(u) < leftMaxDistance && std::abs(v) < rightMaxDistance;
	}

	template<std::floating_point T>
	bool AreIntersecting(const Ray2D<T>& ray, const Line<T>& line, const T maxDistance) noexcept
	{
		const T distance = line.Distance(ray.Origin());
		const T dot = Core::Dot(line.Normal(), ray.Direction());

		return std::signbit(distance) != std::signbit(dot) && std::abs(distance) > T{0} && std::abs(dot) > T{0.0001} &&
			-distance / dot < maxDistance;
	}

	template <std::floating_point T>
	bool AreIntersecting(const Ray2D<T>& ray, const Circle<T>& circle, const T maxDistance) noexcept
	{
		const Core::Vector2<T> centerToRay = ray.Origin() - circle.Center();
		const T b = Core::Dot(ray.Direction(), centerToRay);
		const T c = centerToRay.MagnitudeSquared() - circle.Radius() * circle.Radius();
		const T dis = b * b - c;
		if (dis < T{0})
		{
			return false;
		}

		const T t = -b - std::sqrt(dis);

		return t > T{0} && t <= maxDistance;
	}

	template<std::floating_point T>
	bool AreIntersecting(const Ray2D<T>& ray, const AABR<T>& aabr, const T maxDistance) noexcept
	{
		T tMin = T{0};
		T tMax = maxDistance;

		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			const T min = aabr.Min(i) - ray.Origin()[i];
			const T max = aabr.Max(i) - ray.Origin()[i];
			const T direction = ray.Direction()[i];
			if (std::abs(direction) < T{0.0001}) [[unlikely]]
			{
				if (std::signbit(min) == std::signbit(max) && std::abs(min) > T{0} && std::abs(max) > T{0})
				{
					return false;
				}

				continue;
			}

			const T multiplier = T{1} / direction;
			const Core::Vector2<T> t = Core::Vector2<T>(min, max) * multiplier;
			const auto& [t0, t1] = t.MinMax();

			tMin = std::max(tMin, t0);
			tMax = std::min(tMax, t1);
		}

		return tMin > T{0} && tMin <= tMax;
	}

	template<std::floating_point T>
	bool AreIntersecting(const Ray2D<T>& ray, const OBR<T>& obr, const T maxDistance) noexcept
	{
		const auto inverseRotation = Core::Matrix2x2<T>(obr.Axes()).Transpose();
		const Core::Vector2<T> origin = inverseRotation * (ray.Origin() - obr.Center());
		const Core::Vector2<T> direction = inverseRotation * ray.Direction();
		const auto rotatedRay = Ray2D<T>(origin, direction);
		const auto aabr = AABR<T>(Core::Vector2<T>::Predefined::Zero, obr.Extents());

		return AreIntersecting(rotatedRay, aabr, maxDistance);
	}

	template<std::floating_point T>
	bool AreIntersecting(const Line<T>& left, const Line<T>& right) noexcept
	{
		return std::abs(Core::Dot(left.Normal(), right.Normal())) < T{0.9999};
	}

	template<std::floating_point T>
	bool AreIntersecting(const Line<T>& line, const Ray2D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, line, maxDistance);
	}

	template <std::floating_point T>
	bool AreIntersecting(const Line<T>& line, const Circle<T>& circle) noexcept
	{
		return circle.Contains(line.Project(circle.Center()));
	}

	template<std::floating_point T>
	bool AreIntersecting(const Line<T>& line, const AABR<T>& aabr) noexcept
	{
		const std::array<Core::Vector2<T>, AABR<T>::CornerCount> corners = aabr.Corners();

		return AreIntersecting(line, std::span<const Core::Vector2<T>>(corners.data(), corners.size()));
	}

	template<std::floating_point T>
	bool AreIntersecting(const Line<T>& line, const OBR<T>& obr) noexcept
	{
		const std::array<Core::Vector2<T>, OBR<T>::CornerCount> corners = obr.Corners();

		return AreIntersecting(line, std::span<const Core::Vector2<T>>(corners.data(), corners.size()));
	}

	template <std::floating_point T>
	bool AreIntersecting(const Circle<T>& left, const Circle<T>& right) noexcept
	{
		const T radiusSum = left.Radius() + right.Radius();

		return (left.Center() - right.Center()).MagnitudeSquared() <= radiusSum * radiusSum;
	}

	template <std::floating_point T>
	bool AreIntersecting(const Circle<T>& circle, const Ray2D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, circle, maxDistance);
	}

	template <std::floating_point T>
	bool AreIntersecting(const Circle<T>& circle, const Line<T>& line) noexcept
	{
		return AreIntersecting(line, circle);
	}

	template <std::floating_point T>
	bool AreIntersecting(const Circle<T>& circle, const AABR<T>& aabr) noexcept
	{
		return circle.Contains(aabr.ClosestPoint(circle.Center()));
	}

	template <std::floating_point T>
	bool AreIntersecting(const Circle<T>& circle, const OBR<T>& obr) noexcept
	{
		const auto inverseRotation = Core::Matrix2x2<T>(obr.Axes()).Transpose();
		const Core::Vector2<T> center = inverseRotation * (circle.Center() - obr.Center());
		const auto rotatedCircle = Circle<T>(center, circle.Radius());
		const auto aabr = AABR<T>(Core::Vector2<T>::Predefined::Zero, obr.Extents());

		return AreIntersecting(rotatedCircle, aabr);
	}

	template<Core::Arithmetic T>
	bool AreIntersecting(const AABR<T>& left, const AABR<T>& right) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			if (left.Min(i) > right.Max(i) || left.Max(i) < right.Min(i))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	bool AreIntersecting(const AABR<T>& aabr, const Ray2D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, aabr, maxDistance);
	}

	template<std::floating_point T>
	bool AreIntersecting(const AABR<T>& aabr, const Line<T>& line) noexcept
	{
		return AreIntersecting(line, aabr);
	}

	template <std::floating_point T>
	bool AreIntersecting(const AABR<T>& aabr, const Circle<T>& circle) noexcept
	{
		return AreIntersecting(circle, aabr);
	}

	template<std::floating_point T>
	bool AreIntersecting(const AABR<T>& aabr, const OBR<T>& obr) noexcept
	{
		return CheckSat<T, OBR<T>::CornerCount>(aabr.Center(), aabr.Extents(), AABR<T>::Axes, obr.Corners()) &&
			CheckSat<T, AABR<T>::CornerCount>(obr.Center(), obr.Extents(), obr.Axes(), aabr.Corners());
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBR<T>& left, const OBR<T>& right) noexcept
	{
		return CheckSat<T, OBR<T>::CornerCount>(left.Center(), left.Extents(), left.Axes(), right.Corners()) &&
			CheckSat<T, OBR<T>::CornerCount>(right.Center(), right.Extents(), right.Axes(), left.Corners());
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBR<T>& obr, const Ray2D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, obr, maxDistance);
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBR<T>& obr, const Line<T>& line) noexcept
	{
		return AreIntersecting(line, obr);
	}

	template <std::floating_point T>
	bool AreIntersecting(const OBR<T>& obr, const Circle<T>& circle) noexcept
	{
		return AreIntersecting(circle, obr);
	}

	template<std::floating_point T>
	bool AreIntersecting(const OBR<T>& obr, const AABR<T>& aabr) noexcept
	{
		return AreIntersecting(aabr, obr);
	}

	template<std::floating_point T>
	bool AreIntersecting(const Line<T>& line, std::span<const Core::Vector2<T>> corners) noexcept
	{
		for (std::size_t positives = 0, negatives = 0; const Core::Vector2<T>& corner : corners)
		{
			const std::int8_t side = line.Side(corner);
			positives += side > std::int8_t{0};
			negatives += side < std::int8_t{0};

			if (side == std::int8_t{0} || positives > 0 && negatives > 0)
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T, std::size_t CornerCount>
	bool CheckSat(const Core::Vector2<T>& center, const Core::Vector2<T>& extents, const std::span<const Core::Vector2<T>, 2> axes, const std::span<const Core::Vector2<T>, CornerCount> corners)
	{
		for (std::size_t axisIndex = 0; axisIndex < Core::Vector2<T>::ComponentCount; ++axisIndex)
		{
			const Core::Vector2<T>& normal = axes[axisIndex];
			const T extent = extents[axisIndex];

			std::array<T, CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = Core::Dot(normal, corners[cornerIndex] - center);
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		return true;
	}
}
