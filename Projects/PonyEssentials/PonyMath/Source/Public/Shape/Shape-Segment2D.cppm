/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Segment2D;

import <cmath>;
import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Segment2D final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Segment2D() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Segment2D(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Segment2D(const Segment2D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Segment2D(Segment2D&& other) noexcept = default;

		constexpr ~Segment2D() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Point0() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Point0() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Point1() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Point1() const noexcept;

		[[nodiscard("Pure function")]]
		T Length() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T LengthSquared() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Vector() const noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		constexpr void Set(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Segment2D<U>() const noexcept;

		constexpr Segment2D& operator =(const Segment2D& other) noexcept = default;
		constexpr Segment2D& operator =(Segment2D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Segment2D& other) const noexcept;

	private:
		Core::Vector2<T> point0;
		Core::Vector2<T> point1;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Segment2D<T>& left, const Segment2D<T>& right, T tolerance = T{ 0.00001 }) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Segment2D<T>& segment);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Segment2D<T>::Segment2D(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept :
		point0(point0),
		point1(point1)
	{
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Segment2D<T>::Point0() noexcept
	{
		return point0;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Segment2D<T>::Point0() const noexcept
	{
		return point0;
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Segment2D<T>::Point1() noexcept
	{
		return point1;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Segment2D<T>::Point1() const noexcept
	{
		return point1;
	}

	template<std::floating_point T>
	T Segment2D<T>::Length() const noexcept
	{
		return Vector().Magnitude();
	}

	template<std::floating_point T>
	constexpr T Segment2D<T>::LengthSquared() const noexcept
	{
		return Vector().MagnitudeSquared();
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> Segment2D<T>::Vector() const noexcept
	{
		return point1 - point0;
	}

	template<std::floating_point T>
	bool Segment2D<T>::IsFinite() const noexcept
	{
		return point0.IsFinite() && point1.IsFinite();
	}

	template<std::floating_point T>
	constexpr void Segment2D<T>::Set(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept
	{
		this->point0 = point0;
		this->point1 = point1; 
	}

	template<std::floating_point T>
	std::string Segment2D<T>::ToString() const
	{
		return std::format("Point0: {}, Point1: {}", point0.ToString(), point1.ToString());
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Segment2D<T>::operator Segment2D<U>() const noexcept
	{
		return Segment2D<U>(static_cast<Core::Vector2<U>>(point0), static_cast<Core::Vector2<U>>(point1));
	}

	template<std::floating_point T>
	constexpr bool Segment2D<T>::operator ==(const Segment2D& other) const noexcept
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
	constexpr bool AreAlmostEqual(const Segment2D<T>& left, const Segment2D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Point0(), right.Point0(), tolerance) && Core::AreAlmostEqual(left.Point1(), right.Point1(), tolerance) ||
			Core::AreAlmostEqual(left.Point0(), right.Point1(), tolerance) && Core::AreAlmostEqual(left.Point1(), right.Point0(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Segment2D<T>& segment)
	{
		return stream << segment.ToString();
	}
}
