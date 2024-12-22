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

export module PonyEngine.Render.Direct3D12:Direct3D12SwapChainParams;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render target parameters.
	struct Direct3D12SwapChainParams final
	{
		DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM; ///< Back buffer format.
		UINT bufferCount = 2u; ///< Buffer count.
	};
}
