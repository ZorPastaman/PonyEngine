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

import <array>;
import <cstddef>;
import <format>;
import <string>;

import PonyMath.Core;

import :Box;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	class AABB final
	{
	public:
		using ValueType = T; ///< Value type.

		static constexpr std::array<Core::Vector3<T>, 3> Axes = { Core::Vector3<T>::Predefined::Right, Core::Vector3<T>::Predefined::Up, Core::Vector3<T>::Predefined::Forward };

		static constexpr std::size_t LeftBottomNearIndex = 0;
		static constexpr std::size_t RightBottomNearIndex = 1;
		static constexpr std::size_t LeftTopNearIndex = 2;
		static constexpr std::size_t RightTopNearIndex = 3;
		static constexpr std::size_t LeftBottomFarIndex = 4;
		static constexpr std::size_t RightBottomFarIndex = 5;
		static constexpr std::size_t LeftTopFarIndex = 6;
		static constexpr std::size_t RightTopFarIndex = 7;
		static constexpr std::size_t CornerCount = 8;

		struct Predefined; ///< Predefined AABBs.

		[[nodiscard("Pure constructor")]]
		constexpr AABB() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr AABB(T x, T y, T z, T halfWidth, T halfHeight, T halfDepth) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr AABB(const Core::Vector3<T>& center, const Core::Vector3<T>& extents) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr AABB(const Box<T>& box) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr AABB(const AABB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr AABB(AABB&& other) noexcept = default;

		constexpr ~AABB() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Center() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Center() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T ExtentX() const noexcept;
		constexpr void ExtentX(T extent) noexcept;
		[[nodiscard("Pure function")]]
		constexpr T ExtentY() const noexcept;
		constexpr void ExtentY(T extent) noexcept;
		[[nodiscard("Pure function")]]
		constexpr T ExtentZ() const noexcept;
		constexpr void ExtentZ(T extent) noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Extent(std::size_t index) const noexcept;
		constexpr void Extent(std::size_t index, T extent) noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Extents() const noexcept;
		constexpr void Extents(const Core::Vector3<T>& extents) noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Depth() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Size(std::size_t index) const noexcept;

		/// @brief Gets the minimal x point.
		/// @return Minimal x.
		[[nodiscard("Pure function")]]
		constexpr T MinX() const noexcept;
		/// @brief Gets the minimal y point.
		/// @return Minimal y.
		[[nodiscard("Pure function")]]
		constexpr T MinY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T MinZ() const noexcept;
		/// @brief Gets the minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Min() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Min(std::size_t index) const noexcept;
		/// @brief Gets the maximal x point.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxX() const noexcept;
		/// @brief Gets the maximal x point.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T MaxZ() const noexcept;
		/// @brief Gets the maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Max() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;

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

		/// @brief Computes an area.
		/// @return Area.
		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Volume() const noexcept;

		/// @brief Checks if all the rect data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the rect contains the point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector3<T>& point) const noexcept;

		/// @brief Creates a string representing the rect.
		/// @return String representing the rect.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the rect to a rect of another type.
		/// @tparam U Target type.
		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator AABB<U>() const noexcept;
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Box<T>() const noexcept;

		constexpr AABB& operator =(const AABB& other) noexcept = default;
		constexpr AABB& operator =(AABB&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr bool operator ==(const AABB& other) const noexcept = default;

	private:
		Core::Vector3<T> center;
		Core::Vector3<T> extents;
	};

	/// @brief Checks if the two AABBs are almost equal with the tolerance value.
	/// @tparam T Value type.
	/// @param left Left rect.
	/// @param right Right rect.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const AABB<T>& left, const AABB<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts aabb.ToString() into the @p stream.
	/// @tparam T Value type.
	/// @param stream Target stream.
	/// @param aabb Source AABB.
	/// @return @p stream.
	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const AABB<T>& aabb);

	template<Core::Arithmetic T>
	struct AABB<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = AABB(T{0}, T{0}, T{0}, T{0}, T{0}, T{0}); ///< AABB(0, 0, 0, 0, 0, 0).
	};
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr AABB<T>::AABB(const T x, const T y, const T z, const T halfWidth, const T halfHeight, const T halfDepth) noexcept :
		center(x, y, z),
		extents(std::abs(halfWidth), std::abs(halfHeight), std::abs(halfDepth))
	{
	}

	template<Core::Arithmetic T>
	constexpr AABB<T>::AABB(const Core::Vector3<T>& center, const Core::Vector3<T>& extents) noexcept :
		center(center),
		extents(Core::Abs(extents))
	{
	}

	template<Core::Arithmetic T>
	constexpr AABB<T>::AABB(const Box<T>& box) noexcept :
		center(box.Center()),
		extents(std::abs(box.Width() / T{2}), std::abs(box.Height() / T{2}), std::abs(box.Depth() / T{2}))
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

	template<Core::Arithmetic T>
	constexpr T AABB<T>::ExtentX() const noexcept
	{
		return extents[0];
	}

	template<Core::Arithmetic T>
	constexpr void AABB<T>::ExtentX(const T extent) noexcept
	{
		extents[0] = std::abs(extent);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::ExtentY() const noexcept
	{
		return extents[1];
	}

	template<Core::Arithmetic T>
	constexpr void AABB<T>::ExtentY(const T extent) noexcept
	{
		extents[1] = std::abs(extent);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::ExtentZ() const noexcept
	{
		return extents[2];
	}

	template<Core::Arithmetic T>
	constexpr void AABB<T>::ExtentZ(const T extent) noexcept
	{
		extents[2] = std::abs(extent);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<Core::Arithmetic T>
	constexpr void AABB<T>::Extent(const std::size_t index, const T extent) noexcept
	{
		extents[index] = std::abs(extent);
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector3<T>& AABB<T>::Extents() const noexcept
	{
		return extents;
	}

	template<Core::Arithmetic T>
	constexpr void AABB<T>::Extents(const Core::Vector3<T>& extents) noexcept
	{
		this->extents = Core::Abs(extents);
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Width() const noexcept
	{
		return ExtentX() * T{2};
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Height() const noexcept
	{
		return ExtentY() * T{2};
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Depth() const noexcept
	{
		return ExtentZ() * T{2};
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
	constexpr Core::Vector3<T> AABB<T>::Min() const noexcept
	{
		return Core::Vector3<T>(MinX(), MinY(), MinZ());
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Min(const std::size_t index) const noexcept
	{
		return center[index] - extents[index];
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
	constexpr Core::Vector3<T> AABB<T>::Max() const noexcept
	{
		return Core::Vector3<T>(MaxX(), MaxY(), MaxZ());
	}

	template<Core::Arithmetic T>
	constexpr T AABB<T>::Max(const std::size_t index) const noexcept
	{
		return center[index] + extents[index];
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
		Core::Vector2<T> corner;
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
		return (ExtentX() * ExtentY() + ExtentY() * ExtentZ() + ExtentX() * ExtentZ()) * T{8};
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
	constexpr bool AABB<T>::Contains(const Core::Vector3<T>& point) const noexcept
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

	template<Core::Arithmetic T>
	std::string AABB<T>::ToString() const
	{
		return std::format("Center: {}, Extents: {}", center.ToString(), extents.ToString());
	}

	template<Core::Arithmetic T>
	template<Core::Arithmetic U>
	constexpr AABB<T>::operator AABB<U>() const noexcept
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
