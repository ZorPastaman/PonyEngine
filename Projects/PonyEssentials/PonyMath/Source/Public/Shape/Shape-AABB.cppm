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

export module PonyMath.Shape:AABB;

import <algorithm>;
import <array>;
import <cmath>;
import <concepts>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import PonyMath.Core;

import :Box;

export namespace PonyMath::Shape
{
	/// @brief Axis-aligned bounding box implementation.
	/// @tparam T Component type.
	template<Core::Arithmetic T>
	class AABB final
	{
	public:
		using ValueType = T; ///< Component type.

		/// @brief AABB axes.
		static constexpr std::array<Core::Vector3<T>, 3> Axes = { Core::Vector3<T>::Predefined::Right, Core::Vector3<T>::Predefined::Up, Core::Vector3<T>::Predefined::Forward };

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

		/// @brief Creates a zero AABB.
		[[nodiscard("Pure constructor")]]
		constexpr AABB() noexcept = default;
		/// @brief Creates an AABB.
		/// @param x Center x component.
		/// @param y Center y component.
		/// @param z Center z component.
		/// @param halfWidth Half width. Must be positive.
		/// @param halfHeight Half height. Must be positive.
		/// @param halfDepth Half depth. Must be positive.
		[[nodiscard("Pure constructor")]]
		constexpr AABB(T x, T y, T z, T halfWidth, T halfHeight, T halfDepth) noexcept;
		/// @brief Creates an AABB.
		/// @param center Center.
		/// @param extents Extents. Half-sizes in every dimension. All the components must be positive.
		[[nodiscard("Pure constructor")]]
		constexpr AABB(const Core::Vector3<T>& center, const Core::Vector3<T>& extents) noexcept;
		/// @brief Converts the @p box to an AABB.
		/// @param box Box.
		[[nodiscard("Pure constructor")]]
		explicit AABB(const Box<T>& box) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr AABB(const AABB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr AABB(AABB&& other) noexcept = default;

		constexpr ~AABB() noexcept = default;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Center() noexcept;
		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Center() const noexcept;

		/// @brief Gets the x extent.
		/// @return X extent. Must be positive.
		[[nodiscard("Pure function")]]
		constexpr T& ExtentX() noexcept;
		/// @brief Gets the x extent.
		/// @return X extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentX() const noexcept;
		/// @brief Gets the y extent.
		/// @return Y extent. Must be positive.
		[[nodiscard("Pure function")]]
		constexpr T& ExtentY() noexcept;
		/// @brief Gets the y extent.
		/// @return Y extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentY() const noexcept;
		/// @brief Gets the z extent.
		/// @return Z extent. Must be positive.
		[[nodiscard("Pure function")]]
		constexpr T& ExtentZ() noexcept;
		/// @brief Gets the z extent.
		/// @return Z extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentZ() const noexcept;
		/// @brief Gets an extent by the @p index.
		/// @param index Extent index. 0 -> x, 1 -> y, 2 -> z.
		/// @return Extent. Must be positive.
		[[nodiscard("Pure function")]]
		constexpr T& Extent(std::size_t index) noexcept;
		/// @brief Gets an extent by the @p index.
		/// @param index Extent index. 0 -> x, 1 -> y, 2 -> z.
		/// @return Extent.
		[[nodiscard("Pure function")]]
		constexpr const T& Extent(std::size_t index) const noexcept;
		/// @brief Gets the extents.
		/// @return Extents. All the components must be positive.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Extents() noexcept;
		/// @brief Gets the extents.
		/// @return Extents.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Extents() const noexcept;

		/// @brief Gets the width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		/// @brief Gets the height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		/// @brief Gets the depth.
		/// @return Depth.
		[[nodiscard("Pure function")]]
		constexpr T Depth() const noexcept;
		/// @brief Gets the size by the @p index.
		/// @param index Size index. 0 -> width, 1 -> height, 2 -> depth.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr T Size(std::size_t index) const noexcept;

		/// @brief Gets the minimal x.
		/// @return Minimal x.
		[[nodiscard("Pure function")]]
		constexpr T MinX() const noexcept;
		/// @brief Gets the minimal y.
		/// @return Minimal y.
		[[nodiscard("Pure function")]]
		constexpr T MinY() const noexcept;
		/// @brief Gets the minimal z.
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
		/// @brief Gets the maximal x.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxX() const noexcept;
		/// @brief Gets the maximal y.
		/// @return Maximal y.
		[[nodiscard("Pure function")]]
		constexpr T MaxY() const noexcept;
		/// @brief Gets the maximal z.
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

		/// @brief Checks if all the AABB data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the AABB contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool Contains(const Core::Vector3<T>& point) const noexcept;
		/// @brief Calculates the closest point on the box.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the box, the @p point is returned.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> ClosestPoint(const Core::Vector3<T>& point) const noexcept;

		/// @brief Creates a string representing the AABB.
		/// @return String representing the AABB.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the AABB to an AABB of another type.
		/// @tparam U Target type.
		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit operator AABB<U>() const noexcept;
		/// @brief Converts the AABB to a box.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Box<T>() const noexcept;

		constexpr AABB& operator =(const AABB& other) noexcept = default;
		constexpr AABB& operator =(AABB&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const AABB& other) const noexcept = default;

	private:
		Core::Vector3<T> center; ///< Center.
		Core::Vector3<T> extents; ///< Extents.
	};

	/// @brief Checks if the two AABBs are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left AABB.
	/// @param right Right AABB.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const AABB<T>& left, const AABB<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts aabb.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param aabb Source AABB.
	/// @return @p stream.
	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const AABB<T>& aabb);

	template<Core::Arithmetic T>
	struct AABB<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static inline const auto Zero = AABB(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}); ///< AABB(0, 0, 0, 0, 0, 0).
	};
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr AABB<T>::AABB(const T x, const T y, const T z, const T halfWidth, const T halfHeight, const T halfDepth) noexcept :
		center(x, y, z),
		extents(halfWidth, halfHeight, halfDepth)
	{
	}

	template<Core::Arithmetic T>
	constexpr AABB<T>::AABB(const Core::Vector3<T>& center, const Core::Vector3<T>& extents) noexcept :
		center(center),
		extents(extents)
	{
	}

	template<Core::Arithmetic T>
	AABB<T>::AABB(const Box<T>& box) noexcept :
		center(box.Center()),
		extents(Core::Abs(box.Size() / T{2}))
	{
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T>& AABB<T>::Center() noexcept
	{
		return center;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector3<T>& AABB<T>::Center() const noexcept
	{
		return center;
	}

	template <Core::Arithmetic T>
	constexpr T& AABB<T>::ExtentX() noexcept
	{
		return extents[0];
	}

	template <Core::Arithmetic T>
	constexpr const T& AABB<T>::ExtentX() const noexcept
	{
		return extents[0];
	}

	template <Core::Arithmetic T>
	constexpr T& AABB<T>::ExtentY() noexcept
	{
		return extents[1];
	}

	template <Core::Arithmetic T>
	constexpr const T& AABB<T>::ExtentY() const noexcept
	{
		return extents[1];
	}

	template <Core::Arithmetic T>
	constexpr T& AABB<T>::ExtentZ() noexcept
	{
		return extents[2];
	}

	template <Core::Arithmetic T>
	constexpr const T& AABB<T>::ExtentZ() const noexcept
	{
		return extents[2];
	}

	template <Core::Arithmetic T>
	constexpr T& AABB<T>::Extent(const std::size_t index) noexcept
	{
		return extents[index];
	}

	template <Core::Arithmetic T>
	constexpr const T& AABB<T>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template <Core::Arithmetic T>
	constexpr Core::Vector3<T>& AABB<T>::Extents() noexcept
	{
		return extents;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector3<T>& AABB<T>::Extents() const noexcept
	{
		return extents;
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Width() const noexcept
	{
		return Size(0);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Height() const noexcept
	{
		return Size(1);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Depth() const noexcept
	{
		return Size(2);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Size(const std::size_t index) const noexcept
	{
		return Extent(index) * T{2};
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::MinX() const noexcept
	{
		return Min(0);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::MinY() const noexcept
	{
		return Min(1);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::MinZ() const noexcept
	{
		return Min(2);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Min(const std::size_t index) const noexcept
	{
		return center[index] - extents[index];
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::Min() const noexcept
	{
		return Core::Vector3<T>(MinX(), MinY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::MaxX() const noexcept
	{
		return Max(0);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::MaxY() const noexcept
	{
		return Max(1);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::MaxZ() const noexcept
	{
		return Max(2);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Max(const std::size_t index) const noexcept
	{
		return center[index] + extents[index];
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::Max() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MaxY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::LeftBottomNear() const noexcept
	{
		return Core::Vector3<T>(MinX(), MinY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::RightBottomNear() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MinY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::LeftTopNear() const noexcept
	{
		return Core::Vector3<T>(MinX(), MaxY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::RightTopNear() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MaxY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::LeftBottomFar() const noexcept
	{
		return Core::Vector3<T>(MinX(), MinY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::RightBottomFar() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MinY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::LeftTopFar() const noexcept
	{
		return Core::Vector3<T>(MinX(), MaxY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::RightTopFar() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MaxY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::Corner(const std::size_t index) const noexcept
	{
		Core::Vector3<T> corner;
		corner.X() = index & 1 ? MaxX() : MinX();
		corner.Y() = index & 2 ? MaxY() : MinY();
		corner.Z() = index & 4 ? MaxZ() : MinZ();

		return corner;
	}

	template<Core::Arithmetic T>
	constexpr std::array<Core::Vector3<T>, 8> AABB<T>::Corners() const noexcept
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
	constexpr T AABB<T>::Area() const noexcept
	{
		return (ExtentX() * ExtentY() + ExtentX() * ExtentZ() + ExtentY() * ExtentZ()) * T{8};
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Volume() const noexcept
	{
		return ExtentX() * ExtentY() * ExtentZ() * T{8};
	}

	template<Core::Arithmetic T>
	bool AABB<T>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return center.IsFinite() && extents.IsFinite();
	}

	template<Core::Arithmetic T>
	bool AABB<T>::Contains(const Core::Vector3<T>& point) const noexcept
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			if (std::abs(point[i] - center[i]) > extents[i])
			{
				return false;
			}
		}

		return true;
	}

	template <Core::Arithmetic T>
	constexpr Core::Vector3<T> AABB<T>::ClosestPoint(const Core::Vector3<T>& point) const noexcept
	{
		return Core::Clamp(point, Min(), Max());
	}

	template<Core::Arithmetic T>
	std::string AABB<T>::ToString() const
	{
		return std::format("Center: {}, Extents: {}", center.ToString(), extents.ToString());
	}

	template<Core::Arithmetic T>
	template<Core::Arithmetic U>
	AABB<T>::operator AABB<U>() const noexcept
	{
		return AABB<U>(static_cast<Core::Vector3<U>>(center), static_cast<Core::Vector3<U>>(extents));
	}

	template<Core::Arithmetic T>
	constexpr AABB<T>::operator Box<T>() const noexcept
	{
		return Box<T>(Min(), Max() - Min());
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const AABB<T>& left, const AABB<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) && Core::AreAlmostEqual(left.Extents(), right.Extents(), tolerance);
	}

	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const AABB<T>& aabb)
	{
		return stream << aabb.ToString();
	}
}
