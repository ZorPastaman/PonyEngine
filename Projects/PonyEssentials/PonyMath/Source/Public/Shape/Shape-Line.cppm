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

export module PonyMath.Shape:Line;

import <cmath>;
import <concepts>;
import <cstdint>;
import <format>;
import <ostream>;
import <string>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief Line implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class Line final
	{
	public:
		using ValueType = T; ///< Component type.

		struct Predefined; ///< Predefined lines.

		/// @brief Create a horizontal line that passes through the origin.
		[[nodiscard("Pure constructor")]]
		constexpr Line() noexcept;
		/// @brief Creates a line.
		/// @param normal Line normal. Must be unit.
		/// @param distance Distance from the origin. If it's positive, the normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure constructor")]]
		constexpr Line(const Core::Vector2<T>& normal, T distance) noexcept;
		/// @brief Creates a line.
		/// @param normal Line normal. Must be unit.
		/// @param point Point that the line passes through.
		[[nodiscard("Pure constructor")]]
		constexpr Line(const Core::Vector2<T>& normal, const Core::Vector2<T>& point) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Line(const Line& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Line(Line&& other) noexcept = default;

		/// @brief Creates a line that passes through two points.
		/// @note The points must be different.
		/// @param point0 Point 0.
		/// @param point1 Point 1.
		/// @return Creates line.
		[[nodiscard("Pure function")]]
		static Line Create(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept;

		constexpr ~Line() noexcept = default;

		/// @brief Gets the line normal.
		/// @return Line normal. Must be unit.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Normal() noexcept;
		/// @brief Gets the line normal.
		/// @return Line normal.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Normal() const noexcept;
		/// @brief Gets the distance between the line and the origin.
		/// @return Distance between the line and the origin. If it's positive, the line normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure function")]]
		constexpr T& Distance() noexcept;
		/// @brief Gets the distance between the line and the origin.
		/// @return Distance between the line and the origin. If it's positive, the line normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure function")]]
		constexpr const T& Distance() const noexcept;

		/// @brief Creates a line which normal looks in the opposite direction.
		/// @return Flipped line.
		[[nodiscard("Pure function")]]
		constexpr Line Flipped() const noexcept;
		/// @brief Rotates the line normal to the opposite direction.
		constexpr void Flip() noexcept;

		/// @brief Checks if all the components are finite.
		/// @return @a True if they are all finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Calculates a distance between the line and the @p point.
		/// @param point Point.
		/// @return Distance between the line and the @p point. It's positive if the point lies in the direction of the normal and negative otherwise.
		[[nodiscard("Pure function")]]
		constexpr T Distance(const Core::Vector2<T>& point) const noexcept;
		/// @brief Projects the @p point onto the line.
		/// @param point Point.
		/// @return Projected point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Project(const Core::Vector2<T>& point) const noexcept;
		/// @brief Calculates a side of the @p point.
		/// @param point Point.
		/// @return 1 if the point lies in the direction of the normal; -1 if the point lies in the opposite direction; 0 is the point lies on the line.
		[[nodiscard("Pure function")]]
		constexpr std::int8_t Side(const Core::Vector2<T>& point) const noexcept;

		/// @brief Creates a string representing the line.
		/// @return String representing the line.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the line to a line of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Line<U>() const noexcept;

		constexpr Line& operator =(const Line& other) noexcept = default;
		constexpr Line& operator =(Line&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Line& other) const noexcept = default;

	private:
		Core::Vector2<T> normal; ///< Normal.
		T distance; ///< Distance between the line and the origin. If it's positive, the normal looks at the origin; otherwise it looks away from it.
	};

	/// @brief Checks if the two lines are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left line.
	/// @param right Right line.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Line<T>& left, const Line<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts line.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param line Source line.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const Line<T>& line);

	template<std::floating_point T>
	struct Line<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Up = Line(Core::Vector2<T>::Predefined::Up, T{0}); ///< Line(Up, 0).
		static constexpr auto Down = Line(Core::Vector2<T>::Predefined::Down, T{0}); ///< Line(Down, 0).
		static constexpr auto Right = Line(Core::Vector2<T>::Predefined::Right, T{0}); ///< Line(Right, 0).
		static constexpr auto Left = Line(Core::Vector2<T>::Predefined::Left, T{0}); ///< Line(Left, 0).
	};
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
	constexpr Line<T>::Line(const Core::Vector2<T>& normal, const T distance) noexcept :
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
	Line<T> Line<T>::Create(const Core::Vector2<T>& point0, const Core::Vector2<T>& point1) noexcept
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
		return Core::Signum<std::int8_t>(Distance(point));
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
