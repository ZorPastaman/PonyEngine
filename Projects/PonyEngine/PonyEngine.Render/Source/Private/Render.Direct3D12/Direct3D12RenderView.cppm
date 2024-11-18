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

import :Direct3D12Viewport;

export namespace PonyEngine::Render
{
	class Direct3D12RenderView final : public IDirect3D12RenderView
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderView(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix, const PonyMath::Utility::Resolution<UINT>& resolution) noexcept;
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
		virtual PonyMath::Utility::Resolution<unsigned int> Resolution() const noexcept override;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& TargetViewMatrix() const noexcept;
		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& TargetProjectionMatrix() const noexcept;

		[[nodiscard("Pure function")]]
		const Direct3D12Viewport& Viewport() const noexcept;

		Direct3D12RenderView& operator =(const Direct3D12RenderView& other) noexcept = default;
		Direct3D12RenderView& operator =(Direct3D12RenderView&& other) noexcept = default;

	private:
		PonyMath::Core::Matrix4x4<FLOAT> viewMatrix;
		PonyMath::Core::Matrix4x4<FLOAT> projectionMatrix;

		Direct3D12Viewport viewport;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderView::Direct3D12RenderView(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix, const PonyMath::Utility::Resolution<UINT>& resolution) noexcept :
		viewMatrix(viewMatrix),
		projectionMatrix(projectionMatrix),
		viewport(resolution)
	{
	}

	PonyMath::Core::Matrix4x4<float> Direct3D12RenderView::ViewMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(viewMatrix);
	}

	void Direct3D12RenderView::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		viewMatrix = static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix);
	}

	PonyMath::Core::Matrix4x4<float> Direct3D12RenderView::ProjectionMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(projectionMatrix);
	}

	void Direct3D12RenderView::ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		projectionMatrix = static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix);
	}

	PonyMath::Utility::Resolution<unsigned int> Direct3D12RenderView::Resolution() const noexcept
	{
		PonyMath::Utility::Resolution<unsigned int> resolution;
		resolution.Width() = static_cast<unsigned int>(viewport.Rect().right - viewport.Rect().left);
		resolution.Height() = static_cast<unsigned int>(viewport.Rect().bottom - viewport.Rect().top);

		return resolution;
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12RenderView::TargetViewMatrix() const noexcept
	{
		return viewMatrix;
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12RenderView::TargetProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	const Direct3D12Viewport& Direct3D12RenderView::Viewport() const noexcept
	{
		return viewport;
	}
}
