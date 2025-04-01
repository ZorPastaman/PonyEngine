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

import :AABB;

export namespace PonyMath::Shape
{
	/// @brief Oriented bounding box implementation.
	/// @tparam T Component type.
	template<std::floating_point T>
	class OBB final
	{
	public:
		using ValueType = T; ///< Component type.

		static constexpr std::size_t AxesCount = 3; ///< Axes count.

		static constexpr std::size_t LeftBottomNearIndex = 0; ///< Left bottom near corner index.
		static constexpr std::size_t RightBottomNearIndex = 1; ///< Right bottom near corner index.
		static constexpr std::size_t LeftTopNearIndex = 2; ///< Left top near corner index.
		static constexpr std::size_t RightTopNearIndex = 3; ///< Right top near corner index.
		static constexpr std::size_t LeftBottomFarIndex = 4; ///< Left bottom far corner index.
		static constexpr std::size_t RightBottomFarIndex = 5; ///< Right bottom far corner index.
		static constexpr std::size_t LeftTopFarIndex = 6; ///< Left top far corner index.
		static constexpr std::size_t RightTopFarIndex = 7; ///< Right top far corner index.
		static constexpr std::size_t CornerCount = 8; ///< Corner count.

		struct Predefined; ///< Predefined OBBs.

		/// @brief Creates a zero OBB.
		[[nodiscard("Pure constructor")]]
		constexpr OBB() noexcept;
		/// @brief Creates an OBB that covers the same space as the @p aabb.
		/// @param aabb Axis-aligned bounding box.
		[[nodiscard("Pure constructor")]]
		explicit constexpr OBB(const AABB<T>& aabb) noexcept;
		/// @brief Creates an OBB that is the @p aabb rotated with the @p quaternion.
		/// @param aabb Axis-aligned bounding box.
		/// @param quaternion Rotation around origin.
		[[nodiscard("Pure constructor")]]
		OBB(const AABB<T>& aabb, const Core::Quaternion<T>& quaternion) noexcept;
		/// @brief Creates an OBB that is the @p aabb transformed with the @p rs matrix.
		/// @param aabb Axis-aligned bounding box.
		/// @param rs Rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBB(const AABB<T>& aabb, const Core::Matrix3x3<T>& rs) noexcept;
		/// @brief Creates an OBB that is the @p aabb transformed with the @p trs matrix.
		/// @param aabb Axis-aligned bounding box.
		/// @param trs Translation-rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBB(const AABB<T>& aabb, const Core::Matrix4x4<T>& trs) noexcept;
		/// @brief Creates an OBB that is the @p obb rotated with the @p quaternion.
		/// @param obb Oriented bounding box.
		/// @param quaternion Rotation around origin.
		[[nodiscard("Pure constructor")]]
		OBB(const OBB& obb, const Core::Quaternion<T>& quaternion) noexcept;
		/// @brief Creates an OBB that is the @p obb transformed with the @p rs matrix.
		/// @param obb Oriented bounding box.
		/// @param rs Rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBB(const OBB& obb, const Core::Matrix3x3<T>& rs) noexcept;
		/// @brief Creates an OBB that is the @p obb transformed with the @p trs matrix.
		/// @param obb Oriented bounding box.
		/// @param trs Translation-rotation-scaling matrix.
		[[nodiscard("Pure constructor")]]
		OBB(const OBB& obb, const Core::Matrix4x4<T>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const OBB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(OBB&& other) noexcept = default;

		constexpr ~OBB() noexcept = default;

		/// @brief Gets the center.
		/// @return Center.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Center() const noexcept;
		/// @brief Gets the x-axis extent.
		/// @return X-axis extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentX() const noexcept;
		/// @brief Gets the y-axis extent.
		/// @return Y-axis extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentY() const noexcept;
		/// @brief Gets the z-axis extent.
		/// @return Z-axis extent.
		[[nodiscard("Pure function")]]
		constexpr const T& ExtentZ() const noexcept;
		/// @brief Gets the extent of an axis at the @p index.
		/// @param index Axis index. 0 -> x, 1 -> y, 2 -> z.
		/// @return Extent.
		[[nodiscard("Pure function")]]
		constexpr const T& Extent(std::size_t index) const noexcept;
		/// @brief Gets extents.
		/// @return Extents.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Extents() const noexcept;
		/// @brief Gets the x-axis.
		/// @return X-axis. It's always unit.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& AxisX() const noexcept;
		/// @brief Gets the y-axis.
		/// @return Y-axis. It's always unit.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& AxisY() const noexcept;
		/// @brief Gets the z-axis.
		/// @return Z-axis. It's always unit.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& AxisZ() const noexcept;
		/// @brief Gets an axis by the @p index.
		/// @param index Axis index. 0 -> x, 1 -> y, 2 -> z.
		/// @return Axis.
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Axis(std::size_t index) const noexcept;
		/// @brief Gets the axes.
		/// @return Axes. 0 -> x, 1 -> y, 2 -> z.
		[[nodiscard("Pure function")]]
		constexpr std::span<const Core::Vector3<T>, 3> Axes() const noexcept;

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

		/// @brief Calculates a left bottom near point.
		/// @return Left bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomNear() const noexcept;
		/// @brief Calculates a right bottom near point.
		/// @return Right bottom near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomNear() const noexcept;
		/// @brief Calculates a left top near point.
		/// @return Left top near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopNear() const noexcept;
		/// @brief Calculates a right near point.
		/// @return Right top near point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopNear() const noexcept;
		/// @brief Calculates a left bottom far point.
		/// @return Left bottom far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftBottomFar() const noexcept;
		/// @brief Calculates a right bottom far point.
		/// @return Right bottom far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightBottomFar() const noexcept;
		/// @brief Calculates a left top far point.
		/// @return Left top far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> LeftTopFar() const noexcept;
		/// @brief Calculates a right top far point.
		/// @return Right top far point.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> RightTopFar() const noexcept;
		/// @brief Calculates a corner by the @p index.
		/// @param index Corner index.
		/// @return Corner.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> Corner(std::size_t index) const noexcept;
		/// @brief Calculates corners.
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

		/// @brief Checks if all the rect data is finite.
		/// @return @a True if they are finite; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFinite() const noexcept;

		/// @brief Checks if the OBB contains the @p point.
		/// @param point Point to check.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool Contains(const Core::Vector3<T>& point) const noexcept;
		/// @brief Calculates the closest point on the box.
		/// @param point Point.
		/// @return The closest point. If the @p point lies inside the box, the @p point is returned.
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T> ClosestPoint(const Core::Vector3<T>& point) const noexcept;

		/// @brief Creates a string representing the OBB.
		/// @return String representing the OBB.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		/// @brief Converts the OBB to an OBB of another type.
		/// @tparam U Target type.
		template<std::floating_point U> [[nodiscard("Pure operator")]]
		explicit constexpr operator OBB<U>() const noexcept;

		constexpr OBB& operator =(const OBB& other) noexcept = default;
		constexpr OBB& operator =(OBB&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const OBB& other) const noexcept = default;

	private:
		/// @brief Makes every axis unit and multiplies extents by their magnitudes. It also solves zero-length axes.
		void ResolveExtentsAxes() noexcept;

		Core::Vector3<T> center; ///< Center.
		Core::Vector3<T> extents; ///< Extents.
		std::array<Core::Vector3<T>, 3> axes; ///< Axes in order x, y, z.

		friend class OBB;
	};

	/// @brief Checks if the two OBBs are almost equal with the tolerance value.
	/// @tparam T Component type.
	/// @param left Left OBB.
	/// @param right Right OBB.
	/// @param tolerance Tolerance value. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const OBB<T>& left, const OBB<T>& right, T tolerance = T{0.00001}) noexcept;

	/// @brief Puts obb.ToString() into the @p stream.
	/// @tparam T Component type.
	/// @param stream Target stream.
	/// @param obb Source OBB.
	/// @return @p stream.
	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBB<T>& obb);

	template<std::floating_point T>
	struct OBB<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static inline const auto Zero = OBB(AABB<float>::Predefined::Zero); ///< Zero OBB.
	};
}

namespace PonyMath::Shape
{
	/// @brief Calculates a random perpendicular to the @p vector.
	/// @tparam T Component type.
	/// @param vector Source vector.
	/// @return Perpendicular.
	template<std::floating_point T>
	Core::Vector3<T> RandomPerpendicular(const Core::Vector3<T>& vector) noexcept;

	template<std::floating_point T>
	constexpr OBB<T>::OBB() noexcept :
		center(),
		extents(),
		axes(AABB<T>::Axes)
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb) noexcept :
		center(aabb.Center()),
		extents(aabb.Extents()),
		axes(AABB<T>::Axes)
	{
	}

	template<std::floating_point T>
	OBB<T>::OBB(const AABB<T>& aabb, const Core::Quaternion<T>& quaternion) noexcept :
		OBB(aabb, Core::RotationMatrix(quaternion))
	{
	}

	template<std::floating_point T>
	OBB<T>::OBB(const AABB<T>& aabb, const Core::Matrix3x3<T>& rs) noexcept :
		center(rs * aabb.Center()),
		extents(aabb.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			axes[i] = rs.Column(i);
		}

		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	OBB<T>::OBB(const AABB<T>& aabb, const Core::Matrix4x4<T>& trs) noexcept :
		center(Core::TransformPoint(trs, aabb.Center())),
		extents(aabb.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			axes[i] = PonyMath::Core::Vector3<T>(trs.Span(i).template subspan<0, 3>());
		}

		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	OBB<T>::OBB(const OBB& obb, const Core::Quaternion<T>& quaternion) noexcept :
		OBB(obb, Core::RotationMatrix(quaternion))
	{
	}

	template<std::floating_point T>
	OBB<T>::OBB(const OBB& obb, const Core::Matrix3x3<T>& rs) noexcept :
		center(rs * obb.Center()),
		extents(obb.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			axes[i] = rs * obb.Axis(i);
		}

		ResolveExtentsAxes();
	}

	template<std::floating_point T>
	OBB<T>::OBB(const OBB& obb, const Core::Matrix4x4<T>& trs) noexcept :
		center(Core::TransformPoint(trs, obb.Center())),
		extents(obb.Extents())
	{
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			axes[i] = Core::TransformDirection(trs, obb.Axis(i));
		}

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
	constexpr T OBB<T>::Width() const noexcept
	{
		return Size(0);
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Height() const noexcept
	{
		return Size(1);
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Depth() const noexcept
	{
		return Size(2);
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Size(const std::size_t index) const noexcept
	{
		return Extent(index) * T{2};
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::LeftBottomNear() const noexcept
	{
		return Center() - AxisX() * ExtentX() - AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::RightBottomNear() const noexcept
	{
		return Center() + AxisX() * ExtentX() - AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::LeftTopNear() const noexcept
	{
		return Center() - AxisX() * ExtentX() + AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::RightTopNear() const noexcept
	{
		return Center() + AxisX() * ExtentX() + AxisY() * ExtentY() - AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::LeftBottomFar() const noexcept
	{
		return Center() - AxisX() * ExtentX() - AxisY() * ExtentY() + AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::RightBottomFar() const noexcept
	{
		return Center() + AxisX() * ExtentX() - AxisY() * ExtentY() + AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::LeftTopFar() const noexcept
	{
		return Center() - AxisX() * ExtentX() + AxisY() * ExtentY() + AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::RightTopFar() const noexcept
	{
		return Center() + AxisX() * ExtentX() + AxisY() * ExtentY() + AxisZ() * ExtentZ();
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::Corner(const std::size_t index) const noexcept
	{
		const T extentX = index & 1 ? ExtentX() : -ExtentX();
		const T extentY = index & 2 ? ExtentY() : -ExtentY();
		const T extentZ = index & 4 ? ExtentZ() : -ExtentZ();

		return Center() + AxisX() * extentX + AxisY() * extentY + AxisZ() * extentZ;
	}

	template<std::floating_point T>
	constexpr std::array<Core::Vector3<T>, 8> OBB<T>::Corners() const noexcept
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
	bool OBB<T>::Contains(const Core::Vector3<T>& point) const noexcept
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

	template <std::floating_point T>
	constexpr Core::Vector3<T> OBB<T>::ClosestPoint(const Core::Vector3<T>& point) const noexcept
	{
		const Core::Vector3<T> delta = point - center;

		Core::Vector3<T> answer = center;
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			const T dot = Core::Dot(delta, axes[i]);
			answer += axes[i] * std::clamp(dot, -extents[i], extents[i]);
		}

		return answer;
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
			axes[0] = Core::Cross(axes[1], axes[2]);
			break;
		case 2:
			extents[1] = T{0};
			axes[1] = Core::Cross(axes[2], axes[0]);
			break;
		case 3:
			extents[0] = T{0};
			extents[1] = T{0};
			axes[0] = RandomPerpendicular(axes[2]).Normalized();
			axes[1] = Core::Cross(axes[2], axes[0]);
			break;
		case 4:
			extents[2] = T{0};
			axes[2] = Core::Cross(axes[0], axes[1]);
			break;
		case 5:
			extents[0] = T{0};
			extents[2] = T{0};
			axes[0] = RandomPerpendicular(axes[1]).Normalized();
			axes[2] = Core::Cross(axes[0], axes[1]);
			break;
		case 6:
			extents[1] = T{0};
			extents[2] = T{0};
			axes[1] = RandomPerpendicular(axes[0]).Normalized();
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
		default: [[likely]]
			break;
		}
	}

	template <std::floating_point T>
	template <std::floating_point U>
	constexpr OBB<T>::operator OBB<U>() const noexcept
	{
		OBB<U> answer;
		answer.center = static_cast<Core::Vector3<U>>(center);
		answer.extents = static_cast<Core::Vector3<U>>(extents);
		for (std::size_t i = 0; i < Core::Vector3<T>::ComponentCount; ++i)
		{
			answer.axes[i] = static_cast<Core::Vector3<U>>(axes[i]);
		}

		return answer;
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const OBB<T>& left, const OBB<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) && Core::AreAlmostEqual(left.Extents(), right.Extents(), tolerance) &&
			Core::AreAlmostEqual(left.AxisX(), right.AxisX(), tolerance) && Core::AreAlmostEqual(left.AxisY(), right.AxisY(), tolerance) &&
			Core::AreAlmostEqual(left.AxisZ(), right.AxisZ(), tolerance);
	}

	template <std::floating_point T>
	Core::Vector3<T> RandomPerpendicular(const Core::Vector3<T>& vector) noexcept
	{
		const Core::Vector3<T>& right = std::abs(vector.X()) > T{0.5} ? Core::Vector3<T>::Predefined::Up : Core::Vector3<T>::Predefined::Right;

		return Core::Cross(vector, right);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBB<T>& obb)
	{
		return stream << obb.ToString();
	}
}
