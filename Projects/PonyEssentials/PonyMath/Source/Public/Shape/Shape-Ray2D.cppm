/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyMath.Shape:Ray2D;

import <algorithm>;
import <concepts>;
import <format>;
import <limits>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief 2D ray implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Ray2D final
	{
	public:
		using ValueType = T; ///< Component type.

		struct Predefined; ///< Predefined rays.

		/// @brief Creates a default ray. The ray origin is the world origin, the ray direction is a right unit vector.
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D() noexcept;
		/// @brief Creates a ray.
		/// @param origin Ray origin.
		/// @param direction Ray direction. Must be unit.
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D(const Core::Vector2<T>& origin, const Core::Vector2<T>& direction) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D(const Ray2D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D(Ray2D&& other) noexcept = default;

		/// @brief Creates a ray that starts at the @p origin and passes the @p target.
		/// @param origin Ray origin.
		/// @param target Target point.
		/// @return Created ray.
		[[nodiscard("Pure function")]]
		static Ray2D Create(const Core::Vector2<T>& origin, const Core::Vector2<T>& target) noexcept;

		constexpr ~Ray2D() noexcept = default;

		/// @brief Gets the ray origin.
		/// @return Origin.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Origin() noexcept;
		/// @brief Gets the ray origin.
		/// @return Origin.
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector2<T>& Origin() const noexcept;
		/// @brief Gets the ray direction.
		/// @return Direction. Must be unit.
		[[nodiscard("Pure constructor")]]
		constexpr Core::Vector2<T>& Direction() noexcept;
		/// @brief Gets the ray direction.
		/// @return Direction.
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector2<T>& Direction() const noexcept;

		/// @brief Creates a ray with the same origin but an opposite direction.
		/// @return Flipped ray.
		[[nodiscard("Pure function")]]
		constexpr Ray2D Flipped() const noexcept;
		/// @brief Sets an opposite direction.
		constexpr void Flip() noexcept;

		/// @brief Checks if all the components are finite.
		/// @return @a True if they are all finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Projects the @p point onto the ray.
		/// @param point Point to project.
		/// @param maxDistance Ray max distance.
		/// @return Projected point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Project(const Core::Vector2<T>& point, T maxDistance = std::numeric_limits<T>::infinity()) const noexcept;
		/// @brief Normalizes the @p point.
		/// @param point Point to normalize.
		/// @return Normalized point.
		[[nodiscard("Pure function")]]
		constexpr T Normalize(const Core::Vector2<T>& point) const noexcept;
		/// @brief Unnormalizes a point by its normalized @p value.
		/// @param value Normalized value.
		/// @return Unnormalized point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Unnormalize(T value) const noexcept;

		/// @brief Creates a string representing the ray.
		/// @return String representing the ray.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the ray to a ray of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Ray2D<U>() const noexcept;

		constexpr Ray2D& operator =(const Ray2D& other) noexcept = default;
		constexpr Ray2D& operator =(Ray2D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Ray2D& other) const noexcept = default;

	private:
		Core::Vector2<T> origin; ///< Origin.
		Core::Vector2<T> direction; ///< Direction.
	};

	/// @brief Checks if the two rays are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left ray.
	/// @param right Right ray.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Ray2D<T>& left, const Ray2D<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts ray.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param ray Source ray.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray2D<T>& ray);

	template<std::floating_point T>
	struct Ray2D<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Up = Ray2D(Core::Vector2<T>::Predefined::Zero, Core::Vector2<T>::Predefined::Up); ///< Ray2D(Zero, Up).
		static constexpr auto Down = Ray2D(Core::Vector2<T>::Predefined::Zero, Core::Vector2<T>::Predefined::Down); ///< Ray2D(Zero, Down).
		static constexpr auto Right = Ray2D(Core::Vector2<T>::Predefined::Zero, Core::Vector2<T>::Predefined::Right); ///< Ray2D(Zero, Right).
		static constexpr auto Left = Ray2D(Core::Vector2<T>::Predefined::Zero, Core::Vector2<T>::Predefined::Left); ///< Ray2D(Zero, Left).
	};
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Ray2D<T>::Ray2D() noexcept :
		origin(Core::Vector2<T>::Predefined::Zero),
		direction(Core::Vector2<T>::Predefined::Right)
	{
	}

	template<std::floating_point T>
	constexpr Ray2D<T>::Ray2D(const Core::Vector2<T>& origin, const Core::Vector2<T>& direction) noexcept :
		origin(origin),
		direction(direction)
	{
	}

	template<std::floating_point T>
	Ray2D<T> Ray2D<T>::Create(const Core::Vector2<T>& origin, const Core::Vector2<T>& target) noexcept
	{
		return Ray2D(origin, (target - origin).Normalized());
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Ray2D<T>::Origin() noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Ray2D<T>::Origin() const noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Ray2D<T>::Direction() noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Ray2D<T>::Direction() const noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr Ray2D<T> Ray2D<T>::Flipped() const noexcept
	{
		return Ray2D(origin, -direction);
	}

	template<std::floating_point T>
	constexpr void Ray2D<T>::Flip() noexcept
	{
		direction = -direction;
	}

	template<std::floating_point T>
	bool Ray2D<T>::IsFinite() const noexcept
	{
		return origin.IsFinite() && direction.IsFinite();
	}

	template <std::floating_point T>
	constexpr Core::Vector2<T> Ray2D<T>::Project(const Core::Vector2<T>& point, const T maxDistance) const noexcept
	{
		const T normalized = std::clamp(Normalize(point), T{0}, maxDistance);

		return Unnormalize(normalized);
	}

	template<std::floating_point T>
	constexpr T Ray2D<T>::Normalize(const Core::Vector2<T>& point) const noexcept
	{
		return Core::Dot(direction, point - origin);
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> Ray2D<T>::Unnormalize(const T value) const noexcept
	{
		return origin + direction * value;
	}

	template<std::floating_point T>
	std::string Ray2D<T>::ToString() const
	{
		return std::format("Origin: {}, Direction: {}", origin.ToString(), direction.ToString());
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Ray2D<T>::operator Ray2D<U>() const noexcept
	{
		return Ray2D<U>(static_cast<Core::Vector2<U>>(origin), static_cast<Core::Vector2<U>>(direction));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Ray2D<T>& left, const Ray2D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Origin(), right.Origin(), tolerance) && Core::AreAlmostEqual(left.Direction(), right.Direction(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray2D<T>& ray)
	{
		return stream << ray.ToString();
	}
}
