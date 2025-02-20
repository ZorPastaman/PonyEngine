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
import <span>;

import PonyMath.Core;

import :AABR;
import :Line;
import :OBR;
import :Ray2D;

export namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& left, const Ray2D<T>& right, T leftMaxDistance = std::numeric_limits<T>::infinity(), T rightMaxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Line<T>& line, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const AABR<T>& aabr, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const OBR<T>& obr, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line<T>& left, const Line<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line<T>& line, const Ray2D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line<T>& line, const AABR<T>& aabr) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line<T>& line, const OBR<T>& obr) noexcept;

	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABR<T>& left, const AABR<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABR<T>& aabr, const Ray2D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABR<T>& aabr, const Line<T>& line) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const AABR<T>& aabr, const OBR<T>& obr) noexcept;

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBR<T>& left, const OBR<T>& right) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBR<T>& obr, const Ray2D<T>& ray, T maxDistance = std::numeric_limits<T>::infinity()) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBR<T>& obr, const Line<T>& line) noexcept;
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const OBR<T>& obr, const AABR<T>& aabr) noexcept;
}

namespace PonyMath::Shape
{
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Line<T>& line, std::span<const Core::Vector2<T>> corners) noexcept;

	template<std::floating_point T, std::size_t CornerCount> [[nodiscard("Pure function")]]
	constexpr bool AreIntersecting(const Core::Vector2<T>& center, const Core::Vector2<T>& extents, std::span<const Core::Vector2<T>, 2> axes, std::span<const Core::Vector2<T>, CornerCount> corners);

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& left, const Ray2D<T>& right, const T leftMaxDistance, const T rightMaxDistance) noexcept
	{
		const Core::Vector2<T> leftToRight = right.Origin() - left.Origin();

		const T u = Core::CrossZ(right.Direction(), leftToRight);
		const T v = Core::CrossZ(left.Direction(), leftToRight);
		const T det = Core::CrossZ(right.Direction(), left.Direction());

		return std::signbit(u) == std::signbit(v) && std::signbit(u) == std::signbit(det) &&
			std::abs(u) > T{0.0001} && std::abs(v) > T{0.0001} && std::abs(det) > T{0.0001} &&
			std::abs(u) < leftMaxDistance && std::abs(v) < rightMaxDistance;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const Line<T>& line, const T maxDistance) noexcept
	{
		const T distance = line.Distance(ray.Origin());
		const T dot = Core::Dot(line.Normal(), ray.Direction());

		return std::signbit(distance) != std::signbit(dot) && std::abs(distance) > T{0.0001} && std::abs(dot) > T{0.0001} &&
			-distance / dot < maxDistance;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const AABR<T>& aabr, const T maxDistance) noexcept
	{
		T tMin = T{0};
		T tMax = maxDistance;

		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			const T min = aabr.Min(i) - ray.Origin()[i];
			const T max = aabr.Max(i) - ray.Origin()[i];
			const T direction = ray.Direction()[i];
			if (std::abs(direction) < T{0.0001})
			{
				if (min < T{0} && max < T{0} || min > T{0} && max > T{0})
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

		return tMin > T{0.0001} && tMin <= tMax;
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Ray2D<T>& ray, const OBR<T>& obr, const T maxDistance) noexcept
	{
		const Core::Matrix2x2<T> inverseRotation = Core::RotationMatrix(obr.AxisX(), obr.AxisY()).Inverse();
		const Core::Vector2<T> origin = inverseRotation * (ray.Origin() - obr.Center());
		const Core::Vector2<T> direction = inverseRotation * ray.Direction();
		const AABR<T> aabr = AABR<T>(Core::Vector2<T>::Predefined::Zero, obr.Extents());

		return AreIntersecting(Ray2D<T>(origin, direction), aabr, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line<T>& left, const Line<T>& right) noexcept
	{
		return std::abs(Core::Dot(left.Normal(), right.Normal())) < T{1};
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line<T>& line, const Ray2D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, line, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line<T>& line, const AABR<T>& aabr) noexcept
	{
		return AreIntersecting(line, aabr.Corners());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line<T>& line, const OBR<T>& obr) noexcept
	{
		return AreIntersecting(line, obr.Corners());
	}

	template<Core::Arithmetic T>
	constexpr bool AreIntersecting(const AABR<T>& left, const AABR<T>& right) noexcept
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
	constexpr bool AreIntersecting(const AABR<T>& aabr, const Ray2D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, aabr, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABR<T>& aabr, const Line<T>& line) noexcept
	{
		return AreIntersecting(line, aabr);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const AABR<T>& aabr, const OBR<T>& obr) noexcept
	{
		return AreIntersecting(aabr.Center(), aabr.Extents(), AABR<T>::Axes, obr.Corners()) &&
			AreIntersecting(obr.Center(), obr.Extents(), obr.Axes(), aabr.Corners());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBR<T>& left, const OBR<T>& right) noexcept
	{
		return AreIntersecting(left.Center(), left.Extents(), left.Axes(), right.Corners()) &&
			AreIntersecting(right.Center(), right.Extents(), right.Axes(), left.Corners());
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBR<T>& obr, const Ray2D<T>& ray, const T maxDistance) noexcept
	{
		return AreIntersecting(ray, obr, maxDistance);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBR<T>& obr, const Line<T>& line) noexcept
	{
		return AreIntersecting(line, obr);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const OBR<T>& obr, const AABR<T>& aabr) noexcept
	{
		return AreIntersecting(aabr, obr);
	}

	template<std::floating_point T>
	constexpr bool AreIntersecting(const Line<T>& line, std::span<const Core::Vector2<T>> corners) noexcept
	{
		for (std::size_t i = 0, positives = 0, negatives = 0; i < Rect<T>::CornerCount; ++i)
		{
			const std::int8_t side = line.Side(corners[i]);
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
	constexpr bool AreIntersecting(const Core::Vector2<T>& center, const Core::Vector2<T>& extents, const std::span<const Core::Vector2<T>, 2> axes, const std::span<const Core::Vector2<T>, CornerCount> corners)
	{
		for (std::size_t axisIndex = 0; axisIndex < 2; ++axisIndex)
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
