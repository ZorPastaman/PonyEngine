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
		Camera(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix, 
			const PonyMath::Color::RGBA<FLOAT>& clearColor, const PonyMath::Shape::Rect<FLOAT>& viewportRect,
			std::int32_t sortingOrder) noexcept;
		[[nodiscard("Pure constructor")]]
		Camera(const Camera& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Camera(Camera&& other) noexcept = default;

		~Camera() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ViewMatrix() const noexcept override;
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ProjectionMatrix() const noexcept override;
		virtual void ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> ClearColor() const noexcept override;
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Shape::Rect<float> ViewportRect() const noexcept override;
		virtual void ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::int32_t SortingOrder() const noexcept override;
		virtual void SortingOrder(std::int32_t order) noexcept override;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& ViewMatrixD3D12() const noexcept;
		void ViewMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& ProjectionMatrixD3D12() const noexcept;
		void ProjectionMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Color::RGBA<FLOAT>& ClearColorD3D12() const noexcept;
		void ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Shape::Rect<FLOAT>& ViewportRectD3D12() const noexcept;
		void ViewportRectD3D12(const PonyMath::Shape::Rect<FLOAT>& rect) noexcept;

		Camera& operator =(const Camera& other) noexcept = default;
		Camera& operator =(Camera&& other) noexcept = default;

	private:
		PonyMath::Core::Matrix4x4<FLOAT> viewMatrix;
		PonyMath::Core::Matrix4x4<FLOAT> projectionMatrix;

		PonyMath::Color::RGBA<FLOAT> clearColor;

		PonyMath::Shape::Rect<FLOAT> viewportRect;

		std::int32_t sortingOrder;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Camera::Camera(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix, 
		const PonyMath::Color::RGBA<FLOAT>& clearColor, const PonyMath::Shape::Rect<FLOAT>& viewportRect,
		const std::int32_t sortingOrder) noexcept :
		viewMatrix(viewMatrix),
		projectionMatrix(projectionMatrix),
		clearColor(clearColor),
		viewportRect(viewportRect),
		sortingOrder(sortingOrder)
	{
	}

	PonyMath::Core::Matrix4x4<float> Camera::ViewMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(ViewMatrixD3D12());
	}

	void Camera::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		ViewMatrixD3D12(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix));
	}

	PonyMath::Core::Matrix4x4<float> Camera::ProjectionMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(ProjectionMatrixD3D12());
	}

	void Camera::ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		ProjectionMatrixD3D12(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix));
	}

	PonyMath::Color::RGBA<float> Camera::ClearColor() const noexcept
	{
		return static_cast<PonyMath::Color::RGBA<float>>(ClearColorD3D12());
	}

	void Camera::ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept
	{
		ClearColorD3D12(static_cast<PonyMath::Color::RGBA<FLOAT>>(color));
	}

	PonyMath::Shape::Rect<float> Camera::ViewportRect() const noexcept
	{
		return static_cast<PonyMath::Shape::Rect<float>>(ViewportRectD3D12());
	}

	void Camera::ViewportRect(const PonyMath::Shape::Rect<float>& rect) noexcept
	{
		ViewportRectD3D12(static_cast<PonyMath::Shape::Rect<FLOAT>>(rect));
	}

	std::int32_t Camera::SortingOrder() const noexcept
	{
		return sortingOrder;
	}

	void Camera::SortingOrder(const std::int32_t order) noexcept
	{
		sortingOrder = order;
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Camera::ViewMatrixD3D12() const noexcept
	{
		return viewMatrix;
	}

	void Camera::ViewMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept
	{
		viewMatrix = matrix;
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Camera::ProjectionMatrixD3D12() const noexcept
	{
		return projectionMatrix;
	}

	void Camera::ProjectionMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept
	{
		projectionMatrix = matrix;
	}

	const PonyMath::Color::RGBA<FLOAT>& Camera::ClearColorD3D12() const noexcept
	{
		return clearColor;
	}

	void Camera::ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept
	{
		clearColor = color;
	}

	const PonyMath::Shape::Rect<FLOAT>& Camera::ViewportRectD3D12() const noexcept
	{
		return viewportRect;
	}

	void Camera::ViewportRectD3D12(const PonyMath::Shape::Rect<FLOAT>& rect) noexcept
	{
		viewportRect = rect;
	}

}
