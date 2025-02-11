/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 3033-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:Ray3D;

import <concepts>;
import <format>;
import <string>;

import PonyMath.Core;

import :Segment3D;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class Ray3D final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr Ray3D(const Segment3D<T>& segment) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D(const Ray3D& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Ray3D(Ray3D&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		static constexpr Ray3D Create(const Core::Vector3<T>& origin, const Core::Vector3<T>& target) noexcept;

		constexpr ~Ray3D() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Origin() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector3<T>& Origin() const noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Core::Vector3<T>& Direction() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr const Core::Vector3<T>& Direction() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Ray3D Flipped() const noexcept;
		constexpr void Flip() noexcept;

		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Normalize(const Core::Vector3<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Unnormalize(T value) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T NormalizeVector(const Core::Vector3<T>& vector) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> UnnormalizeVector(T value) const noexcept;

		constexpr void Set(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction) noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Ray3D<U>() const noexcept;

		constexpr Ray3D& operator =(const Ray3D& other) noexcept = default;
		constexpr Ray3D& operator =(Ray3D&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Ray3D& other) const noexcept = default;

	private:
		Core::Vector3<T> origin;
		Core::Vector3<T> direction;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Ray3D<T>& left, const Ray3D<T>& right, T tolerance = T{ 0.00001 }) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray3D<T>& ray);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr Ray3D<T>::Ray3D() noexcept :
		origin(Core::Vector3<T>::Predefined::Zero),
		direction(Core::Vector3<T>::Predefined::Forward)
	{
	}

	template<std::floating_point T>
	constexpr Ray3D<T>::Ray3D(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction) noexcept :
		origin(origin),
		direction(direction)
	{
	}

	template<std::floating_point T>
	constexpr Ray3D<T>::Ray3D(const Segment3D<T>& segment) noexcept :
		origin(segment.Point0()),
		direction((segment.Point1() - segment.Point0()).Normalized())
	{
	}

	template<std::floating_point T>
	constexpr Ray3D<T> Ray3D<T>::Create(const Core::Vector3<T>& origin, const Core::Vector3<T>& target) noexcept
	{
		return Ray3D(origin, (target - origin).Normalized());
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Ray3D<T>::Origin() noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Ray3D<T>::Origin() const noexcept
	{
		return origin;
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& Ray3D<T>::Direction() noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& Ray3D<T>::Direction() const noexcept
	{
		return direction;
	}

	template<std::floating_point T>
	constexpr Ray3D<T> Ray3D<T>::Flipped() const noexcept
	{
		return Ray3D(origin, -direction);
	}

	template<std::floating_point T>
	constexpr void Ray3D<T>::Flip() noexcept
	{
		*this = Flipped();
	}

	template<std::floating_point T>
	bool Ray3D<T>::IsFinite() const noexcept
	{
		return origin.IsFinite() && direction.IsFinite();
	}

	template<std::floating_point T>
	constexpr T Ray3D<T>::Normalize(const Core::Vector3<T>& point) const noexcept
	{
		return Core::Dot(direction, point - origin);
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Ray3D<T>::Unnormalize(const T value) const noexcept
	{
		return origin + direction * value;
	}

	template<std::floating_point T>
	constexpr T Ray3D<T>::NormalizeVector(const Core::Vector3<T>& vector) const noexcept
	{
		return Core::Dot(direction, vector);
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> Ray3D<T>::UnnormalizeVector(const T value) const noexcept
	{
		return direction * value;
	}

	template<std::floating_point T>
	constexpr void Ray3D<T>::Set(const Core::Vector3<T>& origin, const Core::Vector3<T>& direction) noexcept
	{
		this->origin = origin;
		this->direction = direction;
	}

	template<std::floating_point T>
	std::string Ray3D<T>::ToString() const
	{
		return std::format("Origin: {}, Direction: {}", origin.ToString(), direction.ToString());
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr Ray3D<T>::operator Ray3D<U>() const noexcept
	{
		return Ray3D<U>(static_cast<Core::Vector3<U>>(origin), static_cast<Core::Vector3<U>>(direction));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Ray3D<T>& left, const Ray3D<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Origin(), right.Origin(), tolerance) && Core::AreAlmostEqual(left.Direction(), right.Direction(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Ray3D<T>& ray)
	{
		return stream << ray.ToString();
	}
}
