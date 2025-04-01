/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Inside2D;

import <array>;
import <cstddef>;
import <concepts>;
import <span>;

import PonyMath.Core;

import :AABR;
import :Circle;
import :OBR;

export namespace PonyMath::Shape
{
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const Circle<T>& small, const Circle<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const Circle<T>& small, const AABR<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const Circle<T>& small, const OBR<T>& large) noexcept;

	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	bool IsInside(const AABR<T>& small, const AABR<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const AABR<T>& small, const Circle<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const AABR<T>& small, const OBR<T>& large) noexcept;

	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const OBR<T>& small, const OBR<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const OBR<T>& small, const Circle<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const OBR<T>& small, const AABR<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	/// @brief Checks if all the @p corners are inside the @p large.
	/// @tparam T Component type.
	/// @param corners Corners.
	/// @param large Large shape.
	/// @return @a True if all the @p corners are inside the @p large; @a false otherwise.
	template<std::floating_point T>
	bool IsInside(std::span<const Core::Vector2<T>> corners, const Circle<T>& large) noexcept;
	/// @brief Checks if all the @p corners are inside the @p large.
	/// @tparam T Component type.
	/// @param corners Corners.
	/// @param large Large shape.
	/// @return @a True if all the @p corners are inside the @p large; @a false otherwise.
	template<std::floating_point T>
	bool IsInside(std::span<const Core::Vector2<T>> corners, const OBR<T>& large) noexcept;

	template <std::floating_point T>
	bool IsInside(const Circle<T>& small, const Circle<T>& large) noexcept
	{
		return (small.Center() - large.Center()).Magnitude() + small.Radius() <= large.Radius();
	}

	template <std::floating_point T>
	bool IsInside(const Circle<T>& small, const AABR<T>& large) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			if (small.Center()[i] - large.Min(i) < small.Radius() ||
				large.Max(i) - small.Center()[i] < small.Radius())
			{
				return false;
			}
		}

		return true;
	}

	template <std::floating_point T>
	bool IsInside(const Circle<T>& small, const OBR<T>& large) noexcept
	{
		const auto inverseRotation = Core::Matrix2x2<T>(large.Axes()).Transpose();
		const Core::Vector2<T> center = inverseRotation * (small.Center() - large.Center());
		const Circle<T> circle = Circle<T>(center, small.Radius());
		const AABR<T> aabr = AABR<T>(Core::Vector2<T>::Predefined::Zero, large.Extents());

		return IsInside(circle, aabr);
	}

	template<Core::Arithmetic T>
	bool IsInside(const AABR<T>& small, const AABR<T>& large) noexcept
	{
		return large.Contains(small.Min()) && large.Contains(small.Max());
	}

	template <std::floating_point T>
	bool IsInside(const AABR<T>& small, const Circle<T>& large) noexcept
	{
		const std::array<Core::Vector2<T>, AABR<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector2<T>>(corners.data(), corners.size()), large);
	}

	template<std::floating_point T>
	bool IsInside(const AABR<T>& small, const OBR<T>& large) noexcept
	{
		const std::array<Core::Vector2<T>, OBR<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector2<T>>(corners.data(), corners.size()), large);
	}

	template<std::floating_point T>
	bool IsInside(const OBR<T>& small, const OBR<T>& large) noexcept
	{
		const std::array<Core::Vector2<T>, OBR<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector2<T>>(corners.data(), corners.size()), large);
	}

	template <std::floating_point T>
	bool IsInside(const OBR<T>& small, const Circle<T>& large) noexcept
	{
		const std::array<Core::Vector2<T>, OBR<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector2<T>>(corners.data(), corners.size()), large);
	}

	template<std::floating_point T>
	bool IsInside(const OBR<T>& small, const AABR<T>& large) noexcept
	{
		const std::array<Core::Vector2<T>, OBR<T>::CornerCount> corners = small.Corners();
		Core::Vector2<T> min = Core::Min(corners[0], corners[1]);
		Core::Vector2<T> max = Core::Max(corners[0], corners[1]);
		for (std::size_t i = 2; i < corners.size(); ++i)
		{
			min = Core::Min(min, corners[i]);
			max = Core::Max(max, corners[i]);
		}

		return large.Contains(min) && large.Contains(max);
	}

	template <std::floating_point T>
	bool IsInside(const std::span<const Core::Vector2<T>> corners, const Circle<T>& large) noexcept
	{
		for (const Core::Vector2<T>& corner : corners)
		{
			if (!large.Contains(corner))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	bool IsInside(const std::span<const Core::Vector2<T>> corners, const OBR<T>& large) noexcept
	{
		for (const Core::Vector2<T>& corner : corners)
		{
			if (!large.Contains(corner))
			{
				return false;
			}
		}

		return true;
	}
}
