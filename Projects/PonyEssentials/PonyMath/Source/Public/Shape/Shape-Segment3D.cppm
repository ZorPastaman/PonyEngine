/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 3033-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Segment3D;

import <cmath>;
import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Segment3D final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Segment3D() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Segment3D(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Segment3D(const Segment3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Segment3D(Segment3D&& other) noexcept = default;

		constexpr ~Segment3D() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Point0() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Point0() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Point1() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Point1() const noexcept;

		[[nodiscard("Pure function")]]
		T Length() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T LengthSquared() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Vector() const noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		constexpr void Set(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Segment3D<U>() const noexcept;

		constexpr Segment3D& operator =(const Segment3D& other) noexcept = default;
		constexpr Segment3D& operator =(Segment3D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Segment3D& other) const noexcept;

	private:
		Core::Vector3<T> point0;
		Core::Vector3<T> point1;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Segment3D<T>& left, const Segment3D<T>& right, T tolerance = T{ 0.00001 }) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Segment3D<T>& segment);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Segment3D<T>::Segment3D(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1) noexcept :
		point0(point0),
		point1(point1)
	{
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Segment3D<T>::Point0() noexcept
	{
		return point0;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Segment3D<T>::Point0() const noexcept
	{
		return point0;
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Segment3D<T>::Point1() noexcept
	{
		return point1;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Segment3D<T>::Point1() const noexcept
	{
		return point1;
	}

	template<std::floating_point T>
	T Segment3D<T>::Length() const noexcept
	{
		return Vector().Magnitude();
	}

	template<std::floating_point T>
	constexpr T Segment3D<T>::LengthSquared() const noexcept
	{
		return Vector().MagnitudeSquared();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Segment3D<T>::Vector() const noexcept
	{
		return point1 - point0;
	}

	template<std::floating_point T>
	bool Segment3D<T>::IsFinite() const noexcept
	{
		return point0.IsFinite() && point1.IsFinite();
	}

	template<std::floating_point T>
	constexpr void Segment3D<T>::Set(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1) noexcept
	{
		this->point0 = point0;
		this->point1 = point1;
	}

	template<std::floating_point T>
	std::string Segment3D<T>::ToString() const
	{
		return std::format("Point0: {}, Point1: {}", point0.ToString(), point1.ToString());
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Segment3D<T>::operator Segment3D<U>() const noexcept
	{
		return Segment3D<U>(static_cast<Core::Vector3<U>>(point0), static_cast<Core::Vector3<U>>(point1));
	}

	template<std::floating_point T>
	constexpr bool Segment3D<T>::operator ==(const Segment3D& other) const noexcept
	{
		if (point0 == other.point0)
		{
			return point1 == other.point1;
		}
		if (point0 == other.point1)
		{
			return point1 == other.point0;
		}

		return false;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Segment3D<T>& left, const Segment3D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Point0(), right.Point0(), tolerance) && Core::AreAlmostEqual(left.Point1(), right.Point1(), tolerance) ||
			Core::AreAlmostEqual(left.Point0(), right.Point1(), tolerance) && Core::AreAlmostEqual(left.Point1(), right.Point0(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Segment3D<T>& segment)
	{
		return stream << segment.ToString();
	}
}
