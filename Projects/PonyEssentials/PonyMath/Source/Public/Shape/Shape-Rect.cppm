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

export module PonyMath.Shape:Rect;

import <array>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief Rectangle implementation.
	/// @tparam T Component type.
	template<Core::Arithmetic T>
	class Rect final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t LeftBottomIndex = 0; ///< (MinX, MinY) corner index.
		static constexpr std::size_t RightBottomIndex = 1; ///< (MaxX, MinY) corner index.
		static constexpr std::size_t LeftTopIndex = 2; ///< (MinX, MaxY) corner index.
		static constexpr std::size_t RightTopIndex = 3; ///< (MaxX, MaxY) corner index.
		static constexpr std::size_t CornerCount = 4; ///< Corner count.

		struct Predefined; ///< Predefined rects.

		/// @brief Creates a zero rect.
		[[nodiscard("Pure constructor")]]
		constexpr Rect() noexcept = default;
		/// @brief Creates a rect.
		/// @param x X position. It's a minimal point on an x-axis.
		/// @param y Y position. It's a minimal point on a y-axis.
		/// @param width Rect width. Must be non-negative.
		/// @param height Rect height. Must be non-negative.
		[[nodiscard("Pure constructor")]]
		constexpr Rect(T x, T y, T width, T height) noexcept;
		/// @brief Creates a rect.
		/// @param position Rect position. It's its minimal point.
		/// @param size Rect size. Both coordinates must be non-negative.
		[[nodiscard("Pure constructor")]]
		constexpr Rect(const Core::Vector2<T>& position, const Core::Vector2<T>& size) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Rect(const Rect& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Rect(Rect&& other) noexcept = default;

		constexpr ~Rect() noexcept = default;

		/// @brief Gets the position (minX, minY).
		/// @return Position.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Position() noexcept;
		/// @brief Gets the position (minX, minY).
		/// @return Position.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Position() const noexcept;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Size() noexcept;
		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Size() const noexcept;

		/// @brief Gets the minimal x point.
		/// @return Minimal x.
		[[nodiscard("Pure function")]]
		constexpr T MinX() const noexcept;
		/// @brief Gets the minimal y point.
		/// @return Minimal y.
		[[nodiscard("Pure function")]]
		constexpr T MinY() const noexcept;
		/// @brief Gets the minimal point component by the @p index.
		/// @param index Point component index. 0 -> x, 1 -> y.
		/// @return Minimal point component.
		[[nodiscard("Pure function")]]
		constexpr T Min(std::size_t index) const noexcept;
		/// @brief Gets the minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Min() const noexcept;
		/// @brief Sets the minimal x point keeping the max point.
		/// @param minX Minimal x point to set.
		constexpr void MinX(T minX) noexcept;
		/// @brief Sets the minimal y point keeping the max point.
		/// @param minY Minimal y point to set.
		constexpr void MinY(T minY) noexcept;
		/// @brief Sets the minimal point component by the @p index.
		/// @param index Point component index. 0 -> x, 1 -> y.
		/// @param min Minimal component.
		constexpr void Min(std::size_t index, T min) noexcept;
		/// @brief Sets the minimal point keeping the max point.
		/// @param min Minimal point to set.
		constexpr void Min(const Core::Vector2<T>& min) noexcept;

		/// @brief Gets the maximal x point.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxX() const noexcept;
		/// @brief Gets the maximal x point.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxY() const noexcept;
		/// @brief Gets the maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Max() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;
		/// @brief Sets the maximal x point keeping the min point.
		/// @param maxX Maximal x point to set.
		constexpr void MaxX(T maxX) noexcept;
		/// @brief Sets the maximal y point keeping the min point.
		/// @param maxY Maximal y point to set.
		constexpr void MaxY(T maxY) noexcept;
		/// @brief Sets the maximal point keeping the min point.
		/// @param max Maximal point to set.
		constexpr void Max(const Core::Vector2<T>& max) noexcept;
		constexpr void Max(std::size_t index, T max) noexcept;

		/// @brief Gets the width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		/// @brief Sets the width.
		/// @tparam KeepCenter If it's @a true, both the position and size are changed to keep the center the same; if it's @a false, the width is changed only.
		/// @param width Width to set.
		template<bool KeepCenter = false>
		constexpr void Width(T width) noexcept;
		/// @brief Gets the height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		/// @brief Sets the height.
		/// @tparam KeepCenter If it's @a true, both the position and size are changed to keep the center the same; if it's @a false, the height is changed only.
		/// @param height Height to set.
		template<bool KeepCenter = false>
		constexpr void Height(T height) noexcept;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Center() const noexcept;
		/// @brief Sets the center keeping the size.
		/// @param center Center to set.
		constexpr void Center(const Core::Vector2<T>& center) noexcept;

		/// @brief Gets the (MinX, MinY) point.
		/// @return Left bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> LeftBottom() const noexcept;
		/// @brief Gets the (MaxX, MinY) point.
		/// @return Left bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> RightBottom() const noexcept;
		/// @brief Gets the (MinX, MaxY) point.
		/// @return Left bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> LeftTop() const noexcept;
		/// @brief Gets the (MaxX, MaxY) point.
		/// @return Left bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> RightTop() const noexcept;
		/// @brief Gets the corner by the @p index.
		/// @param index Corner index.
		/// @return Corner.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Corner(std::size_t index) const noexcept;
		/// @brief Gets the corners.
		/// @return Corners.
		[[nodiscard("Pure function")]]
		constexpr std::array<Core::Vector2<T>, 4> Corners() const noexcept;

		/// @brief Computes a perimeter.
		/// @return Perimeter.
		[[nodiscard("Pure function")]]
		constexpr T Perimeter() const noexcept;
		/// @brief Computes an area.
		/// @return Area.
		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;

		/// @brief Checks if all the rect data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the rect contains the point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector2<T>& point) const noexcept;

		/// @brief Normalizes the point inside the rect.
		/// @details Min point is [0, 0]; Max point is [1, 1].
		/// @param point Point to normalize.
		/// @return Normalized point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Normalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Unnormalizes the point inside the rect.
		/// @details Min point is [0, 0]; Max point is [1, 1].
		/// @param point Point to unnormalize.
		/// @return Unnormalized point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Unnormalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Normalizes the rect inside the other rect.
		/// @details Min point is [0, 0]; Max point is [1, 1].
		/// @param rect Rect to normalize.
		/// @return Normalized rect.
		[[nodiscard("Pure function")]]
		constexpr Rect Normalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Unnormalizes the rect inside the other rect.
		/// @details Min point is [0, 0]; Max point is [1, 1].
		/// @param rect Rect to unnormalize.
		/// @return Unnormalized rect.
		[[nodiscard("Pure function")]]
		constexpr Rect Unnormalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Adjusts position and size so that the rect keeps its shape but its size becomes positive.
		constexpr void ResolveNegativeSize() noexcept;

		/// @brief Creates a string representing the rect.
		/// @return String representing the rect.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the rect to a rect of another type.
		/// @tparam U Target type.
		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Rect<U>() const noexcept;

		constexpr Rect& operator =(const Rect& other) noexcept = default;
		constexpr Rect& operator =(Rect&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Rect& other) const noexcept = default;

	private:
		Core::Vector2<T> position; ///< Position.
		Core::Vector2<T> size; ///< Size.
	};

	/// @brief Checks if the two rects are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left rect.
	/// @param right Right rect.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Rect<T>& left, const Rect<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts rect.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param rect Source rect.
	/// @return @p stream.
	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Rect<T>& rect);

	template<Core::Arithmetic T>
	struct Rect<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = Rect(T{0}, T{0}, T{0}, T{0}); ///< Rect(0, 0, 0, 0).
		static constexpr auto NormalizedFull = Rect(T{0}, T{0}, T{1}, T{1}); ///< Rect(0, 0, 1, 1).
	};
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr Rect<T>::Rect(const T x, const T y, const T width, const T height) noexcept :
		position(x, y),
		size(width, height)
	{
	}

	template<Core::Arithmetic T>
	constexpr Rect<T>::Rect(const Core::Vector2<T>& position, const Core::Vector2<T>& size) noexcept :
		position(position),
		size(size)
	{
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T>& Rect<T>::Position() noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector2<T>& Rect<T>::Position() const noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T>& Rect<T>::Size() noexcept
	{
		return size;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector2<T>& Rect<T>::Size() const noexcept
	{
		return size;
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MinX() const noexcept
	{
		return position.X();
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MinY() const noexcept
	{
		return position.Y();
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Min(const std::size_t index) const noexcept
	{
		return position[index];
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Min() const noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::MinX(const T minX) noexcept
	{
		size.X() = MaxX() - minX;
		position.X() = minX;
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::MinY(const T minY) noexcept
	{
		size.Y() = MaxY() - minY;
		position.Y() = minY;
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Min(const std::size_t index, const T min) noexcept
	{
		size[index] = Max(index) - min;
		position[index] = min;
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Min(const Core::Vector2<T>& min) noexcept
	{
		size = Max() - min;
		position = min;
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MaxX() const noexcept
	{
		return position.X() + size.X();
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::MaxY() const noexcept
	{
		return position.Y() + size.Y();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Max() const noexcept
	{
		return position + size;
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Max(const std::size_t index) const noexcept
	{
		return position[index] + size[index];
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::MaxX(const T maxX) noexcept
	{
		size.X() = maxX - position.X();
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::MaxY(const T maxY) noexcept
	{
		size.Y() = maxY - position.Y();
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Max(const Core::Vector2<T>& max) noexcept
	{
		size = max - position;
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Max(const std::size_t index, const T max) noexcept
	{
		size[index] = max - position[index];
	}

	template<Core::Arithmetic T>
	bool Rect<T>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return position.IsFinite() && size.IsFinite();
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Width() const noexcept
	{
		return size.X();
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Rect<T>::Width(const T width) noexcept
	{
		if constexpr (KeepCenter)
		{
			position.X() -= (width - size.X()) / T{2};;
		}

		size.X() = width;
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Height() const noexcept
	{
		return size.Y();
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Rect<T>::Height(const T height) noexcept
	{
		if constexpr (KeepCenter)
		{
			position.Y() -= (height - size.Y()) / T{2};
		}

		size.Y() = height;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Center() const noexcept
	{
		return position + size / T{2};
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::Center(const Core::Vector2<T>& center) noexcept
	{
		position = center - (Center() - position);
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::LeftBottom() const noexcept
	{
		return Min();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::RightBottom() const noexcept
	{
		return Core::Vector2<T>(MaxX(), MinY());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::LeftTop() const noexcept
	{
		return Core::Vector2<T>(MinX(), MaxY());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::RightTop() const noexcept
	{
		return Max();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Corner(const std::size_t index) const noexcept
	{
		Core::Vector2<T> corner;
		corner.X() = index & 1 ? MaxX() : MinX();
		corner.Y() = index & 2 ? MaxY() : MinY();

		return corner;
	}

	template<Core::Arithmetic T>
	constexpr std::array<Core::Vector2<T>, 4> Rect<T>::Corners() const noexcept
	{
		return std::array<Core::Vector2<T>, 4>
		{
			LeftBottom(),
			RightBottom(),
			LeftTop(),
			RightTop()
		};
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Perimeter() const noexcept
	{
		return (size.X() + size.Y()) * T{2};
	}

	template<Core::Arithmetic T>
	constexpr T Rect<T>::Area() const noexcept
	{
		return size.X() * size.Y();
	}

	template<Core::Arithmetic T>
	constexpr bool Rect<T>::Contains(const Core::Vector2<T>& point) const noexcept
	{
		return point.X() >= MinX() && point.Y() >= MinY() && point.X() <= MaxX() && point.Y() <= MaxY();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Normalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Core::Divide(point - position, size);
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> Rect<T>::Unnormalize(const Core::Vector2<T>& point) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Core::Multiply(point, size) + position;
	}

	template<Core::Arithmetic T>
	constexpr Rect<T> Rect<T>::Normalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Rect(Normalize(rect.position), Core::Divide(rect.size, size));
	}

	template<Core::Arithmetic T>
	constexpr Rect<T> Rect<T>::Unnormalize(const Rect& rect) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Rect(Unnormalize(rect.position), Core::Multiply(rect.size, size));
	}

	template<Core::Arithmetic T>
	constexpr void Rect<T>::ResolveNegativeSize() noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			if (size[i] < T{0})
			{
				position[i] += size[i];
				size[i] = -size[i];
			}
		}
	}

	template<Core::Arithmetic T>
	template<Core::Arithmetic U>
	constexpr Rect<T>::operator Rect<U>() const noexcept
	{
		return Rect<U>(static_cast<Core::Vector2<U>>(position), static_cast<Core::Vector2<U>>(size));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Rect<T>& left, const Rect<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Position(), right.Position(), tolerance) && Core::AreAlmostEqual(left.Size(), right.Size(), tolerance);
	}

	template<Core::Arithmetic T>
	std::string Rect<T>::ToString() const
	{
		return std::format("Position: {}, Size: {}", position.ToString(), size.ToString());
	}

	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Rect<T>& rect)
	{
		return stream << rect.ToString();
	}
}
