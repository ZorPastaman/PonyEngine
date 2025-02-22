/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Render.Direct3D12.Detail:Camera;

import <optional>;
import <memory>;
import <variant>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;

import PonyEngine.Render.Detail;
import PonyEngine.Render.Direct3D12;

import :Buffer;
import :DescriptorHeap;

export namespace PonyEngine::Render::Direct3D12
{
	class Camera final : public ICamera
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Camera(const CameraParams& cameraParams) noexcept;
		[[nodiscard("Pure constructor")]]
		Camera(const Camera& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Camera(Camera&& other) noexcept = default;

		~Camera() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewMatrix() const noexcept override;
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ProjectionMatrix() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ViewProjectionMatrix() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const CameraProjection& Projection() const noexcept override;
		virtual void Projection(const CameraProjection& projection) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Color::RGBA<float>& ClearColor() const noexcept override;
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Shape::Rect<float>& ViewportRect() const noexcept override;
		virtual void ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t SortingOrder() const noexcept override;
		virtual void SortingOrder(std::int32_t order) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const ICuller& Culler() const noexcept override;

		Camera& operator =(const Camera& other) noexcept = default;
		Camera& operator =(Camera&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		PonyMath::Core::Matrix4x4<float> ComputeProjectionMatrix() const noexcept;
		[[nodiscard("Pure function")]]
		static PonyMath::Core::Matrix4x4<float> ComputePerspectiveMatrix(const PerspectiveParams& params) noexcept;
		[[nodiscard("Pure function")]]
		static PonyMath::Core::Matrix4x4<float> ComputeOrthographicMatrix(const OrthographicParams& params) noexcept;

		PonyMath::Core::Matrix4x4<float> viewMatrix;
		CameraProjection projection;
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> projectionMatrix;
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> viewProjectionMatrix;
		mutable std::optional<std::variant<FrustumCuller, BoxCuller>> culler;

		PonyMath::Color::RGBA<float> clearColor;

		PonyMath::Shape::Rect<float> viewportRect;

		std::int32_t sortingOrder;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Camera::Camera(const CameraParams& cameraParams) noexcept :
		viewMatrix(cameraParams.viewMatrix),
		projection(cameraParams.projection),
		clearColor(cameraParams.clearColor),
		viewportRect(cameraParams.viewportRect),
		sortingOrder(cameraParams.sortingOrder)
	{
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ViewMatrix() const noexcept
	{
		return viewMatrix;
	}

	void Camera::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		viewMatrix = matrix;
		viewProjectionMatrix = std::nullopt;
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ProjectionMatrix() const noexcept
	{
		if (!projectionMatrix)
		{
			projectionMatrix = ComputeProjectionMatrix();
		}

		return projectionMatrix.value();
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ViewProjectionMatrix() const noexcept
	{
		if (!viewProjectionMatrix)
		{
			viewProjectionMatrix = ProjectionMatrix() * ViewMatrix();
		}

		return viewProjectionMatrix.value();
	}

	const CameraProjection& Camera::Projection() const noexcept
	{
		return projection;
	}

	void Camera::Projection(const CameraProjection& projection) noexcept
	{
		this->projection = projection;
		projectionMatrix = std::nullopt;
		viewProjectionMatrix = std::nullopt;
		culler = std::nullopt;
	}

	const PonyMath::Color::RGBA<float>& Camera::ClearColor() const noexcept
	{
		return clearColor;
	}

	void Camera::ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept
	{
		clearColor = color;
	}

	const PonyMath::Shape::Rect<float>& Camera::ViewportRect() const noexcept
	{
		return viewportRect;
	}

	void Camera::ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept
	{
		viewportRect = rect;
	}

	std::int32_t Camera::SortingOrder() const noexcept
	{
		return sortingOrder;
	}

	void Camera::SortingOrder(const std::int32_t order) noexcept
	{
		sortingOrder = order;
	}

	const ICuller& Camera::Culler() const noexcept
	{
		if (!culler)
		{
			switch (projection.index())
			{
			case 0:
				culler = FrustumCuller(std::get<0>(projection));
				break;
			case 1:
				culler = BoxCuller(std::get<1>(projection));
			default: [[unlikely]]
				assert(false && "Unsupported projection type.");
				culler = BoxCuller(PonyMath::Shape::AABB<float>::Predefined::Zero);
				break;
			}
		}

		if (culler->index() == 0)
		{
			return std::get<0>(culler.value());
		}

		return std::get<1>(culler.value());
	}

	PonyMath::Core::Matrix4x4<float> Camera::ComputeProjectionMatrix() const noexcept
	{
		switch (projection.index())
		{
		case 0:
			return ComputePerspectiveMatrix(std::get<0>(projection));
		case 1:
			return ComputeOrthographicMatrix(std::get<1>(projection));
		default: [[unlikely]]
			assert(false && "Unsupported projection type.");
			return PonyMath::Core::Matrix4x4<float>::Predefined::Identity;
		}
	}

	PonyMath::Core::Matrix4x4<float> Camera::ComputePerspectiveMatrix(const PerspectiveParams& params) noexcept
	{
		return PonyMath::Core::PerspectiveMatrix(params.fov, params.aspect, params.nearPlane, params.farPlane);
	}

	PonyMath::Core::Matrix4x4<float> Camera::ComputeOrthographicMatrix(const OrthographicParams& params) noexcept
	{
		return PonyMath::Core::OrthographicMatrix(params.width, params.height, params.nearPlane, params.farPlane);
	}
}
