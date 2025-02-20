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
		FrustumCuller() noexcept;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(const CameraFrustum& frustum, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(const PerspectiveParams& perspective, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(const FrustumCuller& other) noexcept;
		[[nodiscard("Pure constructor")]]
		FrustumCuller(FrustumCuller&& other) noexcept;

		~FrustumCuller() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& aabb) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Core::Vector3<float>& point, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::AABB<float>& aabb, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsVisible(const PonyMath::Shape::OBB<float>& obb, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept override;

		FrustumCuller& operator =(const FrustumCuller& other) noexcept = default;
		FrustumCuller& operator =(FrustumCuller&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		bool CheckVisibility(const PonyMath::Shape::OBB<float>& obb) const noexcept;

		CameraFrustum frustum;
		PonyMath::Core::Matrix4x4<float> viewMatrix;
	};
}

namespace PonyEngine::Render
{
	FrustumCuller::FrustumCuller() noexcept :
		viewMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity)
	{
	}

	FrustumCuller::FrustumCuller(const CameraFrustum& frustum, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept :
		frustum(frustum),
		viewMatrix(viewMatrix)
	{
	}

	FrustumCuller::FrustumCuller(const PerspectiveParams& perspective, const PonyMath::Core::Matrix4x4<float>& viewMatrix) noexcept :
		frustum(perspective),
		viewMatrix(viewMatrix)
	{
	}

	FrustumCuller::FrustumCuller(const FrustumCuller& other) noexcept :
		frustum(other.frustum),
		viewMatrix(other.viewMatrix)
	{
	}

	FrustumCuller::FrustumCuller(FrustumCuller&& other) noexcept :
		frustum(std::move(other.frustum)),
		viewMatrix(std::move(other.viewMatrix))
	{
	}

	bool FrustumCuller::IsVisible(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		return frustum.Contains(PonyMath::Core::TransformPoint(viewMatrix, point));
	}

	bool FrustumCuller::IsVisible(const PonyMath::Shape::AABB<float>& aabb) const noexcept
	{
		return CheckVisibility(PonyMath::Shape::OBB<float>(aabb, viewMatrix));
	}

	bool FrustumCuller::IsVisible(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		return CheckVisibility(PonyMath::Shape::OBB<float>(obb, viewMatrix));
	}

	bool FrustumCuller::IsVisible(const PonyMath::Core::Vector3<float>& point, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept
	{
		return frustum.Contains(PonyMath::Core::TransformPoint(viewMatrix * modelMatrix, point));
	}

	bool FrustumCuller::IsVisible(const PonyMath::Shape::AABB<float>& aabb, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept
	{
		return CheckVisibility(PonyMath::Shape::OBB<float>(aabb, viewMatrix * modelMatrix));
	}

	bool FrustumCuller::IsVisible(const PonyMath::Shape::OBB<float>& obb, const PonyMath::Core::Matrix4x4<float>& modelMatrix) const noexcept
	{
		return CheckVisibility(PonyMath::Shape::OBB<float>(obb, viewMatrix * modelMatrix));
	}

	bool FrustumCuller::CheckVisibility(const PonyMath::Shape::OBB<float>& obb) const noexcept
	{
		const std::array<PonyMath::Core::Vector3<float>, PonyMath::Shape::OBB<float>::CornerCount> boxCorners = obb.Corners();

		for (std::size_t axisIndex = 0; axisIndex < CameraFrustum::DifferentNormalPlaneCount; ++axisIndex)
		{
			const PonyMath::Core::Vector3<float>& axis = frustum.Plane(axisIndex).Normal();
			const std::pair<float, float>& extents = frustum.Extent(axisIndex);

			std::array<float, PonyMath::Shape::OBB<float>::CornerCount> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < PonyMath::Shape::OBB<float>::CornerCount; ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(axis, boxCorners[cornerIndex] - frustum.Center());
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			if (*min > extents.second || *max < extents.first)
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
