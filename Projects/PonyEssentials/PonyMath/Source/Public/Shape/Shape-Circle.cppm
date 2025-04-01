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

export module PonyMath.Shape:Circle;

import <cmath>;
import <concepts>;
import <format>;
import <numbers>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief Circle implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Circle final
	{
	public:
		using ValueType = T; ///< Component type.

		struct Predefined; ///< Predefined circles.

		/// @brief Creates a circle with the center in the origin and zero radius.
		[[nodiscard("Pure constructor")]]
		constexpr Circle() noexcept = default;
		/// @brief Creates a circle.
		/// @param x Center x component.
		/// @param y Center y component.
		/// @param radius Circle radius. Must be positive.
		[[nodiscard("Pure constructor")]]
		constexpr Circle(T x, T y, T radius) noexcept;
		/// @brief Creates a circle.
		/// @param center Circle center.
		/// @param radius Circle radius. Must be positive.
		[[nodiscard("Pure constructor")]]
		constexpr Circle(const Core::Vector2<T>& center, T radius) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Circle(const Circle& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Circle(Circle&& other) noexcept = default;

		constexpr ~Circle() noexcept = default;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Center() noexcept;
		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Center() const noexcept;
		/// @brief Gets the radius.
		/// @return Radius. Must be positive.
		[[nodiscard("Pure function")]]
		constexpr T& Radius() noexcept;
		/// @brief Gets the radius.
		/// @return Radius.
		[[nodiscard("Pure function")]]
		constexpr const T& Radius() const noexcept;

		/// @brief Calculates a diameter.
		/// @return Diameter.
		[[nodiscard("Pure function")]]
		constexpr T Diameter() const noexcept;

		/// @brief Calculates a perimeter.
		/// @return Perimeter.
		[[nodiscard("Pure function")]]
		constexpr T Perimeter() const noexcept;
		/// @brief Calculates an area.
		/// @return Area.
		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;

		/// @brief Checks if all the box data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Checks if the circle contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector2<T>& point) const noexcept;
		/// @brief Calculates the closest point on the circle.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the circle, the @p point is returned.
		[[nodiscard("Pure function")]]
		Core::Vector2<T> ClosestPoint(const Core::Vector2<T>& point) const noexcept;

		/// @brief Creates a string representing the circle.
		/// @return String representing the circle.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the circle to a circle of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Circle<U>() const noexcept;

		constexpr Circle& operator =(const Circle& other) noexcept = default;
		constexpr Circle& operator =(Circle&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Circle& other) const noexcept = default;

	private:
		Core::Vector2<T> center; ///< Center.
		T radius; ///< Radius
	};

	/// @brief Checks if the two circles are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left circle.
	/// @param right Right circle.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Circle<T>& left, const Circle<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts circle.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param circle Source circle.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Circle<T>& circle);

	template<std::floating_point T>
	struct Circle<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = Circle(Core::Vector2<T>::Predefined::Zero, T{0}); ///< Circle(Zero, 0).
	};
}

namespace PonyMath::Shape
{
	template <std::floating_point T>
	constexpr Circle<T>::Circle(const T x, const T y, const T radius) noexcept :
		center(x, y),
		radius{radius}
	{
	}

	template <std::floating_point T>
	constexpr Circle<T>::Circle(const Core::Vector2<T>& center, const T radius) noexcept :
		center(center),
		radius{radius}
	{
	}

	template <std::floating_point T>
	constexpr Core::Vector2<T>& Circle<T>::Center() noexcept
	{
		return center;
	}

	template <std::floating_point T>
	constexpr const Core::Vector2<T>& Circle<T>::Center() const noexcept
	{
		return center;
	}

	template <std::floating_point T>
	constexpr T& Circle<T>::Radius() noexcept
	{
		return radius;
	}

	template <std::floating_point T>
	constexpr const T& Circle<T>::Radius() const noexcept
	{
		return radius;
	}

	template <std::floating_point T>
	constexpr T Circle<T>::Diameter() const noexcept
	{
		return radius * T{2};
	}

	template <std::floating_point T>
	constexpr T Circle<T>::Perimeter() const noexcept
	{
		return T{2} * std::numbers::pi_v<T> * radius;
	}

	template <std::floating_point T>
	constexpr T Circle<T>::Area() const noexcept
	{
		return std::numbers::pi_v<T> * radius * radius;
	}

	template <std::floating_point T>
	bool Circle<T>::IsFinite() const noexcept
	{
		return center.IsFinite() && std::isfinite(radius);
	}

	template <std::floating_point T>
	constexpr bool Circle<T>::Contains(const Core::Vector2<T>& point) const noexcept
	{
		return Core::AreAlmostEqual(point, center, radius);
	}

	template <std::floating_point T>
	Core::Vector2<T> Circle<T>::ClosestPoint(const Core::Vector2<T>& point) const noexcept
	{
		return Core::ClampMagnitude(point - center, radius) + center;
	}

	template <std::floating_point T>
	std::string Circle<T>::ToString() const
	{
		return std::format("Center: {}, Radius: {}", center.ToString(), radius);
	}

	template <std::floating_point T>
	template <std::floating_point U>
	constexpr Circle<T>::operator Circle<U>() const noexcept
	{
		return Circle<U>(static_cast<Core::Vector2<U>>(center), static_cast<U>(radius));
	}

	template <std::floating_point T>
	bool AreAlmostEqual(const Circle<T>& left, const Circle<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) && Core::AreAlmostEqual(left.Radius(), right.Radius(), tolerance);
	}

	template <std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Circle<T>& circle)
	{
		return stream << circle.ToString();
	}
}
