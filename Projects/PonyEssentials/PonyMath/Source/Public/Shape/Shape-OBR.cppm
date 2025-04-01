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

export module PonyMath.Shape:OBR;

import <algorithm>;
import <array>;
import <concepts>;
import <cmath>;
import <cstddef>;
import <format>;
import <ostream>;
import <span>;
import <string>;

import PonyMath.Core;

import :AABR;

export namespace PonyMath::Shape
{
	/// @brief Oriented bounding rect implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class OBR final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t AxesCount = 2; ///< Axes count.

		static constexpr std::size_t LeftBottomIndex = 0; ///< Left bottom corner index.
		static constexpr std::size_t RightBottomIndex = 1; ///< Right bottom corner index.
		static constexpr std::size_t LeftTopIndex = 2; ///< Left top corner index.
		static constexpr std::size_t RightTopIndex = 3; ///< Right top corner index.
		static constexpr std::size_t CornerCount = 4; ///< Corner count.

		struct Predefined; ///< Predefined OBRs.

		/// @brief Creates a zero OBR.
		[[nodiscard("Pure constructor")]]
		constexpr OBR() noexcept;
		/// @brief Creates an OBR that covers the same space as the @p aabr.
		/// @param aabr Axis-aligned bounding rect.
		[[nodiscard("Pure constructor")]]
		explicit constexpr OBR(const AABR<T>& aabr) noexcept;
		/// @brief Creates an OBR that is the @p aabr rotated with the @p angle.
		/// @param aabr Axis-aligned bounding rect.
		/// @param angle Rotation angle in radians.
		[[nodiscard("Pure constructor")]]
		OBR(const AABR<T>& aabr, T angle) noexcept;
		/// @brief Creates an OBR that is the @p aabr transformed with the @p rs matrix.
		/// @param aabr Axis-aligned bounding rect.
		/// @param rs Rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBR(const AABR<T>& aabr, const Core::Matrix2x2<T>& rs) noexcept;
		/// @brief Creates an OBR that is the @p aabr transformed with the @p trs matrix.
		/// @param aabr Axis-aligned bounding rect.
		/// @param trs Translation-rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBR(const AABR<T>& aabr, const Core::Matrix3x3<T>& trs) noexcept;
		/// @brief Creates an OBR that is the @p obr rotated with the @p angle.
		/// @param obr Oriented bounding rect.
		/// @param angle Rotation angle in radians.
		[[nodiscard("Pure constructor")]]
		OBR(const OBR& obr, T angle) noexcept;
		/// @brief Creates an OBR that is the @p obr transformed with the @p rs matrix.
		/// @param obr Oriented bounding rect.
		/// @param rs Rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBR(const OBR& obr, const Core::Matrix2x2<T>& rs) noexcept;
		/// @brief Creates an OBR that is the @p obr transformed with the @p trs matrix.
		/// @param obr Oriented bounding rect.
		/// @param trs Translation-rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBR(const OBR& obr, const Core::Matrix3x3<T>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const OBR& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(OBR&& other) noexcept = default;

		constexpr ~OBR() noexcept = default;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Center() const noexcept;
		/// @brief Gets the x-extent.
		/// @return X-extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentX() const noexcept;
		/// @brief Gets the y-extent.
		/// @return Y-extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentY() const noexcept;
		/// @brief Gets an extent by the @p index.
		/// @param index Extent index. 0 -> x, 1 -> y.
		/// @return Extent.
		[[nodiscard("Pure function")]]
		constexpr const T& Extent(std::size_t index) const noexcept;
		/// @brief Gets the extents.
		/// @return Extents.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Extents() const noexcept;
		/// @brief Gets the x-axis.
		/// @return X-axis.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& AxisX() const noexcept;
		/// @brief Gets the y-axis.
		/// @return Y-axis.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& AxisY() const noexcept;
		/// @brief Gets an axis by the @p index.
		/// @param index Axis index. 0 -> x, 1 -> y.
		/// @return Axis.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Axis(std::size_t index) const noexcept;
		/// @brief Gets the axes.
		/// @return Axes.
		[[nodiscard("Pure function")]]
		constexpr std::span<const Core::Vector2<T>, 2> Axes() const noexcept;

		/// @brief Calculates a width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		/// @brief Calculates a height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		/// @brief Calculates a size by the @p index.
		/// @param index Size index. 0 -> x, y -> 1.
		/// @return Size.
		[[nodiscard("Pure function")]]
		constexpr T Size(std::size_t index) const noexcept;

		/// @brief Calculates a left bottom point.
		/// @return Left bottom point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> LeftBottom() const noexcept;
		/// @brief Calculates a right bottom point.
		/// @return Left bottom point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> RightBottom() const noexcept;
		/// @brief Calculates a left top point.
		/// @return Left bottom point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> LeftTop() const noexcept;
		/// @brief Calculates a right top point.
		/// @return Left bottom point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> RightTop() const noexcept;
		/// @brief Calculates a corner by the @p index.
		/// @param index Corner index.
		/// @return Corner.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> Corner(std::size_t index) const noexcept;
		/// @brief Calculates corners.
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

		/// @brief Checks if all the OBR data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Checks if the OBR contains the @p point.
		/// @param point Point to check.
		/// @return @a True if the OBR contains the @p point; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector2<T>& point) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector2<T> ClosestPoint(const Core::Vector2<T>& point) const noexcept;

		/// @brief Creates a string representing the OBR.
		/// @return String representing the OBR.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the OBR to an OBR of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator OBR<U>() const noexcept;

		constexpr OBR& operator =(const OBR& other) noexcept = default;
		constexpr OBR& operator =(OBR&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const OBR& other) const noexcept = default;

	private:
		/// @brief Makes every axis unit and multiplies extents by their magnitudes. It also solves zero-length axes.
		void ResolveExtentsAxes() noexcept;

		Core::Vector2<T> center; ///< Center.
		Core::Vector2<T> extents; ///< Extents.
		std::array<Core::Vector2<T>, 2> axes; ///< Axes in order x, y.

		friend class OBR;
	};

	/// @brief Checks if the two OBRs are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left OBR.
	/// @param right Right OBR.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const OBR<T>& left, const OBR<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts obr.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param obr Source OBR.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBR<T>& obr);

	template<std::floating_point T>
	struct OBR<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static inline const auto Zero = OBR(AABR<float>::Predefined::Zero); ///< Zero OBR.
	};
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr OBR<T>::OBR() noexcept :
		center(),
		extents(),
		axes(AABR<T>::Axes)
	{
	}

	template<std::floating_point T>
	constexpr OBR<T>::OBR(const AABR<T>& aabr) noexcept :
		center(aabr.Center()),
		extents(aabr.Extents()),
		axes(AABR<T>::Axes)
	{
	}

	template<std::floating_point T>
	OBR<T>::OBR(const AABR<T>& aabr, const T angle) noexcept :
		OBR(aabr, Core::RotationMatrix(angle))
	{
	}

	template<std::floating_point T>
	OBR<T>::OBR(const AABR<T>& aabr, const Core::Matrix2x2<T>& rs) noexcept :
		center(rs * aabr.Center()),
		extents(aabr.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			axes[i] = rs.Column(i);
		}

		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	OBR<T>::OBR(const AABR<T>& aabr, const Core::Matrix3x3<T>& trs) noexcept :
		center(Core::TransformPoint(trs, aabr.Center())),
		extents(aabr.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			axes[i] = PonyMath::Core::Vector2<T>(trs.Span(i).template subspan<0, 2>());
		}

		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	OBR<T>::OBR(const OBR& obr, const T angle) noexcept :
		OBR(obr, Core::RotationMatrix(angle))
	{
	}

	template<std::floating_point T>
	OBR<T>::OBR(const OBR& obr, const Core::Matrix2x2<T>& rs) noexcept :
		center(rs * obr.Center()),
		extents(obr.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			axes[i] = rs * obr.Axis(i);
		}

		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	OBR<T>::OBR(const OBR& obr, const Core::Matrix3x3<T>& trs) noexcept :
		center(Core::TransformPoint(trs, obr.Center())),
		extents(obr.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			axes[i] = Core::TransformDirection(trs, obr.Axis(i));
		}

		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& OBR<T>::Center() const noexcept
	{
		return center;
	}

	template<std::floating_point T>
	constexpr const T& OBR<T>::ExtentX() const noexcept
	{
		return extents[0];
	}

	template<std::floating_point T>
	constexpr const T& OBR<T>::ExtentY() const noexcept
	{
		return extents[1];
	}

	template<std::floating_point T>
	constexpr const T& OBR<T>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& OBR<T>::Extents() const noexcept
	{
		return extents;
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& OBR<T>::AxisX() const noexcept
	{
		return axes[0];
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& OBR<T>::AxisY() const noexcept
	{
		return axes[1];
	}

	template<std::floating_point T>
	constexpr const Core::Vector2<T>& OBR<T>::Axis(const std::size_t index) const noexcept
	{
		return axes[index];
	}

	template<std::floating_point T>
	constexpr std::span<const Core::Vector2<T>, 2> OBR<T>::Axes() const noexcept
	{
		return axes;
	}

	template<std::floating_point T>
	constexpr T OBR<T>::Width() const noexcept
	{
		return Size(0);
	}

	template<std::floating_point T>
	constexpr T OBR<T>::Height() const noexcept
	{
		return Size(1);
	}

	template<std::floating_point T>
	constexpr T OBR<T>::Size(const std::size_t index) const noexcept
	{
		return Extent(index) * T{2};
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> OBR<T>::LeftBottom() const noexcept
	{
		return Center() - AxisX() * ExtentX() - AxisY() * ExtentY();
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> OBR<T>::RightBottom() const noexcept
	{
		return Center() + AxisX() * ExtentX() - AxisY() * ExtentY();
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> OBR<T>::LeftTop() const noexcept
	{
		return Center() - AxisX() * ExtentX() + AxisY() * ExtentY();
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> OBR<T>::RightTop() const noexcept
	{
		return Center() + AxisX() * ExtentX() + AxisY() * ExtentY();
	}

	template<std::floating_point T>
	constexpr Core::Vector2<T> OBR<T>::Corner(const std::size_t index) const noexcept
	{
		const T extentX = index & 1 ? ExtentX() : -ExtentX();
		const T extentY = index & 2 ? ExtentY() : -ExtentY();

		return Center() + AxisX() * extentX + AxisY() * extentY;
	}

	template<std::floating_point T>
	constexpr std::array<Core::Vector2<T>, 4> OBR<T>::Corners() const noexcept
	{
		const Core::Vector2<T> extentX = AxisX() * ExtentX();
		const Core::Vector2<T> extentY = AxisY() * ExtentY();

		return std::array<Core::Vector2<T>, 4>
		{
			center - extentX - extentY,
			center + extentX - extentY,
			center - extentX + extentY,
			center + extentX + extentY
		};
	}

	template<std::floating_point T>
	constexpr T OBR<T>::Perimeter() const noexcept
	{
		return (ExtentX() + ExtentY()) * T{4};
	}

	template<std::floating_point T>
	constexpr T OBR<T>::Area() const noexcept
	{
		return ExtentX() * ExtentY() * T{4};
	}

	template<std::floating_point T>
	bool OBR<T>::IsFinite() const noexcept
	{
		return Center().IsFinite() && Extents().IsFinite() && AxisX().IsFinite() && AxisY().IsFinite();
	}

	template<std::floating_point T>
	constexpr bool OBR<T>::Contains(const Core::Vector2<T>& point) const noexcept
	{
		const Core::Vector2<T> delta = point - Center();
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			if (const T dot = Core::Dot(delta, Axis(i)); std::abs(dot) > Extent(i))
			{
				return false;
			}
		}

		return true;
	}

	template <std::floating_point T>
	constexpr Core::Vector2<T> OBR<T>::ClosestPoint(const Core::Vector2<T>& point) const noexcept
	{
		const Core::Vector2<T> delta = point - center;

		Core::Vector2<T> answer = center;
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			const T dot = Core::Dot(delta, axes[i]);
			answer += axes[i] * std::clamp(dot, -extents[i], extents[i]);
		}

		return answer;
	}

	template<std::floating_point T>
	std::string OBR<T>::ToString() const
	{
		return std::format("Center: {}, Extents: {}, AxisX: {}, AxisY: {}", Center().ToString(), Extents().ToString(), AxisX().ToString(), AxisY().ToString());
	}

	template<std::floating_point T>
	void OBR<T>::ResolveExtentsAxes() noexcept
	{
		std::size_t incorrectFlags = 0;
		for (std::size_t i = 0; i < axes.size(); ++i)
		{
			if (const T multiplier = axes[i].Magnitude(); multiplier > T{0.0001}) [[likely]]
			{
				extents[i] *= multiplier;
				axes[i] *= T{1} / multiplier;
			}
			else [[unlikely]]
			{
				incorrectFlags |= std::size_t{1} << i;
			}
		}

		switch (incorrectFlags)
		{
		case 1:
			extents[0] = T{0};
			axes[0] = Core::Vector2<T>(axes[1].Y(), -axes[1].X());
			break;
		case 2:
			extents[1] = T{0};
			axes[1] = Core::Vector2<T>(-axes[0].Y(), axes[0].X());
			break;
		case 3:
			extents[0] = T{0};
			extents[1] = T{0};
			axes[0] = Core::Vector2<T>::Predefined::Right;
			axes[1] = Core::Vector2<T>::Predefined::Up;
			break;
		default: [[likely]]
			break;
		}
	}

	template<std::floating_point T>
	template<std::floating_point U>
	constexpr OBR<T>::operator OBR<U>() const noexcept
	{
		OBR<U> answer;
		answer.center = static_cast<Core::Vector2<U>>(center);
		answer.extents = static_cast<Core::Vector2<U>>(extents);
		for (std::size_t i = 0; i < Core::Vector2<T>::ComponentCount; ++i)
		{
			answer.axes[i] = static_cast<Core::Vector2<U>>(axes[i]);
		}

		return answer;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const OBR<T>& left, const OBR<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) && Core::AreAlmostEqual(left.Extents(), right.Extents(), tolerance) &&
			Core::AreAlmostEqual(left.AxisX(), right.AxisX(), tolerance) && Core::AreAlmostEqual(left.AxisY(), right.AxisY(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBR<T>& obr)
	{
		return stream << obr.ToString();
	}
}
