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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RenderView;

import PonyMath.Core;

import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render
{
	class Direct3D12RenderView final : public IDirect3D12RenderView
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderView(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderView(const Direct3D12RenderView& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderView(Direct3D12RenderView&& other) noexcept = default;

		~Direct3D12RenderView() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ViewMatrix() const noexcept override;
		virtual void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ProjectionMatrix() const noexcept override;
		virtual void ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<FLOAT>& ViewMatrixD3D12() const noexcept override;
		virtual void ViewMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<FLOAT>& ProjectionMatrixD3D12() const noexcept override;
		virtual void ProjectionMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept override;

		Direct3D12RenderView& operator =(const Direct3D12RenderView& other) noexcept = default;
		Direct3D12RenderView& operator =(Direct3D12RenderView&& other) noexcept = default;

	private:
		PonyMath::Core::Matrix4x4<FLOAT> viewMatrix;
		PonyMath::Core::Matrix4x4<FLOAT> projectionMatrix;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderView::Direct3D12RenderView(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix) noexcept :
		viewMatrix(viewMatrix),
		projectionMatrix(projectionMatrix)
	{
	}

	PonyMath::Core::Matrix4x4<float> Direct3D12RenderView::ViewMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(ViewMatrixD3D12());
	}

	void Direct3D12RenderView::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		ViewMatrixD3D12(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix));
	}

	PonyMath::Core::Matrix4x4<float> Direct3D12RenderView::ProjectionMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(ProjectionMatrixD3D12());
	}

	void Direct3D12RenderView::ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		ProjectionMatrixD3D12(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix));
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12RenderView::ViewMatrixD3D12() const noexcept
	{
		return viewMatrix;
	}

	void Direct3D12RenderView::ViewMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept
	{
		viewMatrix = matrix;
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12RenderView::ProjectionMatrixD3D12() const noexcept
	{
		return projectionMatrix;
	}

	void Direct3D12RenderView::ProjectionMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept
	{
		projectionMatrix = matrix;
	}
}
