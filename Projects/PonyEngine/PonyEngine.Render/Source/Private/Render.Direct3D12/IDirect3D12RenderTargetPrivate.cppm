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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12RenderTargetPrivate;

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
		virtual DXGI_FORMAT RtvFormat() const noexcept = 0;
		/// @brief Gets the rtv sample description.
		/// @return Sample description.
		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept = 0;

		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& CurrentBackBuffer() noexcept = 0;
		/// @brief Gets a current back buffer.
		/// @return Current back buffer.
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& CurrentBackBuffer() const noexcept = 0;

		/// @brief Gets the current rtv handle.
		/// @return Rtv handle.
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE CurrentRtvHandle() const noexcept = 0;
	};
}
