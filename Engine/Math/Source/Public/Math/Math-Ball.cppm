/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Ball;

import std;

import :Common;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Ball.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	class Ball final
	{
	public:
		using ValueType = T; ///< Component type.
		using CenterType = Vector<T, Size>; ///< Center type.
		using RadiusType = T; ///< Radius type.

		static constexpr std::size_t Dimension = Size; ///< Dimension.

		/// @brief Creates a zero ball.
		[[nodiscard("Pure constructor")]]
		constexpr Ball() noexcept = default;
		/// @brief Creates a ball with a zero center.
		/// @param radius Radius.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Ball(T radius) noexcept;
		/// @brief Creates a ball.
		/// @param center Center.
		/// @param radius Radius.
		[[nodiscard("Pure constructor")]]
		constexpr Ball(const Vector<T, Size>& center, T radius) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Ball(const Ball& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Ball(Ball&& other) noexcept = default;

		constexpr ~Ball() noexcept = default;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, Size>& Center() const noexcept;
		/// @brief Sets the center.
		/// @param center Center.
		constexpr void Center(const Vector<T, Size>& center) noexcept;
		/// @brief Gets the radius.
		/// @return Radius.
		[[nodiscard("Pure function")]]
		constexpr const T& Radius() const noexcept;
		/// @brief Sets the radius.
		/// @param radius Radius.
		constexpr void Radius(T radius) noexcept;

		/// @brief Calculates a diameter.
		/// @return Diameter.
		[[nodiscard("Pure function")]]
		constexpr T Diameter() const noexcept;

		/// @brief Calculates a surface area.
		/// @return Surface area.
		[[nodiscard("Pure function")]]
		T Surface() const noexcept;
		/// @brief Calculates a volume.
		/// @return Volume.
		[[nodiscard("Pure function")]]
		T Volume() const noexcept;

		/// @brief Checks if all the data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept;

		/// @brief Checks if the ball contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Vector<T, Size>& point) const noexcept;
		/// @brief Calculates the closest point on the ball.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the ball, the @p point is returned.
		[[nodiscard("Pure function")]]
		Vector<T, Size> ClosestPoint(const Vector<T, Size>& point) const noexcept;

		/// @brief Creates a string representing the ball.
		/// @return String representing the ball.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts the ball to a ball of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Ball<U, Size>() const noexcept;

		constexpr Ball& operator =(const Ball& other) noexcept = default;
		constexpr Ball& operator =(Ball&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Ball& other) const noexcept = default;

	private:
		/// @brief Surface coefficient for the ball.
		inline static const T SurfaceCoefficient = T{2} * std::pow(std::numbers::pi_v<T>, static_cast<T>(Size / T{2})) / std::tgamma(static_cast<T>(Size / T{2}));
		/// @brief Volume coefficient for the ball.
		inline static const T VolumeCoefficient = std::pow(std::numbers::pi_v<T>, static_cast<T>(Size / T{2})) / std::tgamma(static_cast<T>(Size / T{2} + T{1}));

		Vector<T, Size> center; ///< Ball center.
		T radius; ///< Ball radius.
	};

	/// @brief Interval.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Interval = Ball<T, 1>;
	/// @brief Circle.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Circle = Ball<T, 2>;
	/// @brief Sphere.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Sphere = Ball<T, 3>;

	/// @brief Checks if the two balls are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left ball.
	/// @param rhs Right ball.
	/// @param tolerance Tolerance.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Ball<T, Size>& lhs, const Ball<T, Size>& rhs, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept requires (Size >= 1);

	/// @brief Outputs a string representation of the @p ball.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param stream Target stream.
	/// @param ball Input source.
	/// @return @p stream.
	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Ball<T, Size>& ball) requires (Size >= 1);
}

/// @brief Ball formatter.
/// @tparam T Component type.
/// @tparam Size Dimension.
export template<std::floating_point T, std::size_t Size>
struct std::formatter<PonyEngine::Math::Ball<T, Size>, char>
{
	static constexpr auto parse(std::format_parse_context& context)
	{
		if (context.begin() == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end.");
		}
		if (*context.begin() != '}') [[unlikely]]
		{
			throw std::format_error("Unexpected format specifier.");
		}

		return context.begin();
	}

	static auto format(const PonyEngine::Math::Ball<T, Size>& ball, std::format_context& context)
	{
		return std::ranges::copy(ball.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr Ball<T, Size>::Ball(const T radius) noexcept :
		center(Vector<T, Size>::Zero()),
		radius{Abs(radius)}
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr Ball<T, Size>::Ball(const Vector<T, Size>& center, const T radius) noexcept :
		center(center),
		radius{Abs(radius)}
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr const Vector<T, Size>& Ball<T, Size>::Center() const noexcept
	{
		return center;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr void Ball<T, Size>::Center(const Vector<T, Size>& center) noexcept
	{
		this->center = center;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr const T& Ball<T, Size>::Radius() const noexcept
	{
		return radius;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr void Ball<T, Size>::Radius(const T radius) noexcept
	{
		this->radius = Abs(radius);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr T Ball<T, Size>::Diameter() const noexcept
	{
		return radius * T{2};
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	T Ball<T, Size>::Surface() const noexcept
	{
		if constexpr (Size == 1)
		{
			return SurfaceCoefficient;
		}
		else if constexpr (Size == 2)
		{
			return SurfaceCoefficient * radius;
		}
		else if constexpr (Size == 3)
		{
			return SurfaceCoefficient * radius * radius;
		}
		else
		{
			return SurfaceCoefficient * std::pow(radius, static_cast<T>(Size - T{1}));
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	T Ball<T, Size>::Volume() const noexcept
	{
		if constexpr (Size == 1)
		{
			return VolumeCoefficient * radius;
		}
		else if constexpr (Size == 2)
		{
			return VolumeCoefficient * radius * radius;
		}
		else if constexpr (Size == 3)
		{
			return VolumeCoefficient * radius * radius * radius;
		}
		else
		{
			return VolumeCoefficient * std::pow(radius, static_cast<T>(Size));
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr bool Ball<T, Size>::IsFinite() const noexcept
	{
		return center.IsFinite() && Math::IsFinite(radius);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr bool Ball<T, Size>::Contains(const Vector<T, Size>& point) const noexcept
	{
		return DistanceSquared(point, center) <= radius * radius;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Vector<T, Size> Ball<T, Size>::ClosestPoint(const Vector<T, Size>& point) const noexcept
	{
		return ClampMagnitude(point - center, radius) + center;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	std::string Ball<T, Size>::ToString() const
	{
		return std::format("Center: {}, Radius: {}", center, radius);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	template<std::floating_point U>
	constexpr Ball<T, Size>::operator Ball<U, Size>() const noexcept
	{
		return Ball<U, Size>(static_cast<Vector<U, Size>>(center), static_cast<U>(radius));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreAlmostEqual(const Ball<T, Size>& lhs, const Ball<T, Size>& rhs, const Tolerance<T>& tolerance) noexcept requires (Size >= 1)
	{
		return AreAlmostEqual(lhs.Center(), rhs.Center(), tolerance) && AreAlmostEqual(lhs.Radius(), rhs.Radius(), tolerance);
	}

	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Ball<T, Size>& ball) requires (Size >= 1)
	{
		return stream << ball.ToString();
	}
}
