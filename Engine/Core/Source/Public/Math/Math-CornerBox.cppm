/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Math:CornerBox;

import std;

import PonyEngine.Type;

import :Box;
import :Common;
import :Vector;

export namespace PonyEngine::Math
{
	/// @brief Box which origin is minimal point.
	/// @tparam T Component type.
	/// @tparam Dim Dimension.
	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	class CornerBox final
	{
	public:
		using ValueType = T; ///< Component type.
		using PositionType = Vector<T, Dim>; ///< Position type.
		using SizeType = Vector<T, Dim>; ///< Dim type.

		static constexpr std::size_t Dimension = Dim; ///< Dimension.
		static constexpr std::size_t CornerCount = Box<T, Dim>::CornerCount; ///< Corner count.

		using CornersType = std::array<Vector<T, Dim>, CornerCount>; ///< Corners type.

		/// @brief Creates a zero box.
		[[nodiscard("Pure constructor")]]
		constexpr CornerBox() noexcept = default;
		/// @brief Creates a box with a zero center.
		/// @param size Dim.
		[[nodiscard("Pure constructor")]]
		explicit constexpr CornerBox(const Vector<T, Dim>& size) noexcept;
		/// @brief Creates a box.
		/// @param position Position.
		/// @param size Dim.
		[[nodiscard("Pure constructor")]]
		constexpr CornerBox(const Vector<T, Dim>& position, const Vector<T, Dim>& size) noexcept;
		/// @brief Creates a corner box from a normal box.
		/// @param box Box.
		[[nodiscard("Pure constructor")]]
		explicit constexpr CornerBox(const Box<T, Dim>& box) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr CornerBox(const CornerBox& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr CornerBox(CornerBox&& other) noexcept = default;

		constexpr ~CornerBox() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, Dim>& Position() const noexcept;
		/// @brief Sets the position.
		/// @param position Position.
		constexpr void Position(const Vector<T, Dim>& position) noexcept;
		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr const Vector<T, Dim>& Size() const noexcept;
		/// @brief Sets the size.
		/// @param size Dim.
		constexpr void Size(const Vector<T, Dim>& size) noexcept;

		/// @brief Calculates a surface area.
		/// @return Surface area.
		[[nodiscard("Pure function")]]
		constexpr T Surface() const noexcept;
		/// @brief Calculates a volume.
		/// @return Volume.
		[[nodiscard("Pure function")]]
		constexpr T Volume() const noexcept;

		/// @brief Calculates a minimal value on an axis.
		/// @param index Axis index. Must be in range [0, Dim).
		/// @return Minimal value.
		[[nodiscard("Pure function")]]
		constexpr T Min(std::size_t index) const noexcept;
		/// @brief Calculates a minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Dim> Min() const noexcept;
		/// @brief Calculates a maximal value on an axis.
		/// @param index Axis index. Must be in range [0, Dim).
		/// @return Maximal value.
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;
		/// @brief Calculates a maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Dim> Max() const noexcept;
		/// @brief Calculates a corner.
		/// @param index Corner index. Must be in range [0, CornerCount).
		/// @return Corner.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Dim> Corner(std::size_t index) const noexcept requires (Dim <= std::numeric_limits<std::size_t>::digits);
		/// @brief Calculates corners.
		/// @return Corners.
		[[nodiscard("Pure function")]]
		constexpr CornersType Corners() const noexcept requires (Dim <= std::numeric_limits<std::size_t>::digits);

		/// @brief Changes the box so that its size becomes positive and its space stays the same.
		constexpr void ResolveNegativeSize() noexcept;

		/// @brief Checks if all the data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the box contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Vector<T, Dim>& point) const noexcept;
		/// @brief Calculates the closest point on the box.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the box, the @p point is returned.
		[[nodiscard("Pure function")]]
		constexpr Vector<T, Dim> ClosestPoint(const Vector<T, Dim>& point) const noexcept;

		/// @brief Creates a string representing the box.
		/// @return String representing the box.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Casts the box to a box of another type.
		/// @tparam U Target type.
		template<Type::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator CornerBox<U, Dim>() const noexcept;
		/// @brief Casts the box to a box of another type.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Box<T, Dim>() const noexcept;

		constexpr CornerBox& operator =(const CornerBox& other) noexcept = default;
		constexpr CornerBox& operator =(CornerBox&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const CornerBox& other) const noexcept = default;

	private:
		Vector<T, Dim> position; ///< Position.
		Vector<T, Dim> size; ///< Dim.
	};

	/// @brief Corner rectangle.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using CornerRect = CornerBox<T, 2>;
	/// @brief Corner cuboid.
	/// @tparam T Component type.
	template<Type::Arithmetic T>
	using CornerCuboid = CornerBox<T, 3>;

	/// @brief Checks if the two boxes are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param lhs Left box.
	/// @param rhs Right box.
	/// @param tolerance Tolerance.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T, std::size_t Size> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const CornerBox<T, Size>& lhs, const CornerBox<T, Size>& rhs, const Tolerance<T>& tolerance = Tolerance<T>()) noexcept;

	/// @brief Outputs a string representation of the @p box.
	/// @tparam T Component type.
	/// @tparam Size Dimension.
	/// @param stream Target stream.
	/// @param box Input source.
	/// @return @p stream.
	template<Type::Arithmetic T, std::size_t Size>
	std::ostream& operator <<(std::ostream& stream, const CornerBox<T, Size>& box);
}

/// @brief Box formatter.
/// @tparam T Component type.
/// @tparam Size Dimension.
export template<PonyEngine::Type::Arithmetic T, std::size_t Size>
struct std::formatter<PonyEngine::Math::CornerBox<T, Size>, char>
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

	static auto format(const PonyEngine::Math::CornerBox<T, Size>& box, std::format_context& context)
	{
		return std::ranges::copy(box.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Math
{
	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr CornerBox<T, Dim>::CornerBox(const Vector<T, Dim>& size) noexcept :
		position(Vector<T, Dim>::Zero()),
		size(size)
	{
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr CornerBox<T, Dim>::CornerBox(const Vector<T, Dim>& position, const Vector<T, Dim>& size) noexcept :
		position(position),
		size(size)
	{
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr CornerBox<T, Dim>::CornerBox(const Box<T, Dim>& box) noexcept :
		position(box.Min()),
		size(box.Edges())
	{
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr const Vector<T, Dim>& CornerBox<T, Dim>::Position() const noexcept
	{
		return position;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr void CornerBox<T, Dim>::Position(const Vector<T, Dim>& position) noexcept
	{
		this->position = position;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr const Vector<T, Dim>& CornerBox<T, Dim>::Size() const noexcept
	{
		return size;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr void CornerBox<T, Dim>::Size(const Vector<T, Dim>& size) noexcept
	{
		this->size = size;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr T CornerBox<T, Dim>::Surface() const noexcept
	{
		return Box<T, Dim>(Abs(size / T{2})).Surface();
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr T CornerBox<T, Dim>::Volume() const noexcept
	{
		return Box<T, Dim>(Abs(size / T{2})).Volume();
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr T CornerBox<T, Dim>::Min(const std::size_t index) const noexcept
	{
		return position[index];
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr Vector<T, Dim> CornerBox<T, Dim>::Min() const noexcept
	{
		return position;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr T CornerBox<T, Dim>::Max(const std::size_t index) const noexcept
	{
		return position[index] + size[index];
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr Vector<T, Dim> CornerBox<T, Dim>::Max() const noexcept
	{
		return position + size;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr Vector<T, Dim> CornerBox<T, Dim>::Corner(std::size_t index) const noexcept requires (Dim <= std::numeric_limits<std::size_t>::digits)
	{
		Vector<T, Dim> corner;
		for (std::size_t i = 0uz; i < Dim; ++i, index >>= 1uz)
		{
			corner[i] = index & 1uz ? Max(i) : Min(i);
		}

		return corner;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr CornerBox<T, Dim>::CornersType CornerBox<T, Dim>::Corners() const noexcept requires (Dim <= std::numeric_limits<std::size_t>::digits)
	{
		const Vector<T, Dim> min = Min();
		const Vector<T, Dim> max = Max();

		std::array<Vector<T, Dim>, CornerCount> corners;
		for (std::size_t i = 0uz; i < CornerCount; ++i)
		{
			Vector<T, Dim>& corner = corners[i];
			for (std::size_t j = 0uz, index = i; j < Dim; ++j, index >>= 1uz)
			{
				corner[j] = index & 1uz ? max[j] : min[j];
			}
		}

		return corners;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr void CornerBox<T, Dim>::ResolveNegativeSize() noexcept
	{
		for (std::size_t i = 0; i < Dim; ++i)
		{
			position[i] = std::min(position[i], position[i] + size[i]);
			size[i] = Abs(size[i]);
		}
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr bool CornerBox<T, Dim>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return position.IsFinite() && size.IsFinite();
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr bool CornerBox<T, Dim>::Contains(const Vector<T, Dim>& point) const noexcept
	{
		for (std::size_t i = 0; i < Dim; ++i)
		{
			if (point[i] < position[i] || point[i] > position[i] + size[i])
			{
				return false;
			}
		}

		return true;
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr Vector<T, Dim> CornerBox<T, Dim>::ClosestPoint(const Vector<T, Dim>& point) const noexcept
	{
		const Vector<T, Dim> min = Min();
		const Vector<T, Dim> max = Max();

		return Clamp(point, Math::Min(min, max), Math::Max(min, max));
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	std::string CornerBox<T, Dim>::ToString() const
	{
		return std::format("Position: {}, Size: {}", position, size);
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	template<Type::Arithmetic U>
	constexpr CornerBox<T, Dim>::operator CornerBox<U, Dim>() const noexcept
	{
		return CornerBox<U, Dim>(static_cast<Vector<U, Dim>>(position), static_cast<Vector<U, Dim>>(size));
	}

	template<Type::Arithmetic T, std::size_t Dim> requires (Dim >= 1)
	constexpr CornerBox<T, Dim>::operator Box<T, Dim>() const noexcept
	{
		const Vector<T, Dim> extents = size / T{2};
		return Box<T, Dim>(position + extents, extents);
	}

	template<std::floating_point T, std::size_t Size>
	constexpr bool AreAlmostEqual(const CornerBox<T, Size>& lhs, const CornerBox<T, Size>& rhs, const Tolerance<T>& tolerance) noexcept
	{
		return AreAlmostEqual(lhs.Position(), rhs.Position(), tolerance) && AreAlmostEqual(lhs.Size(), rhs.Size(), tolerance);
	}

	template<Type::Arithmetic T, std::size_t Size>
	std::ostream& operator<<(std::ostream& stream, const CornerBox<T, Size>& box)
	{
		return stream << box.ToString();
	}
}
