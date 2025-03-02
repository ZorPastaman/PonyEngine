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

export module PonyMath.Shape:AABR;

import <array>;
import <cmath>;
import <cstddef>;
import <format>;
import <ostream>;
import <string>;
import <type_traits>;

import PonyMath.Core;

import :Rect;

export namespace PonyMath::Shape
{
	/// @brief Axis-aligned bounding rect implementation.
	/// @tparam T Component type.
	template<Core::Arithmetic T>
	class AABR final
	{
	public:
		using ValueType = T; ///< Value type.

		/// @brief AABR axes.
		static constexpr std::array<Core::Vector2<T>, 2> Axes = { Core::Vector2<T>::Predefined::Right, Core::Vector2<T>::Predefined::Up };

		static constexpr std::size_t LeftBottomIndex = 0; ///< (MinX, MinY) corner index.
		static constexpr std::size_t RightBottomIndex = 1; ///< (MaxX, MinY) corner index.
		static constexpr std::size_t LeftTopIndex = 2; ///< (MinX, MaxY) corner index.
		static constexpr std::size_t RightTopIndex = 3; ///< (MaxX, MaxY) corner index.
		static constexpr std::size_t CornerCount = 4; ///< Corner count.

		struct Predefined; ///< Predefined AABRs.

		/// @brief Creates an empty AABR.
		[[nodiscard("Pure constructor")]]
		constexpr AABR() noexcept = default;
		/// @brief Creates an AABR.
		/// @param x Center x component.
		/// @param y Center y component.
		/// @param halfWidth Half width.
		/// @param halfHeight Half height.
		[[nodiscard("Pure constructor")]]
		AABR(T x, T y, T halfWidth, T halfHeight) noexcept;
		/// @brief Creates an AABR.
		/// @param center Center.
		/// @param extents Extents. Half-sizes in every dimension.
		[[nodiscard("Pure constructor")]]
		AABR(const Core::Vector2<T>& center, const Core::Vector2<T>& extents) noexcept;
		/// @brief Converts the @p rect to an AABR.
		/// @param rect Rect to convert.
		[[nodiscard("Pure constructor")]]
		explicit AABR(const Rect<T>& rect) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr AABR(const AABR& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr AABR(AABR&& other) noexcept = default;

		constexpr ~AABR() noexcept = default;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Center() noexcept;
		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Center() const noexcept;

		/// @brief Gets the x extent.
		/// @return X extent.
		[[nodiscard("Pure function")]]
		constexpr T ExtentX() const noexcept;
		/// @brief Sets the x extent.
		/// @param extent X extent to set.
		constexpr void ExtentX(T extent) noexcept;
		/// @brief Gets the y extent.
		/// @return Y extent.
		[[nodiscard("Pure function")]]
		constexpr T ExtentY() const noexcept;
		/// @brief Sets the y extent.
		/// @param extent Y extent to set.
		constexpr void ExtentY(T extent) noexcept;
		/// @brief Gets an extent by the @p index.
		/// @param index Extent index. 0 -> x, 1 -> y.
		/// @return Extent.
		[[nodiscard("Pure function")]]
		constexpr T Extent(std::size_t index) const noexcept;
		/// @brief Sets an extent by the @p index.
		/// @param index Extent index. 0 -> x, 1 -> y.
		/// @param extent Extent to set.
		constexpr void Extent(std::size_t index, T extent) noexcept;
		/// @brief Gets the extents.
		/// @return Extents.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Extents() const noexcept;
		/// @brief Sets the extents.
		/// @param extents Extents to set.
		constexpr void Extents(const Core::Vector2<T>& extents) noexcept;

		/// @brief Gets the width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		/// @brief Gets the height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		/// @brief Gets the size by the @p index.
		/// @param index Size index. 0 -> width, 1 -> height.
		/// @return Size.
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
		/// @brief Gets the minimal component by the @p index.
		/// @param index Component index. 0 -> x, 1 -> y.
		/// @return Minimal component.
		[[nodiscard("Pure function")]]
		constexpr T Min(std::size_t index) const noexcept;
		/// @brief Gets the minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Min() const noexcept;
		/// @brief Gets the maximal x point.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxX() const noexcept;
		/// @brief Gets the maximal x point.
		/// @return Maximal x.
		[[nodiscard("Pure function")]]
		constexpr T MaxY() const noexcept;
		/// @brief Gets the maximal component by the @p index.
		/// @param index Component index. 0 -> x, 1 -> y.
		/// @return Maximal component.
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;
		/// @brief Gets the maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Max() const noexcept;

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

		/// @brief Calculates a perimeter.
		/// @return Perimeter.
		[[nodiscard("Pure function")]]
		constexpr T Perimeter() const noexcept;
		/// @brief Calculates an area.
		/// @return Area.
		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;

		/// @brief Checks if all the AABR data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept requires (std::is_floating_point_v<T>);

		/// @brief Checks if the AABR contains the point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector2<T>& point) const noexcept;

		/// @brief Creates a string representing the AABR.
		/// @return String representing the AABR.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the AABR to an AABR of another type.
		/// @tparam U Target type.
		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator AABR<U>() const noexcept;
		/// @brief Converts the AABR to a rect.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Rect<T>() const noexcept;

		constexpr AABR& operator =(const AABR& other) noexcept = default;
		constexpr AABR& operator =(AABR&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr bool operator ==(const AABR& other) const noexcept = default;

	private:
		Core::Vector2<T> center; ///< Center
		Core::Vector2<T> extents; ///< Extents
	};

	/// @brief Checks if the two AABRs are almost equal with the tolerance value.
	/// @tparam T Value type.
	/// @param left Left rect.
	/// @param right Right rect.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const AABR<T>& left, const AABR<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts aabr.ToString() into the @p stream.
	/// @tparam T Value type.
	/// @param stream Target stream.
	/// @param aabr Source AABR.
	/// @return @p stream.
	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const AABR<T>& aabr);

	template<Core::Arithmetic T>
	struct AABR<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static inline const auto Zero = AABR(T{0}, T{0}, T{0}, T{0}); ///< AABR(0, 0, 0, 0).
	};
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	AABR<T>::AABR(const T x, const T y, const T halfWidth, const T halfHeight) noexcept :
		center(x, y),
		extents(std::abs(halfWidth), std::abs(halfHeight))
	{
	}

	template<Core::Arithmetic T>
	AABR<T>::AABR(const Core::Vector2<T>& center, const Core::Vector2<T>& extents) noexcept :
		center(center),
		extents(Core::Abs(extents))
	{
	}

	template<Core::Arithmetic T>
	AABR<T>::AABR(const Rect<T>& rect) noexcept :
		center(rect.Center()),
		extents(Core::Abs(rect.Size() / T{2}))
	{
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T>& AABR<T>::Center() noexcept
	{
		return center;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector2<T>& AABR<T>::Center() const noexcept
	{
		return center;
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::ExtentX() const noexcept
	{
		return Extent(0);
	}

	template<Core::Arithmetic T>
	constexpr void AABR<T>::ExtentX(const T extent) noexcept
	{
		Extent(0, extent);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::ExtentY() const noexcept
	{
		return Extent(1);
	}

	template<Core::Arithmetic T>
	constexpr void AABR<T>::ExtentY(const T extent) noexcept
	{
		Extent(1, extent);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<Core::Arithmetic T>
	constexpr void AABR<T>::Extent(const std::size_t index, const T extent) noexcept
	{
		extents[index] = std::abs(extent);
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector2<T>& AABR<T>::Extents() const noexcept
	{
		return extents;
	}

	template<Core::Arithmetic T>
	constexpr void AABR<T>::Extents(const Core::Vector2<T>& extents) noexcept
	{
		this->extents = Core::Abs(extents);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Width() const noexcept
	{
		return Size(0);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Height() const noexcept
	{
		return Size(1);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Size(const std::size_t index) const noexcept
	{
		return Extent(index) * T{2};
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::MinX() const noexcept
	{
		return Min(0);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::MinY() const noexcept
	{
		return Min(1);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Min(const std::size_t index) const noexcept
	{
		return center[index] - extents[index];
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> AABR<T>::Min() const noexcept
	{
		return Core::Vector2<T>(MinX(), MinY());
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::MaxX() const noexcept
	{
		return Max(0);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::MaxY() const noexcept
	{
		return Max(1);
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Max(const std::size_t index) const noexcept
	{
		return center[index] + extents[index];
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> AABR<T>::Max() const noexcept
	{
		return Core::Vector2<T>(MaxX(), MaxY());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> AABR<T>::LeftBottom() const noexcept
	{
		return Core::Vector2<T>(MinX(), MinY());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> AABR<T>::RightBottom() const noexcept
	{
		return Core::Vector2<T>(MaxX(), MinY());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> AABR<T>::LeftTop() const noexcept
	{
		return Core::Vector2<T>(MinX(), MaxY());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> AABR<T>::RightTop() const noexcept
	{
		return Core::Vector2<T>(MaxX(), MaxY());
	}

	template<Core::Arithmetic T>
	constexpr Core::Vector2<T> AABR<T>::Corner(const std::size_t index) const noexcept
	{
		Core::Vector2<T> corner;
		corner.X() = index & 1 ? MaxX() : MinX();
		corner.Y() = index & 2 ? MaxY() : MinY();

		return corner;
	}

	template<Core::Arithmetic T>
	constexpr std::array<Core::Vector2<T>, 4> AABR<T>::Corners() const noexcept
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
	constexpr T AABR<T>::Perimeter() const noexcept
	{
		return (ExtentX() + ExtentY()) * T{4};
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Area() const noexcept
	{
		return ExtentX() * ExtentY() * T{4};
	}

	template<Core::Arithmetic T>
	bool AABR<T>::IsFinite() const noexcept requires (std::is_floating_point_v<T>)
	{
		return center.IsFinite() && extents.IsFinite();
	}

	template<Core::Arithmetic T>
	constexpr bool AABR<T>::Contains(const Core::Vector2<T>& point) const noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			if (std::abs(point[i] - center[i]) > extents[i])
			{
				return false;
			}
		}

		return true;
	}

	template<Core::Arithmetic T>
	std::string AABR<T>::ToString() const
	{
		return std::format("Center: {}, Extents: {}", center.ToString(), extents.ToString());
	}

	template<Core::Arithmetic T>
	template<Core::Arithmetic U>
	constexpr AABR<T>::operator AABR<U>() const noexcept
	{
		return AABR<U>(static_cast<Core::Vector2<U>>(center), static_cast<Core::Vector2<U>>(extents));
	}

	template<Core::Arithmetic T>
	constexpr AABR<T>::operator Rect<T>() const noexcept
	{
		return Rect<T>(Min(), Max() - Min());
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const AABR<T>& left, const AABR<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) && Core::AreAlmostEqual(left.Extents(), right.Extents(), tolerance);
	}

	template<Core::Arithmetic T>
	std::ostream& operator <<(std::ostream& stream, const AABR<T>& aabr)
	{
		return stream << aabr.ToString();
	}
}
