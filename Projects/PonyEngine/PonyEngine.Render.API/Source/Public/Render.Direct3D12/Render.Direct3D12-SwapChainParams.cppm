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

export module PonyEngine.Render.Direct3D12:SwapChainParams;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render target parameters.
	struct SwapChainParams final
	{
		UINT bufferCount = 3u; ///< Buffer count.
	};
}
