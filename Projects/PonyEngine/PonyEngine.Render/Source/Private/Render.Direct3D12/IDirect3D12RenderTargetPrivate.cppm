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
	class IDirect3D12RenderTargetPrivate : public IDirect3D12RenderTarget
	{
		INTERFACE_BODY(IDirect3D12RenderTargetPrivate)

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& GetBackBuffer(UINT index) noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& GetBackBuffer(UINT index) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetRtvHandle(UINT index) const noexcept = 0;
	};
}
