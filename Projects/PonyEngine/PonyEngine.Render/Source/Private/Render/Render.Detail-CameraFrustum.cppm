/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:CameraFrustum;

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
		bool IsInside(const PonyMath::Core::Vector3<float>& point) const noexcept;

		CameraFrustum& operator =(const CameraFrustum& other) noexcept = default;
		CameraFrustum& operator =(CameraFrustum&& other) noexcept = default;

	private:
		static constexpr std::size_t LeftBottomNear = 0;
		static constexpr std::size_t RightBottomNear = 1;
		static constexpr std::size_t LeftTopNear = 2;
		static constexpr std::size_t RightTopNear = 3;
		static constexpr std::size_t LeftBottomFar = 4;
		static constexpr std::size_t RightBottomFar = 5;
		static constexpr std::size_t LeftTopFar = 6;
		static constexpr std::size_t RightTopFar = 7;

		static constexpr std::size_t Left = 0;
		static constexpr std::size_t Right = 1;
		static constexpr std::size_t Bottom = 2;
		static constexpr std::size_t Top = 3;
		static constexpr std::size_t Near = 4;
		static constexpr std::size_t Far = 5;

		std::array<PonyMath::Core::Vector3<float>, 8> corners;
		std::array<PonyMath::Shape::Plane<float>, 6> planes;
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
	}

	bool CameraFrustum::IsInside(const PonyMath::Core::Vector3<float>& point) const noexcept
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
