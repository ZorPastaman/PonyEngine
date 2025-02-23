/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Ray2D;

import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Ray2D final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D(const Core::Vector2<T>& origin, const Core::Vector2<T>& direction) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D(const Ray2D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Ray2D(Ray2D&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		static constexpr Ray2D Create(const Core::Vector2<T>& origin, const Core::Vector2<T>& target) noexcept;

		constexpr ~Ray2D() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Origin() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector2<T>& Origin() const noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Core::Vector2<T>& Direction() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector2<T>& Direction() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Ray2D Flipped() const noexcept;
		constexpr void Flip() noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Normalize(const Core::Vector2<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Unnormalize(T value) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T NormalizeVector(const Core::Vector2<T>& vector) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> UnnormalizeVector(T value) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Ray2D<U>() const noexcept;

		constexpr Ray2D& operator =(const Ray2D& other) noexcept = default;
		constexpr Ray2D& operator =(Ray2D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Ray2D& other) const noexcept = default;

	private:
		Core::Vector2<T> origin;
		Core::Vector2<T> direction;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Ray2D<T>& left, const Ray2D<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray2D<T>& ray);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Ray2D<T>::Ray2D() noexcept :
		origin(Core::Vector2<T>::Predefined::Zero),
		direction(Core::Vector2<T>::Predefined::Right)
	{
	}

	template<std::floating_point T>
	constexpr Ray2D<T>::Ray2D(const Core::Vector2<T>& origin, const Core::Vector2<T>& direction) noexcept :
		origin(origin),
		direction(direction)
	{
	}

	template<std::floating_point T>
	constexpr Ray2D<T> Ray2D<T>::Create(const Core::Vector2<T>& origin, const Core::Vector2<T>& target) noexcept
	{
		return Ray2D(origin, (target - origin).Normalized());
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Ray2D<T>::Origin() noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Ray2D<T>::Origin() const noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T>& Ray2D<T>::Direction() noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& Ray2D<T>::Direction() const noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr Ray2D<T> Ray2D<T>::Flipped() const noexcept
	{
		return Ray2D(origin, -direction);
	}

	template<std::floating_point T>
	constexpr void Ray2D<T>::Flip() noexcept
	{
		*this = Flipped();
	}

	template<std::floating_point T>
	bool Ray2D<T>::IsFinite() const noexcept
	{
		return origin.IsFinite() && direction.IsFinite();
	}

	template<std::floating_point T>
	constexpr T Ray2D<T>::Normalize(const Core::Vector2<T>& point) const noexcept
	{
		return Core::Dot(direction, point - origin);
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> Ray2D<T>::Unnormalize(const T value) const noexcept
	{
		return origin + direction * value;
	}

	template<std::floating_point T>
	constexpr T Ray2D<T>::NormalizeVector(const Core::Vector2<T>& vector) const noexcept
	{
		return Core::Dot(direction, vector);
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> Ray2D<T>::UnnormalizeVector(const T value) const noexcept
	{
		return direction * value;
	}

	template<std::floating_point T>
	std::string Ray2D<T>::ToString() const
	{
		return std::format("Origin: {}, Direction: {}", origin.ToString(), direction.ToString());
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Ray2D<T>::operator Ray2D<U>() const noexcept
	{
		return Ray2D<U>(static_cast<Core::Vector2<U>>(origin), static_cast<Core::Vector2<U>>(direction));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Ray2D<T>& left, const Ray2D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Origin(), right.Origin(), tolerance) && Core::AreAlmostEqual(left.Direction(), right.Direction(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray2D<T>& ray)
	{
		return stream << ray.ToString();
	}
}
