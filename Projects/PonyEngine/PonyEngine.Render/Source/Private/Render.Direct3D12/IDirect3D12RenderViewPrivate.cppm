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
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderViewPrivate;

import PonyMath.Core;

import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render
{
	/// @brief Render target view.
	class IDirect3D12RenderViewPrivate : public IDirect3D12RenderView
	{
		INTERFACE_BODY(IDirect3D12RenderViewPrivate)

		/// @brief Gets the view translation-rotation-scaling matrix.
		/// @return View matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<FLOAT>& ViewMatrixD3D12() const noexcept = 0;
		/// @brief Sets the view translation-rotation-scaling matrix.
		/// @param matrix View matrix.
		virtual void ViewMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept = 0;

		/// @brief Gets the projection matrix.
		/// @return Projection matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<FLOAT>& ProjectionMatrixD3D12() const noexcept = 0;
		/// @brief Sets the projection matrix.
		/// @param matrix Projection matrix.
		virtual void ProjectionMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept = 0;
	};
}
