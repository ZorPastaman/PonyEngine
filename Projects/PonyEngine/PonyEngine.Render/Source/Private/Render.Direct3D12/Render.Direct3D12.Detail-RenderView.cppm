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

export module PonyEngine.Render.Direct3D12.Detail:RenderView;

import PonyMath.Core;

import :RenderViewParams;
import :IRenderViewPrivate;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render view.
	class RenderView final : public IRenderViewPrivate
	{
	public:
		/// @brief Creates a @p RenderView.
		/// @param params Render view parameters.
		[[nodiscard("Pure constructor")]]
		explicit RenderView(const RenderViewParams& params) noexcept;
		[[nodiscard("Pure constructor")]]
		RenderView(const RenderView& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		RenderView(RenderView&& other) noexcept = default;

		~RenderView() noexcept = default;

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

		RenderView& operator =(const RenderView& other) noexcept = default;
		RenderView& operator =(RenderView&& other) noexcept = default;

	private:
		PonyMath::Core::Matrix4x4<FLOAT> viewMatrix; ///< View matrix.
		PonyMath::Core::Matrix4x4<FLOAT> projectionMatrix; ///< Projection matrix.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RenderView::RenderView(const RenderViewParams& params) noexcept :
		viewMatrix(params.viewMatrix),
		projectionMatrix(params.projectionMatrix)
	{
	}

	PonyMath::Core::Matrix4x4<float> RenderView::ViewMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(ViewMatrixD3D12());
	}

	void RenderView::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		ViewMatrixD3D12(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix));
	}

	PonyMath::Core::Matrix4x4<float> RenderView::ProjectionMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(ProjectionMatrixD3D12());
	}

	void RenderView::ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		ProjectionMatrixD3D12(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix));
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& RenderView::ViewMatrixD3D12() const noexcept
	{
		return viewMatrix;
	}

	void RenderView::ViewMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept
	{
		viewMatrix = matrix;
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& RenderView::ProjectionMatrixD3D12() const noexcept
	{
		return projectionMatrix;
	}

	void RenderView::ProjectionMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept
	{
		projectionMatrix = matrix;
	}
}
