/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:FrustumCuller;

import <algorithm>;
import <array>;
import <cstddef>;
import <utility>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

import :CameraFrustum;

export namespace PonyEngine::Render
{
	/// @brief Camera frustum culler.
	class FrustumCuller final : public ICuller
	{
	public:
		/// @brief Creates a zero frustum culler.
		[[nodiscard("Pure constructor")]]
		FrustumCuller() noexcept = default;
		/// @brief Creates a frustum culler.
		/// @param frustum Camera frustum.
		[[nodiscard("Pure constructor")]]
		explicit FrustumCuller(const CameraFrustum& frustum) noexcept;
		/// @brief Creates a frustum culler.
		/// @param perspective Perspective projection parameters.
		[[nodiscard("Pure constructor")]]
		explicit FrustumCuller(const Perspective& perspective) noexcept;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(const FrustumCuller& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(FrustumCuller&& other) noexcept = default;

		~FrustumCuller() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept override;

		FrustumCuller& operator =(const FrustumCuller& other) noexcept = default;
		FrustumCuller& operator =(FrustumCuller&& other) noexcept = default;

	private:
		CameraFrustum frustum; ///< Camera frustum.
	};
}

namespace PonyEngine::Render
{
	FrustumCuller::FrustumCuller(const CameraFrustum& frustum) noexcept :
		frustum(frustum)
	{
	}

	FrustumCuller::FrustumCuller(const Perspective& perspective) noexcept :
		frustum(perspective)
	{
	}

	bool FrustumCuller::IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		return frustum.Contains(point);
	}

	bool FrustumCuller::IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		// Check by center.
		if (frustum.Contains(obb.Center()))
		{
			return true;
		}

		// Check by bounding sphere.
		for (const float radiusSqr = obb.Extents().MagnitudeSquared(); const PonyMath::Shape::Plane<float>& plane : frustum.Planes())
		{
			if (const float distance = plane.Distance(obb.Center()); distance < 0.f && distance * distance > radiusSqr)
			{
				return false;
			}
		}

		const std::array<PonyMath::Core::Vector3<float>, PonyMath::Shape::OBB<float>::CornerCount> obbCorners = obb.Corners();

		// Check by corners.
		for (const PonyMath::Core::Vector3<float>& corner : obbCorners)
		{
			if (frustum.Contains(corner))
			{
				return true;
			}
		}

		// Check by SAT (first step).
		for (std::size_t axisIndex = 0; axisIndex < CameraFrustum::DifferentNormalPlaneCount; ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = frustum.Plane(axisIndex).Normal();
			const auto& [minExtent, maxExtent] = frustum.Extent(axisIndex);

			std::array<float, PonyMath::Shape::OBB<float>::CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::OBB<float>::CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, obbCorners[cornerIndex] - frustum.Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > maxExtent || *max < minExtent)
			{
				return false;
			}
		}

		// Check by SAT (second step).
		for (std::size_t axisIndex = 0; axisIndex < PonyMath::Shape::OBB<float>::AxesCount; ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = obb.Axis(axisIndex);
			const float extent = obb.Extent(axisIndex);

			std::array<float, CameraFrustum::CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < CameraFrustum::CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, frustum.Corner(cornerIndex) - obb.Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extent || *max < -extent)
			{
				return false;
			}
		}

		// Check by SAT (third step).
		for (const PonyMath::Core::Vector3<float>& frustumEdge : frustum.Edges())
		{
			for (const PonyMath::Core::Vector3<float>& boxAxis : obb.Axes())
			{
				const PonyMath::Core::Vector3<float> axis = PonyMath::Core::Cross(frustumEdge, boxAxis);

				std::array<float, CameraFrustum::CornerCount> frustumProjections;
				std::array<float, PonyMath::Shape::OBB<float>::CornerCount> obbProjections;
				for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::OBB<float>::CornerCount; ++cornerIndex)
				{
					frustumProjections[cornerIndex] = PonyMath::Core::Dot(axis, frustum.Corner(cornerIndex));
					obbProjections[cornerIndex] = PonyMath::Core::Dot(axis, obbCorners[cornerIndex]);
				}

				const auto [frustumMin, frustumMax] = std::ranges::minmax_element(frustumProjections);
				const auto [boxMin, boxMax] = std::ranges::minmax_element(obbProjections);
				if (*frustumMin > *boxMax || *frustumMax < *boxMin)
				{
					return false;
				}
			}
		}

		return true;
	}
}
