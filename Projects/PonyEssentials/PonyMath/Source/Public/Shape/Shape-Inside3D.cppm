/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Inside3D;

import <array>;
import <cstddef>;
import <concepts>;
import <span>;

import PonyMath.Core;

import :AABB;
import :OBB;
import :Sphere;

export namespace PonyMath::Shape
{
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const Sphere<T>& small, const Sphere<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const Sphere<T>& small, const AABB<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const Sphere<T>& small, const OBB<T>& large) noexcept;

	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<Core::Arithmetic T> [[nodiscard("Pure function")]]
	bool IsInside(const AABB<T>& small, const AABB<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const AABB<T>& small, const Sphere<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const AABB<T>& small, const OBB<T>& large) noexcept;

	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const OBB<T>& small, const OBB<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const OBB<T>& small, const Sphere<T>& large) noexcept;
	/// @brief Checks if the @p small is fully inside the @p large.
	/// @tparam T Component type.
	/// @param small Small shape.
	/// @param large Large shape.
	/// @return @a True if the @p small is fully inside the @p large; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool IsInside(const OBB<T>& small, const AABB<T>& large) noexcept;
}

namespace PonyMath::Shape
{
	/// @brief Checks if all the @p corners are inside the @p large.
	/// @tparam T Component type.
	/// @param corners Corners.
	/// @param large Large shape.
	/// @return @a True if all the @p corners are inside the @p large; @a false otherwise.
	template<std::floating_point T>
	bool IsInside(std::span<const Core::Vector3<T>> corners, const Sphere<T>& large) noexcept;
	/// @brief Checks if all the @p corners are inside the @p large.
	/// @tparam T Component type.
	/// @param corners Corners.
	/// @param large Large shape.
	/// @return @a True if all the @p corners are inside the @p large; @a false otherwise.
	template<std::floating_point T>
	bool IsInside(std::span<const Core::Vector3<T>> corners, const OBB<T>& large) noexcept;

	template <std::floating_point T>
	bool IsInside(const Sphere<T>& small, const Sphere<T>& large) noexcept
	{
		return (small.Center() - large.Center()).Magnitude() + small.Radius() <= large.Radius();
	}

	template <std::floating_point T>
	bool IsInside(const Sphere<T>& small, const AABB<T>& large) noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
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
	bool IsInside(const Sphere<T>& small, const OBB<T>& large) noexcept
	{
		const auto inverseRotation = Core::Matrix3x3<T>(large.Axes()).Transpose();
		const Core::Vector3<T> center = inverseRotation * (small.Center() - large.Center());
		const Sphere<T> sphere = Sphere<T>(center, small.Radius());
		const AABB<T> aabb = AABB<T>(Core::Vector3<T>::Predefined::Zero, large.Extents());

		return IsInside(sphere, aabb);
	}

	template<Core::Arithmetic T>
	bool IsInside(const AABB<T>& small, const AABB<T>& large) noexcept
	{
		return large.Contains(small.Min()) && large.Contains(small.Max());
	}

	template <std::floating_point T>
	bool IsInside(const AABB<T>& small, const Sphere<T>& large) noexcept
	{
		const std::array<Core::Vector3<T>, AABB<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector3<T>>(corners.data(), corners.size()), large);
	}

	template<std::floating_point T>
	bool IsInside(const AABB<T>& small, const OBB<T>& large) noexcept
	{
		const std::array<Core::Vector3<T>, AABB<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector3<T>>(corners.data(), corners.size()), large);
	}

	template<std::floating_point T>
	bool IsInside(const OBB<T>& small, const OBB<T>& large) noexcept
	{
		const std::array<Core::Vector3<T>, OBB<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector3<T>>(corners.data(), corners.size()), large);
	}

	template <std::floating_point T>
	bool IsInside(const OBB<T>& small, const Sphere<T>& large) noexcept
	{
		const std::array<Core::Vector3<T>, OBB<T>::CornerCount> corners = small.Corners();

		return IsInside(std::span<const Core::Vector3<T>>(corners.data(), corners.size()), large);
	}

	template<std::floating_point T>
	bool IsInside(const OBB<T>& small, const AABB<T>& large) noexcept
	{
		std::array<Core::Vector3<T>, OBB<T>::CornerCount> corners = small.Corners();
		Core::Vector3<T> min = Core::Min(corners[0], corners[1]);
		Core::Vector3<T> max = Core::Max(corners[0], corners[1]);
		for (std::size_t i = 2; i < corners.size(); ++i)
		{
			min = Core::Min(min, corners[i]);
			max = Core::Max(max, corners[i]);
		}

		return large.Contains(min) && large.Contains(max);
	}

	template <std::floating_point T>
	bool IsInside(std::span<const Core::Vector3<T>> corners, const Sphere<T>& large) noexcept
	{
		for (const Core::Vector3<T>& corner : corners)
		{
			if (!large.Contains(corner))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	bool IsInside(const std::span<const Core::Vector3<T>> corners, const OBB<T>& large) noexcept
	{
		for (const Core::Vector3<T>& corner : corners)
		{
			if (!large.Contains(corner))
			{
				return false;
			}
		}

		return true;
	}
}
