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

export module PonyMath.Shape:Sphere;

import <cmath>;
import <concepts>;
import <format>;
import <numbers>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief Sphere implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Sphere final
	{
	public:
		using ValueType = T; ///< Component type.

		struct Predefined; ///< Predefined spheres.

		/// @brief Creates a zero sphere.
		[[nodiscard("Pure constructor")]]
		constexpr Sphere() noexcept = default;
		/// @brief Creates a sphere.
		/// @param x Center x component.
		/// @param y Center y component.
		/// @param z Center z component.
		/// @param radius Radius.
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(T x, T y, T z, T radius) noexcept;
		/// @brief Creates a sphere.
		/// @param center Center.
		/// @param radius Radius.
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(const Core::Vector3<T>& center, T radius) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(const Sphere& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(Sphere&& other) noexcept = default;

		constexpr ~Sphere() noexcept = default;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Center() noexcept;
		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Center() const noexcept;
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

		/// @brief Calculates an area.
		/// @return Area.
		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;
		/// @brief Calculates a volume.
		/// @return Volume.
		[[nodiscard("Pure function")]]
		constexpr T Volume() const noexcept;

		/// @brief Checks if all the box data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Checks if the sphere contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector3<T>& point) const noexcept;
		/// @brief Calculates the closest point on the sphere.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the sphere, the @p point is returned.
		[[nodiscard("Pure function")]]
		Core::Vector3<T> ClosestPoint(const Core::Vector3<T>& point) const noexcept;

		/// @brief Creates a string representing the sphere.
		/// @return String representing the sphere.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the sphere to a sphere of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Sphere<U>() const noexcept;

		constexpr Sphere& operator =(const Sphere& other) noexcept = default;
		constexpr Sphere& operator =(Sphere&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Sphere& other) const noexcept = default;

	private:
		Core::Vector3<T> center; ///< Center.
		T radius; ///< Radius.
	};

	/// @brief Checks if the two spheres are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left sphere.
	/// @param right Right sphere.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Sphere<T>& left, const Sphere<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts sphere.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param sphere Source sphere.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Sphere<T>& sphere);

	template<std::floating_point T>
	struct Sphere<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = Sphere(Core::Vector3<T>::Predefined::Zero, T{0}); ///< Sphere(Zero, 0).
	};
}

namespace PonyMath::Shape
{
	template <std::floating_point T>
	constexpr Sphere<T>::Sphere(const T x, const T y, const T z, const T radius) noexcept :
		center(x, y, z),
		radius{radius}
	{
	}

	template <std::floating_point T>
	constexpr Sphere<T>::Sphere(const Core::Vector3<T>& center, const T radius) noexcept :
		center(center),
		radius{radius}
	{
	}

	template <std::floating_point T>
	constexpr Core::Vector3<T>& Sphere<T>::Center() noexcept
	{
		return center;
	}

	template <std::floating_point T>
	constexpr const Core::Vector3<T>& Sphere<T>::Center() const noexcept
	{
		return center;
	}

	template <std::floating_point T>
	constexpr T& Sphere<T>::Radius() noexcept
	{
		return radius;
	}

	template <std::floating_point T>
	constexpr const T& Sphere<T>::Radius() const noexcept
	{
		return radius;
	}

	template <std::floating_point T>
	constexpr T Sphere<T>::Diameter() const noexcept
	{
		return radius * T{2};
	}

	template <std::floating_point T>
	constexpr T Sphere<T>::Area() const noexcept
	{
		return T{4} * std::numbers::pi_v<T> * radius * radius;
	}

	template <std::floating_point T>
	constexpr T Sphere<T>::Volume() const noexcept
	{
		return T{4} / T{3} * std::numbers::pi_v<T> * radius * radius * radius;
	}

	template <std::floating_point T>
	bool Sphere<T>::IsFinite() const noexcept
	{
		return center.IsFinite() && std::isfinite(radius);
	}

	template <std::floating_point T>
	constexpr bool Sphere<T>::Contains(const Core::Vector3<T>& point) const noexcept
	{
		return Core::AreAlmostEqual(point, center, radius);
	}

	template <std::floating_point T>
	Core::Vector3<T> Sphere<T>::ClosestPoint(const Core::Vector3<T>& point) const noexcept
	{
		return Core::ClampMagnitude(point - center, radius) + center;
	}

	template <std::floating_point T>
	std::string Sphere<T>::ToString() const
	{
		return std::format("Center: {}, Radius: {}", center.ToString(), radius);
	}

	template <std::floating_point T>
	template <std::floating_point U>
	constexpr Sphere<T>::operator Sphere<U>() const noexcept
	{
		return Sphere<U>(static_cast<Core::Vector3<U>>(center), static_cast<U>(radius));
	}

	template <std::floating_point T>
	bool AreAlmostEqual(const Sphere<T>& left, const Sphere<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) && Core::AreAlmostEqual(left.Radius(), right.Radius(), tolerance);
	}

	template <std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Sphere<T>& sphere)
	{
		return stream << sphere.ToString();
	}
}
