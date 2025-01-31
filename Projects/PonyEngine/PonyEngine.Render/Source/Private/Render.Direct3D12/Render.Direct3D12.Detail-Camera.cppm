/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Camera;

import <memory>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;

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
		virtual void ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Color::RGBA<float>& ClearColor() const noexcept override;
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Shape::Rect<float>& ViewportRect() const noexcept override;
		virtual void ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t SortingOrder() const noexcept override;
		virtual void SortingOrder(std::int32_t order) noexcept override;

		Camera& operator =(const Camera& other) noexcept = default;
		Camera& operator =(Camera&& other) noexcept = default;

	private:
		PonyMath::Core::Matrix4x4<float> viewMatrix;
		PonyMath::Core::Matrix4x4<float> projectionMatrix;

		PonyMath::Color::RGBA<float> clearColor;

		PonyMath::Shape::Rect<float> viewportRect;

		std::int32_t sortingOrder;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Camera::Camera(const CameraParams& cameraParams) noexcept :
		viewMatrix(cameraParams.viewMatrix),
		projectionMatrix(cameraParams.projectionMatrix),
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
	}

	const PonyMath::Core::Matrix4x4<float>& Camera::ProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	void Camera::ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		projectionMatrix = matrix;
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
}
