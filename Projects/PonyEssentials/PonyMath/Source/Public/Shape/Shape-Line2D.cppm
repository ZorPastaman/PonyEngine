/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Line2D;

import <cmath>;
import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

import :Ray2D;
import :Segment2D;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Line2D final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Line2D() noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line2D(const Core::Vector2<T>& normal, T distance = T{0}) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line2D(const Core::Vector2<T>& normal, const Core::Vector2<T>& point) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line2D(const Ray2D<T>& ray) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line2D(const Segment2D<T>& segment) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Line2D(const Line2D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Line2D(Line2D&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		static constexpr Line2D Create(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept;

		constexpr ~Line2D() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Normal() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Normal() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& Distance() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Distance() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Line2D Flipped() const noexcept;
		constexpr void Flip() noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Distance(const Core::Vector2<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Project(const Core::Vector2<T>& point) const noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::int8_t Side(const Core::Vector2<T>& point) const noexcept;

		constexpr void Set(const Core::Vector2<T>& normal, T distance = T{0}) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Line2D<U>() const noexcept;

		constexpr Line2D& operator =(const Line2D& other) noexcept = default;
		constexpr Line2D& operator =(Line2D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Line2D& other) const noexcept = default;

	private:
		Core::Vector2<T> normal;
		T distance;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Line2D<T>& left, const Line2D<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Line2D<T>& line);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Line2D<T>::Line2D() noexcept :
		normal(Core::Vector2<T>::Predefined::Up),
		distance{0}
	{
	}

	template<std::floating_point T>
	constexpr Line2D<T>::Line2D(const Core::Vector2<T>& normal, T distance) noexcept :
		normal(normal),
		distance{distance}
	{
	}

	template<std::floating_point T>
	constexpr Line2D<T>::Line2D(const Core::Vector2<T>& normal, const Core::Vector2<T>& point) noexcept :
		normal(normal),
		distance{-Core::Dot(normal, point)}
	{
	}

	template<std::floating_point T>
	constexpr Line2D<T>::Line2D(const Ray2D<T>& ray) noexcept :
		normal(Core::Vector2<T>(-ray.Direction().Y(), ray.Direction().X())),
		distance(-Core::Dot(normal, ray.Origin()))
	{
	}

	template<std::floating_point T>
	constexpr Line2D<T>::Line2D(const Segment2D<T>& segment) noexcept :
		Line2D(Ray2D<T>(segment))
	{
	}

	template<std::floating_point T>
	constexpr Line2D<T> Line2D<T>::Create(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept
	{
		const Core::Vector2<T> inlineVector = point1 - point0;
		const Core::Vector2<T> normal = Core::Vector2<T>(-inlineVector.Y(), inlineVector.X()).Normalized();

		return Line2D(normal, point0);
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Line2D<T>::Normal() noexcept
	{
		return normal;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Line2D<T>::Normal() const noexcept
	{
		return normal;
	}

	template<std::floating_point T>
	constexpr T& Line2D<T>::Distance() noexcept
	{
		return distance;
	}

	template<std::floating_point T>
	constexpr const T& Line2D<T>::Distance() const noexcept
	{
		return distance;
	}

	template<std::floating_point T>
	constexpr Line2D<T> Line2D<T>::Flipped() const noexcept
	{
		return Line2D(-normal, -distance);
	}

	template<std::floating_point T>
	constexpr void Line2D<T>::Flip() noexcept
	{
		*this = Flipped();
	}

	template<std::floating_point T>
	bool Line2D<T>::IsFinite() const noexcept
	{
		return normal.IsFinite() && std::isfinite(distance);
	}

	template<std::floating_point T>
	constexpr T Line2D<T>::Distance(const Core::Vector2<T>& point) const noexcept
	{
		return Core::Dot(point, normal) + distance;
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> Line2D<T>::Project(const Core::Vector2<T>& point) const noexcept
	{
		return point - normal * Distance(point);
	}

	template<std::floating_point T>
	constexpr std::int8_t Line2D<T>::Side(const Core::Vector2<T>& point) const noexcept
	{
		return Core::Signum<T, std::int8_t>(Distance(point));
	}

	template<std::floating_point T>
	constexpr void Line2D<T>::Set(const Core::Vector2<T>& normal, const T distance) noexcept
	{
		this->normal = normal;
		this->distance = distance;
		this->distance = distance;
	}

	template<std::floating_point T>
	std::string Line2D<T>::ToString() const
	{
		return std::format("Normal: {}, Distance: {}", normal.ToString(), distance);
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Line2D<T>::operator Line2D<U>() const noexcept
	{
		return Line2D<U>(static_cast<Core::Vector2<U>>(normal), static_cast<U>(distance));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Line2D<T>& left, const Line2D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Normal(), right.Normal(), tolerance) && Core::AreAlmostEqual(left.Distance(), right.Distance(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Line2D<T>& line)
	{
		return stream << line.ToString();
	}
}
