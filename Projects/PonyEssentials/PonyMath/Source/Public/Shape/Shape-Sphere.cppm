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
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Sphere final
	{
	public:
		using ValueType = T;

		struct Predefined;

		[[nodiscard("Pure constructor")]]
		constexpr Sphere() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(T x, T y, T z, T radius) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(const Core::Vector3<T>& center, T radius) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(const Sphere& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Sphere(Sphere&& other) noexcept = default;

		constexpr ~Sphere() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Center() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Center() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& Radius() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Radius() const noexcept;

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

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector3<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> ClosestPoint(const Core::Vector3<T>& point) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Sphere<U>() const noexcept;

		constexpr Sphere& operator =(const Sphere& other) noexcept = default;
		constexpr Sphere& operator =(Sphere&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Sphere& other) const noexcept = default;

	private:
		Core::Vector3<T> center;
		T radius;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Sphere<T>& left, const Sphere<T>& right, T tolerance = T{ 0.00001 }) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Sphere<T>& sphere);

	template<std::floating_point T>
	struct Sphere<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = Sphere(Core::Vector3<T>::Predefined::Zero, T{0});
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
