/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:OrientedBox;

import std;

import :Box;
import :Common;
import :Matrix;
import :Transformations;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Oriented box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	class OrientedBox final
	{
	public:
		using ValueType = T; ///< Component type.
		using CenterType = Vector<T, Size>; ///< Center type.
		using ExtentsType = Vector<T, Size>; ///< Extents type.
		using AxisType = Vector<T, Size>; ///< Axis type.

		static constexpr std::size_t Dimension = Size; ///< Dimension.
		static constexpr std::size_t CornerCount = Box<T, Size>::CornerCount; ///< Corner count.

		using CornersType = std::array<Vector<T, Size>, CornerCount>; ///< Corners type.

		/// @brief Creates a zero oriented box.
		[[nodiscard("Pure constructor")]]
		constexpr OrientedBox() noexcept;
		/// @brief Creates an oriented box with a zero center and default axes.
		/// @param extents Extents.
		[[nodiscard("Pure constructor")]]
		explicit constexpr OrientedBox(const Vector<T, Size>& extents) noexcept;
		/// @brief Creates an oriented box with default axes.
		/// @param center Center.
		/// @param extents Extents.
		[[nodiscard("Pure constructor")]]
		constexpr OrientedBox(const Vector<T, Size>& center, const Vector<T, Size>& extents) noexcept;
		/// @brief Creates an oriented box.
		/// @param center Center.
		/// @param extents Extents.
		/// @param axes Axes. Must be mutually perpendicular. They are normalized automatically with a fallback to a zero vector.
		[[nodiscard("Pure constructor")]]
		OrientedBox(const Vector<T, Size>& center, const Vector<T, Size>& extents, const Matrix<T, Size, Size>& axes) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OrientedBox(const OrientedBox& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr OrientedBox(OrientedBox&& other) noexcept = default;

		constexpr ~OrientedBox() noexcept = default;

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
		/// @brief Gets the axes.
		/// @return Axes.
		[[nodiscard("Pure function")]]
		constexpr const Matrix<T, Size, Size>& Axes() const noexcept;
		/// @brief Sets the axes.
		/// @param axes Axes. Must be mutually perpendicular. They are normalized automatically with a fallback to a zero vector.
		void Axes(const Matrix<T, Size, Size>& axes) noexcept;
		/// @brief Gets the axis.
		/// @param index Axis index. Must be in range [0, Size).
		/// @return Axis.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, Size>& Axis(std::size_t index) const noexcept;
		/// @brief Sets the axis.
		/// @param index Axis index. Must be in range [0, Size).
		/// @param axis Axis. Must be perpendicular to other axes. It is normalized automatically with a fallback to a zero vector.
		void Axis(std::size_t index, const Vector<T, Size>& axis) noexcept;

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
		constexpr bool IsFinite() const noexcept;
		/// @brief Checks if all the axes are mutually perpendicular.
		/// @return @a True if they are mutually perpendicular; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool AreAxesPerpendicular() const noexcept;
		/// @brief Checks if at least one axis is zero.
		/// @return @a True if at least one axis is zero; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool HasZeroAxis() const noexcept;

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

		/// @brief Casts the oriented box to an oriented box of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator OrientedBox<U, Size>() const noexcept;

		OrientedBox& operator =(const OrientedBox& other) noexcept = default;
		OrientedBox& operator =(OrientedBox&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const OrientedBox& other) const noexcept = default;

	private:
		Vector<T, Size> center; ///< Center.
		Vector<T, Size> extents; ///< Extents.
		Matrix<T, Size, Size> axes; ///< Axes.
	};

	/// @brief Oriented rectangle.
	/// @tparam T Component type.
	template<std::floating_point T>
	using OrientedRect = OrientedBox<T, 2>;
	/// @brief Oriented cuboid.
	/// @tparam T Component type.
	template<std::floating_point T>
	using OrientedCuboid = OrientedBox<T, 3>;

	/// @brief Checks if the two oriented boxes are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left box.
	/// @param rhs Right box.
	/// @param tolerance Tolerance.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const OrientedBox<T, Size>& lhs, const OrientedBox<T, Size>& rhs, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept;

	/// @brief Outputs a string representation of the @p box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param stream Target stream.
	/// @param box Input source.
	/// @return @p stream.
	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const OrientedBox<T, Size>& box);
}

/// @brief Oriented box formatter.
/// @tparam T Component type.
/// @tparam Size Dimension.
export template<std::floating_point T, std::size_t Size>
struct std::formatter<PonyEngine::Math::OrientedBox<T, Size>, char>
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

	static auto format(const PonyEngine::Math::OrientedBox<T, Size>& box, std::format_context& context)
	{
		return std::ranges::copy(box.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr OrientedBox<T, Size>::OrientedBox() noexcept :
		center(Vector<T, Size>::Zero()),
		extents(Vector<T, Size>::Zero()),
		axes(Box<T, Size>::Axes)
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr OrientedBox<T, Size>::OrientedBox(const Vector<T, Size>& extents) noexcept :
		center(Vector<T, Size>::Zero()),
		extents(Abs(extents)),
		axes(Box<T, Size>::Axes)
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr OrientedBox<T, Size>::OrientedBox(const Vector<T, Size>& center, const Vector<T, Size>& extents) noexcept :
		center(center),
		extents(Abs(extents)),
		axes(Box<T, Size>::Axes)
	{
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	OrientedBox<T, Size>::OrientedBox(const Vector<T, Size>& center, const Vector<T, Size>& extents, const Matrix<T, Size, Size>& axes) noexcept :
		center(center),
		extents(Abs(extents))
	{
		Axes(axes);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr const Vector<T, Size>& OrientedBox<T, Size>::Center() const noexcept
	{
		return center;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr void OrientedBox<T, Size>::Center(const Vector<T, Size>& center) noexcept
	{
		this->center = center;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr const Vector<T, Size>& OrientedBox<T, Size>::Extents() const noexcept
	{
		return extents;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr void OrientedBox<T, Size>::Extents(const Vector<T, Size>& extents) noexcept
	{
		for (std::size_t i = 0; i < Size; ++i)
		{
			Extent(i, extents[i]);
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr const T& OrientedBox<T, Size>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr void OrientedBox<T, Size>::Extent(const std::size_t index, const T extent) noexcept
	{
		if (!axes.Column(index).IsZero()) [[likely]]
		{
			extents[index] = Abs(extent);
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr const Matrix<T, Size, Size>& OrientedBox<T, Size>::Axes() const noexcept
	{
		return axes;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void OrientedBox<T, Size>::Axes(const Matrix<T, Size, Size>& axes) noexcept
	{
		for (std::size_t i = 0; i < Size; ++i)
		{
			Axis(i, axes.Column(i));
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr const Vector<T, Size>& OrientedBox<T, Size>::Axis(const std::size_t index) const noexcept
	{
		return axes.Column(index);
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	void OrientedBox<T, Size>::Axis(const std::size_t index, const Vector<T, Size>& axis) noexcept
	{
		const T magnitude = axis.Magnitude();
		if (AreAlmostEqual(magnitude, T{0})) [[unlikely]]
		{
			extents[index] = T{0};
			axes.Column(index, Vector<T, Size>::Zero());
		}
		else [[likely]]
		{
			extents[index] *= magnitude;
			axes.Column(index, axis * (T{1} / magnitude));
		}
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr T OrientedBox<T, Size>::Edge(const std::size_t index) const noexcept
	{
		return extents[index] * T{2};
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> OrientedBox<T, Size>::Edges() const noexcept
	{
		return extents * T{2};
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr T OrientedBox<T, Size>::Surface() const noexcept
	{
		return Box<T, Size>(extents).Surface();
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr T OrientedBox<T, Size>::Volume() const noexcept
	{
		return Box<T, Size>(extents).Volume();
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> OrientedBox<T, Size>::Corner(std::size_t index) const noexcept requires (Size <= std::numeric_limits<std::size_t>::digits)
	{
		Vector<T, Size> delta;
		for (std::size_t i = 0uz; i < Size; ++i, index >>= 1uz)
		{
			delta[i] = index & 1uz ? extents[i] : -extents[i];
		}

		return center + axes * delta;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr OrientedBox<T, Size>::CornersType OrientedBox<T, Size>::Corners() const noexcept requires (Size <= std::numeric_limits<std::size_t>::digits)
	{
		std::array<Vector<T, Size>, CornerCount> corners;
		for (std::size_t i = 0uz; i < CornerCount; ++i)
		{
			corners[i] = Corner(i);
		}

		return corners;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr bool OrientedBox<T, Size>::IsFinite() const noexcept
	{
		return center.IsFinite() && extents.IsFinite() && axes.IsFinite();
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr bool OrientedBox<T, Size>::AreAxesPerpendicular() const noexcept
	{
		return AreAlmostEqual(Abs(axes.Determinant()), T{1});
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr bool OrientedBox<T, Size>::HasZeroAxis() const noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (axes.Column(i).IsAlmostZero())
			{
				return true;
			}
		}

		return false;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr bool OrientedBox<T, Size>::Contains(const Vector<T, Size>& point) const noexcept
	{
		const Vector<T, Size> delta = point - center;
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (Abs(Dot(delta, axes.Column(i))) > extents[i])
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	constexpr Vector<T, Size> OrientedBox<T, Size>::ClosestPoint(const Vector<T, Size>& point) const noexcept
	{
		const Vector<T, Size> delta = Clamp(TransformInverse(axes, point - center), -extents, extents);

		return center + axes * delta;
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	std::string OrientedBox<T, Size>::ToString() const
	{
		return std::format("Center: {}, Extents: {}, Axes: {}", center.ToString(), extents.ToString(), axes.Transpose().ToString());
	}

	template<std::floating_point T, std::size_t Size> requires (Size >= 1)
	template<std::floating_point U>
	constexpr OrientedBox<T, Size>::operator OrientedBox<U, Size>() const noexcept
	{
		return OrientedBox<U, Size>(static_cast<Vector<U, Size>>(center), static_cast<Vector<U, Size>>(extents), static_cast<Matrix<U, Size, Size>>(axes));
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreAlmostEqual(const OrientedBox<T, Size>& lhs, const OrientedBox<T, Size>& rhs, const Tolerance<T>& tolerance) noexcept
	{
		for (std::size_t i = 0uz; i < Size; ++i)
		{
			if (!AreAlmostEqual(std::min(std::abs(Dot(lhs.Axis(i), rhs.Axis(i))), T{1}), T{1}, tolerance))
			{
				return false;
			}
		}

		return AreAlmostEqual(lhs.Center(), rhs.Center(), tolerance) && AreAlmostEqual(lhs.Extents(), rhs.Extents(), tolerance);
	}

	template<std::floating_point T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const OrientedBox<T, Size>& box)
	{
		return stream << box.ToString();
	}
}
