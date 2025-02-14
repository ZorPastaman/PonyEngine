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
		virtual bool IsVisible(const PonyMath::Shape::Box<float>& box) const noexcept override;

		FrustumCuller& operator =(const FrustumCuller& other) noexcept = default;
		FrustumCuller& operator =(FrustumCuller&& other) noexcept = default;

	private:
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
		return frustum.IsInside(PonyMath::Core::TransformPoint(viewMatrix, point));
	}

	bool FrustumCuller::IsVisible(const PonyMath::Shape::Box<float>& box) const noexcept
	{
		return true;
	}
}
