/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:CameraFrustum;

import <algorithm>;
import <array>;
import <cmath>;
import <concepts>;
import <cstddef>;
import <format>;
import <span>;
import <string>;

import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	class CameraFrustum final
	{
	public:
		static constexpr std::size_t LeftBottomNear = 0;
		static constexpr std::size_t RightBottomNear = 1;
		static constexpr std::size_t LeftTopNear = 2;
		static constexpr std::size_t RightTopNear = 3;
		static constexpr std::size_t LeftBottomFar = 4;
		static constexpr std::size_t RightBottomFar = 5;
		static constexpr std::size_t LeftTopFar = 6;
		static constexpr std::size_t RightTopFar = 7;
		static constexpr std::size_t CornerCount = 8;

		static constexpr std::size_t Left = 0;
		static constexpr std::size_t Right = 1;
		static constexpr std::size_t Bottom = 2;
		static constexpr std::size_t Top = 3;
		static constexpr std::size_t Near = 4;
		static constexpr std::size_t Far = 5;
		static constexpr std::size_t PlaneCount = 6;
		static constexpr std::size_t DifferentNormalPlaneCount = 5;

		[[nodiscard("Pure constructor")]]
		CameraFrustum() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit CameraFrustum(const PerspectiveParams& perspective) noexcept;
		[[nodiscard("Pure constructor")]]
		CameraFrustum(const CameraFrustum& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		CameraFrustum(CameraFrustum&& other) noexcept = default;

		~CameraFrustum() noexcept = default;

		[[nodiscard("Pure function")]]
		const PonyMath::Shape::Plane<float>& Plane(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyMath::Shape::Plane<float>, 6> Planes() const noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Vector3<float>& Center() const noexcept;

		[[nodiscard("Pure function")]]
		const std::pair<float, float>& Extent(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const std::pair<float, float>, 5> Extents() const noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Vector3<float>& Corner(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyMath::Core::Vector3<float>, 8> Corners() const noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Vector3<float>& Edge(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyMath::Core::Vector3<float>, 6> Edges() const noexcept;

		[[nodiscard("Pure function")]]
		bool Contains(const PonyMath::Core::Vector3<float>& point) const noexcept;

		CameraFrustum& operator =(const CameraFrustum& other) noexcept = default;
		CameraFrustum& operator =(CameraFrustum&& other) noexcept = default;

	private:
		std::array<PonyMath::Shape::Plane<float>, 6> planes;

		PonyMath::Core::Vector3<float> center;
		std::array<std::pair<float, float>, 5> extents;
		std::array<PonyMath::Core::Vector3<float>, 8> corners;

		std::array<PonyMath::Core::Vector3<float>, 6> edgeNormals;
	};
}

namespace PonyEngine::Render
{
	CameraFrustum::CameraFrustum(const PerspectiveParams& perspective) noexcept
	{
		const float tan = std::tan(perspective.fov * 0.5f);
		const float nearHalfHeight = tan * perspective.nearPlane;
		const float nearHalfWidth = nearHalfHeight * perspective.aspect;
		const float farHalfHeight = tan * perspective.farPlane;
		const float farHalfWidth = farHalfHeight * perspective.aspect;

		corners[LeftBottomNear] = PonyMath::Core::Vector3<float>(-nearHalfWidth, -nearHalfHeight, perspective.nearPlane);
		corners[RightBottomNear] = PonyMath::Core::Vector3<float>(nearHalfWidth, -nearHalfHeight, perspective.nearPlane);
		corners[LeftTopNear] = PonyMath::Core::Vector3<float>(-nearHalfWidth, nearHalfHeight, perspective.nearPlane);
		corners[RightTopNear] = PonyMath::Core::Vector3<float>(nearHalfWidth, nearHalfHeight, perspective.nearPlane);
		corners[LeftBottomFar] = PonyMath::Core::Vector3<float>(-farHalfWidth, -farHalfHeight, perspective.farPlane);
		corners[RightBottomFar] = PonyMath::Core::Vector3<float>(farHalfWidth, -farHalfHeight, perspective.farPlane);
		corners[LeftTopFar] = PonyMath::Core::Vector3<float>(-farHalfWidth, farHalfHeight, perspective.farPlane);
		corners[RightTopFar] = PonyMath::Core::Vector3<float>(farHalfWidth, farHalfHeight, perspective.farPlane);

		planes[Left] = PonyMath::Shape::Plane<float>(corners[LeftBottomNear], corners[LeftTopNear], corners[LeftTopFar]);
		planes[Right] = PonyMath::Shape::Plane<float>(corners[RightTopNear], corners[RightBottomNear], corners[RightTopFar]);
		planes[Bottom] = PonyMath::Shape::Plane<float>(corners[RightBottomNear], corners[LeftBottomNear], corners[RightBottomFar]);
		planes[Top] = PonyMath::Shape::Plane<float>(corners[LeftTopNear], corners[RightTopNear], corners[RightTopFar]);
		planes[Near] = PonyMath::Shape::Plane<float>(corners[RightTopNear], corners[LeftTopNear], corners[LeftBottomNear]);
		planes[Far] = PonyMath::Shape::Plane<float>(corners[LeftTopFar], corners[RightTopFar], corners[RightBottomFar]);

		auto cornerSum = PonyMath::Core::Vector3<float>::Predefined::Zero;
		for (const PonyMath::Core::Vector3<float>& corner : corners)
		{
			cornerSum += corner;
		}
		center = cornerSum * (1.f / 8.f);

		for (std::size_t planeIndex = 0; planeIndex < DifferentNormalPlaneCount; ++planeIndex)
		{
			const PonyMath::Core::Vector3<float>& normal = planes[planeIndex].Normal();

			std::array<float, 8> projections;
			for (std::size_t cornerIndex = 0; cornerIndex < corners.size(); ++cornerIndex)
			{
				projections[cornerIndex] = PonyMath::Core::Dot(normal, corners[cornerIndex] - center);
			}

			const auto [min, max] = std::ranges::minmax_element(projections);
			extents[planeIndex] = std::pair(*min, *max);
		}

		edgeNormals[0] = (corners[RightBottomNear] - corners[LeftBottomNear]).Normalized();
		edgeNormals[1] = (corners[LeftTopNear] - corners[LeftBottomNear]).Normalized();
		edgeNormals[2] = (corners[LeftTopFar] - corners[LeftTopNear]).Normalized();
		edgeNormals[3] = (corners[RightTopFar] - corners[RightTopNear]).Normalized();
		edgeNormals[4] = (corners[RightBottomFar] - corners[RightBottomNear]).Normalized();
		edgeNormals[5] = (corners[LeftBottomFar] - corners[LeftBottomNear]).Normalized();
	}

	const PonyMath::Shape::Plane<float>& CameraFrustum::Plane(const std::size_t index) const noexcept
	{
		return planes[index];
	}

	std::span<const PonyMath::Shape::Plane<float>, 6> CameraFrustum::Planes() const noexcept
	{
		return planes;
	}

	const PonyMath::Core::Vector3<float>& CameraFrustum::Center() const noexcept
	{
		return center;
	}

	const std::pair<float, float>& CameraFrustum::Extent(const std::size_t index) const noexcept
	{
		return extents[index];
	}

	std::span<const std::pair<float, float>, 5> CameraFrustum::Extents() const noexcept
	{
		return extents;
	}

	const PonyMath::Core::Vector3<float>& CameraFrustum::Corner(const std::size_t index) const noexcept
	{
		return corners[index];
	}

	std::span<const PonyMath::Core::Vector3<float>, 8> CameraFrustum::Corners() const noexcept
	{
		return corners;
	}

	const PonyMath::Core::Vector3<float>& CameraFrustum::Edge(const std::size_t index) const noexcept
	{
		return edgeNormals[index];
	}

	std::span<const PonyMath::Core::Vector3<float>, 6> CameraFrustum::Edges() const noexcept
	{
		return edgeNormals;
	}

	bool CameraFrustum::Contains(const PonyMath::Core::Vector3<float>& point) const noexcept
	{
		for (const PonyMath::Shape::Plane<float>& plane : planes)
		{
			if (plane.Side(point) < std::int8_t{0})
			{
				return false;
			}
		}

		return true;
	}
}
