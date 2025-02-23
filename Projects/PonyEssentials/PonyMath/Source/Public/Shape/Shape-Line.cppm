/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Line;

import <cmath>;
import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

import :Ray2D;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Line final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Line() noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line(const Core::Vector2<T>& normal, T distance = T{0}) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line(const Core::Vector2<T>& normal, const Core::Vector2<T>& point) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Line(const Ray2D<T>& ray) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Line(const Line& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Line(Line&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		static constexpr Line Create(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept;

		constexpr ~Line() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Normal() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Normal() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& Distance() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Distance() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Line Flipped() const noexcept;
		constexpr void Flip() noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Distance(const Core::Vector2<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Project(const Core::Vector2<T>& point) const noexcept;

		[[nodiscard("Pure function")]]
		constexpr std::int8_t Side(const Core::Vector2<T>& point) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Line<U>() const noexcept;

		constexpr Line& operator =(const Line& other) noexcept = default;
		constexpr Line& operator =(Line&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Line& other) const noexcept = default;

	private:
		Core::Vector2<T> normal;
		T distance;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Line<T>& left, const Line<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Line<T>& line);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Line<T>::Line() noexcept :
		normal(Core::Vector2<T>::Predefined::Up),
		distance{0}
	{
	}

	template<std::floating_point T>
	constexpr Line<T>::Line(const Core::Vector2<T>& normal, T distance) noexcept :
		normal(normal),
		distance{distance}
	{
	}

	template<std::floating_point T>
	constexpr Line<T>::Line(const Core::Vector2<T>& normal, const Core::Vector2<T>& point) noexcept :
		normal(normal),
		distance{-Core::Dot(normal, point)}
	{
	}

	template<std::floating_point T>
	constexpr Line<T>::Line(const Ray2D<T>& ray) noexcept :
		normal(Core::Vector2<T>(-ray.Direction().Y(), ray.Direction().X())),
		distance(-Core::Dot(normal, ray.Origin()))
	{
	}

	template<std::floating_point T>
	constexpr Line<T> Line<T>::Create(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept
	{
		const Core::Vector2<T> inlineVector = point1 - point0;
		const Core::Vector2<T> normal = Core::Vector2<T>(-inlineVector.Y(), inlineVector.X()).Normalized();

		return Line(normal, point0);
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Line<T>::Normal() noexcept
	{
		return normal;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Line<T>::Normal() const noexcept
	{
		return normal;
	}

	template<std::floating_point T>
	constexpr T& Line<T>::Distance() noexcept
	{
		return distance;
	}

	template<std::floating_point T>
	constexpr const T& Line<T>::Distance() const noexcept
	{
		return distance;
	}

	template<std::floating_point T>
	constexpr Line<T> Line<T>::Flipped() const noexcept
	{
		return Line(-normal, -distance);
	}

	template<std::floating_point T>
	constexpr void Line<T>::Flip() noexcept
	{
		*this = Flipped();
	}

	template<std::floating_point T>
	bool Line<T>::IsFinite() const noexcept
	{
		return normal.IsFinite() && std::isfinite(distance);
	}

	template<std::floating_point T>
	constexpr T Line<T>::Distance(const Core::Vector2<T>& point) const noexcept
	{
		return Core::Dot(point, normal) + distance;
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> Line<T>::Project(const Core::Vector2<T>& point) const noexcept
	{
		return point - normal * Distance(point);
	}

	template<std::floating_point T>
	constexpr std::int8_t Line<T>::Side(const Core::Vector2<T>& point) const noexcept
	{
		return Core::Signum<T, std::int8_t>(Distance(point));
	}

	template<std::floating_point T>
	std::string Line<T>::ToString() const
	{
		return std::format("Normal: {}, Distance: {}", normal.ToString(), distance);
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Line<T>::operator Line<U>() const noexcept
	{
		return Line<U>(static_cast<Core::Vector2<U>>(normal), static_cast<U>(distance));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Line<T>& left, const Line<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Normal(), right.Normal(), tolerance) && Core::AreAlmostEqual(left.Distance(), right.Distance(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Line<T>& line)
	{
		return stream << line.ToString();
	}
}
