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

export module PonyMath.Shape:OBB;

import <array>;
import <concepts>;
import <format>;
import <span>;
import <string>;

import PonyMath.Core;

import :AABB;

export namespace PonyMath::Shape
{
	template<std::floating_point T>
	class OBB final
	{
	public:
		using ValueType = T; ///< Value type.

		static constexpr std::size_t AxesCount = 3;

		static constexpr std::size_t LeftBottomNearIndex = 0;
		static constexpr std::size_t RightBottomNearIndex = 1;
		static constexpr std::size_t LeftTopNearIndex = 2;
		static constexpr std::size_t RightTopNearIndex = 3;
		static constexpr std::size_t LeftBottomFarIndex = 4;
		static constexpr std::size_t RightBottomFarIndex = 5;
		static constexpr std::size_t LeftTopFarIndex = 6;
		static constexpr std::size_t RightTopFarIndex = 7;
		static constexpr std::size_t CornerCount = 8;

		[[nodiscard("Pure constructor")]]
		constexpr OBB() noexcept;
		[[nodiscard("Pure constructor")]]
		explicit constexpr OBB(const AABB<T>& aabb) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const AABB<T>& aabb, const Core::Quaternion<T>& quaternion) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const AABB<T>& aabb, const Core::Matrix3x3<T>& rs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const AABB<T>& aabb, const Core::Matrix4x4<T>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const OBB& obb, const Core::Quaternion<T>& quaternion) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const OBB& obb, const Core::Matrix3x3<T>& rs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const OBB& obb, const Core::Matrix4x4<T>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const OBB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(OBB&& other) noexcept = default;

		constexpr ~OBB() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Center() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentZ() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const T& Extent(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Extents() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& AxisX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& AxisY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& AxisZ() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Axis(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		constexpr std::span<const Core::Vector3<T>, 3> Axes() const noexcept;

		[[nodiscard("Pure function")]]
		Core::Vector3<T> LeftBottomNear() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> RightBottomNear() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> LeftTopNear() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> RightTopNear() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> LeftBottomFar() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> RightBottomFar() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> LeftTopFar() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> RightTopFar() const noexcept;
		[[nodiscard("Pure function")]]
		Core::Vector3<T> Corner(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::array<Core::Vector3<T>, 8> Corners() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr T Width() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Height() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Depth() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Size(std::size_t index) const noexcept;

		/// @brief Computes an area.
		/// @return Area.
		[[nodiscard("Pure function")]]
		constexpr T Area() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr T Volume() const noexcept;

		/// @brief Checks if all the rect data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		[[nodiscard("Pure function")]]
		constexpr bool Contains(const Core::Vector3<T>& point) const noexcept;

		[[nodiscard("Pure function")]]
		std::string ToString() const;

		constexpr OBB& operator =(const OBB& other) noexcept = default;
		constexpr OBB& operator =(OBB&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const OBB& other) const noexcept = default;

	private:
		void ResolveExtentsAxes() noexcept;

		Core::Vector3<T> center;
		Core::Vector3<T> extents;
		std::array<Core::Vector3<T>, 3> axes;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const OBB<T>& left, const OBB<T>& right, T tolerance = T{ 0.00001 }) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBB<T>& obb);
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr OBB<T>::OBB() noexcept :
		axes{ Core::Vector3<T>::Predefined::Right, Core::Vector3<T>::Predefined::Up, Core::Vector3<T>::Predefined::Forward }
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb) noexcept :
		center(aabb.Center()),
		extents(aabb.Extents()),
		axes{ Core::Vector3<T>::Predefined::Right, Core::Vector3<T>::Predefined::Up, Core::Vector3<T>::Predefined::Forward }
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb, const Core::Quaternion<T>& quaternion) noexcept :
		OBB(aabb, Core::RotationMatrix(quaternion))
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb, const Core::Matrix3x3<T>& rs) noexcept :
		center(rs * aabb.Center()),
		extents(aabb.Extents()),
		axes{ rs * AABB<T>::Axes[0], rs * AABB<T>::Axes[1], rs * AABB<T>::Axes[2] }
	{
		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb, const Core::Matrix4x4<T>& trs) noexcept :
		center(Core::TransformPoint(trs, aabb.Center())),
		extents(aabb.Extents()),
		axes{ Core::TransformDirection(trs, AABB<T>::Axes[0]), Core::TransformDirection(trs, AABB<T>::Axes[1]), Core::TransformDirection(trs, AABB<T>::Axes[2]) }
	{
		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const OBB& obb, const Core::Quaternion<T>& quaternion) noexcept :
		OBB(obb, Core::RotationMatrix(quaternion))
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const OBB& obb, const Core::Matrix3x3<T>& rs) noexcept :
		center(rs * obb.Center()),
		extents(obb.Extents()),
		axes{ rs * obb.AxisX(), rs * obb.AxisY(), rs * obb.AxisZ() }
	{
		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const OBB& obb, const Core::Matrix4x4<T>& trs) noexcept :
		center(Core::TransformPoint(trs, obb.Center())),
		extents(obb.Extents()),
		axes{ Core::TransformDirection(trs, obb.AxisX()), Core::TransformDirection(trs, obb.AxisY()), Core::TransformDirection(trs, obb.AxisZ()) }
	{
		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::Center() const noexcept
	{
		return center;
	}

	template<std::floating_point T>
	constexpr const T& OBB<T>::ExtentX() const noexcept
	{
		return extents[0];
	}

	template<std::floating_point T>
	constexpr const T& OBB<T>::ExtentY() const noexcept
	{
		return extents[1];
	}

	template<std::floating_point T>
	constexpr const T& OBB<T>::ExtentZ() const noexcept
	{
		return extents[2];
	}

	template<std::floating_point T>
	constexpr const T& OBB<T>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::Extents() const noexcept
	{
		return extents;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::AxisX() const noexcept
	{
		return axes[0];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::AxisY() const noexcept
	{
		return axes[1];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::AxisZ() const noexcept
	{
		return axes[2];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::Axis(const std::size_t index) const noexcept
	{
		return axes[index];
	}

	template<std::floating_point T>
	constexpr std::span<const Core::Vector3<T>, 3> OBB<T>::Axes() const noexcept
	{
		return axes;
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftBottomNear() const noexcept
	{
		return Center() - AxisX() * ExtentX() - AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightBottomNear() const noexcept
	{
		return Center() + AxisX() * ExtentX() - AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftTopNear() const noexcept
	{
		return Center() - AxisX() * ExtentX() + AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightTopNear() const noexcept
	{
		return Center() + AxisX() * ExtentX() + AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftBottomFar() const noexcept
	{
		return Center() - AxisX() * ExtentX() - AxisY() * ExtentY() + AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightBottomFar() const noexcept
	{
		return Center() + AxisX() * ExtentX() - AxisY() * ExtentY() + AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftTopFar() const noexcept
	{
		return Center() - AxisX() * ExtentX() + AxisY() * ExtentY() + AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightTopFar() const noexcept
	{
		return Center() + ExtentX() + ExtentY() + ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::Corner(const std::size_t index) const noexcept
	{
		const T extentX = index & 1 ? ExtentX() : -ExtentX();
		const T extentY = index & 2 ? ExtentY() : -ExtentY();
		const T extentZ = index & 4 ? ExtentZ() : -ExtentZ();

		return Center() + AxisX() * extentX + AxisY() * extentY + AxisZ() * extentZ;
	}

	template<std::floating_point T>
	std::array<Core::Vector3<T>, 8> OBB<T>::Corners() const noexcept
	{
		const Core::Vector3<T> extentX = AxisX() * ExtentX();
		const Core::Vector3<T> extentY = AxisY() * ExtentY();
		const Core::Vector3<T> extentZ = AxisZ() * ExtentZ();

		return std::array<Core::Vector3<T>, 8>
		{
			center - extentX - extentY - extentZ,
			center + extentX - extentY - extentZ,
			center - extentX + extentY - extentZ,
			center + extentX + extentY - extentZ,
			center - extentX - extentY + extentZ,
			center + extentX - extentY + extentZ,
			center - extentX + extentY + extentZ,
			center + extentX + extentY + extentZ
		};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Width() const noexcept
	{
		return ExtentX() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Height() const noexcept
	{
		return ExtentY() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Depth() const noexcept
	{
		return ExtentZ() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Size(const std::size_t index) const noexcept
	{
		return Extent(index) * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Area() const noexcept
	{
		return (ExtentX() * ExtentY() + ExtentX() * ExtentZ() + ExtentY() * ExtentZ()) * T{8};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Volume() const noexcept
	{
		return ExtentX() * ExtentY() * ExtentZ() * T{8};
	}

	template<std::floating_point T>
	bool OBB<T>::IsFinite() const noexcept
	{
		return Center().IsFinite() && Extents().IsFinite() && AxisX().IsFinite() && AxisY().IsFinite() && AxisZ().IsFinite();
	}

	template<std::floating_point T>
	constexpr bool OBB<T>::Contains(const Core::Vector3<T>& point) const noexcept
	{
		const Core::Vector3<T> delta = point - Center();
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			if (const T dot = Core::Dot(delta, Axis(i)); std::abs(dot) > Extent(i))
			{
				return false;
			}
		}

		return true;
	}

	template<std::floating_point T>
	std::string OBB<T>::ToString() const
	{
		return std::format("Center: {}, Extents: {}, AxisX: {}, AxisY: {}, AxisZ: {}", Center().ToString(), Extents().ToString(), AxisX().ToString(), AxisY().ToString(), AxisZ().ToString());
	}

	template<std::floating_point T>
	void OBB<T>::ResolveExtentsAxes() noexcept
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
				incorrectFlags |= std::size_t{1} << i;
			}
		}

		switch (incorrectFlags)
		{
		case 1:
			extents[0] = T{0};
			axes[0] = Core::Cross(axes[1], axes[2]);
			break;
		case 2:
			extents[1] = T{0};
			axes[1] = Core::Cross(axes[2], axes[0]);
			break;
		case 3:
			extents[0] = T{0};
			extents[1] = T{0};
			axes[0] = Core::Vector3<T>(axes[2].Z(), axes[2].Y(), -axes[2].X());
			axes[1] = Core::Cross(axes[2], axes[0]);
			break;
		case 4:
			extents[2] = T{0};
			axes[2] = Core::Cross(axes[0], axes[1]);
			break;
		case 5:
			extents[0] = T{0};
			extents[2] = T{0};
			axes[0] = Core::Vector3<T>(axes[1].Y(), -axes[1].X(), axes[1].Z());
			axes[2] = Core::Cross(axes[0], axes[1]);
			break;
		case 6:
			extents[1] = T{0};
			extents[2] = T{0};
			axes[1] = Core::Vector3<T>(-axes[0].Y(), axes[0].X(), axes[0].Z());
			axes[2] = Core::Cross(axes[0], axes[1]);
			break;
		case 7:
			extents[0] = T{0};
			extents[1] = T{0};
			extents[2] = T{0};
			axes[0] = Core::Vector3<T>::Predefined::Right;
			axes[1] = Core::Vector3<T>::Predefined::Up;
			axes[2] = Core::Vector3<T>::Predefined::Forward;
			break;
		default:
			break;
		}
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const OBB<T>& left, const OBB<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) && Core::AreAlmostEqual(left.Extents(), right.Extents(), tolerance) &&
			Core::AreAlmostEqual(left.AxisX(), right.AxisX(), tolerance) && Core::AreAlmostEqual(left.AxisY(), right.AxisY(), tolerance) &&
			Core::AreAlmostEqual(left.AxisZ(), right.AxisZ(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBB<T>& obb)
	{
		return stream << obb.ToString();
	}
}
