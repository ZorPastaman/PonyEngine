/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:Box;

import std;

import PonyEngine.Type;

import :Common;
import :Matrix;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	class Box final
	{
	private:
		/// @brief Calculates corner count.
		/// @return Corner count.
		[[nodiscard("Pure function")]]
		static constexpr std::size_t CalculateCornerCount() noexcept;

	public:
		using ValueType = T; ///< Component type.
		using CenterType = Vector<T, Size>; ///< Center type.
		using ExtentsType = Vector<T, Size>; ///< Extents type.

		static constexpr std::size_t Dimension = Size; ///< Dimension.
		static constexpr Matrix<T, Size, Size> Axes = Matrix<T, Size, Size>::Identity(); ///< Axes.
		static constexpr std::size_t CornerCount = CalculateCornerCount(); ///< Corner count.

		using CornersType = std::array<Vector<T, Size>, CornerCount>; ///< Corners type.

		/// @brief Creates a zero box.
		[[nodiscard("Pure constructor")]]
		constexpr Box() noexcept = default;
		/// @brief Creates a box with a zero center.
		/// @param extents Extents.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Box(const Vector<T, Size>& extents) noexcept;
		/// @brief Creates a box.
		/// @param center Center.
		/// @param extents Extents.
		[[nodiscard("Pure constructor")]]
		constexpr Box(const Vector<T, Size>& center, const Vector<T, Size>& extents) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Box(const Box& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Box(Box&& other) noexcept = default;

		constexpr ~Box() noexcept = default;

		/// @brief Creates an axis-aligned bounding box.
		/// @param points Points to bound.
		/// @return Axis-aligned bounding box.
		[[nodiscard("Pure function")]]
		static constexpr Box CreateBounds(std::span<const Vector<T, Size>> points) noexcept;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, Size>& Center() const noexcept;
		/// @brief Sets the center.
		/// @param center Center.
		constexpr void Center(const Vector<T, Size>& center) noexcept;
		/// @brief Gets the extents.
		/// @return Extents.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, Size>& Extents() const noexcept;
		/// @brief Sets the extents.
		/// @param extents Extents.
		constexpr void Extents(const Vector<T, Size>& extents) noexcept;
		/// @brief Gets the extent.
		/// @param index Extent index. Must be in range [0, Size).
		/// @return Extent.
		[[nodiscard("Pure function")]]
		constexpr const T& Extent(std::size_t index) const noexcept;
		/// @brief Sets the extent.
		/// @param index Extent index. Must be in range [0, Size).
		/// @param extent Extent.
		constexpr void Extent(std::size_t index, T extent) noexcept;

		/// @brief Calculates the edge length.
		/// @param index Edge index. Must be in range [0, Size).
		/// @return Edge length.
		[[nodiscard("Pure function")]]
		constexpr T Edge(std::size_t index) const noexcept;
		/// @brief Calculates the edge lengths.
		/// @return Edge lengths.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Size> Edges() const noexcept;
		/// @brief Calculates a surface area.
		/// @return Surface area.
		[[nodiscard("Pure function")]]
		constexpr T Surface() const noexcept;
		/// @brief Calculates a volume.
		/// @return Volume.
		[[nodiscard("Pure function")]]
		constexpr T Volume() const noexcept;

		/// @brief Calculates a minimal value on an axis.
		/// @param index Axis index. Must be in range [0, Size).
		/// @return Minimal value.
		[[nodiscard("Pure function")]]
		constexpr T Min(std::size_t index) const noexcept;
		/// @brief Calculates a minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Size> Min() const noexcept;
		/// @brief Calculates a maximal value on an axis.
		/// @param index Axis index. Must be in range [0, Size).
		/// @return Maximal value.
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;
		/// @brief Calculates a maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Size> Max() const noexcept;
		/// @brief Calculates a corner.
		/// @param index Corner index. Must be in range [0, CornerCount).
		/// @return Corner.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Size> Corner(std::size_t index) const noexcept requires (Size <= std::numeric_limits<std::size_t>::digits);
		/// @brief Calculates corners.
		/// @return Corners.
		[[nodiscard("Pure function")]]
		constexpr CornersType Corners() const noexcept requires (Size <= std::numeric_limits<std::size_t>::digits);

		/// @brief Checks if all the data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the box contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Vector<T, Size>& point) const noexcept;
		/// @brief Calculates the closest point on the box.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the box, the @p point is returned.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Size> ClosestPoint(const Vector<T, Size>& point) const noexcept;

		/// @brief Creates a string representing the box.
		/// @return String representing the box.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts the box to a box of another type.
		/// @tparam U Target type.
		template<Type::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Box<U, Size>() const noexcept;

		constexpr Box& operator =(const Box& other) noexcept = default;
		constexpr Box& operator =(Box&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Box& other) const noexcept = default;

	private:
		Vector<T, Size> center; ///< Center.
		Vector<T, Size> extents; ///< Extents.
	};

	/// @brief Rectangle.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Rect = Box<T, 2>;
	/// @brief Cuboid.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using Cuboid = Box<T, 3>;

	/// @brief Checks if the two boxes are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left box.
	/// @param rhs Right box.
	/// @param tolerance Tolerance.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Box<T, Size>& lhs, const Box<T, Size>& rhs, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept;

	/// @brief Outputs a string representation of the @p box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param stream Target stream.
	/// @param box Input source.
	/// @return @p stream.
	template<Type::Arithmetic T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Box<T, Size>& box);
}

/// @brief Box formatter.
/// @tparam T Component type.
/// @tparam Size Dimension.
export template<PonyEngine::Type::Arithmetic T, std::size_t Size>
struct std::formatter<PonyEngine::Math::Box<T, Size>, char>
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

	static auto format(const PonyEngine::Math::Box<T, Size>& box, std::format_context& context)
	{
		return std::ranges::copy(box.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr std::size_t Box<T, Size>::CalculateCornerCount() noexcept
	{
		std::size_t cornerCount = 2uz;
		for (std::size_t i = 1uz; i < Size; ++i)
		{
			cornerCount *= 2uz;
		}

		return cornerCount;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Box<T, Size>::Box(const Vector<T, Size>& extents) noexcept :
		center(Vector<T, Size>::Zero()),
		extents(Abs(extents))
	{
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Box<T, Size>::Box(const Vector<T, Size>& center, const Vector<T, Size>& extents) noexcept :
		center(center),
		extents(Abs(extents))
	{
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Box<T, Size> Box<T, Size>::CreateBounds(const std::span<const Vector<T, Size>> points) noexcept
	{
		if (points.size() == 0uz) [[unlikely]]
		{
			return Box();
		}

		Vector<T, Size> min = points[0];
		Vector<T, Size> max = points[0];
		for (std::size_t i = 1uz; i < points.size(); ++i)
		{
			min = Math::Min(min, points[i]);
			max = Math::Max(max, points[i]);
		}

		using TimeType = std::conditional_t<std::is_floating_point_v<T>, T, double>;
		const Vector<T, Size> center = Lerp(min, max, TimeType{0.5});
		Vector<T, Size> extents;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			extents[i] = std::max(max[i] - center[i], center[i] - min[i]);
		}

		return Box(center, extents);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr const Vector<T, Size>& Box<T, Size>::Center() const noexcept
	{
		return center;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr void Box<T, Size>::Center(const Vector<T, Size>& center) noexcept
	{
		this->center = center;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr const Vector<T, Size>& Box<T, Size>::Extents() const noexcept
	{
		return extents;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr void Box<T, Size>::Extents(const Vector<T, Size>& extents) noexcept
	{
		this->extents = Abs(extents);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr const T& Box<T, Size>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr void Box<T, Size>::Extent(const std::size_t index, const T extent) noexcept
	{
		extents[index] = Abs(extent);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr T Box<T, Size>::Edge(const std::size_t index) const noexcept
	{
		return extents[index] * T{2};
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> Box<T, Size>::Edges() const noexcept
	{
		return extents * T{2};
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr T Box<T, Size>::Surface() const noexcept
	{
		T answer = T{0};
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			T product = T{1};
			for (std::size_t j = 0uz; j < i; ++j)
			{
				product *= Edge(j);
			}
			for (std::size_t j = i + 1uz; j < Size; ++j)
			{
				product *= Edge(j);
			}
			answer += product;
		}

		return answer * T{2};
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr T Box<T, Size>::Volume() const noexcept
	{
		T answer = T{1};
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer *= Edge(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr T Box<T, Size>::Min(const std::size_t index) const noexcept
	{
		return center[index] - extents[index];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> Box<T, Size>::Min() const noexcept
	{
		Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = Min(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr T Box<T, Size>::Max(const std::size_t index) const noexcept
	{
		return center[index] + extents[index];
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> Box<T, Size>::Max() const noexcept
	{
		Vector<T, Size> answer;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			answer[i] = Max(i);
		}

		return answer;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> Box<T, Size>::Corner(std::size_t index) const noexcept requires (Size <= std::numeric_limits<std::size_t>::digits)
	{
		Vector<T, Size> corner;
		for (std::size_t i = 0uz; i < Size; ++i, index >>= 1uz)
		{
			corner[i] = index & 1uz ? Max(i) : Min(i);
		}

		return corner;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Box<T, Size>::CornersType Box<T, Size>::Corners() const noexcept requires (Size <= std::numeric_limits<std::size_t>::digits)
	{
		std::array<Vector<T, Size>, CornerCount> corners;
		for (std::size_t i = 0uz; i < CornerCount; ++i)
		{
			corners[i] = Corner(i);
		}

		return corners;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr bool Box<T, Size>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return center.IsFinite() && extents.IsFinite();
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr bool Box<T, Size>::Contains(const Vector<T, Size>& point) const noexcept
	{
		for (std::size_t i = 0; i < Size; ++i)
		{
			if (Abs(point[i] - center[i]) > extents[i])
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> Box<T, Size>::ClosestPoint(const Vector<T, Size>& point) const noexcept
	{
		return Clamp(point, Min(), Max());
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	std::string Box<T, Size>::ToString() const
	{
		return std::format("Center: {}, Extents: {}", center, extents);
	}

	template<Type::Arithmetic T, std::size_t Size> requires (Size >= 1)
	template<Type::Arithmetic U>
	constexpr Box<T, Size>::operator Box<U, Size>() const noexcept
	{
		return Box<U, Size>(static_cast<Vector<U, Size>>(center), static_cast<Vector<U, Size>>(extents));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreAlmostEqual(const Box<T, Size>& lhs, const Box<T, Size>& rhs, const Tolerance<T>& tolerance) noexcept
	{
		return AreAlmostEqual(lhs.Center(), rhs.Center(), tolerance) && AreAlmostEqual(lhs.Extents(), rhs.Extents(), tolerance);
	}

	template<Type::Arithmetic T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const Box<T, Size>& box)
	{
		return stream << box.ToString();
	}
}
