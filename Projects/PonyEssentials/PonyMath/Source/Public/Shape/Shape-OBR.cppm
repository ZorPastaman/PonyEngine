/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Shape:OBR;

import <array>;
import <concepts>;
import <format>;
import <span>;
import <string>;

import PonyMath.Core;

import :AABR;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class OBR final
	{
	public:
		using ValueType = T; ///< Value type.

		static constexpr std::size_t AxesCount = 2;

		static constexpr std::size_t LeftBottomIndex = 0;
		static constexpr std::size_t RightBottomIndex = 1;
		static constexpr std::size_t LeftTopIndex = 2;
		static constexpr std::size_t RightTopIndex = 3;
		static constexpr std::size_t CornerCount = 4;

		[[nodiscard("Pure constructor")]]
		constexpr OBR() noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const AABR<T>& aabr, T angle) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const AABR<T>& aabr, const Core::Matrix2x2<T>& rs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const AABR<T>& aabr, const Core::Matrix3x3<T>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const OBR& obr, T angle) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const OBR& obr, const Core::Matrix2x2<T>& rs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const OBR& obr, const Core::Matrix3x3<T>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(const OBR& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr OBR(OBR&& other) noexcept = default;

		constexpr ~OBR() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Center() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Extent(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Extents() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& AxisX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& AxisY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector2<T>& Axis(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::span<const Core::Vector2<T>, 2> Axes() const noexcept;

		[[nodiscard("Pure function")]]
		Core::Vector2<T> LeftBottom() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector2<T> RightBottom() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector2<T> LeftTop() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector2<T> RightTop() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector2<T> Corner(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::array<Core::Vector2<T>, 4> Corners() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Size(std::size_t index) const noexcept;

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
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector2<T>& point) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator OBR<U>() const noexcept;

		constexpr OBR& operator =(const OBR& other) noexcept = default;
		constexpr OBR& operator =(OBR&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const OBR& other) const noexcept = default;

	private:
		void ResolveExtentsAxes() noexcept;

		Core::Vector2<T> center;
		Core::Vector2<T> extents;
		std::array<Core::Vector2<T>, 2> axes;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const OBR<T>& left, const OBR<T>& right, T tolerance = T{0.00001}) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBR<T>& obr);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr OBR<T>::OBR() noexcept :
		axes{ Core::Vector2<T>::Predefined::Right, Core::Vector2<T>::Predefined::Up }
	{
	}

	template<std::floating_point T>
	constexpr OBR<T>::OBR(const AABR<T>& aabr, const T angle) noexcept :
		OBR(aabr, Core::RotationMatrix(angle))
	{
	}

	template<std::floating_point T>
	constexpr OBR<T>::OBR(const AABR<T>& aabr, const Core::Matrix2x2<T>& rs) noexcept :
		center(rs * aabr.Center()),
		extents(aabr.Extents()),
		axes{ rs * AABR<T>::Axes[0], rs * AABR<T>::Axes[1] }
	{
		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr OBR<T>::OBR(const AABR<T>& aabr, const Core::Matrix3x3<T>& trs) noexcept :
		center(Core::TransformPoint(trs, aabr.Center())),
		extents(aabr.Extents()),
		axes{ Core::TransformDirection(trs, AABR<T>::Axes[0]), Core::TransformDirection(trs, AABR<T>::Axes[1]) }
	{
		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr OBR<T>::OBR(const OBR& obr, const T angle) noexcept :
		OBR(obr, Core::RotationMatrix(angle))
	{
	}

	template<std::floating_point T>
	constexpr OBR<T>::OBR(const OBR& obr, const Core::Matrix2x2<T>& rs) noexcept :
		center(rs * obr.Center()),
		extents(obr.Extents()),
		axes{ rs * obr.AxisX(), rs * obr.AxisY() }
	{
		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr OBR<T>::OBR(const OBR& obr, const Core::Matrix3x3<T>& trs) noexcept :
		center(Core::TransformPoint(trs, obr.Center())),
		extents(obr.Extents()),
		axes{ Core::TransformDirection(trs, obr.AxisX()), Core::TransformDirection(trs, obr.AxisY()) }
	{
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
	Core::Vector2<T> OBR<T>::LeftBottom() const noexcept
	{
		return Center() - AxisX() * ExtentX() - AxisY() * ExtentY();
	}

	template<std::floating_point T>
	Core::Vector2<T> OBR<T>::RightBottom() const noexcept
	{
		return Center() + AxisX() * ExtentX() - AxisY() * ExtentY();
	}

	template<std::floating_point T>
	Core::Vector2<T> OBR<T>::LeftTop() const noexcept
	{
		return Center() - AxisX() * ExtentX() + AxisY() * ExtentY();
	}

	template<std::floating_point T>
	Core::Vector2<T> OBR<T>::RightTop() const noexcept
	{
		return Center() + AxisX() * ExtentX() + AxisY() * ExtentY();
	}

	template<std::floating_point T>
	Core::Vector2<T> OBR<T>::Corner(const std::size_t index) const noexcept
	{
		const T extentX = index & 1 ? ExtentX() : -ExtentX();
		const T extentY = index & 2 ? ExtentY() : -ExtentY();

		return Center() + AxisX() * extentX + AxisY() * extentY;
	}

	template<std::floating_point T>
	std::array<Core::Vector2<T>, 4> OBR<T>::Corners() const noexcept
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
	constexpr T OBR<T>::Width() const noexcept
	{
		return ExtentX() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBR<T>::Height() const noexcept
	{
		return ExtentY() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBR<T>::Size(const std::size_t index) const noexcept
	{
		return Extent(index) * T{2};
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
			if (const T multiplier = axes[i].Magnitude(); multiplier > T{0.0001})
			{
				extents[i] *= multiplier;
				axes[i] *= T{1} / multiplier;
			}
			else
			{
				incorrectFlags |= 1 << i;
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
		default:
			break;
		}
	}

	template<std::floating_point T>
	template<Core::Arithmetic U>
	constexpr OBR<T>::operator OBR<U>() const noexcept
	{
		OBR<U> answer;
		answer.center = static_cast<Core::Vector2<U>>(center);
		answer.extents = static_cast<Core::Vector2<U>>(extents);
		answer.axes[0] = static_cast<Core::Vector2<U>>(axes[0]);
		answer.axes[1] = static_cast<Core::Vector2<U>>(axes[1]);

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
