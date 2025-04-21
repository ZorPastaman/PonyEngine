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

export module PonyEngine.Render.DXGI.Detail:ISwapChain;

import <cstdint>;

export namespace PonyEngine::Render::DXGI
{
	/// @brief DXGI swap chain.
	class ISwapChain
	{
		INTERFACE_BODY(ISwapChain)

		/// @brief Gets a current back buffer index.
		/// @return Current back buffer index.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t GetCurrentBackBufferIndex() const noexcept = 0;
		/// @brief Gets a back buffer.
		/// @param bufferIndex Back buffer index.
		/// @param buffer Buffer pointer.
		/// @return Result of the call.
		virtual HRESULT GetBackBuffer(std::uint32_t bufferIndex, ID3D12Resource2** buffer) const noexcept = 0;
	};
}
