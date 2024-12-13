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
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.DXGI.Detail:IDXGISwapChain;

export namespace PonyEngine::Render
{
	/// @brief DXGI swap chain.
	class IDXGISwapChain
	{
		INTERFACE_BODY(IDXGISwapChain)

		/// @brief Gets a sample description of the swap chain.
		/// @return Sample description.
		[[nodiscard("Pure function")]]
		virtual DXGI_SAMPLE_DESC SampleDesc() const noexcept = 0;

		/// @brief Gets a current back buffer index.
		/// @return Current back buffer index.
		[[nodiscard("Pure function")]]
		virtual UINT GetCurrentBackBufferIndex() const noexcept = 0;
		/// @brief Gets a back buffer.
		/// @param bufferIndex Back buffer index.
		/// @param buffer Buffer pointer.
		/// @return Result of the call.
		virtual HRESULT GetBackBuffer(UINT bufferIndex, ID3D12Resource2** buffer) const noexcept = 0;
	};
}
