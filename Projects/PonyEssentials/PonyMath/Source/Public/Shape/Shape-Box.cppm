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

export module PonyMath.Shape:Box;

import <algorithm>;
import <array>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import PonyMath.Core;

export namespace PonyMath::Shape
{
	/// @brief Box implementation.
	/// @tparam T Component type.
	template<Core::Arithmetic T>
	class Box final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t LeftBottomNearIndex = 0; ///< (MinX, MinY, MinZ) corner index.
		static constexpr std::size_t RightBottomNearIndex = 1; ///< (MaxX, MinY, MinZ) corner index.
		static constexpr std::size_t LeftTopNearIndex = 2; ///< (MinX, MaxY, MinZ) corner index.
		static constexpr std::size_t RightTopNearIndex = 3; ///< (MaxX, MaxY, MinZ) corner index.
		static constexpr std::size_t LeftBottomFarIndex = 4; ///< (MinX, MinY, MaxZ) corner index.
		static constexpr std::size_t RightBottomFarIndex = 5; ///< (MaxX, MinY, MaxZ) corner index.
		static constexpr std::size_t LeftTopFarIndex = 6; ///< (MinX, MaxY, MaxZ) corner index.
		static constexpr std::size_t RightTopFarIndex = 7; ///< (MaxX, MaxY, MaxZ) corner index.
		static constexpr std::size_t CornerCount = 8; ///< Corner count.

		struct Predefined; ///< Predefined AABBs.

		/// @brief Creates a zero box.
		[[nodiscard("Pure constructor")]]
		constexpr Box() noexcept = default;
		/// @brief Creates a box.
		/// @param x Position x component.
		/// @param y Position y component.
		/// @param z Position z component.
		/// @param width Width.
		/// @param height Height.
		/// @param depth Depth.
		[[nodiscard("Pure constructor")]]
		constexpr Box(T x, T y, T z, T width, T height, T depth) noexcept;
		/// @brief Creates a box.
		/// @param position Box position.
		/// @param size Box size.
		[[nodiscard("Pure constructor")]]
		constexpr Box(const Core::Vector3<T>& position, const Core::Vector3<T>& size) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Box(const Box& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Box(Box&& other) noexcept = default;

		constexpr ~Box() noexcept = default;

		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Position() noexcept;
		/// @brief Gets the position.
		/// @return Position.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Position() const noexcept;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Size() noexcept;
		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Size() const noexcept;

		/// @brief Gets the minimal x point.
		/// @return Minimal x.
		[[nodiscard("Pure function")]]
		constexpr T MinX() const noexcept;
		/// @brief Gets the minimal y point.
		/// @return Minimal y.
		[[nodiscard("Pure function")]]
		constexpr T MinY() const noexcept;
		/// @brief Gets the minimal z point.
		/// @return Minimal z.
		[[nodiscard("Pure function")]]
		constexpr T MinZ() const noexcept;
		/// @brief Gets the minimal component by the @p index.
		/// @param index Component index. 0 -> x, 1 -> y, 2 -> z.
		/// @return Minimal component.
		[[nodiscard("Pure function")]]
		constexpr T Min(std::size_t index) const noexcept;
		/// @brief Gets the minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Min() const noexcept;
		/// @brief Sets the minimal x point keeping the max point.
		/// @param minX Minimal x point to set.
		constexpr void MinX(T minX) noexcept;
		/// @brief Sets the minimal y point keeping the max point.
		/// @param minY Minimal y point to set.
		constexpr void MinY(T minY) noexcept;
		/// @brief Sets the minimal z point keeping the max point.
		/// @param minZ Minimal z point to set.
		constexpr void MinZ(T minZ) noexcept;
		/// @brief Sets the minimal component by the @p index.
		/// @param index Component index. 0 -> x, 1 -> y, 2 -> z.
		/// @param min Minimal component.
		constexpr void Min(std::size_t index, T min) noexcept;
		/// @brief Sets the minimal point keeping the max point.
		/// @param min Minimal point to set.
		constexpr void Min(const Core::Vector3<T>& min) noexcept;

		/// @brief Gets the maximal x point.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxX() const noexcept;
		/// @brief Gets the maximal y point.
		/// @return Maximal y.
		[[nodiscard("Pure function")]]
		constexpr T MaxY() const noexcept;
		/// @brief Gets the maximal z point.
		/// @return Maximal z.
		[[nodiscard("Pure function")]]
		constexpr T MaxZ() const noexcept;
		/// @brief Gets the maximal component by the @p index.
		/// @param index Component index. 0 -> x, 1 -> y, 2 -> z.
		/// @return Maximal component.
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;
		/// @brief Gets the maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Max() const noexcept;
		/// @brief Sets the maximal x point keeping the min point.
		/// @param maxX Maximal x point to set.
		constexpr void MaxX(T maxX) noexcept;
		/// @brief Sets the maximal y point keeping the min point.
		/// @param maxY Maximal y point to set.
		constexpr void MaxY(T maxY) noexcept;
		/// @brief Sets the maximal z point keeping the min point.
		/// @param maxZ Maximal z point to set.
		constexpr void MaxZ(T maxZ) noexcept;
		/// @brief Sets the maximal component by the @p index.
		/// @param index Component index. 0 -> x, 1 -> y, 2 -> z.
		/// @param max Maximal component.
		constexpr void Max(std::size_t index, T max) noexcept;
		/// @brief Sets the maximal point keeping the min point.
		/// @param max Maximal point to set.
		constexpr void Max(const Core::Vector3<T>& max) noexcept;

		/// @brief Gets the width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		/// @brief Sets the width.
		/// @tparam KeepCenter If it's @a true, the center of the box is kept; otherwise its position is kept.
		/// @param width Width.
		template<bool KeepCenter = false>
		constexpr void Width(T width) noexcept;
		/// @brief Gets the height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		/// @brief Sets the height.
		/// @tparam KeepCenter If it's @a true, the center of the box is kept; otherwise its position is kept.
		/// @param height Height.
		template<bool KeepCenter = false>
		constexpr void Height(T height) noexcept;
		/// @brief Gets the depth.
		/// @return Depth.
		[[nodiscard("Pure function")]]
		constexpr T Depth() const noexcept;
		/// @brief Sets the depth.
		/// @tparam KeepCenter If it's @a true, the center of the box is kept; otherwise its position is kept.
		/// @param depth Depth.
		template<bool KeepCenter = false>
		constexpr void Depth(T depth) noexcept;
		/// @brief Gets the size by the @p index.
		/// @param index Size index. 0 -> width, 1 -> height, 2 -> depth.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr T Size(std::size_t index) const noexcept;
		/// @brief Sets the size by the @p index.
		/// @tparam KeepCenter If it's @a true, the center of the box is kept; otherwise its position is kept.
		/// @param index Size index. 0 -> width, 1 -> height, 2 -> depth.
		/// @param size Size to set.
		template<bool KeepCenter = false>
		constexpr void Size(std::size_t index, T size) noexcept;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Center() const noexcept;
		/// @brief Sets the center keeping the size.
		/// @param center Center to set.
		constexpr void Center(const Core::Vector3<T>& center) noexcept;

		/// @brief Gets the (MinX, MinY, MinZ) point.
		/// @return Left bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomNear() const noexcept;
		/// @brief Gets the (MaxX, MinY, MinZ) point.
		/// @return Right bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomNear() const noexcept;
		/// @brief Gets the (MinX, MaxY, MinZ) point.
		/// @return Left top near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopNear() const noexcept;
		/// @brief Gets the (MaxX, MaxY, MinZ) point.
		/// @return Right top near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopNear() const noexcept;
		/// @brief Gets the (MinX, MinY, MaxZ) point.
		/// @return Left bottom far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomFar() const noexcept;
		/// @brief Gets the (MaxX, MinY, MaxZ) point.
		/// @return Right bottom far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomFar() const noexcept;
		/// @brief Gets the (MinX, MaxY, MaxZ) point.
		/// @return Left top far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopFar() const noexcept;
		/// @brief Gets the (MaxX, MaxY, MaxZ) point.
		/// @return Right top far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopFar() const noexcept;
		/// @brief Gets the corner by the @p index.
		/// @param index Corner index.
		/// @return Corner.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Corner(std::size_t index) const noexcept;
		/// @brief Gets the corners.
		/// @return Corners.
		[[nodiscard("Pure function")]]
		constexpr std::array<Core::Vector3<T>, 8> Corners() const noexcept;

		/// @brief Calculates an area.
		/// @return Area.
		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;
		/// @brief Calculates a volume.
		/// @return Volume.
		[[nodiscard("Pure function")]]
		constexpr T Volume() const noexcept;

		/// @brief Checks if all the box data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the box contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector3<T>& point) const noexcept;
		/// @brief Calculates the closest point on the box.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the box, the @p point is returned.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> ClosestPoint(const Core::Vector3<T>& point) const noexcept;

		/// @brief Normalizes the point inside the box.
		/// @details Min point is [0, 0, 0]; Max point is [1, 1, 1].
		/// @param point Point to normalize.
		/// @return Normalized point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Normalize(const Core::Vector3<T>& point) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Unnormalizes the point inside the box.
		/// @details Min point is [0, 0, 0]; Max point is [1, 1, 1].
		/// @param point Point to unnormalize.
		/// @return Unnormalized point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Unnormalize(const Core::Vector3<T>& point) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Normalizes the box inside the other box.
		/// @details Min point is [0, 0, 0]; Max point is [1, 1, 1].
		/// @param box Box to normalize.
		/// @return Normalized box.
		[[nodiscard("Pure function")]]
		constexpr Box Normalize(const Box& box) const noexcept requires (std::is_floating_point_v<T>);
		/// @brief Unnormalizes the box inside the other box.
		/// @details Min point is [0, 0, 0]; Max point is [1, 1, 1].
		/// @param box Box to unnormalize.
		/// @return Unnormalized box.
		[[nodiscard("Pure function")]]
		constexpr Box Unnormalize(const Box& box) const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Sets a positive sign to the size and adjusts the position so that the box take the same space.
		void ResolveNegativeSize() noexcept;

		/// @brief Creates a string representing the box.
		/// @return String representing the box.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the box to a box of another type.
		/// @tparam U Target type.
		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Box<U>() const noexcept;

		constexpr Box& operator =(const Box& other) noexcept = default;
		constexpr Box& operator =(Box&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Box& other) const noexcept = default;

	private:
		Core::Vector3<T> position; ///< Position.
		Core::Vector3<T> size; ///< Size.
	};

	/// @brief Checks if the two boxes are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left box.
	/// @param right Right box.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Box<T>& left, const Box<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts box.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param box Source box.
	/// @return @p stream.
	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Box<T>& box);

	template<Core::Arithmetic T>
	struct Box<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = Box(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}); ///< Box(0, 0, 0, 0, 0, 0).
		static constexpr auto NormalizedFull = Box(T{0}, T{0}, T{0}, T{1}, T{1}, T{1}); ///< Box(0, 0, 0, 1, 1, 1).
	};
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr Box<T>::Box(const T x, const T y, const T z, const T width, const T height, const T depth) noexcept :
		position(x, y, z),
		size(width, height, depth)
	{
	}

	template<Core::Arithmetic T>
	constexpr Box<T>::Box(const Core::Vector3<T>& position, const Core::Vector3<T>& size) noexcept :
		position(position),
		size(size)
	{
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T>& Box<T>::Position() noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector3<T>& Box<T>::Position() const noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T>& Box<T>::Size() noexcept
	{
		return size;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector3<T>& Box<T>::Size() const noexcept
	{
		return size;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MinX() const noexcept
	{
		return Min(0);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MinY() const noexcept
	{
		return Min(1);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MinZ() const noexcept
	{
		return Min(2);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Min(const std::size_t index) const noexcept
	{
		return position[index];
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Min() const noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MinX(const T minX) noexcept
	{
		Min(0, minX);
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MinY(const T minY) noexcept
	{
		Min(1, minY);
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MinZ(const T minZ) noexcept
	{
		Min(2, minZ);
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Min(const std::size_t index, const T min) noexcept
	{
		size[index] = Max(index) - min;
		position[index] = min;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Min(const Core::Vector3<T>& min) noexcept
	{
		size = Max() - min;
		position = min;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MaxX() const noexcept
	{
		return Max(0);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MaxY() const noexcept
	{
		return Max(1);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MaxZ() const noexcept
	{
		return Max(2);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Max(const std::size_t index) const noexcept
	{
		return position[index] + size[index];
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Max() const noexcept
	{
		return position + size;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MaxX(const T maxX) noexcept
	{
		Max(0, maxX);
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MaxY(const T maxY) noexcept
	{
		Max(1, maxY);
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MaxZ(const T maxZ) noexcept
	{
		Max(2, maxZ);
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Max(const std::size_t index, const T max) noexcept
	{
		size[index] = max - position[index];
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Max(const Core::Vector3<T>& max) noexcept
	{
		size = max - position;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Width() const noexcept
	{
		return Size(0);
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Box<T>::Width(const T width) noexcept
	{
		Size<KeepCenter>(0, width);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Height() const noexcept
	{
		return Size(1);
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Box<T>::Height(const T height) noexcept
	{
		Size<KeepCenter>(1, height);
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Depth() const noexcept
	{
		return Size(2);
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Box<T>::Depth(const T depth) noexcept
	{
		Size<KeepCenter>(2, depth);
	}

	template <Core::Arithmetic T>
	constexpr T Box<T>::Size(const std::size_t index) const noexcept
	{
		return size[index];
	}

	template <Core::Arithmetic T>
	template <bool KeepCenter>
	constexpr void Box<T>::Size(const std::size_t index, const T size) noexcept
	{
		if constexpr (KeepCenter)
		{
			position[index] -= (size - this->size[index]) / T{2};
		}

		this->size[index] = size;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Center() const noexcept
	{
		return position + size / T{2};
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Center(const Core::Vector3<T>& center) noexcept
	{
		position = center - size / T{2};
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::LeftBottomNear() const noexcept
	{
		return Core::Vector3<T>(MinX(), MinY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::RightBottomNear() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MinY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::LeftTopNear() const noexcept
	{
		return Core::Vector3<T>(MinX(), MaxY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::RightTopNear() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MaxY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::LeftBottomFar() const noexcept
	{
		return Core::Vector3<T>(MinX(), MinY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::RightBottomFar() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MinY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::LeftTopFar() const noexcept
	{
		return Core::Vector3<T>(MinX(), MaxY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::RightTopFar() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MaxY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Corner(const std::size_t index) const noexcept
	{
		Core::Vector3<T> corner;
		corner.X() = index & 1 ? MaxX() : MinX();
		corner.Y() = index & 2 ? MaxY() : MinY();
		corner.Z() = index & 4 ? MaxZ() : MinZ();

		return corner;
	}

	template<Core::Arithmetic T>
	constexpr std::array<Core::Vector3<T>, 8> Box<T>::Corners() const noexcept
	{
		return std::array<Core::Vector3<T>, 8>
		{
			LeftBottomNear(),
			RightBottomNear(),
			LeftTopNear(),
			RightTopNear(),
			LeftBottomFar(),
			RightBottomFar(),
			LeftTopFar(),
			RightTopFar()
		};
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Area() const noexcept
	{
		return (size.X() * size.Y() + size.X() * size.Z() + size.Y() * size.Z()) * T{2};
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Volume() const noexcept
	{
		return size.X() * size.Y() * size.Z();
	}

	template<Core::Arithmetic T>
	bool Box<T>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return position.IsFinite() && size.IsFinite();
	}

	template<Core::Arithmetic T>
	constexpr bool Box<T>::Contains(const Core::Vector3<T>& point) const noexcept
	{
		return point.X() >= MinX() && point.Y() >= MinY() && point.Z() >= MinZ() &&
			point.X() <= MaxX() && point.Y() <= MaxY() && point.Z() <= MaxZ();
	}

	template <Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::ClosestPoint(const Core::Vector3<T>& point) const noexcept
	{
		Core::Vector3<T> answer;
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			answer[i] = std::clamp(point[i], Min(i), Max(i));
		}

		return answer;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Normalize(const Core::Vector3<T>& point) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Core::Divide(point - position, size);
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Unnormalize(const Core::Vector3<T>& point) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Core::Multiply(point, size) + position;
	}

	template<Core::Arithmetic T>
	constexpr Box<T> Box<T>::Normalize(const Box& box) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Box(Normalize(box.position), Core::Divide(box.size, size));
	}

	template<Core::Arithmetic T>
	constexpr Box<T> Box<T>::Unnormalize(const Box& box) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Box(Unnormalize(box.position), Core::Multiply(box.size, size));
	}

	template<Core::Arithmetic T>
	void Box<T>::ResolveNegativeSize() noexcept
	{
		position = Core::Min(position, position + size);
		size = Core::Abs(size);
	}

	template<Core::Arithmetic T>
	std::string Box<T>::ToString() const
	{
		return std::format("Position: {}, Size: {}", position.ToString(), size.ToString());
	}

	template<Core::Arithmetic T>
	template<Core::Arithmetic U>
	constexpr Box<T>::operator Box<U>() const noexcept
	{
		return Box<U>(static_cast<Core::Vector3<U>>(position), static_cast<Core::Vector3<U>>(size));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const Box<T>& left, const Box<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Position(), right.Position(), tolerance) && Core::AreAlmostEqual(left.Size(), right.Size(), tolerance);
	}

	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const Box<T>& box)
	{
		return stream << box.ToString();
	}
}
