/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Plane;

import <cmath>;
import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Plane final // TODO: Add docs and test, add inside and intersecting
	{
	public:
		using ValueType = T;

		[[nodiscard("Pure constructor")]]
		constexpr Plane() noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Plane(const Core::Vector3<T>& normal, T distance = T{0}) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Plane(const Core::Vector3<T>& normal, const Core::Vector3<T>& point) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Plane(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1, const Core::Vector3<T>& point2) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Plane(const Plane& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Plane(Plane&& other) noexcept = default;

		constexpr ~Plane() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Normal() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Normal() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& Distance() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Distance() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Plane Flipped() const noexcept;
		constexpr void Flip() noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Distance(const Core::Vector3<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Project(const Core::Vector3<T>& point) const noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::int8_t Side(const Core::Vector3<T>& point) const noexcept;

		constexpr void Set(const Core::Vector3<T>& normalToSet, T distanceToSet = T{0}) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Plane<U>() const noexcept;

		constexpr Plane& operator =(const Plane& other) noexcept = default;
		constexpr Plane& operator =(Plane&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Plane& other) const noexcept = default;

	private:
		Core::Vector3<T> normal;
		T distance;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Plane<T>& left, const Plane<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Plane<T>& plane);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Plane<T>::Plane() noexcept :
		normal(Core::Vector3<T>::Predefined::Forward),
		distance{0}
	{
	}

	template<std::floating_point T>
	constexpr Plane<T>::Plane(const Core::Vector3<T>& normal, const T distance) noexcept :
		normal(normal),
		distance{distance}
	{
	}

	template<std::floating_point T>
	constexpr Plane<T>::Plane(const Core::Vector3<T>& normal, const Core::Vector3<T>& point) noexcept :
		normal(normal),
		distance{-Core::Dot(normal, point)}
	{
	}

	template<std::floating_point T>
	constexpr Plane<T>::Plane(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1, const Core::Vector3<T>& point2) noexcept :
		normal(Core::Cross(point1 - point0, point2 - point0).Normalized()),
		distance{-Core::Dot(normal, point0)}
	{
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Plane<T>::Normal() noexcept
	{
		 return normal;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Plane<T>::Normal() const noexcept
	{
		return normal;
	}

	template<std::floating_point T>
	constexpr T& Plane<T>::Distance() noexcept
	{
		return distance;
	}

	template<std::floating_point T>
	constexpr const T& Plane<T>::Distance() const noexcept
	{
		return distance;
	}

	template<std::floating_point T>
	constexpr Plane<T> Plane<T>::Flipped() const noexcept
	{
		return Plane(-normal, -distance);
	}

	template<std::floating_point T>
	constexpr void Plane<T>::Flip() noexcept
	{
		*this = Flipped();
	}

	template<std::floating_point T>
	bool Plane<T>::IsFinite() const noexcept
	{
		return normal.IsFinite() && std::isfinite(distance);
	}

	template<std::floating_point T>
	constexpr T Plane<T>::Distance(const Core::Vector3<T>& point) const noexcept
	{
		return Core::Dot(point, normal) + distance;
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Plane<T>::Project(const Core::Vector3<T>& point) const noexcept
	{
		return point - normal * Distance(point);
	}

	template<std::floating_point T>
	constexpr std::int8_t Plane<T>::Side(const Core::Vector3<T>& point) const noexcept
	{
		return Core::Signum<T, std::int8_t>(Distance(point));
	}

	template<std::floating_point T>
	constexpr void Plane<T>::Set(const Core::Vector3<T>& normalToSet, const T distanceToSet) noexcept
	{
		normal = normalToSet;
		distance = distanceToSet;
	}

	template<std::floating_point T>
	std::string Plane<T>::ToString() const
	{
		return std::format("Normal: {}, Distance: {}", normal.ToString(), distance);
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Plane<T>::operator Plane<U>() const noexcept
	{
		return Plane<U>(static_cast<Core::Vector3<U>>(normal), static_cast<U>(distance));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Plane<T>& left, const Plane<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Normal(), right.Normal(), tolerance) && Core::AreAlmostEqual(left.Distance(), right.Distance(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Plane<T>& plane)
	{
		return stream << plane.ToString();
	}
}
