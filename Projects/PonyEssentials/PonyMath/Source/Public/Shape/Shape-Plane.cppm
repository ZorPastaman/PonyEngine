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
import <cstdint>;
import <concepts>;
import <format>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief Plane implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Plane final
	{
	public:
		using ValueType = T; ///< Value type.

		/// @brief Creates a plane passes the origin and which normal looks forward.
		[[nodiscard("Pure constructor")]]
		constexpr Plane() noexcept;
		/// @brief Creates a plane.
		/// @param normal Plane normal. Must be unit.
		/// @param distance Distance from the origin. If it's positive, the plane normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Plane(const Core::Vector3<T>& normal, T distance = T{0}) noexcept;
		/// @brief Creates a plane that passes the @p point.
		/// @param normal Plane normal. Must be unit.
		/// @param point Point that is intersected by the plane.
		[[nodiscard("Pure constructor")]]
		constexpr Plane(const Core::Vector3<T>& normal, const Core::Vector3<T>& point) noexcept;
		/// @brief Creates a plane that passes the three points.
		/// @note The points must be different.
		/// @param point0 Point0.
		/// @param point1 Point1.
		/// @param point2 Point2.
		[[nodiscard("Pure constructor")]]
		Plane(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1, const Core::Vector3<T>& point2) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Plane(const Plane& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Plane(Plane&& other) noexcept = default;

		constexpr ~Plane() noexcept = default;

		/// @brief Gets the normal.
		/// @return Normal. Must be unit.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Normal() noexcept;
		/// @brief Gets the normal.
		/// @return Normal.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Normal() const noexcept;
		/// @brief Gets the plane distance from the origin.
		/// @return Distance from the origin. If it's positive, the plane normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure function")]]
		constexpr T& Distance() noexcept;
		/// @brief Gets the plane distance from the origin.
		/// @return Distance from the origin. If it's positive, the plane normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure function")]]
		constexpr const T& Distance() const noexcept;

		/// @brief Creates a plane which normal looks in the opposite direction.
		/// @return Flipped plane.
		[[nodiscard("Pure function")]]
		constexpr Plane Flipped() const noexcept;
		/// @brief Rotates the plane normal to the opposite direction.
		constexpr void Flip() noexcept;

		/// @brief Checks if all the components are finite.
		/// @return @a True if they are all finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Calculates a distance between the plane and the @p point.
		/// @param point Point.
		/// @return Distance between the plane and the @p point. It's positive if the point lies in the direction of the normal and negative otherwise.
		[[nodiscard("Pure function")]]
		constexpr T Distance(const Core::Vector3<T>& point) const noexcept;
		/// @brief Projects the @p point onto the plane.
		/// @param point Point.
		/// @return Projected point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Project(const Core::Vector3<T>& point) const noexcept;
		/// @brief Calculates a side of the @p point.
		/// @param point Point.
		/// @return 1 if the point lies in the direction of the normal; -1 if the point lies in the opposite direction; 0 is the point lies on the plane.
		[[nodiscard("Pure function")]]
		constexpr std::int8_t Side(const Core::Vector3<T>& point) const noexcept;

		/// @brief Creates a string representing the plane.
		/// @return String representing the plane.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the plane to a plane of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Plane<U>() const noexcept;

		constexpr Plane& operator =(const Plane& other) noexcept = default;
		constexpr Plane& operator =(Plane&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Plane& other) const noexcept = default;

	private:
		Core::Vector3<T> normal; ///< Normal.
		T distance; ///< Distance from the origin. If it's positive, the normal looks at the origin; otherwise it looks away from it.
	};

	/// @brief Checks if the two planes are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left plane.
	/// @param right Right plane.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Plane<T>& left, const Plane<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts plane.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param plane Source plane.
	/// @return @p stream.
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
	Plane<T>::Plane(const Core::Vector3<T>& point0, const Core::Vector3<T>& point1, const Core::Vector3<T>& point2) noexcept :
		Plane(Core::Cross(point1 - point0, point2 - point0).Normalized(), point0)
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
		return Core::Signum<std::int8_t>(Distance(point));
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
	bool AreAlmostEqual(const Plane<T>& left, const Plane<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Normal(), right.Normal(), tolerance) && Core::AreAlmostEqual(left.Distance(), right.Distance(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Plane<T>& plane)
	{
		return stream << plane.ToString();
	}
}
