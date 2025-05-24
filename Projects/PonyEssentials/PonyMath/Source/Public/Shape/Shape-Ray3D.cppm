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

export module PonyMath.Shape:Ray3D;

import <algorithm>;
import <concepts>;
import <format>;
import <limits>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief 3D ray implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Ray3D final
	{
	public:
		using ValueType = T; ///< Component type.

		struct Predefined; ///< Predefined rays.

		/// @brief Creates a default ray. The ray origin is the world origin, the ray direction is a right unit vector.
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D() noexcept;
		/// @brief Creates a ray.
		/// @param origin Ray origin.
		/// @param direction Ray direction. Must be unit.
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D(const Ray3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D(Ray3D&& other) noexcept = default;

		/// @brief Creates a ray that starts at the @p origin and passes the @p target.
		/// @param origin Ray origin.
		/// @param target Target point.
		/// @return Created ray.
		[[nodiscard("Pure function")]]
		static constexpr Ray3D Create(const Core::Vector3<T>& origin, const Core::Vector3<T>& target) noexcept;

		constexpr ~Ray3D() noexcept = default;

		/// @brief Gets the ray origin.
		/// @return Origin.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Origin() noexcept;
		/// @brief Gets the ray origin.
		/// @return Origin.
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector3<T>& Origin() const noexcept;
		/// @brief Gets the ray direction.
		/// @return Direction. Must be unit.
		[[nodiscard("Pure constructor")]]
		constexpr Core::Vector3<T>& Direction() noexcept;
		/// @brief Gets the ray direction.
		/// @return Direction.
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector3<T>& Direction() const noexcept;

		/// @brief Creates a ray with the same origin but an opposite direction.
		/// @return Flipped ray.
		[[nodiscard("Pure function")]]
		constexpr Ray3D Flipped() const noexcept;
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
		constexpr Core::Vector3<T> Project(const Core::Vector3<T>& point, T maxDistance = std::numeric_limits<T>::infinity()) const noexcept;
		/// @brief Normalizes the @p point.
		/// @param point Point to normalize.
		/// @return Normalized point.
		[[nodiscard("Pure function")]]
		constexpr T Normalize(const Core::Vector3<T>& point) const noexcept;
		/// @brief Unnormalizes a point by its normalized @p value.
		/// @param value Normalized value.
		/// @return Unnormalized point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Unnormalize(T value) const noexcept;

		/// @brief Creates a string representing the ray.
		/// @return String representing the ray.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the ray to a ray of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Ray3D<U>() const noexcept;

		constexpr Ray3D& operator =(const Ray3D& other) noexcept = default;
		constexpr Ray3D& operator =(Ray3D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Ray3D& other) const noexcept = default;

	private:
		Core::Vector3<T> origin; ///< Origin.
		Core::Vector3<T> direction; ///< Direction.
	};

	/// @brief Checks if the two rays are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left ray.
	/// @param right Right ray.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Ray3D<T>& left, const Ray3D<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts ray.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param ray Source ray.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray3D<T>& ray);

	template<std::floating_point T>
	struct Ray3D<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Forward = Ray3D(Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Forward); ///< Ray3D(Zero, Forward).
		static constexpr auto Back = Ray3D(Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Back); ///< Ray3D(Zero, Back).
		static constexpr auto Up = Ray3D(Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Up); ///< Ray3D(Zero, Up).
		static constexpr auto Down = Ray3D(Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Down); ///< Ray3D(Zero, Down).
		static constexpr auto Right = Ray3D(Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Right); ///< Ray3D(Zero, Right).
		static constexpr auto Left = Ray3D(Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Left); ///< Ray3D(Zero, Left).
	};
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Ray3D<T>::Ray3D() noexcept :
		origin(Core::Vector3<T>::Predefined::Zero),
		direction(Core::Vector3<T>::Predefined::Forward)
	{
	}

	template<std::floating_point T>
	constexpr Ray3D<T>::Ray3D(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction) noexcept :
		origin(origin),
		direction(direction)
	{
	}

	template<std::floating_point T>
	constexpr Ray3D<T> Ray3D<T>::Create(const Core::Vector3<T>& origin, const Core::Vector3<T>& target) noexcept
	{
		return Ray3D(origin, (target - origin).Normalized());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Ray3D<T>::Origin() noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Ray3D<T>::Origin() const noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Ray3D<T>::Direction() noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Ray3D<T>::Direction() const noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr Ray3D<T> Ray3D<T>::Flipped() const noexcept
	{
		return Ray3D(origin, -direction);
	}

	template<std::floating_point T>
	constexpr void Ray3D<T>::Flip() noexcept
	{
		direction = -direction;
	}

	template<std::floating_point T>
	bool Ray3D<T>::IsFinite() const noexcept
	{
		return origin.IsFinite() && direction.IsFinite();
	}

	template <std::floating_point T>
	constexpr Core::Vector3<T> Ray3D<T>::Project(const Core::Vector3<T>& point, const T maxDistance) const noexcept
	{
		const T normalized = std::clamp(Normalize(point), T{0}, maxDistance);

		return Unnormalize(normalized);
	}

	template<std::floating_point T>
	constexpr T Ray3D<T>::Normalize(const Core::Vector3<T>& point) const noexcept
	{
		return Core::Dot(direction, point - origin);
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Ray3D<T>::Unnormalize(const T value) const noexcept
	{
		return origin + direction * value;
	}

	template<std::floating_point T>
	std::string Ray3D<T>::ToString() const
	{
		return std::format("Origin: {}, Direction: {}", origin.ToString(), direction.ToString());
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Ray3D<T>::operator Ray3D<U>() const noexcept
	{
		return Ray3D<U>(static_cast<Core::Vector3<U>>(origin), static_cast<Core::Vector3<U>>(direction));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Ray3D<T>& left, const Ray3D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Origin(), right.Origin(), tolerance) && Core::AreAlmostEqual(left.Direction(), right.Direction(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray3D<T>& ray)
	{
		return stream << ray.ToString();
	}
}
