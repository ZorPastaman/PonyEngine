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
import <cstddef>;
import <format>;
import <string>;

import PonyMath.Core;

import :Rect;

export namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	class AABR final
	{
	public:
		using ValueType = T; ///< Value type.

		struct Predefined; ///< Predefined AABRs.

		static constexpr std::size_t LeftBottomIndex = 0;
		static constexpr std::size_t RightBottomIndex = 1;
		static constexpr std::size_t LeftTopIndex = 2;
		static constexpr std::size_t RightTopIndex = 3;
		static constexpr std::size_t CornerCount = 4;

		[[nodiscard("Pure constructor")]]
		constexpr AABR() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr AABR(T x, T y, T halfWidth, T halfHeight) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr AABR(const Core::Vector2<T>& center, const Core::Vector2<T>& extents) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr AABR(const Rect<T>& rect) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr AABR(const AABR& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr AABR(AABR&& other) noexcept = default;

		constexpr ~AABR() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Center() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Center() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T>& Extents() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Extents() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T& ExtentX() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& ExtentY() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T& Extent(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Extent(std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
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
		/// @brief Gets the minimal point.
		/// @return Minimal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Min() const noexcept;
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
		/// @brief Gets the maximal point.
		/// @return Maximal point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Max() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Max(std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> LeftBottom() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> RightBottom() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> LeftTop() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> RightTop() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Corner(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::array<Core::Vector2<T>, 4> Corners() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Corner(std::size_t index, T angle) const noexcept requires (std::is_floating_point_v<T>);
		[[nodiscard("Pure function")]]
		constexpr std::array<Core::Vector2<T>, 4> Corners(T angle) const noexcept requires (std::is_floating_point_v<T>);

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

		constexpr void ResolveNegativeExtents() noexcept;

		/// @brief Creates a string representing the rect.
		/// @return String representing the rect.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the rect to a rect of another type.
		/// @tparam U Target type.
		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator AABR<U>() const noexcept;
		[[nodiscard("Pure operator")]]
		explicit constexpr operator Rect<T>() const noexcept;

		constexpr AABR& operator =(const AABR& other) noexcept = default;
		constexpr AABR& operator =(AABR&& other) noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr bool operator ==(const AABR& other) const noexcept = default;

	private:
		Core::Vector2<T> center;
		Core::Vector2<T> extents;
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

		static constexpr auto Zero = Rect(T{0}, T{0}, T{0}, T{0}); ///< AABR(0, 0, 0, 0).
	};
}

namespace PonyMath::Shape
{
	template<Core::Arithmetic T>
	constexpr AABR<T>::AABR(const T x, const T y, const T halfWidth, const T halfHeight) noexcept :
		center(x, y),
		extents(halfWidth, halfHeight)
	{
	}

	template<Core::Arithmetic T>
	constexpr AABR<T>::AABR(const Core::Vector2<T>& center, const Core::Vector2<T>& extents) noexcept :
		center(center),
		extents(extents)
	{
	}

	template<Core::Arithmetic T>
	constexpr AABR<T>::AABR(const Rect<T>& rect) noexcept :
		center(rect.Center()),
		extents(rect.Width() / T{2}, rect.Height() / T{2})
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
	constexpr Core::Vector2<T>& AABR<T>::Extents() noexcept
	{
		return extents;
	}

	template<Core::Arithmetic T>
	constexpr const Core::Vector2<T>& AABR<T>::Extents() const noexcept
	{
		return extents;
	}

	template<Core::Arithmetic T>
	constexpr T& AABR<T>::ExtentX() noexcept
	{
		return extents[0];
	}

	template<Core::Arithmetic T>
	constexpr const T& AABR<T>::ExtentX() const noexcept
	{
		return extents[0];
	}

	template<Core::Arithmetic T>
	constexpr T& AABR<T>::ExtentY() noexcept
	{
		return extents[1];
	}

	template<Core::Arithmetic T>
	constexpr const T& AABR<T>::ExtentY() const noexcept
	{
		return extents[1];
	}

	template<Core::Arithmetic T>
	constexpr T& AABR<T>::Extent(const std::size_t index) noexcept
	{
		return extents[index];
	}

	template<Core::Arithmetic T>
	constexpr const T& AABR<T>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Width() const noexcept
	{
		return ExtentX() * T{2};
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Height() const noexcept
	{
		return ExtentY() * T{2};
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
	constexpr Core::Vector2<T> AABR<T>::Min() const noexcept
	{
		return Core::Vector2<T>(MinX(), MinY());
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Min(const std::size_t index) const noexcept
	{
		return center[index] - extents[index];
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
	constexpr Core::Vector2<T> AABR<T>::Max() const noexcept
	{
		return Core::Vector2<T>(MaxX(), MaxY());
	}

	template<Core::Arithmetic T>
	constexpr T AABR<T>::Max(const std::size_t index) const noexcept
	{
		return center[index] + extents[index];
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
	constexpr Core::Vector2<T> AABR<T>::Corner(const std::size_t index, const T angle) const noexcept requires (std::is_floating_point_v<T>)
	{
		return Core::Rotate(Corner(index) - Center(), angle) + Center();
	}

	template<Core::Arithmetic T>
	constexpr std::array<Core::Vector2<T>, 4> AABR<T>::Corners(const T angle) const noexcept requires (std::is_floating_point_v<T>)
	{
		const Core::Matrix2x2<T> rotation = Core::RotationMatrix(angle);
		const Core::Vector2<T> extentsX = rotation * Core::Vector2<T>(ExtentX(), T{0});
		const Core::Vector2<T> extentsY = rotation * Core::Vector2<T>(T{0}, ExtentY());

		return std::array<Core::Vector2<T>, 4>
		{
			Center() - extentsX - extentsY,
			Center() + extentsX - extentsY,
			Center() - extentsX + extentsY,
			Center() + extentsX + extentsY,
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
	constexpr void AABR<T>::ResolveNegativeExtents() noexcept
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			extents[i] = std::abs(extents[i]);
		}
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
