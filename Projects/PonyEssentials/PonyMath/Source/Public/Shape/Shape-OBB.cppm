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

		struct Predefined; ///< Predefined OBBs.

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
		constexpr OBB() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const Core::Vector3<T>& center, const Core::Vector3<T>& extentX, const Core::Vector3<T>& extentY, const Core::Vector3<T>& extentZ) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const Core::Vector3<T>& center, std::span<const Core::Vector3<T>, 3> extents) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const AABB<T>& aabb, const Core::Quaternion<T>& quaternion) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const AABB<T>& aabb, const Core::Matrix3x3<T>& rs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const AABB<T>& aabb, const Core::Matrix4x4<T>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(const OBB& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr OBB(OBB&& other) noexcept = default;

		constexpr ~OBB() noexcept = default;

		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Center() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Center() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& ExtentX() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& ExtentX() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& ExtentY() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& ExtentY() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& ExtentZ() noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& ExtentZ() const noexcept;
		[[nodiscard("Pure function")]]
		constexpr Core::Vector3<T>& Extent(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		constexpr const Core::Vector3<T>& Extent(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<Core::Vector3<T>, 3> Extents() noexcept;
		[[nodiscard("Pure function")]]
		std::span<const Core::Vector3<T>, 3> Extents() const noexcept;

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

		template<Core::Arithmetic U> [[nodiscard("Pure operator")]]
		explicit constexpr operator OBB<U>() const noexcept;

		constexpr OBB& operator =(const OBB& other) noexcept = default;
		constexpr OBB& operator =(OBB&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const OBB& other) const noexcept = default;

	private:
		Core::Vector3<T> center;
		std::array<Core::Vector3<T>, 3> extents;
	};

	template<std::floating_point T> [[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const OBB<T>& left, const OBB<T>& right, T tolerance = T{ 0.00001 }) noexcept;

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBB<T>& obb);

	template<std::floating_point T>
	struct OBB<T>::Predefined final
	{
		NON_CONSTRUCTIBLE_BODY(Predefined)

		static constexpr auto Zero = OBB(Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Zero, Core::Vector3<T>::Predefined::Zero);
	};
}

namespace PonyMath::Shape
{
	template<std::floating_point T>
	constexpr OBB<T>::OBB(const Core::Vector3<T>& center, const Core::Vector3<T>& extentX, const Core::Vector3<T>& extentY, const Core::Vector3<T>& extentZ) noexcept :
		center(center),
		extents{ extentX, extentY, extentZ }
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const Core::Vector3<T>& center, std::span<const Core::Vector3<T>, 3> extents) noexcept :
		center(center)
	{
		std::ranges::copy(extents, this->extents.begin());
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb, const Core::Quaternion<T>& quaternion) noexcept :
		OBB(aabb, Core::RotationMatrix(quaternion))
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb, const Core::Matrix3x3<T>& rs) noexcept :
		center(rs * aabb.Center()),
		extents{ rs * Core::Vector3<T>(aabb.ExtentX(), T{0}, T{0}), rs * Core::Vector3<T>(T{0}, aabb.ExtentY(), T{0}), rs * Core::Vector3<T>(T{0}, T{0}, aabb.ExtentZ())}
	{
	}

	template<std::floating_point T>
	constexpr OBB<T>::OBB(const AABB<T>& aabb, const Core::Matrix4x4<T>& trs) noexcept :
		center(Core::TransformPoint(trs, aabb.Center())),
		extents{ Core::TransformDirection(trs, Core::Vector3<T>(aabb.ExtentX(), T{0}, T{0})), Core::TransformDirection(trs, Core::Vector3<T>(T{0}, aabb.ExtentY(), T{0})), Core::TransformDirection(trs, Core::Vector3<T>(T{0}, T{0}, aabb.ExtentZ())) }
	{
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& OBB<T>::Center() noexcept
	{
		return center;
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::Center() const noexcept
	{
		return center;
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& OBB<T>::ExtentX() noexcept
	{
		return extents[0];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::ExtentX() const noexcept
	{
		return extents[0];
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& OBB<T>::ExtentY() noexcept
	{
		return extents[1];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::ExtentY() const noexcept
	{
		return extents[1];
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& OBB<T>::ExtentZ() noexcept
	{
		return extents[2];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::ExtentZ() const noexcept
	{
		return extents[2];
	}

	template<std::floating_point T>
	constexpr Core::Vector3<T>& OBB<T>::Extent(const std::size_t index) noexcept
	{
		return extents[index];
	}

	template<std::floating_point T>
	constexpr const Core::Vector3<T>& OBB<T>::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	template<std::floating_point T>
	std::span<Core::Vector3<T>, 3> OBB<T>::Extents() noexcept
	{
		return extents;
	}

	template<std::floating_point T>
	std::span<const Core::Vector3<T>, 3> OBB<T>::Extents() const noexcept
	{
		return extents;
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftBottomNear() const noexcept
	{
		return Center() - ExtentX() - ExtentY() - ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightBottomNear() const noexcept
	{
		return Center() + ExtentX() - ExtentY() - ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftTopNear() const noexcept
	{
		return Center() - ExtentX() + ExtentY() - ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightTopNear() const noexcept
	{
		return Center() + ExtentX() + ExtentY() - ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftBottomFar() const noexcept
	{
		return Center() - ExtentX() - ExtentY() + ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightBottomFar() const noexcept
	{
		return Center() + ExtentX() - ExtentY() + ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::LeftTopFar() const noexcept
	{
		return Center() - ExtentX() + ExtentY() + ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::RightTopFar() const noexcept
	{
		return Center() + ExtentX() + ExtentY() + ExtentZ();
	}

	template<std::floating_point T>
	Core::Vector3<T> OBB<T>::Corner(const std::size_t index) const noexcept
	{
		Core::Vector3<T> answer = Center();
		answer += index & 1 ? ExtentX() : -ExtentX();
		answer += index & 2 ? ExtentY() : -ExtentY();
		answer += index & 4 ? ExtentZ() : -ExtentZ();

		return answer;
	}

	template<std::floating_point T>
	std::array<Core::Vector3<T>, 8> OBB<T>::Corners() const noexcept
	{
		return std::array<Core::Vector3<T>, 8>
		{
			Center() - ExtentX() - ExtentY() - ExtentZ(),
			Center() + ExtentX() - ExtentY() - ExtentZ(),
			Center() - ExtentX() + ExtentY() - ExtentZ(),
			Center() + ExtentX() + ExtentY() - ExtentZ(),
			Center() - ExtentX() - ExtentY() + ExtentZ(),
			Center() + ExtentX() - ExtentY() + ExtentZ(),
			Center() - ExtentX() + ExtentY() + ExtentZ(),
			Center() + ExtentX() + ExtentY() + ExtentZ()
		};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Width() const noexcept
	{
		return ExtentX().Magnitude() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Height() const noexcept
	{
		return ExtentY().Magnitude() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Depth() const noexcept
	{
		return ExtentZ().Magnitude() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Size(const std::size_t index) const noexcept
	{
		return Extent(index).Magnitude() * T{2};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Area() const noexcept
	{
		const T halfWidth = ExtentX().Magnitude();
		const T halfHeight = ExtentY().Magnitude();
		const T halfDepth = ExtentZ().Magnitude();

		return (halfWidth * halfHeight + halfWidth * halfDepth + halfHeight * halfDepth) * T{8};
	}

	template<std::floating_point T>
	constexpr T OBB<T>::Volume() const noexcept
	{
		return ExtentX().Magnitude() * ExtentY().Magnitude() * ExtentZ().Magnitude() * T{8};
	}

	template<std::floating_point T>
	bool OBB<T>::IsFinite() const noexcept
	{
		return Center().IsFinite() && ExtentX().IsFinite() && ExtentY().IsFinite() && ExtentZ().IsFinite();
	}

	template<std::floating_point T>
	constexpr bool OBB<T>::Contains(const Core::Vector3<T>& point) const noexcept
	{
		return false;
	}

	template<std::floating_point T>
	std::string OBB<T>::ToString() const
	{
		return std::format("Center: {}, ExtentX: {}, ExtentY: {}", Center().ToString(), ExtentX().ToString(), ExtentY().ToString());
	}

	template<std::floating_point T>
	template<Core::Arithmetic U>
	constexpr OBB<T>::operator OBB<U>() const noexcept
	{
		return OBB<U>(static_cast<Core::Vector3<U>>(Center()), static_cast<Core::Vector3<U>>(ExtentX()), static_cast<Core::Vector3<U>>(ExtentY()));
	}

	template<std::floating_point T>
	constexpr bool AreAlmostEqual(const OBB<T>& left, const OBB<T>& right, const T tolerance) noexcept
	{
		return Core::AreAlmostEqual(left.Center(), right.Center(), tolerance) &&
			Core::AreAlmostEqual(left.ExtentX(), right.ExtentX(), tolerance) && Core::AreAlmostEqual(left.ExtentY(), right.ExtentY(), tolerance);
	}

	template<std::floating_point T>
	std::ostream& operator <<(std::ostream& stream, const OBB<T>& obb)
	{
		return stream << obb.ToString();
	}
}
