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

import PonyMath.Core;

import :Rect;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	class Box final
	{
	public:
		using ValueType = T;

		static constexpr std::size_t LeftBottomNearIndex = 0;
		static constexpr std::size_t RightBottomNearIndex = 1;
		static constexpr std::size_t LeftTopNearIndex = 2;
		static constexpr std::size_t RightTopNearIndex = 3;
		static constexpr std::size_t LeftBottomFarIndex = 0;
		static constexpr std::size_t RightBottomFarIndex = 1;
		static constexpr std::size_t LeftTopFarIndex = 2;
		static constexpr std::size_t RightTopFarIndex = 3;
		static constexpr std::size_t CornerCount = 8;

		struct Predefined;

		[[nodiscard("Pure constructor")]]
		constexpr Box() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Box(T x, T y, T z, T width, T height, T depth) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Box(const Core::Vector3<T>& position, const Core::Vector3<T>& size) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Box(const Rect<T>& rect, T z, T depth) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Box(const Box& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Box(Box&& other) noexcept = default;

		constexpr ~Box() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Position() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Position() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Size() noexcept;
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
		/// @brief Gets the minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Min() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Min(std::size_t index) const noexcept;
		/// @brief Sets the minimal x point keeping the max point.
		/// @param minX Minimal x point to set.
		constexpr void MinX(T minX) noexcept;
		/// @brief Sets the minimal y point keeping the max point.
		/// @param minY Minimal y point to set.
		constexpr void MinY(T minY) noexcept;
		/// @brief Sets the minimal z point keeping the max point.
		/// @param minZ Minimal z point to set.
		constexpr void MinZ(T minZ) noexcept;
		/// @brief Sets the minimal point keeping the max point.
		/// @param min Minimal point to set.
		constexpr void Min(const Core::Vector3<T>& min) noexcept;
		constexpr void Min(std::size_t index, T min) noexcept;

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
		/// @brief Gets the maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Max() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;
		/// @brief Sets the maximal x point keeping the min point.
		/// @param maxX Maximal x point to set.
		constexpr void MaxX(T maxX) noexcept;
		/// @brief Sets the maximal y point keeping the min point.
		/// @param maxY Maximal y point to set.
		constexpr void MaxY(T maxY) noexcept;
		/// @brief Sets the maximal z point keeping the min point.
		/// @param maxZ Maximal z point to set.
		constexpr void MaxZ(T maxZ) noexcept;
		/// @brief Sets the maximal point keeping the min point.
		/// @param max Maximal point to set.
		constexpr void Max(const Core::Vector3<T>& max) noexcept;
		constexpr void Max(std::size_t index, T max) noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		template<bool KeepCenter = false>
		constexpr void Width(T width) noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		template<bool KeepCenter = false>
		constexpr void Height(T height) noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Depth() const noexcept;
		template<bool KeepCenter = false>
		constexpr void Depth(T depth) noexcept;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Center() const noexcept;
		/// @brief Sets the center keeping the size.
		/// @param center Center to set.
		constexpr void Center(const Core::Vector3<T>& center) noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopNear() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopFar() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Corner(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::array<Core::Vector3<T>, 8> Corners() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Volume() const noexcept;

		/// @brief Checks if all the box data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the box contains the point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector3<T>& point) const noexcept;

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
		// TODO: Change ToSet to usual names and use this->

		constexpr void ResolveNegativeSize() noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator Box<U>() const noexcept;

		constexpr Box& operator =(const Box& other) noexcept = default;
		constexpr Box& operator =(Box&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Box& other) const noexcept = default;

	private:
		Core::Vector3<T> position;
		Core::Vector3<T> size;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Box<T>& left, const Box<T>& right, T tolerance = T{0.00001}) noexcept;

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
	constexpr Box<T>::Box(const Rect<T>& rect, const T z, const T depth) noexcept :
		position(rect.Position().X(), rect.Position().Y(), z),
		size(rect.Size().X(), rect.Size().Y(), depth)
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
		return position.X();
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MinY() const noexcept
	{
		return position.Y();
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MinZ() const noexcept
	{
		return position.Z();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Min() const noexcept
	{
		return position;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Min(const std::size_t index) const noexcept
	{
		return position[index];
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MinX(const T minX) noexcept
	{
		size.X() = MaxX() - minX;
		position.X() = minX;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MinY(const T minY) noexcept
	{
		size.Y() = MaxY() - minY;
		position.Y() = minY;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MinZ(const T minZ) noexcept
	{
		size.Z() = MaxZ() - minZ;
		position.Z() = minZ;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Min(const Core::Vector3<T>& min) noexcept
	{
		size = Max() - min;
		position = min;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Min(const std::size_t index, const T min) noexcept
	{
		size[index] = Max(index) - min;
		position[index] = min;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MaxX() const noexcept
	{
		return position.X() + size.X();
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MaxY() const noexcept
	{
		return position.Y() + size.Y();
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::MaxZ() const noexcept
	{
		return position.Z() + size.Z();
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Max() const noexcept
	{
		return position + size;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Max(const std::size_t index) const noexcept
	{
		return position[index] + size[index];
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MaxX(const T maxX) noexcept
	{
		size.X() = maxX - position.X();
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MaxY(const T maxY) noexcept
	{
		size.Y() = maxY - position.Y();
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::MaxZ(const T maxZ) noexcept
	{
		size.Z() = maxZ - position.Z();
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Max(const Core::Vector3<T>& max) noexcept
	{
		size = max - position;
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Max(const std::size_t index, const T max) noexcept
	{
		size[index] = max - position[index];
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Width() const noexcept
	{
		return size.X();
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Box<T>::Width(const T width) noexcept
	{
		if constexpr (KeepCenter)
		{
			position.X() -= (width - size.X()) / T{2};
		}

		size.X() = width;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Height() const noexcept
	{
		return size.Y();
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Box<T>::Height(const T height) noexcept
	{
		if constexpr (KeepCenter)
		{
			position.Y() -= (height - size.Y()) / T{2};
		}

		size.Y() = height;
	}

	template<Core::Arithmetic T>
	constexpr T Box<T>::Depth() const noexcept
	{
		return size.Z();
	}

	template<Core::Arithmetic T>
	template<bool KeepCenter>
	constexpr void Box<T>::Depth(const T depth) noexcept
	{
		if constexpr (KeepCenter)
		{
			position.Z() -= (depth - size.Z()) / T{2};
		}

		size.Z() = depth;
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> Box<T>::Center() const noexcept
	{
		return position + size / T{2};
	}

	template<Core::Arithmetic T>
	constexpr void Box<T>::Center(const Core::Vector3<T>& center) noexcept
	{
		position = center - (Center() - position);
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
		return (size.X() * size.Y() + size.Y() * size.Z() + size.X() * size.Z()) * T{2};
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
	constexpr void Box<T>::ResolveNegativeSize() noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			if (size[i] < T{0})
			{
				position[i] += size[i];
				size[i] = -size[i];
			}
		}
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
