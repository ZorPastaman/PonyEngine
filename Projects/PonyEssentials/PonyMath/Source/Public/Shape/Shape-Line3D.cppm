/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Line3D;

import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

import :Ray3D;
import :Segment3D;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Line3D final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Line3D() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Line3D(const Core::Vector3<T>& point, const Core::Vector3<T>& direction) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line3D(const Ray3D<T>& ray) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line3D(const Segment3D<T>& segment) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Line3D(const Line3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Line3D(Line3D&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		static constexpr Line3D Create(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1) noexcept;

		constexpr ~Line3D() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Point() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Point() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3 <T>& Direction() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3 <T>& Direction() const noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Distance(const Core::Vector3<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Project(const Core::Vector3<T>& point) const noexcept;

		constexpr void Set(const Core::Vector3<T>& point, const Core::Vector3<T>& direction) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Line3D<U>() const noexcept;

		constexpr Line3D& operator =(const Line3D& other) noexcept = default;
		constexpr Line3D& operator =(Line3D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Line3D& other) const noexcept;

	private:
		Core::Vector3<T> point;
		Core::Vector3<T> direction;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Line3D<T>& left, const Line3D<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Line3D<T>& line);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Line3D<T>::Line3D() noexcept :
		point(Core::Vector3<T>::Predefined::Zero),
		direction(Core::Vector3<T>::Predefined::Forward)
	{
	}

	template<std::floating_point T>
	constexpr Line3D<T>::Line3D(const Core::Vector3<T>& point, const Core::Vector3<T>& direction) noexcept :
		point(point),
		direction(direction)
	{

	}

	template<std::floating_point T>
	constexpr Line3D<T>::Line3D(const Ray3D<T>& ray) noexcept :
		point(ray.Origin()),
		direction(ray.Direction())
	{
	}

	template<std::floating_point T>
	constexpr Line3D<T>::Line3D(const Segment3D<T>& segment) noexcept :
		Line3D(Ray3D<T>(segment))
	{
	}

	template<std::floating_point T>
	constexpr Line3D<T> Line3D<T>::Create(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1) noexcept
	{
		return Line3D(point0, (point1 - point0).Normalized());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Line3D<T>::Point() noexcept
	{
		return point;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Line3D<T>::Point() const noexcept
	{
		return point;
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Line3D<T>::Direction() noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Line3D<T>::Direction() const noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	bool Line3D<T>::IsFinite() const noexcept
	{
		return point.IsFinite() && direction.IsFinite();
	}

	template<std::floating_point T>
	constexpr T Line3D<T>::Distance(const Core::Vector3<T>& point) const noexcept
	{
		return (point - Project(point)).Magnitude();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Line3D<T>::Project(const Core::Vector3<T>& point) const noexcept
	{
		return this->point + direction * Core::Dot(point - this->point, direction);
	}

	template<std::floating_point T>
	constexpr void Line3D<T>::Set(const Core::Vector3<T>& point, const Core::Vector3<T>& direction) noexcept
	{
		this->point = point;
		this->direction = direction;
	}

	template<std::floating_point T>
	std::string Line3D<T>::ToString() const
	{
		return std::format("Point: {}, Direction: {}", point.ToString(), direction.ToString());
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Line3D<T>::operator Line3D<U>() const noexcept
	{
		return Line3D<U>(static_cast<Core::Vector3<U>>(point), static_cast<Core::Vector3<U>>(direction));
	}

	template<std::floating_point T>
	constexpr bool Line3D<T>::operator ==(const Line3D& other) const noexcept
	{
		return Core::Angle(direction, other.direction) == T{0} && Distance(other.point) == T{0};
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Line3D<T>& left, const Line3D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(Core::Angle(left.Direction(), right.Direction()), T{0}, tolerance) && Core::AreAlmostEqual((right.Point() - left.Project(right.Point())).MagnitudeSquared(), T{0}, tolerance * tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Line3D<T>& line)
	{
		return stream << line.ToString();
	}
}
