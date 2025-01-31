/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12:SwapChainParams;

import <cstdint>;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render target parameters.
	struct SwapChainParams final
	{
		std::uint32_t bufferCount = 3u; ///< Buffer count.
	};
}
