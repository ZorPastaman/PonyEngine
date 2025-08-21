/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Flat;

import std;

import :Common;
import :Matrix;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Flat.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	class Flat final
	{
	public:
		using ValueType = T; ///< Component type.
		using NormalType = Vector<T, Size>; ///< Normal type.
		using DistanceType = T; ///< Distance type.

		static constexpr std::size_t Dimension = Size; ///< Dimension.

		/// @brief Creates a zero flat.
		[[nodiscard("Pure constructor")]]
		Flat() noexcept;
		/// @brief Creates a flat.
		/// @param normal Flat normal. It's normalized automatically with a fallback to a zero vector.
		/// @param distance Distance from the origin. If it's positive, the flat normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure constructor")]]
		explicit Flat(const Vector<T, Size>& normal, T distance = T{0}) noexcept;
		/// @brief Creates a flat that passes the @p point.
		/// @param normal Flat normal. It's normalized automatically with a fallback to a zero vector.
		/// @param point Point that is intersected by the flat.
		[[nodiscard("Pure constructor")]]
		Flat(const Vector<T, Size>& normal, const Vector<T, Size>& point) noexcept;
		[[nodiscard("Pure constructor")]]
		Flat(const Flat& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Flat(Flat&& other) noexcept = default;

		~Flat() noexcept = default;

		/// @brief Creates a flat that passes the points.
		/// @note The points must be unique.
		/// @note The vectors from the first point to the others must not be collinear.
		/// @param points Points.
		/// @return Flat.
		[[nodiscard("Pure function")]]
		static Flat CreateByPoints(std::span<const Vector<T, Size>, Size> points) noexcept;

		/// @brief Gets the normal.
		/// @return Normal.
		[[nodiscard("Pure function")]]
		const Vector<T, Size>& Normal() const noexcept;
		/// @brief Sets the normal.
		/// @param normal Normal. It's normalized automatically with a fallback to a zero vector.
		void Normal(const Vector<T, Size>& normal) noexcept;
		/// @brief Gets the flat distance from the origin.
		/// @return Distance from the origin. If it's positive, the flat normal looks at the origin; otherwise it looks away from it.
		[[nodiscard("Pure function")]]
		const T& Distance() const noexcept;
		/// @brief Sets the flat distance from the origin.
		/// @param distance Distance from the origin. If it's positive, the flat normal looks at the origin; otherwise it looks away from it.
		void Distance(T distance) noexcept;

		/// @brief Creates a flat which normal looks in the opposite direction.
		/// @return Flipped flat.
		[[nodiscard("Pure function")]]
		Flat Flipped() const noexcept;
		/// @brief Rotates the flat normal to the opposite direction.
		void Flip() noexcept;

		/// @brief Checks if all the components are finite.
		/// @return @a True if they are all finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Calculates a distance between the flat and the @p point.
		/// @param point Point.
		/// @return Distance between the flat and the @p point. It's positive if the point lies in the direction of the normal and negative otherwise.
		[[nodiscard("Pure function")]]
		T Distance(const Vector<T, Size>& point) const noexcept;
		/// @brief Projects the @p point onto the flat.
		/// @param point Point.
		/// @return Projected point.
		[[nodiscard("Pure function")]]
		Vector<T, Size> Project(const Vector<T, Size>& point) const noexcept;
		/// @brief Calculates a side of the @p point.
		/// @param point Point.
		/// @return 1 if the point lies in the direction of the normal; -1 if the point lies in the opposite direction; 0 is the point lies on the flat.
		[[nodiscard("Pure function")]]
		std::int8_t Side(const Vector<T, Size>& point) const noexcept;

		/// @brief Creates a string representing the flat.
		/// @return String representing the flat.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the flat to a flat of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit operator Flat<U, Size>() const noexcept;

		Flat& operator =(const Flat& other) noexcept = default;
		Flat& operator =(Flat&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const Flat& other) const noexcept = default;

	private:
		Vector<T, Size> normal; ///< Normal.
		T distance; ///< Distance from the origin. If it's positive, the normal looks at the origin; otherwise it looks away from it.
	};

	/// @brief Line.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Line = Flat<T, 2>;
	/// @brief Plane.
	/// @tparam T Component type.
	template<std::floating_point T>
	using Plane = Flat<T, 3>;

	/// @brief Checks if the two flats are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left flat.
	/// @param rhs Right flat.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	bool AreAlmostEqual(const Flat<T, Size>& lhs, const Flat<T, Size>& rhs, T tolerance = T{0.00001}) noexcept requires (Size >= 1);

	/// @brief Outputs a string representation of the @p flat.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param stream Target stream.
	/// @param flat Input source.
	/// @return @p stream.
	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Flat<T, Size>& flat) requires (Size >= 1);
}

/// @brief Flat formatter.
/// @tparam T Component type.
/// @tparam Size Dimension.
export template<std::floating_point T, std::size_t Size>
struct std::formatter<PonyEngine::Math::Flat<T, Size>, char>
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

	static auto format(const PonyEngine::Math::Flat<T, Size>& flat, std::format_context& context)
	{
		return std::ranges::copy(flat.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Flat<T, Size>::Flat() noexcept :
		normal(Vector<T, Size>::Zero()),
		distance{0}
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Flat<T, Size>::Flat(const Vector<T, Size>& normal, const T distance) noexcept :
		normal(normal.Normalized(Vector<T, Size>::Zero())),
		distance{distance}
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Flat<T, Size>::Flat(const Vector<T, Size>& normal, const Vector<T, Size>& point) noexcept :
		normal(normal.Normalized(Vector<T, Size>::Zero())),
		distance{-Dot(this->normal, point)}
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Flat<T, Size> Flat<T, Size>::CreateByPoints(const std::span<const Vector<T, Size>, Size> points) noexcept
	{
		if constexpr (Size == 1)
		{
			return Flat(Vector<T, Size>::One(), points[0]);
		}
		if constexpr (Size == 2)
		{
			return Flat(Rotate90CW(points[1] - points[0]), points[0]);
		}
		if constexpr (Size == 3)
		{
			return Flat(Cross(points[1] - points[0], points[2] - points[0]), points[0]);
		}
		else if constexpr (Size > 3)
		{
			Matrix<T, Size - 1, Size> matrix;
			for (std::size_t i = 1uz; i < Size; ++i)
			{
				matrix.Row(i - 1uz, points[i] - points[0]);
			}

			return Flat(matrix.CofactorVector(), points[0]);
		}
		else
		{
			return Flat();
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	const Vector<T, Size>& Flat<T, Size>::Normal() const noexcept
	{
		return normal;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void Flat<T, Size>::Normal(const Vector<T, Size>& normal) noexcept
	{
		this->normal = normal.Normalized(Vector<T, Size>::Zero());
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	const T& Flat<T, Size>::Distance() const noexcept
	{
		return distance;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void Flat<T, Size>::Distance(const T distance) noexcept
	{
		this->distance = distance;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Flat<T, Size> Flat<T, Size>::Flipped() const noexcept
	{
		Flat flipped;
		flipped.normal = -normal;
		flipped.distance = -distance;

		return flipped;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void Flat<T, Size>::Flip() noexcept
	{
		normal = -normal;
		distance = -distance;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	bool Flat<T, Size>::IsFinite() const noexcept
	{
		return normal.IsFinite() && Math::IsFinite(distance);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	T Flat<T, Size>::Distance(const Vector<T, Size>& point) const noexcept
	{
		return Dot(point, normal) + distance;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	Vector<T, Size> Flat<T, Size>::Project(const Vector<T, Size>& point) const noexcept
	{
		return point - normal * Distance(point);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	std::int8_t Flat<T, Size>::Side(const Vector<T, Size>& point) const noexcept
	{
		return Signum<std::int8_t>(Distance(point));
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	std::string Flat<T, Size>::ToString() const
	{
		return std::format("Normal: {}, Distance: {}", normal, distance);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	template<std::floating_point U>
	Flat<T, Size>::operator Flat<U, Size>() const noexcept
	{
		return Flat<U, Size>(static_cast<Vector<U, Size>>(normal), static_cast<U>(distance));
	}

	template<std::floating_point T, std::size_t Size>
	bool AreAlmostEqual(const Flat<T, Size>& lhs, const Flat<T, Size>& rhs, T tolerance) noexcept requires (Size >= 1)
	{
		return AreAlmostEqual(Dot(lhs.Normal(), rhs.Normal()), T{1}, tolerance) && AreAlmostEqual(lhs.Distance(), rhs.Distance(), tolerance);
	}

	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Flat<T, Size>& flat) requires (Size >= 1)
	{
		return stream << flat.ToString();
	}
}
