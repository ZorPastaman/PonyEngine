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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderTargetPrivate;

import PonyMath.Color;
import PonyMath.Utility;

import PonyEngine.Render.Direct3D12;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render target.
	class IDirect3D12RenderTargetPrivate : public IDirect3D12RenderTarget
	{
		INTERFACE_BODY(IDirect3D12RenderTargetPrivate)

		/// @brief Gets the rtv format.
		/// @return Rtv format.
		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT Format() const noexcept = 0;
		/// @brief Gets the rtv sample description.
		/// @return Sample description.
		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept = 0;

		/// @brief Gets the render target buffer.
		/// @return Render target buffer.
		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& RenderTargetBuffer() noexcept = 0;
		/// @brief Gets the render target buffer.
		/// @return Render target buffer.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& RenderTargetBuffer() const noexcept = 0;
		/// @brief Gets the rtv handle.
		/// @return Rtv handle.
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE RtvHandle() const noexcept = 0;

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
