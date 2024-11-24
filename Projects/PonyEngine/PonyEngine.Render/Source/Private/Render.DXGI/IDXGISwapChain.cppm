/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/DXGI/Framework.h"
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.DXGI.Detail:IDXGISwapChain;

export namespace PonyEngine::Render
{
	class IDXGISwapChain
	{
		INTERFACE_BODY(IDXGISwapChain)

		[[nodiscard("Pure function")]]
		virtual UINT GetCurrentBackBufferIndex() const noexcept = 0;
		virtual HRESULT GetBackBuffer(UINT bufferIndex, ID3D12Resource2** buffer) const noexcept = 0;
	};
}
