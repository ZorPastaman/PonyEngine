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
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12:IDirect3D12RenderTarget;

import PonyMath.Color;
import PonyMath.Utility;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render target.
	class IDirect3D12RenderTarget : public IRenderTarget
	{
		INTERFACE_BODY(IDirect3D12RenderTarget)

		/// @brief Gets the render target resolution.
		/// @return Render target resolution.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<UINT>& ResolutionD3D12() const noexcept = 0;

		/// @brief Gets the clear color.
		/// @return Clear color.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Color::RGBA<FLOAT>& ClearColorD3D12() const noexcept = 0;
		/// @brief Sets the clear color.
		/// @param color Clear color.
		virtual void ClearColorD3D12(const PonyMath::Color::RGBA<FLOAT>& color) noexcept = 0;
	};
}
