/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:FrustumCuller;

import <utility>;

import PonyMath.Core;

import PonyEngine.Render;

import :CameraFrustum;

export namespace PonyEngine::Render
{
	class FrustumCuller final : public ICuller
	{
	public:
		[[nodiscard("Pure constructor")]]
		FrustumCuller() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit FrustumCuller(const CameraFrustum& frustum) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit FrustumCuller(const PerspectiveParams& perspective) noexcept;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(const FrustumCuller& other) noexcept;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(FrustumCuller&& other) noexcept;

		~FrustumCuller() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept override;

		FrustumCuller& operator =(const FrustumCuller& other) noexcept = default;
		FrustumCuller& operator =(FrustumCuller&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		bool CheckVisibility(const PonyMath::Shape::OBB<float>& obb) const noexcept;

		CameraFrustum frustum;
	};
}

namespace PonyEngine::Render
{
	FrustumCuller::FrustumCuller(const CameraFrustum& frustum) noexcept :
		frustum(frustum)
	{
	}

	FrustumCuller::FrustumCuller(const PerspectiveParams& perspective) noexcept :
		frustum(perspective)
	{
	}

	FrustumCuller::FrustumCuller(const FrustumCuller& other) noexcept :
		frustum(other.frustum)
	{
	}

	FrustumCuller::FrustumCuller(FrustumCuller&& other) noexcept :
		frustum(std::move(other.frustum))
	{
	}

	bool FrustumCuller::IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		return frustum.Contains(point);
	}

	bool FrustumCuller::IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		return CheckVisibility(obb);
	}

	bool FrustumCuller::CheckVisibility(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		const std::array<PonyMath::Core::Vector3<float>, PonyMath::Shape::OBB<float>::CornerCount> boxCorners = obb.Corners();

		for (std::size_t axisIndex = 0; axisIndex < CameraFrustum::DifferentNormalPlaneCount; ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = frustum.Plane(axisIndex).Normal();
			const auto& [minExtent, maxExtent] = frustum.Extent(axisIndex);

			std::array<float, PonyMath::Shape::OBB<float>::CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::OBB<float>::CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, boxCorners[cornerIndex] - frustum.Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > maxExtent || *max < minExtent)
			{
				return false;
			}
		}

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

		for (const PonyMath::Core::Vector3<float>& frustumEdge : frustum.Edges())
		{
			for (const PonyMath::Core::Vector3<float>& boxAxis : obb.Axes())
			{
				const PonyMath::Core::Vector3<float> normal = PonyMath::Core::Cross(frustumEdge, boxAxis);

				std::array<float, CameraFrustum::CornerCount> frustumProjections;
				for (std::size_t cornerIndex = 0; cornerIndex < CameraFrustum::CornerCount; ++cornerIndex)
				{
					frustumProjections[cornerIndex] = PonyMath::Core::Dot(normal, frustum.Corner(cornerIndex));
				}
				std::array<float, PonyMath::Shape::OBB<float>::CornerCount> boxProjections;
				for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::OBB<float>::CornerCount; ++cornerIndex)
				{
					boxProjections[cornerIndex] = PonyMath::Core::Dot(normal, boxCorners[cornerIndex]);
				}

				const auto [frustumMin, frustumMax] = std::ranges::minmax_element(frustumProjections);
				const auto [boxMin, boxMax] = std::ranges::minmax_element(boxProjections);
				if (*frustumMin > *boxMax || *frustumMax < *boxMin)
				{
					return false;
				}
			}
		}

		return true;
	}
}
